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
   File:   explain.c
   Author: Rene' Jager
   Update: January 4, 1993
   info:   source file for RICE
*/


/* hidden include files */

#include "include.h"
#include "define.h"
#include "type.h"
#include "function.h"
#include "variable.h"
#include "rebuild.h"


/* prototypes of static functions */

PROTOTYPE(static OBJ_FACT *FindFact, (char *));
PROTOTYPE(static void ResetExplained, (void));

PROTOTYPE(static void HowRule, (OBJ_RULE *, int));
PROTOTYPE(static void HowRelation, (OBJ_RELATION *, int, int));

PROTOTYPE(static void WhyRule, (OBJ_RULE *, int));
PROTOTYPE(static void WhyRelation, (OBJ_RELATION *, int, int));


/* reset 'explained' flags */

FUNCTION(static void ResetExplained,
   (void),
   (),
   /* nothing */
)
{
   int i;

   for(i = 1; i <= objectList[0]->number; i++)
      if(objectList[i]->type == TYP_RULE)
         OBJ2RUL(objectList[i])->slot.EXPLAINED = 0;
      if(objectList[i]->type == TYP_RELATION)
         OBJ2REL(objectList[i])->slot.EXPLAINED = 0;
}


/* find fact in object-list */

FUNCTION(static OBJ_FACT *FindFact,
   (char *symbolic),
   (symbolic),
   char *symbolic;
)
{
   int i;

   for(i = 1; i <= objectList[0]->number; i++)
      if(objectList[i]->type == TYP_FACT)
         if(!strcmp(objectList[i]->symbolic, symbolic))
            return OBJ2FAC(objectList[i]);

   /* fact not found */
   Report(MSG_ERROR, MSG_UNKNOWN_FACT, symbolic);
   return 0;
}


/* main explain-how function */

FUNCTION(int ExplainHow,
   (int index, char *symbolic, int depth),
   (index, symbolic, depth),
   int index;
   char *symbolic;
   int depth;
)
{
   OBJ_FACT *fact;

   if(SwitchES(index))
      return -1;

   /* get fact from object-list */
   if(!(fact = FindFact(symbolic)))
      return -1;

   /* reset explained flags */
   ResetExplained();

   /* show recursivily rules and relations */
   HowFact(fact, depth);

   return 0;
}


/* main explain-why function */

FUNCTION(int ExplainWhy,
   (int index, char *symbolic, int depth),
   (index, symbolic, depth),
   int index;
   char *symbolic;
   int depth;
)
{
   OBJ_FACT *fact;

   if(SwitchES(index))
      return -1;

   /* get fact from object-list */
   if(!(fact = FindFact(symbolic)))
      return -1;

   /* reset explained flags */
   ResetExplained();

   /* show recursivily rules and relations */
   WhyFact(fact, depth);

   return 0;
}


/* static explain-how functions */

FUNCTION(void HowFact,
   (OBJ_FACT *fact, int depth),
   (fact, depth),
   OBJ_FACT *fact;
   int depth;
)
{
   int i;

   /* find rules and relation in tree */
   for(i = 1; i <= fact->backward[0]; i++)
   {
      switch(objectList[fact->backward[i]]->type)
      {
         case TYP_RULE:
         {
            OBJ_RULE *rule = IDX2RUL(fact->backward[i]);
            if((rule->slot.FIRED || rule->slot.FIRING) && !rule->slot.EXPLAINED)
               HowRule(rule, depth - 1);
            break;
         }

         case TYP_RELATION:
         {
            OBJ_RELATION *relation = IDX2REL(fact->backward[i]);
            if((relation->slot.FIRED || relation->slot.FIRING) && !relation->slot.EXPLAINED)
               HowRelation(relation, fact->number, depth - 1);
            break;
         }

         default:
            Report(MSG_ERROR, MSG_BUG_INTERNAL);
            Abandon();
      }
   }
}


