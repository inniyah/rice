/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * RICE 4.0x              Copyright (C) 1993             Rene' Jager *
 *                                                                   *
 *                                                                   *
 * This toolbox is free software; you can redistribute it and/or     *
 * modify it under the terms of the GNU General Public License as    *
 * published by the Free Software Foundation; either version 2 of    *
 * the License, or (at your option) any later version.               *
 *                                                                   *
 * This toolbox is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      *
 * GNU General Public License for more details.                      *
 *                                                                   *
 * You should have received a copy of the GNU General Public License *
 * along with this toolbox; if not, write to the:                    *
 *                                                                   *
 *    Free Software Foundation, Inc.                                 *
 *    675 Mass Ave, Cambridge                                        *
 *    MA 02139, USA.                                                 *
 *                                                                   *
 * See the RICE documentation for more information on the toolbox.   *
 * The file COPYING for the complete GNU General Public License.     *
 *                                                                   *
 * You can reach me by (preferably e-mail):                          *
 *                                                                   *
 *    Rene' Jager                                                    *
 *                                                                   *
 *    Delft University of Technology                                 *
 *    Department of Electrical Engineering                           *
 *    Control Laboratory                                             *
 *                                                                   *
 *    Room ET 12.06                                                  *
 *                                                                   *
 *    Mekelweg 4                                                     *
 *    P.O.Box 5031                                                   *
 *    2600 GA  Delft                                                 *
 *    The Netherlands                                                *
 *                                                                   *
 *    e-mail: R.Jager@ET.TUDelft.NL                                  *
 *    phone:  +31-15-78 51 14                                        *
 *    fax:    +31-15-62 67 38                                        *
 *    telex:  38151 butud nl                                         *
 *                                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
   File:   infer.c
   Author: Rene' Jager
   Update: January 4, 1993
   Info:   source file for RICE
*/


/* hidden include files */

#include "include.h"
#include "define.h"
#include "type.h"
#include "function.h"
#include "variable.h"


/* macro for swapping */

#define SwapIndices(ind1,ind2) \
{ \
   int __ind; \
   Protect(1); \
   __ind = ind1; \
   ind1 = ind2; \
   ind2 = __ind; \
   Protect(0); \
}


/* prototypes of static functions */

PROTOTYPE(static int KnownCondition, (OBJ_CONDITION *));
PROTOTYPE(static int KnownRule, (OBJ_RULE *));
PROTOTYPE(static int KnownDimension, (OBJ_DIMENSION *));
PROTOTYPE(static int RelationTarget, (OBJ_RELATION *));

PROTOTYPE(static void EvaluateCondition, (OBJ_CONDITION *, float *, int));
PROTOTYPE(static void EvaluateDimension, (OBJ_DIMENSION *, float *, int));
PROTOTYPE(static void ExecuteAction, (OBJ_ACTION *, float *));
PROTOTYPE(static void ExecuteDimension, (OBJ_DIMENSION *, float *));
PROTOTYPE(static void InferBase, (OBJ_BASE *));
PROTOTYPE(static void InferLayer, (OBJ_LAYER *));
PROTOTYPE(static void InferFact, (OBJ_FACT *));
PROTOTYPE(static void ApplyRule, (OBJ_RULE *));
PROTOTYPE(static void ApplyRelation, (OBJ_RELATION *, int));
PROTOTYPE(static void AskFact, (OBJ_FACT *, int, char *[]));
PROTOTYPE(static void InformFact, (OBJ_FACT *, int, char *[]));
PROTOTYPE(static void RunFact, (OBJ_FACT *, int, char *[]));


/* main infer-funtion */

FUNCTION(int InferKB,
   (int index),
   (index),
   int index;
)
{
   if(SwitchES(index))
      return -1;

   if(!objectList)
      return -1;

   InferBase(IDX2BAS(0));

   return 0;
}


/* static infer-functions */

FUNCTION(static void InferBase,
   (OBJ_BASE *base),
   (base),
   OBJ_BASE *base;
)
{
   register int i, j;
   OBJ_LAYER *layer;

   for(i = 1; i <= base->layer[0]; i++)
   {
      layer = IDX2LAY(base->layer[i]);

      for(j = 1; j <= layer->rule[0]; j++)
         IDX2RUL(layer->rule[j])->slot.FIREABLE = 0;

      for(j = 1; j <= layer->relation[0]; j++)
         IDX2REL(layer->relation[j])->slot.FIREABLE = 0;
   }

   for(i = 1; i <= base->layer[0]; i++)
      if(IDX2OBJ(base->layer[i])->status.ACTIVE)
         InferLayer(IDX2LAY(base->layer[i]));
}


