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
   File:   compile2.c
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


/* include local header file */

#include "compile.h"


/* compile functions */

FUNCTION(OBJ_BASE *CompileBase,
   (char *argument),
   (argument),
   char *argument;
)
{
   OBJ_BASE *base;

   ALLOC(base, 1, OBJ_BASE);
   ALLOC(base->symbolic, strlen(argument) + 1, char);
   ALLOC(base->layer, 1, int);

   memset(&base->status, 0, sizeof(PRP_OBJECT));

   base->type = TYP_BASE;
   base->number = 0;
   base->status.ACTIVE = 1;
   base->layer[0] = 0;

   strcpy(base->symbolic, argument);

   AddObjectToList(BAS2OBJ(base));

   return base;
}


FUNCTION(OBJ_LAYER *CompileLayer,
   (char *argument),
   (argument),
   char *argument;
)
{
   register int i;
   OBJ_LAYER *layer;

   if(strlen(argument))
      for(i = 1; i <= objectList[0]->number; i++)
         if(objectList[i]->type == TYP_LAYER)
            if(!strcmp(objectList[i]->symbolic, argument))
               return IDX2LAY(i);

   ALLOC(layer, 1, OBJ_LAYER);
   ALLOC(layer->init, 1, int);
   ALLOC(layer->data, 1, int);
   ALLOC(layer->goal, 1, int);
   ALLOC(layer->rule, 1, int);
   ALLOC(layer->relation, 1, int);
   ALLOC(layer->symbolic, strlen(argument) + 1, char);

   memset(&layer->status, 0, sizeof(PRP_OBJECT));
   memset(&layer->slot, 0, sizeof(PRP_LAYER));

   layer->type = TYP_LAYER;
   layer->status.ACTIVE = 1;
   layer->init[0] = 0;
   layer->data[0] = 0;
   layer->goal[0] = 0;
   layer->rule[0] = 0;
   layer->relation[0] = 0;

   strcpy(layer->symbolic, argument);

   AddObjectToList(LAY2OBJ(layer));

   return layer;
}


FUNCTION(OBJ_RULE *CompileRule,
   (char *argument),
   (argument),
   char *argument;
)
{
   register int i;
   OBJ_RULE *rule;

   if(strlen(argument))
      for(i = 1; i <= objectList[0]->number; i++)
         if(objectList[i]->type == TYP_RULE)
            if(!strcmp(objectList[i]->symbolic, argument))
               return IDX2RUL(i);

   ALLOC(rule, 1, OBJ_RULE);
   ALLOC(rule->condition, 1, int);
   ALLOC(rule->action, 1, int);
   ALLOC(rule->symbolic, strlen(argument) + 1, char);

   memset(&rule->status, 0, sizeof(PRP_OBJECT));
   memset(&rule->slot, 0, sizeof(PRP_RULE));

   rule->type = TYP_RULE;
   rule->status.ACTIVE = 1;
   rule->condition[0] = 0;
   rule->action[0] = 0;

   strcpy(rule->symbolic, argument);

   AddObjectToList(RUL2OBJ(rule));

   return rule;
}


FUNCTION(OBJ_RELATION *CompileRelation,
   (char *argument),
   (argument),
   char *argument;
)
{
   register int i;
   OBJ_RELATION *relation;

   if(strlen(argument))
      for(i = 1; i <= objectList[0]->number; i++)
         if(objectList[i]->type == TYP_RELATION)
            if(!strcmp(objectList[i]->symbolic, argument))
               return IDX2REL(i);

   ALLOC(relation, 1, OBJ_RELATION);
   ALLOC(relation->dimension, 1, int);
   ALLOC(relation->symbolic, strlen(argument) + 1, char);

   memset(&relation->status, 0, sizeof(PRP_OBJECT));
   memset(&relation->slot, 0, sizeof(PRP_RELATION));

   relation->type = TYP_RELATION;
   relation->status.ACTIVE = 1;
   relation->dimension[0] = 0;

   strcpy(relation->symbolic, argument);

   AddObjectToList(REL2OBJ(relation));

   return relation;
}


FUNCTION(OBJ_CONDITION *CompileCondition,
   (char *argument),
   (argument),
   char *argument;
)
{
   register int i;
   OBJ_CONDITION *condition;

   if(strlen(argument))
      for(i = 1; i <= objectList[0]->number; i++)
         if(objectList[i]->type == TYP_CONDITION)
            if(!strcmp(objectList[i]->symbolic, argument))
               return IDX2CON(i);

   ALLOC(condition, 1, OBJ_CONDITION);
   ALLOC(condition->symbolic, strlen(argument) + 1, char);

   memset(&condition->status, 0, sizeof(PRP_OBJECT));
   memset(&condition->slot, 0, sizeof(PRP_CONDITION));

   condition->type = TYP_CONDITION;
   condition->status.ACTIVE = 1;
   condition->symbolic[0] = 0;
   condition->argc = 0;
   condition->argv = 0;
   condition->user = -1;
   condition->object = -1;
   condition->level = GRD_FALSE;
   condition->norm = 0;
   condition->truth = GRD_UNKNOWN;

   strcpy(condition->symbolic, argument);

   AddObjectToList(CON2OBJ(condition));

   return condition;
}