FUNCTION(static void HowRule,
   (OBJ_RULE *rule, int depth),
   (rule, depth),
   OBJ_RULE *rule;
   int depth;
)
{
   int i;

   /* show rule */
   RebuildRule(0, rule);
   rule->slot.EXPLAINED = 1;

   if(depth)
   {
      /* find next fact in tree */
      for(i = 1; i <= rule->condition[i]; i++)
      {
         if(IDX2OBJ(IDX2CON(rule->condition[i])->object)->type == TYP_FACT)
            HowFact(IDX2FAC(IDX2CON(rule->condition[i])->object), depth);
      }
   }
}


FUNCTION(static void HowRelation,
   (OBJ_RELATION *relation, int fact, int depth),
   (relation, fact, depth),
   OBJ_RELATION *relation;
   int fact;
   int depth;
)
{
   int i;

   /* show relation */
   RebuildRelation(0, relation);
   relation->slot.EXPLAINED = 1;

   if(depth)
   {
      /* find next fact in tree */
      for(i = 1; i <= relation->dimension[i]; i++)
      {
         if(IDX2DIM(relation->dimension[i])->object != fact)
            if(IDX2OBJ(IDX2DIM(relation->dimension[i])->object)->type == TYP_FACT)
               HowFact(IDX2FAC(IDX2DIM(relation->dimension[i])->object), depth);
      }
   }
}


/* static explain-why functions */

FUNCTION(void WhyFact,
   (OBJ_FACT *fact, int depth),
   (fact, depth),
   OBJ_FACT *fact;
   int depth;
)
{
   int i;

   /* find rule or relation which is fired at this moment */
   for(i = 1; i <= fact->forward[0]; i++)
   {
      switch(objectList[fact->forward[i]]->type)
      {
         case TYP_RULE:
         {
            OBJ_RULE *rule = IDX2RUL(fact->forward[i]);
            if(rule->slot.FIRING && !rule->slot.EXPLAINED)
               WhyRule(rule, depth - 1);
            break;
         }

         case TYP_RELATION:
         {
            OBJ_RELATION *relation = IDX2REL(fact->forward[i]);
            if(relation->slot.FIRING && !relation->slot.EXPLAINED)
               WhyRelation(relation, fact->number, depth - 1);
            break;
         }

         default:
            Report(MSG_ERROR, MSG_BUG_INTERNAL);
            Abandon();
      }
   }
}


FUNCTION(static void WhyRule,
   (OBJ_RULE *rule, int depth),
   (rule, depth),
   OBJ_RULE *rule;
   int depth;
)
{
   int i;

   /* show rule */
   RebuildRule(0, rule);

   rule->slot.EXPLAINED = 1;

   if(depth)
   {
      /* find fact which is inferred at the moment and go deeper */
      for(i = 1; i <= rule->action[i]; i++)
      {
         if(IDX2OBJ(IDX2ACT(rule->action[i])->object)->type == TYP_FACT)
            if(IDX2FAC(IDX2ACT(rule->action[i])->object)->slot.INFERRING)
               WhyFact(IDX2FAC(IDX2ACT(rule->action[i])->object), depth);
      }
   }
}


FUNCTION(static void WhyRelation,
   (OBJ_RELATION *relation, int fact, int depth),
   (relation, fact, depth),
   OBJ_RELATION *relation;
   int fact;
   int depth;
)
{
   int i;

   /* show relation */
   RebuildRelation(0, relation);

   relation->slot.EXPLAINED = 1;

   if(depth)
   {
      /* find fact which is inferred at the moment and go deeper */
      for(i = 1; i <= relation->dimension[i]; i++)
      {
         if(IDX2DIM(relation->dimension[i])->object != fact)
            if(IDX2OBJ(IDX2DIM(relation->dimension[i])->object)->type == TYP_FACT)
               if(IDX2FAC(IDX2DIM(relation->dimension[i])->object)->slot.INFERRING)
                  WhyFact(IDX2FAC(IDX2DIM(relation->dimension[i])->object), depth);
      }
   }
}