FUNCTION(static void InferLayer,
   (OBJ_LAYER *layer),
   (layer),
   OBJ_LAYER *layer;
)
{
   register int i;
   OBJ_FACT *fact;
   OBJ_RULE *rule;
   OBJ_RELATION *relation;
   int target, fired;
   float grade = GRD_TRUE;

   /* do all initial actions */
   for(i = 1; i <= layer->init[0]; i++)
      ExecuteAction(IDX2ACT(layer->init[i]), &grade);

   /* in case of forward reasoning, get all data from previous layers */
   if(layer->slot.FORWARD)
   {
      for(i = 1; i <= layer->data[0]; i++)
      {
         fact = IDX2FAC(layer->data[i]);

         InferFact(fact);

         /* fact must be known before inferring layer */
         if(fact->grade == GRD_UNKNOWN)
            if(fact->slot.CODE)
               RunFact(fact, 1, &fact->symbolic);
            else
               AskFact(fact, 1, &fact->symbolic);
      }
   }

   /* release all rules and relations in this layer */
   for(i = 1; i <= layer->rule[0]; i++)
      IDX2RUL(layer->rule[i])->slot.FIREABLE = 1;

   for(i = 1; i <= layer->relation[0]; i++)
      IDX2REL(layer->relation[i])->slot.FIREABLE = 1;

   /* breadth-first forward reasoning */
   if(layer->slot.FORWARD)
   {
      do
      {
         fired = 0;

         for(i = 1; i <= layer->rule[0]; i++)
         {
            rule = IDX2RUL(layer->rule[i]);

            if(rule->status.ACTIVE && rule->slot.FIREABLE && !rule->slot.FIRED)
               if(KnownRule(rule))
               {
                  ApplyRule(rule);
                  fired = 1;
               }
         }

         for(i = 1; i <= layer->relation[0]; i++)
         {
            relation = IDX2REL(layer->relation[i]);

            if(relation->status.ACTIVE && relation->slot.FIREABLE && !relation->slot.FIRED)
               if(target = RelationTarget(relation))
               {
                  ApplyRelation(relation, target);
                  fired = 1;
               }
         }
      }
      while(fired);
   }

   /* depth-first backward reasoning */
   if(layer->slot.BACKWARD)
   {
      for(i = 1; i <= layer->goal[0]; i++)
      {
         fact = IDX2FAC(layer->goal[i]);

         InferFact(fact);

         if(fact->grade == GRD_UNKNOWN)
            if(fact->slot.CODE)
               RunFact(fact, 1, &fact->symbolic);
            elif(interactiveMode)
               AskFact(fact, 1, &fact->symbolic);
      }
   }
}


FUNCTION(static void InferFact,
   (OBJ_FACT *fact),
   (fact),
   OBJ_FACT *fact;
)
{
   register int i;

   /* if fact is already being inferred */
   if(fact->slot.INFERRING)
      return;

   fact->slot.INFERRING = 1;

   if(fact->grade == GRD_UNKNOWN)
   {
      for(i = 1; i <= fact->backward[0]; i++)
      {
         switch(IDX2OBJ(fact->backward[i])->type)
         {
            case TYP_RULE:
               if(IDX2RUL(fact->backward[i])->slot.FIREABLE)
                  if(IDX2RUL(fact->backward[i])->status.ACTIVE)
                     ApplyRule(IDX2RUL(fact->backward[i]));
               break;

            case TYP_RELATION:
               if(IDX2REL(fact->backward[i])->slot.FIREABLE)
                  if(IDX2REL(fact->backward[i])->status.ACTIVE)
                     ApplyRelation(IDX2REL(fact->backward[i]), fact->number);
               break;

            default:
               Report(MSG_ERROR, MSG_BUG_INTERNAL);
               Abandon();
               break;
         }
      }
   }

   fact->slot.INFERRING = 0;
}


/* help-functions */