FUNCTION(OBJ_ACTION *CompileAction,
   (char *argument),
   (argument),
   char *argument;
)
{
   register int i;
   OBJ_ACTION *action;

   if(strlen(argument))
      for(i = 1; i <= objectList[0]->number; i++)
         if(objectList[i]->type == TYP_ACTION)
            if(!strcmp(objectList[i]->symbolic, argument))
               return IDX2ACT(i);

   ALLOC(action, 1, OBJ_ACTION);
   ALLOC(action->symbolic, strlen(argument) + 1, char);

   memset(&action->status, 0, sizeof(PRP_OBJECT));
   memset(&action->slot, 0, sizeof(PRP_ACTION));

   action->type = TYP_ACTION;
   action->status.ACTIVE = 1;
   action->symbolic[0] = 0;
   action->argc = 0;
   action->argv = 0;
   action->user = -1;
   action->object = -1;
   action->grade = GRD_TRUE;
   action->level = (GRD_FALSE + GRD_TRUE)/2.0;
   action->norm = 0;
   action->truth = GRD_UNKNOWN;

   strcpy(action->symbolic, argument);

   AddObjectToList(ACT2OBJ(action));

   return action;
}


FUNCTION(OBJ_DIMENSION *CompileDimension,
   (char *argument),
   (argument),
   char *argument;
)
{
   register int i;
   OBJ_DIMENSION *dimension;

   if(strlen(argument))
      for(i = 1; i <= objectList[0]->number; i++)
         if(objectList[i]->type == TYP_DIMENSION)
            if(!strcmp(objectList[i]->symbolic, argument))
               return IDX2DIM(i);

   ALLOC(dimension, 1, OBJ_DIMENSION);
   ALLOC(dimension->symbolic, strlen(argument) + 1, char);

   memset(&dimension->status, 0, sizeof(PRP_OBJECT));
   memset(&dimension->slot, 0, sizeof(PRP_DIMENSION));

   dimension->type = TYP_DIMENSION;
   dimension->status.ACTIVE = 1;
   dimension->symbolic[0] = 0;
   dimension->argc = 0;
   dimension->argv = 0;
   dimension->object = -1;
   dimension->grade = GRD_TRUE;
   dimension->level = GRD_FALSE;
   dimension->user[0] = dimension->user[1] = -1;
   dimension->norm[0] = dimension->norm[1] = 0;
   dimension->truth[0] = dimension->truth[1] = GRD_UNKNOWN;

   strcpy(dimension->symbolic, argument);

   AddObjectToList(DIM2OBJ(dimension));

   return dimension;
}


FUNCTION(void CompileConditionKeyword,
   (OBJ_CONDITION *condition, char *argument),
   (condition, argument),
   OBJ_CONDITION *condition;
   char *argument;
)
{
   if(KeysInString1(argument, STR_L))
      condition->slot.LHSL = 1;
   elif(KeysInString1(argument, STR_P))
      condition->slot.LHSP = 1;
   elif(KeysInString1(argument, STR_Z))
      condition->slot.LHSZ = 1;
   elif(KeysInString1(argument, STR_U))
   {
      condition->slot.LHSU = 1;
      condition->user = atoi(argument);
   }
   else
      condition->slot.LHSZ = 1;  /* default condition operator */

   /* first check on general 'if', which could mean 'and' or 'or' */

   if(!KeysInString1(argument, STR_IF))
   {
      condition->slot.AND = KeysInString1(argument, STR_AND) ? 1 : 0;
      condition->slot.OR  = KeysInString1(argument, STR_OR)  ? 1 : 0;
   }

   condition->slot.NOT  = (strstr(argument, STR_NOT) != 0);
   condition->slot.LAY  = (strstr(argument, STR_LAY) != 0);
   condition->slot.RUL  = (strstr(argument, STR_RUL) != 0);
   condition->slot.REL  = (strstr(argument, STR_REL) != 0);
   condition->slot.CON  = (strstr(argument, STR_CON) != 0);
   condition->slot.ACT  = (strstr(argument, STR_ACT) != 0);
   condition->slot.DIM  = (strstr(argument, STR_DIM) != 0);
   condition->slot.GRD  = (strstr(argument, STR_GRD) != 0);
   condition->slot.CUT  = (strstr(argument, STR_CUT) != 0);
   condition->slot.ON   = (strstr(argument, STR_ON)  != 0);
   condition->slot.OFF  = (strstr(argument, STR_OFF) != 0);
   condition->slot.BKW  = (strstr(argument, STR_BKW) != 0);
   condition->slot.FRW  = (strstr(argument, STR_FRW) != 0);
   condition->slot.USR  = (strstr(argument, STR_USR) != 0 ||
                           strstr(argument, STR_ASK) != 0);
   condition->slot.SHW  = (strstr(argument, STR_WHY) != 0 ||
                           strstr(argument, STR_SHW) != 0);
   condition->slot.RUN  = (strstr(argument, STR_RUN) != 0);

   condition->slot.FAC  = !(condition->slot.LAY ||
                            condition->slot.RUL ||
                            condition->slot.REL ||
                            condition->slot.CON ||
                            condition->slot.ACT ||
                            condition->slot.DIM);

   if(condition->slot.AND)
   {
      if(condition->slot.LHSL)
         condition->norm = LukasiewiczAnd;
      elif(condition->slot.LHSP)
         condition->norm = ProbabilityAnd;
      elif(condition->slot.LHSZ)
         condition->norm = ZadehAnd;
      else
         condition->norm = userAnd[condition->user];
   }
   elif(condition->slot.OR)
   {
      if(condition->slot.LHSL)
         condition->norm = LukasiewiczOr;
      elif(condition->slot.LHSP)
         condition->norm = ProbabilityOr;
      elif(condition->slot.LHSZ)
         condition->norm = ZadehOr;
      else
         condition->norm = userOr[condition->user];
   }
   else
      condition->norm = 0;   /* no norm yet */
}