FUNCTION(static void ApplyRule,
   (OBJ_RULE *rule),
   (rule),
   OBJ_RULE *rule;
)
{
   register int i;
   OBJ_CONDITION *condition;
   float grade, degree;

   if((rule->slot.FIRED || rule->slot.FIRING) && !recursiveMode)
      return;

   rule->slot.FIRING = 1;

   if(rule->slot.INTERSECTION)
   {
      grade = GRD_TRUE;

      for(i = 1; i <= rule->condition[0]; i++)
      {
         condition = IDX2CON(rule->condition[i]);

         if(condition->status.ACTIVE)
            EvaluateCondition(condition, &degree, MOD_DEPTH);
         else
            degree = GRD_TRUE;

         grade = (*condition->norm)(grade, degree);

         if(grade == GRD_FALSE)
         {
            if(selectiveMode && i > 1 && !condition->slot.IF)
               if(!IDX2CON(rule->condition[i-1])->slot.IF)
                  SwapIndices(rule->condition[i], rule->condition[i-1]);

            break;
         }
      }
   }
   elif(rule->slot.UNION)
   {
      grade = GRD_FALSE;

      for(i = 1; i <= rule->condition[0]; i++)
      {
         condition = IDX2CON(rule->condition[i]);

         if(condition->status.ACTIVE)
            EvaluateCondition(condition, &degree, MOD_DEPTH);
         else
            degree = GRD_FALSE;

         grade = (*condition->norm)(grade, degree);

         if(grade == GRD_TRUE)
         {
            if(selectiveMode && i > 1 && !condition->slot.IF)
               if(!IDX2CON(rule->condition[i-1])->slot.IF)
                  SwapIndices(rule->condition[i], rule->condition[i-1]);

            break;
         }
      }
   }

   /* grade should have usable value */
   if(grade != GRD_UNKNOWN)
   {
      for(i = 1; i <= rule->action[0]; i++)
      {
         /* action should be active */
         if(IDX2ACT(rule->action[i])->status.ACTIVE && grade != GRD_UNKNOWN)
            ExecuteAction(IDX2ACT(rule->action[i]), &grade);
      }
   }

   rule->slot.FIRED = 1;
   rule->slot.FIRING = 0;
}


FUNCTION(static int KnownCondition,
   (OBJ_CONDITION *condition),
   (condition),
   OBJ_CONDITION *condition;
)
{
   /* condition object should be a fact */
   if(condition->slot.FAC)
   {
      /* nothing to be inferred */
      if(condition->slot.ON || condition->slot.OFF)
         return 1;

      /* in case of arguments always unknown */
      if(condition->argc > 1)
         return 0;

      /* run or ask perform in repetitive mode */
      if((condition->slot.RUN || condition->slot.USR) && repetitiveMode)
         return 0;

      /* just an unknown fact */
      if(IDX2FAC(condition->object)->grade == GRD_UNKNOWN)
         return 0;
   }

   return 1;
}


FUNCTION(static int KnownRule,
   (OBJ_RULE *rule),
   (rule),
   OBJ_RULE *rule;
)
{
   register int i;
   int known;

   if(rule->slot.INTERSECTION)
   {
      /* false condition is sufficient */
      for(i = 1, known = 1; i <= rule->condition[0]; i++)
         if(!KnownCondition(IDX2CON(rule->condition[i])))
            known = 0;
         else
            if(IDX2FAC(IDX2CON(rule->condition[i])->object)->grade == GRD_FALSE)
               return 1;

      if(known)
         return 1;
   }
   elif(rule->slot.UNION)
   {
      /* true condition is sufficient */
      for(i = 1, known = 1; i <= rule->condition[0]; i++)
         if(!KnownCondition(IDX2CON(rule->condition[i])))
            known = 0;
         else
            if(IDX2FAC(IDX2CON(rule->condition[i])->object)->grade == GRD_TRUE)
               return 1;

      if(known)
         return 1;
   }

   return 0;
}


FUNCTION(static void EvaluateCondition,
   (OBJ_CONDITION *condition, float *grade, int mode),
   (condition, grade, mode),
   OBJ_CONDITION *condition;
   float *grade;
   int mode;
)
{
   float degree = GRD_UNKNOWN;

   if(condition->slot.ON)
      degree = IDX2OBJ(condition->object)->status.ACTIVE ? GRD_TRUE : GRD_FALSE;
   elif(condition->slot.OFF)
      degree = IDX2OBJ(condition->object)->status.ACTIVE ? GRD_FALSE : GRD_TRUE;
   elif(condition->slot.FAC)
   {
      OBJ_FACT *fact;

      fact = IDX2FAC(condition->object);

      if(mode == MOD_DEPTH)
      {
         if(condition->slot.RUN)
         {
            if(repetitiveMode || fact->grade == GRD_UNKNOWN || condition->argc > 1)
            {
               RunFact(fact, condition->argc, condition->argv);
               degree = fact->grade;

               /* arguments make it temporal */
               if(condition->argc > 1)
                  fact->grade = GRD_UNKNOWN;
            }
         }
         elif(condition->slot.USR)
         {
            if(repetitiveMode || fact->grade == GRD_UNKNOWN || condition->argc > 1)
            {
               AskFact(fact, condition->argc, condition->argv);
               degree = fact->grade;

               /* arguments make it temporal */
               if(condition->argc > 1)
                  fact->grade = GRD_UNKNOWN;
            }
         }
         else
         {
            /* explaination */
            if(condition->slot.SHW)
               WhyFact(fact, -1);

            if(fact->grade == GRD_UNKNOWN)
               InferFact(fact);

            if(fact->grade == GRD_UNKNOWN)
            {
               if(fact->slot.CODE)
                  RunFact(fact, condition->argc, condition->argv);
               elif(interactiveMode)
                  AskFact(fact, condition->argc, condition->argv);

               degree = fact->grade;

               /* arguments make it temporal */
               if(condition->argc > 1)
                  fact->grade = GRD_UNKNOWN;
            }
            else
               degree = fact->grade;
         }
      }
      else
         degree = fact->grade;
   }
   elif(condition->slot.LAY)
   {
      OBJ_LAYER *layer;

      layer = IDX2LAY(condition->object);

      if(condition->slot.BKW)
         degree = layer->slot.BACKWARD ? GRD_TRUE : GRD_FALSE;
      elif(condition->slot.FRW)
         degree = layer->slot.FORWARD ? GRD_TRUE : GRD_FALSE;
   }
   elif(condition->slot.CON)
   {
      OBJ_CONDITION *condition2;

      condition2 = IDX2CON(condition->object);

      if(condition->slot.CUT)
         degree = condition2->level;
   }
   elif(condition->slot.ACT)
   {
      OBJ_ACTION *action;

      action = IDX2ACT(condition->object);

      if(condition->slot.GRD)
         degree = action->grade;
      elif(condition->slot.CUT)
         degree = action->level;
   }
   elif(condition->slot.DIM)
   {
      OBJ_DIMENSION *dimension;

      dimension = IDX2DIM(condition->object);

      if(condition->slot.GRD)
         degree = dimension->grade;
      elif(condition->slot.CUT)
         degree = dimension->level;
   }

   if(condition->slot.NOT)
      degree = FNOT(degree);

   condition->truth = *grade = FCUT(degree, condition->level);
}