FUNCTION(void CompileActionKeyword,
   (OBJ_ACTION *action, char *argument),
   (action, argument),
   OBJ_ACTION *action;
   char *argument;
)
{
   if(KeysInString1(argument, STR_L))
      action->slot.RHSL = 1;
   elif(KeysInString1(argument, STR_P))
      action->slot.RHSP = 1;
   elif(KeysInString1(argument, STR_Z))
      action->slot.RHSZ = 1;
   elif(KeysInString1(argument, STR_U))
   {
      action->slot.RHSU = 1;
      action->user = atoi(argument);
   }
   else
      action->slot.RHSP = 1;   /* default action operator */

   if(action->slot.INIT = (strstr(argument, STR_INIT) != 0))
      action->slot.RHSZ = 1;

   action->slot.THEN = (strstr(argument, STR_THEN) != NULL);
   action->slot.ELSE = (strstr(argument, STR_ELSE) != 0);
   action->slot.NOT  = (strstr(argument, STR_NOT)  != 0);
   action->slot.LAY  = (strstr(argument, STR_LAY)  != 0);
   action->slot.RUL  = (strstr(argument, STR_RUL)  != 0);
   action->slot.REL  = (strstr(argument, STR_REL)  != 0);
   action->slot.CON  = (strstr(argument, STR_CON)  != 0);
   action->slot.ACT  = (strstr(argument, STR_ACT)  != 0);
   action->slot.DIM  = (strstr(argument, STR_DIM)  != 0);
   action->slot.GRD  = (strstr(argument, STR_GRD)  != 0);
   action->slot.CUT  = (strstr(argument, STR_CUT)  != 0);
   action->slot.ON   = (strstr(argument, STR_ON)   != 0);
   action->slot.OFF  = (strstr(argument, STR_OFF)  != 0);
   action->slot.BKW  = (strstr(argument, STR_BKW)  != 0);
   action->slot.FRW  = (strstr(argument, STR_FRW)  != 0);
   action->slot.USR  = (strstr(argument, STR_USR)  != 0 ||
                        strstr(argument, STR_INF)  != 0);
   action->slot.SHW  = (strstr(argument, STR_HOW)  != 0 ||
                        strstr(argument, STR_SHW)  != 0);
   action->slot.RUN  = (strstr(argument, STR_RUN)  != 0);
   action->slot.INV  = (strstr(argument, STR_INV)  != 0);

   if(action->slot.INV || action->slot.FRW || action->slot.BKW)
      action->slot.LAY = 1;

   action->slot.FAC  = !(action->slot.LAY ||
                         action->slot.RUL ||
                         action->slot.REL ||
                         action->slot.CON ||
                         action->slot.ACT ||
                         action->slot.DIM);

   if(action->slot.RHSL)
      action->norm = LukasiewiczAnd;
   elif(action->slot.RHSP)
      action->norm = ProbabilityAnd;
   elif(action->slot.RHSZ)
      action->norm = ZadehAnd;
   else
      action->norm = userAnd[action->user];
}