FUNCTION(static void ExecuteAction,
   (OBJ_ACTION *action, float *grade),
   (action, grade),
   OBJ_ACTION *action;
   float *grade;
)
{
   float degree = *grade;

   if(action->slot.THEN && degree < action->level)
      return;

   if(action->slot.ELSE && degree > action->level)
      return;

   if(action->slot.ELSE)
      degree = FNOT(degree);

   if(action->slot.NOT)
      degree = FNOT(degree);

   action->truth = degree = (*action->norm)(action->grade, degree);

   if(action->slot.ON || action->slot.OFF)
   {
      /* activate in case of ON flag */
      IDX2OBJ(action->object)->status.ACTIVE =
         (!action->slot.NOT && action->slot.ON) ||
         (action->slot.NOT && action->slot.OFF);

      /* also (in)activate rules and relations of layers */
      if(action->slot.LAY)
      {
         register int i;
         OBJ_LAYER *layer = IDX2LAY(action->object);

         for(i = 1; i <= layer->rule[0]; i++)
            IDX2RUL(layer->rule[i])->status.ACTIVE = layer->status.ACTIVE;

         for(i = 1; i <= layer->relation[0]; i++)
            IDX2RUL(layer->relation[i])->status.ACTIVE = layer->status.ACTIVE;
      }
   }
   elif(action->slot.FAC)
   {
      OBJ_FACT *fact;

      fact = IDX2FAC(action->object);

      /* run or inform if trivial, assign degree as temporal */
      if(action->slot.RUN || (action->argc > 1 && IDX2FAC(action->object)->slot.CODE))
      {
         fact->grade = degree;
         RunFact(fact, action->argc, action->argv);

         /* grade is temporal in case of arguments */
         if(action->argc > 1)
            fact->grade = GRD_UNKNOWN;
      }
      elif(action->slot.USR || (action->argc > 1 && !IDX2FAC(action->object)->slot.CODE))
      {
         fact->grade = degree;
         InformFact(fact, action->argc, action->argv);

         /* grade is temporal in case of arguments */
         if(action->argc > 1)
            fact->grade = GRD_UNKNOWN;
      }
      elif(action->slot.SHW)
      {
         fact->grade = degree;
         HowFact(fact, -1);

         /* grade is temporal in case of arguments */
         if(action->argc > 1)
            fact->grade = GRD_UNKNOWN;
      }
      else
      {
         /* when not an init take average when multiple concluded */
         if(action->slot.INIT)
            fact->grade = degree;
         else
            fact->grade = (fact->sumgrade += degree)/(fact->numgrade += 1);
      }
   }
   elif(action->slot.LAY)
   {
      OBJ_LAYER *layer;

      layer = IDX2LAY(action->object);

      if(action->slot.BKW)
         layer->slot.BACKWARD = (action->slot.NOT ? 0 : 1);
      elif(action->slot.FRW)
         layer->slot.FORWARD = (action->slot.NOT ? 0 : 1);
      elif(action->slot.INV)
         InferLayer(OBJ2LAY(objectList[action->object]));
   }
   elif(action->slot.CON)
   {
      OBJ_CONDITION *condition;

      condition = IDX2CON(action->object);

      if(action->slot.CUT)
         condition->level = degree;
   }
   elif(action->slot.ACT)
   {
      OBJ_ACTION *action2;

      action2 = IDX2ACT(action->object);

      if(action->slot.GRD)
         action2->grade = degree;
      elif(action->slot.CUT)
         action2->level = degree;
   }
   elif(action->slot.DIM)
   {
      OBJ_DIMENSION *dimension;

      dimension = IDX2DIM(action->object);

      if(action->slot.GRD)
         dimension->grade = degree;
      elif(action->slot.CUT)
         dimension->level = degree;
   }
}


FUNCTION(static int KnownDimension,
   (OBJ_DIMENSION *dimension),
   (dimension),
   OBJ_DIMENSION *dimension;
)
{
   /* unknown object can only be a fact */
   if(dimension->slot.FAC)
   {
      /* always unknown in case of arguments */
      if(dimension->argc > 1)
         return 0;

      /* perforn run or ask in repetitive mode */
      if((dimension->slot.RUN || dimension->slot.USR) && repetitiveMode)
         return 0;

      /* just an unknown fact */
      if(IDX2FAC(dimension->object)->grade == GRD_UNKNOWN)
         return 0;
   }

   return 1;
}


FUNCTION(static int RelationTarget,
   (OBJ_RELATION *relation),
   (relation),
   OBJ_RELATION *relation;
)
{
   register int i;
   int target = 0;

   for(i = 1; i <= relation->dimension[0]; i++)
      if(!KnownDimension(IDX2DIM(relation->dimension[i])))
         if(target)
            return 0;
         else
            target = IDX2DIM(relation->dimension[i])->object;

   return target;
}


FUNCTION(static void ApplyRelation,
   (OBJ_RELATION *relation, int target),
   (relation, target),
   OBJ_RELATION *relation;
   int target;
)
{
   register int i;
   OBJ_DIMENSION *dimension, *output = 0;
   float grade, degree;

   if(!relation->status.ACTIVE)
      return;

   if((relation->slot.FIRED || relation->slot.FIRING) && !recursiveMode)
      return;

   relation->slot.FIRING = 1;

   if(relation->dimension[0] > 1)
      grade = GRD_TRUE;
   else
      grade = GRD_UNKNOWN;

   for(i = 1; i <= relation->dimension[0]; i++)
   {
      dimension = IDX2DIM(relation->dimension[i]);

      if(dimension->object != target)
      {
         if(dimension->status.ACTIVE)
            EvaluateDimension(dimension, &degree, MOD_DEPTH);
         else
            degree = GRD_TRUE;

         grade = (*dimension->norm)(grade, degree);

         if(grade == GRD_FALSE)
         {
            if(selectiveMode && i > 1)
               SwapIndices(relation->dimension[i], relation->dimension[i-1]);

            break;
         }
      }
      else
         output = dimension;

      if(grade == GRD_FALSE)
         break;
   }

   if(!output)   /* quickly find target dimension */
   {
      for(; i <= relation->dimension[0]; i++)
      {
         dimension = IDX2DIM(relation->dimension[i]);

         if(dimension->object == target)
         {
            output = dimension;
            break;
         }
      }
   }

   if(output->status.ACTIVE)
      ExecuteDimension(output, &grade);

   relation->slot.FIRED = 1;
   relation->slot.FIRING = 0;
}


FUNCTION(static void EvaluateDimension,
   (OBJ_DIMENSION *dimension, float *grade, int mode),
   (dimension, grade, mode),
   OBJ_DIMENSION *dimension;
   float *grade;
   int mode;
)
{
   float degree = GRD_UNKNOWN;

   if(dimension->slot.ON)
      degree = IDX2OBJ(dimension->object)->status.ACTIVE ? GRD_TRUE : GRD_FALSE;
   elif(dimension->slot.OFF)
      degree = IDX2OBJ(dimension->object)->status.ACTIVE ? GRD_FALSE : GRD_TRUE;
   elif(dimension->slot.FAC)
   {
      OBJ_FACT *fact;

      fact = IDX2FAC(dimension->object);

      if(mode == MOD_DEPTH)
      {
         if(dimension->slot.RUN)
         {
            if(repetitiveMode || fact->grade == GRD_UNKNOWN || dimension->argc > 1)
            {
               RunFact(fact, dimension->argc, dimension->argv);
               degree = fact->grade;
               if(dimension->argc > 1)   /* reset because of arguments */
                  fact->grade = GRD_UNKNOWN;
            }
         }
         elif(dimension->slot.USR)
         {
            if(repetitiveMode || fact->grade == GRD_UNKNOWN || dimension->argc > 1)
            {
               AskFact(fact, dimension->argc, dimension->argv);
               degree = fact->grade;
               if(dimension->argc > 1)   /* reset because of arguments */
                  fact->grade = GRD_UNKNOWN;
            }
         }
         else
         {
            /* explaination */
            if(dimension->slot.SHW)
               WhyFact(fact, -1);

            if(fact->grade == GRD_UNKNOWN)
               InferFact(fact);

            if(fact->grade == GRD_UNKNOWN)
            {
               if(fact->slot.CODE)
                  RunFact(fact, dimension->argc, dimension->argv);
               elif(interactiveMode)
                  AskFact(fact, dimension->argc, dimension->argv);

               degree = fact->grade;

               if(dimension->argc > 1)
                  fact->grade = GRD_UNKNOWN;  /* reset due to arguments */
            }
            else
               degree = fact->grade;
         }
      }
      else
         degree = fact->grade;
   }
   elif(dimension->slot.LAY)
   {
      OBJ_LAYER *layer;

      layer = IDX2LAY(dimension->object);

      if(dimension->slot.BKW)
         degree = layer->slot.BACKWARD ? GRD_TRUE : GRD_FALSE;
      elif(dimension->slot.FRW)
         degree = layer->slot.FORWARD ? GRD_TRUE : GRD_FALSE;
   }
   elif(dimension->slot.CON)
   {
      OBJ_CONDITION *condition;

      condition = IDX2CON(dimension->object);

      if(dimension->slot.CUT)
         degree = condition->level;
   }
   elif(dimension->slot.ACT)
   {
      OBJ_ACTION *action;

      action = IDX2ACT(dimension->object);

      if(dimension->slot.GRD)
         degree = action->grade;
      elif(dimension->slot.CUT)
         degree = action->level;
   }
   elif(dimension->slot.DIM)
   {
      OBJ_DIMENSION *dimension2;

      dimension2 = IDX2DIM(dimension->object);

      if(dimension->slot.GRD)
         degree = dimension2->grade;
      elif(dimension->slot.CUT)
         degree = dimension2->level;
   }

   if(dimension->slot.NOT)
      degree = FNOT(degree);

   dimension->truth[0] = *grade = FCUT(degree, dimension->level);
}