FUNCTION(void CompileDimensionKeyword,
   (OBJ_DIMENSION *dimension, char *argument),
   (dimension, argument),
   OBJ_DIMENSION *dimension;
   char *argument;
)
{
   if(KeysInString1(argument, STR_L))
      dimension->slot.LHSL = 1;
   elif(KeysInString1(argument, STR_P))
      dimension->slot.LHSP = 1;
   elif(KeysInString1(argument, STR_Z))
      dimension->slot.LHSZ = 1;
   elif(KeysInString1(argument, STR_U))
   {
      dimension->slot.LHSU = 1;
      dimension->user[0] = atoi(argument);
      while(isdigit(*argument)) argument++;
   }
   else
      dimension->slot.LHSZ = 1;   /* default condition operator */

   if(KeysInString1(argument, STR_L))
      dimension->slot.RHSL = 1;
   elif(KeysInString1(argument, STR_P))
      dimension->slot.RHSP = 1;
   elif(KeysInString1(argument, STR_Z))
      dimension->slot.RHSZ = 1;
   elif(KeysInString1(argument, STR_U))
   {
      dimension->slot.RHSU = 1;
      dimension->user[1] = atoi(argument);
      while(isdigit(*argument)) argument++;
   }
   else
      dimension->slot.RHSZ = 1;   /* default action operator */

   argument += sizeof(STR_DIM) - 1;

   dimension->slot.NOT  = (strstr(argument, STR_NOT) != 0);
   dimension->slot.LAY  = (strstr(argument, STR_LAY) != 0);
   dimension->slot.RUL  = (strstr(argument, STR_RUL) != 0);
   dimension->slot.REL  = (strstr(argument, STR_REL) != 0);
   dimension->slot.CON  = (strstr(argument, STR_CON) != 0);
   dimension->slot.ACT  = (strstr(argument, STR_ACT) != 0);
   dimension->slot.DIM  = (strstr(argument, STR_DIM) != 0);
   dimension->slot.GRD  = (strstr(argument, STR_GRD) != 0);
   dimension->slot.CUT  = (strstr(argument, STR_CUT) != 0);
   dimension->slot.ON   = (strstr(argument, STR_ON)  != 0);
   dimension->slot.OFF  = (strstr(argument, STR_OFF) != 0);
   dimension->slot.BKW  = (strstr(argument, STR_BKW) != 0);
   dimension->slot.FRW  = (strstr(argument, STR_FRW) != 0);
   dimension->slot.USR  = (strstr(argument, STR_USR) != 0);
   dimension->slot.SHW  = (strstr(argument, STR_SHW) != 0);
   dimension->slot.RUN  = (strstr(argument, STR_RUN) != 0);

   dimension->slot.FAC  = !(dimension->slot.LAY ||
                            dimension->slot.RUL ||
                            dimension->slot.REL ||
                            dimension->slot.CON ||
                            dimension->slot.ACT ||
                            dimension->slot.DIM);

   if(dimension->slot.LHSL)
      dimension->norm[0] = LukasiewiczAnd;
   elif(dimension->slot.LHSP)
      dimension->norm[0] = ProbabilityAnd;
   elif(dimension->slot.LHSZ)
      dimension->norm[0] = ZadehAnd;
   else
      dimension->norm[0] = userAnd[dimension->user[0]];

   if(dimension->slot.RHSL)
      dimension->norm[1] = LukasiewiczAnd;
   elif(dimension->slot.RHSP)
      dimension->norm[1] = ProbabilityAnd;
   elif(dimension->slot.RHSZ)
      dimension->norm[1] = ZadehAnd;
   else
      dimension->norm[1] = userAnd[dimension->user[1]];
}


/* extra-functions */

FUNCTION(char **CompileArguments,
   (int *argc, char *argument),
   (argc, argument),
   int *argc;
   char *argument;
)
{
   register int i;
   int len;
   char **argv, *prevarg, *nextarg;

   *argc = 1;
   ALLOC(argv, *argc, char *);
   argv[*argc - 1] = 0;

   len = strlen(argument);
   if(!len || argument[len - 1] != CHR_RIGHTPARENT)
      return argv;

   for(i = len - 1; i > 0 && argument[i] != CHR_LEFTPARENT; i--);

   if(!i)
      return argv;

   argument[i] = argument[len - 1] = 0;
   StripString(argument);

   prevarg = argument + i + 1;
   while((nextarg = strchr(prevarg, CHR_COMMA)) && *prevarg)
   {
      *nextarg = 0;
      StripString(prevarg);
      *argc += 1;
      REALLOC(argv, *argc, char *);
      ALLOC(argv[*argc - 1], strlen(prevarg) + 1, char);
      strcpy(argv[*argc - 1], prevarg);
      prevarg = nextarg + 1;
      nextarg = strchr(prevarg, CHR_COMMA);
   }
   StripString(prevarg);
   *argc += 1;
   REALLOC(argv, *argc, char *);
   ALLOC(argv[*argc - 1], strlen(prevarg) + 1, char);
   strcpy(argv[*argc - 1], prevarg);

   return argv;
}