FUNCTION(static void ExecuteDimension,
   (OBJ_DIMENSION *dimension, float *grade),
   (dimension, grade),
   OBJ_DIMENSION *dimension;
   float *grade;
)
{
   float degree = *grade;

   if(degree < dimension->level)
      return;

   if(dimension->slot.NOT)
      degree = FNOT(degree);

   dimension->truth[1] = degree = (*dimension->norm)(dimension->grade, degree);

   if(dimension->slot.ON || dimension->slot.OFF)
   {
      /* activate in case of ON flag */
      IDX2OBJ(dimension->object)->status.ACTIVE =
         (!dimension->slot.NOT && dimension->slot.ON) ||
         (dimension->slot.NOT && dimension->slot.OFF);

      /* also (in)activate rules and relations of layers */
      if(dimension->slot.LAY)
      {
         register int i;
         OBJ_LAYER *layer = IDX2LAY(dimension->object);

         for(i = 1; i <= layer->rule[0]; i++)
            IDX2RUL(layer->rule[i])->status.ACTIVE = layer->status.ACTIVE;

         for(i = 1; i <= layer->relation[0]; i++)
            IDX2RUL(layer->relation[i])->status.ACTIVE = layer->status.ACTIVE;
      }
   }
   elif(dimension->slot.FAC)
   {
      OBJ_FACT *fact;

      fact = IDX2FAC(dimension->object);

      /* run or inform when trivial */
      if(dimension->slot.RUN || (dimension->argc > 1 && fact->slot.CODE))
      {
         fact->grade = degree;
         RunFact(fact, dimension->argc, dimension->argv);

         /* grade is temporal in case of arguments */
         if(dimension->argc > 1)
            fact->grade = GRD_UNKNOWN;
      }
      elif(dimension->slot.USR || (dimension->argc > 1 && !fact->slot.CODE))
      {
         fact->grade = degree;
         InformFact(fact, dimension->argc, dimension->argv);

            /* grade is temporal in case of arguments */
         if(dimension->argc > 1)
            fact->grade = GRD_UNKNOWN;
      }
      elif(dimension->slot.SHW)
      {
         fact->grade = degree;
         HowFact(fact, -1);

         /* grade is temporal in case of arguments */
         if(dimension->argc > 1)
            fact->grade = GRD_UNKNOWN;
      }
      else
      {
         /* take average when multiple concluded */
         fact->grade = (fact->sumgrade += degree)/(fact->numgrade += 1);
      }
   }
   elif(dimension->slot.LAY)
   {
      OBJ_LAYER *layer;

      layer = IDX2LAY(dimension->object);

      if(dimension->slot.BKW)
         layer->slot.BACKWARD = (dimension->slot.NOT ? 0 : 1);
      elif(dimension->slot.FRW)
         layer->slot.FORWARD = (dimension->slot.NOT ? 0 : 1);
   }
   elif(dimension->slot.CON)
   {
      OBJ_CONDITION *condition;

      condition = IDX2CON(dimension->object);

      if(dimension->slot.CUT)
         condition->level = degree;
   }
   elif(dimension->slot.ACT)
   {
      OBJ_ACTION *action;

      action = IDX2ACT(dimension->object);

      if(dimension->slot.GRD)
         action->grade = degree;
      elif(dimension->slot.CUT)
         action->level = degree;
   }
   elif(dimension->slot.DIM)
   {
      OBJ_DIMENSION *dimension2;

      dimension2 = IDX2DIM(dimension->object);

      if(dimension->slot.GRD)
         dimension2->grade = degree;
      elif(dimension->slot.CUT)
         dimension2->level = degree;
   }
}


FUNCTION(static void AskFact,
   (OBJ_FACT *fact, int argc, char *argv[]),
   (fact, argc, argv),
   OBJ_FACT *fact;
   int argc;
   char *argv[];
)
{
   argv[0] = fact->symbolic;

   Ask(argc, argv, &fact->grade);
}


FUNCTION(static void InformFact,
   (OBJ_FACT *fact, int argc, char *argv[]),
   (fact, argc, argv),
   OBJ_FACT *fact;
   int argc;
   char *argv[];
)
{
   float grade;

   grade = fact->grade;
   argv[0] = fact->symbolic;

   Inform(argc, argv, &grade);
}


FUNCTION(static void RunFact,
   (OBJ_FACT *fact, int argc, char *argv[]),
   (fact, argc, argv),
   OBJ_FACT *fact;
   int argc;
   char *argv[];
)
{
   argv[0] = fact->symbolic;

   Run(fact->link, argc, argv, &fact->grade);

   if(fact->grade < GRD_FALSE || GRD_TRUE < fact->grade)
      fact->grade = GRD_UNKNOWN;
}




