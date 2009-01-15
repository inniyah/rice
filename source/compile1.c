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
   File:   compile1.c
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


/* swap kb */

FUNCTION(int SwapKB,
   (int index, PROTOTYPE(void (*func), (void))),
   (index, func),
   int index;
   PROTOTYPE(void (*func), (void));
)
{
   if(SaveKB(index, STR_SWAPFILE))
      return -1;

   if(DestroyKB(index))
      return -1;

   if(func)
      (*func)();

   if(LoadKB(index, STR_SWAPFILE))
      return -1;

   if(remove(STR_SWAPFILE))
      return -1;

   return 0;
}


/* main append-function */

FUNCTION(int AppendKB,
   (int index, char *filename),
   (index, filename),
   int index;
   char *filename;
)
{
   FILE *file;

   if(SwitchES(index))
      return -1;

   if(!(file = fopen(filename, "rt")))
   {
      Report(MSG_ERROR, MSG_FILE_OPEN, filename);
      return -1;
   }

   CompileFile(file);
   DestroyMacroList();

   if(fclose(file))
   {
      Report(MSG_ERROR, MSG_FILE_CLOSE, filename);
      return -1;
   }

   if(SwapKB(index, 0))
      return -1;

   return 0;
}


/* main compile-function */

FUNCTION(int CompileKB,
   (int index, char *filename),
   (index, filename),
   int index;
   char *filename;
)
{
   FILE *file;

   if(DestroyKB(index))
      return -1;

   if(!(file = fopen(filename, "rt")))
   {
      Report(MSG_ERROR, MSG_FILE_OPEN, filename);
      return -1;
   }

   CompileFile(file);
   DestroyMacroList();

   if(fclose(file))
   {
      Report(MSG_ERROR, MSG_FILE_CLOSE, filename);
      return -1;
   }

   if(SwapKB(index, 0))
      return -1;

   return 0;
}


/* compile-functions */

FUNCTION(void CompileFile,
   (FILE *file),
   (file),
   FILE *file;
)
{
   char line[SIZ_LINE];

   line[0] = 0;

   do
      CompileLine(line, file);
   while(fgets(line, SIZ_LINE - 1, file));
}


FUNCTION(void CompileLine,
   (char *orgline, FILE *file),
   (orgline, file),
   char *orgline;
   FILE *file;
)
{
   int nrarguments;
   FILE *incfile;
   char line[SIZ_LINE], *argument[SIZ_LINE/2], *delimiter, empty = 0;

   static int key = KEY_NONE, state = KEY_NONE, user;

   static OBJ_OBJECT *object;
   static OBJ_BASE *base;
   static OBJ_LAYER *layer;
   static OBJ_RULE *rule;
   static OBJ_RELATION *relation;
   static OBJ_FACT *fact;
   static OBJ_CONDITION *condition;
   static OBJ_ACTION *action;
   static OBJ_DIMENSION *dimension;

   if(!strlen(strcpy(line, StripString(orgline))))
   {
      rule = 0;
      relation = 0;
      fact = 0;
      condition = 0;
      action = 0;
      dimension = 0;

      state = KEY_NONE;

      return;
   }

   nrarguments = SIZ_LINE/2;
   while(nrarguments)
      argument[--nrarguments] = &line[strlen(line)];

   if(delimiter = strchr(argument[nrarguments] = line, CHR_SPACE))
      nrarguments = 1;
   else
      if(delimiter = strchr(argument[nrarguments] = line, CHR_TAB))
         nrarguments = 1;
      else
         nrarguments = 0;

   while(delimiter)
   {
      *delimiter = 0;
      StripString(argument[nrarguments - 1]);
      argument[nrarguments++] = delimiter + 1;
      delimiter = strchr(delimiter + 1, CHR_COLON);
   }
   StripString(argument[nrarguments - 1]);

   if(!objectList)
   {
      object = 0;
      base = 0;
      layer = 0;
      rule = 0;
      relation = 0;
      fact = 0;
      condition = 0;
      action = 0;
      dimension = 0;
   }

   switch(key = StringToKey(argument[0]))
   {
      case KEY_DEFINE:
         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(CompileMacro(argument[1], file))
         {
            Report(MSG_WARNING, MSG_ARGUMENT_UNEXPECTED, orgline);
            break;
         }
         break;

      case KEY_INCLUDE:
         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(!(incfile = fopen(argument[1], "r")))
         {
            Report(MSG_ERROR, MSG_FILE_OPEN, argument[1]);
            break;
         }

         CompileFile(incfile);

         if(fclose(incfile))
         {
            Report(MSG_ERROR, MSG_FILE_CLOSE, argument[1]);
            break;
         }
         break;

      case KEY_BASE:
         base = CompileBase(argument[1]);

         layer = 0;
         rule = 0;
         relation = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_LAYER:
         if(!base)
         {
            base = CompileBase(&empty);
         }

         layer = CompileLayer(argument[1]);
         AddIndex(layer->number, base->layer);

         layer->status.ACTIVE = strcmp(argument[2], STR_OFF) ? 1 : 0;

         rule = 0;
         relation = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_INITx:
         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(!layer)
         {
            if(!base)
            {
               base = CompileBase(&empty);
            }
            layer = CompileLayer(&empty);
            AddIndex(layer->number, base->layer);
         }

         action = CompileAction(&empty);
         AddIndex(action->number, layer->init);
         CompileActionKeyword(action, argument[0]);

         if(action->slot.LAY)
            object = LAY2OBJ(CompileLayer(argument[1]));
         elif(action->slot.RUL)
            object = RUL2OBJ(CompileRule(argument[1]));
         elif(action->slot.REL)
            object = REL2OBJ(CompileRelation(argument[1]));
         else
         {
            action->argv = CompileArguments(&action->argc, argument[1]);
            object = FAC2OBJ(CompileFact(argument[1]));
         }

         action->argv[0] = object->symbolic;
         action->object = object->number;
         action->grade = (strlen(argument[2])) ? atof(argument[2]) : GRD_TRUE;
         action->level = GRD_FALSE;

         if(action->slot.RUN)
            IDX2FAC(action->object)->slot.CODE = 1;

         rule = 0;
         relation = 0;
         fact = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_DATA:
         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(strlen(argument[2]))
         {
            Report(MSG_WARNING, MSG_ARGUMENT_UNEXPECTED, orgline);
         }

         if(!layer)
         {
            if(!base)
            {
               base = CompileBase(&empty);
            }
            layer = CompileLayer(&empty);
            AddIndex(layer->number, base->layer);
         }

         fact = CompileFact(argument[1]);
         AddIndex(fact->number, layer->data);

         layer->slot.FORWARD = 1;

         rule = 0;
         relation = 0;
         fact = 0;
         action = 0;
         condition = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_GOAL:
         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(strlen(argument[2]))
         {
            Report(MSG_WARNING, MSG_ARGUMENT_UNEXPECTED, orgline);
         }

         if(!layer)
         {
            if(!base)
            {
               base = CompileBase(&empty);
            }
            layer = CompileLayer(&empty);
            AddIndex(layer->number, base->layer);
         }

         fact = CompileFact(argument[1]);
         AddIndex(fact->number, layer->goal);

         layer->slot.BACKWARD = 1;

         rule = 0;
         relation = 0;
         fact = 0;
         action = 0;
         condition = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_RULE:
         if(!layer)
         {
            if(!base)
            {
               base = CompileBase(&empty);
            }
            layer = CompileLayer(&empty);
            AddIndex(layer->number, base->layer);
         }

         rule = CompileRule(argument[1]);
         AddIndex(rule->number, layer->rule);

         rule->status.ACTIVE = strcmp(argument[2], STR_OFF) ? 1 : 0;

         relation = 0;
         fact = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_RELATION:
         if(condition)
         {
            Report(MSG_ERROR, MSG_KEYWORD_UNEXPECTED, orgline);
            break;
         }

         if(!layer)
         {
            if(!base)
            {
               base = CompileBase(&empty);
            }
            layer = CompileLayer(&empty);
            AddIndex(layer->number, base->layer);
         }

         relation = CompileRelation(argument[1]);
         AddIndex(relation->number, layer->relation);

         relation->status.ACTIVE = strcmp(argument[2], STR_OFF) ? 1 : 0;

         rule = 0;
         fact = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_CONDITION:
         if(!rule)
         {
            if(!layer)
            {
               if(!base)
               {
                  base = CompileBase(&empty);
               }
               layer = CompileLayer(&empty);
               AddIndex(layer->number, base->layer);
            }
            rule = CompileRule(&empty);
            AddIndex(rule->number, layer->rule);
         }

         condition = CompileCondition(argument[1]);
         AddIndex(condition->number, rule->condition);

         condition->status.ACTIVE = strcmp(argument[2], STR_OFF) ? 1 : 0;

         relation = 0;
         fact = 0;
         action = 0;
         dimension = 0;
         break;

      case KEY_ACTION:
         if(!rule)
         {
            if(!layer)
            {
               if(!base)
               {
                  base = CompileBase(&empty);
               }
               layer = CompileLayer(&empty);
               AddIndex(layer->number, base->layer);
            }
            rule = CompileRule(&empty);
            AddIndex(rule->number, layer->rule);
         }

         action = CompileAction(argument[1]);
         AddIndex(action->number, rule->action);

         action->status.ACTIVE = strcmp(argument[2], STR_OFF) ? 1 : 0;

         relation = 0;
         fact = 0;
         condition = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_DIMENSION:
         if(!relation)
         {
            if(!layer)
            {
               if(!base)
               {
                  base = CompileBase(&empty);
               }
               layer = CompileLayer(&empty);
               AddIndex(layer->number, base->layer);
            }
            relation = CompileRelation(&empty);
            AddIndex(relation->number, layer->relation);
         }

         dimension = CompileDimension(argument[1]);
         AddIndex(dimension->number, relation->dimension);

         dimension->status.ACTIVE = strcmp(argument[2], STR_OFF) ? 1 : 0;

         rule = 0;
         fact = 0;
         condition = 0;
         action = 0;

         state = key;
         break;

      case KEY_ANDx:
         if(state == KEY_LANDx || state == KEY_LANDx ||
            state == KEY_UANDx || state == KEY_ZANDx)
         {
            key = state;
         }

      case KEY_ORx:
         if(key != KEY_ANDx)
            if(state == KEY_LORx || state == KEY_LORx ||
               state == KEY_UORx || state == KEY_ZORx)
            {
               key = state;
            }

      case KEY_LIFx:
      case KEY_PIFx:
      case KEY_ZIFx:
      case KEY_UIFx:
      case KEY_LANDx:
      case KEY_PANDx:
      case KEY_ZANDx:
      case KEY_UANDx:
      case KEY_LORx:
      case KEY_PORx:
      case KEY_ZORx:
      case KEY_UORx:
         if((state == KEY_LIFx && (key == KEY_LANDx || key == KEY_LORx)) ||
            (state == KEY_PIFx && (key == KEY_PANDx || key == KEY_PORx)) ||
            (state == KEY_ZIFx && (key == KEY_ZANDx || key == KEY_ZORx)) ||
            (state == KEY_UIFx && (key == KEY_UANDx || key == KEY_UORx)))
         {
            state = key;
         }

         if(state == KEY_LANDx || state == KEY_LORx ||
            state == KEY_PANDx || state == KEY_PORx ||
            state == KEY_ZANDx || state == KEY_ZORx ||
            state == KEY_UANDx || state == KEY_UORx)
         {
            if(key != state)
            {
               Report(MSG_ERROR, MSG_KEYWORD_UNEXPECTED, orgline);
               break;
            }
         }
         elif(state != KEY_CONDITION && state != KEY_RULE)
            rule = 0;

         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(nrarguments > 3)
            Report(MSG_WARNING, MSG_ARGUMENT_UNEXPECTED, orgline);

         if(!condition)
         {
            if(!rule)
            {
               if(!layer)
               {
                  if(!base)
                  {
                     base = CompileBase(&empty);
                  }
                  layer = CompileLayer(&empty);
                  AddIndex(layer->number, base->layer);
               }
               rule = CompileRule(&empty);
               AddIndex(rule->number, layer->rule);
            }
            condition = CompileCondition(&empty);
            AddIndex(condition->number, rule->condition);
         }

         CompileConditionKeyword(condition, argument[0]);

         /* previous condition has no norm so give the same as current */

         if(rule->condition[0] == 2 && !IDX2CON(rule->condition[1])->norm)
         {
            IDX2CON(rule->condition[1])->norm = condition->norm;
            IDX2CON(rule->condition[1])->slot.AND = condition->slot.AND;
            IDX2CON(rule->condition[1])->slot.OR = condition->slot.OR;
         }

         if(key == KEY_UANDx || key == KEY_UORx)
         {
            if((key == KEY_UANDx && !userAnd) || (key == KEY_UORx && !userOr))
            {
               Report(MSG_ERROR, MSG_NORM_MISSING, orgline);
               break;
            }

            if(key == state)
            {
               if(condition->user != user)
               {
                  Report(MSG_WARNING, MSG_NORM_CHANGED, condition->user, user, orgline);

                  condition->user = user;

                  if(key == KEY_UANDx)
                     condition->norm = userAnd[user];
                  elif(key == KEY_UORx)
                     condition->norm = userOr[user];
               }
            }
            user = condition->user;

            if((key == KEY_UANDx && user >= nrUserAnd) ||
               (key == KEY_UORx  && user >= nrUserOr))
            {
               Report(MSG_ERROR, MSG_NORM_INVALID, condition->user, orgline);
            }
         }

         if(condition->slot.AND)
            rule->slot.INTERSECTION = 1;
         elif(condition->slot.OR)
            rule->slot.UNION = 1;

         if(condition->slot.LAY)
            object = LAY2OBJ(CompileLayer(argument[1]));
         elif(condition->slot.RUL)
            object = RUL2OBJ(CompileRule(argument[1]));
         elif(condition->slot.REL)
            object = REL2OBJ(CompileRelation(argument[1]));
         elif(condition->slot.CON)
            object = CON2OBJ(CompileCondition(argument[1]));
         elif(condition->slot.ACT)
            object = ACT2OBJ(CompileAction(argument[1]));
         elif(condition->slot.DIM)
            object = DIM2OBJ(CompileDimension(argument[1]));
         else
         {
            condition->argv = CompileArguments(&condition->argc, argument[1]);
            object = FAC2OBJ(fact = CompileFact(argument[1]));
            AddIndex(rule->number, fact->forward);
         }

         condition->argv[0] = object->symbolic;
         condition->object = object->number;
         condition->level = (strlen(argument[2])) ? atof(argument[2]) : GRD_FALSE;

         if(condition->slot.RUN)
            IDX2FAC(condition->object)->slot.CODE = 1;

         relation = 0;
         fact = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_xTHENx :
      case KEY_xELSEx :
         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(nrarguments > 4)
            Report(MSG_WARNING, MSG_ARGUMENT_UNEXPECTED, orgline);

         if(!action)
         {
            if(!rule)
            {
               base = CompileBase(&empty);
               Report(MSG_ERROR, MSG_KEYWORD_UNEXPECTED, orgline);
               break;
            }
            action = CompileAction(&empty);
            AddIndex(action->number, rule->action);
         }

         CompileActionKeyword(action, argument[0]);

         /* when rule has no type and only one condition with no norm yet */
         if(rule->condition[0] == 1)
         {
            IDX2CON(rule->condition[1])->norm = ZadehAnd;
            IDX2CON(rule->condition[1])->slot.AND = 1;
            rule->slot.INTERSECTION = 1;
         }

         if(action->slot.LAY)
            object = LAY2OBJ(CompileLayer(argument[1]));
         elif(action->slot.RUL)
            object = RUL2OBJ(CompileRule(argument[1]));
         elif(action->slot.REL)
            object = REL2OBJ(CompileRelation(argument[1]));
         elif(action->slot.CON)
            object = CON2OBJ(CompileCondition(argument[1]));
         elif(action->slot.ACT)
            object = ACT2OBJ(CompileAction(argument[1]));
         elif(action->slot.DIM)
            object = DIM2OBJ(CompileDimension(argument[1]));
         else
         {
            action->argv = CompileArguments(&action->argc, argument[1]);
            object = FAC2OBJ(fact = CompileFact(argument[1]));
            AddIndex(rule->number, fact->backward);
         }

         action->argv[0] = object->symbolic;
         action->object = object->number;
         action->grade = (strlen(argument[2])) ? atof(argument[2]) : GRD_TRUE;
         action->level = (strlen(argument[3])) ? atof(argument[3]) : (GRD_TRUE + GRD_FALSE)/2;

         if(action->slot.RUN)
            IDX2FAC(action->object)->slot.CODE = 1;

         relation = 0;
         fact = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;      

      case KEY_LxDIMx:
      case KEY_PxDIMx:
      case KEY_ZxDIMx:
      case KEY_UxDIMx:
         if(state == KEY_LxDIMx || state == KEY_PxDIMx ||
            state == KEY_ZxDIMx || state == KEY_UxDIMx)
         {
            if(key != state)
            {
               Report(MSG_ERROR, MSG_KEYWORD_UNEXPECTED, orgline);
               break;
            }
         }
         elif(state != KEY_DIMENSION && state != KEY_RELATION)
            relation = 0;

         if(!strlen(argument[1]))
         {
            Report(MSG_ERROR, MSG_ARGUMENT_MISSING, orgline);
            break;
         }

         if(nrarguments > 4)
            Report(MSG_WARNING, MSG_ARGUMENT_UNEXPECTED, orgline);

         if(!dimension)
         {
            if(!relation)
            {
               if(!layer)
               {
                  if(!base)
                  {
                     base = CompileBase(&empty);
                  }
                  layer = CompileLayer(&empty);
                  AddIndex(layer->number, base->layer);
               }
               relation = CompileRelation(&empty);
               AddIndex(relation->number, layer->relation);
            }
            dimension = CompileDimension(&empty);
            AddIndex(dimension->number, relation->dimension);
         }

         CompileDimensionKeyword(dimension, argument[0]);

         if(key == KEY_UxDIMx || key == KEY_UxDIMx)
         {
            if(key == state)
            {
               if(dimension->user[0] != user)
               {
                  Report(MSG_WARNING, MSG_NORM_CHANGED, dimension->user[0], user, orgline);

                  dimension->user[0] = user;
                  dimension->norm[0] = userAnd[user];
               }
            }
            user = condition->user;
         }

         if(dimension->slot.LAY)
            object = LAY2OBJ(CompileLayer(argument[1]));
         elif(dimension->slot.RUL)
            object = RUL2OBJ(CompileRule(argument[1]));
         elif(dimension->slot.REL)
            object = REL2OBJ(CompileRelation(argument[1]));
         elif(dimension->slot.CON)
            object = CON2OBJ(CompileCondition(argument[1]));
         elif(dimension->slot.ACT)
            object = ACT2OBJ(CompileAction(argument[1]));
         elif(dimension->slot.DIM)
            object = DIM2OBJ(CompileDimension(argument[1]));
         else
         {
            dimension->argv = CompileArguments(&dimension->argc, argument[1]);
            object = FAC2OBJ(fact = CompileFact(argument[1]));
            AddIndex(relation->number, fact->forward);
            AddIndex(relation->number, fact->backward);
         }

         dimension->argv[0] = object->symbolic;
         dimension->object = object->number;
         dimension->grade = (strlen(argument[2])) ? atof(argument[2]) : GRD_TRUE;
         dimension->level = (strlen(argument[3])) ? atof(argument[3]) : GRD_FALSE;

         if(dimension->slot.RUN)
            IDX2FAC(dimension->object)->slot.CODE = 1;

         rule = 0;
         fact = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = key;
         break;

      case KEY_REM:
         key = state; /* state remains the same */
         break;

      case KEY_NONE:
         rule = 0;
         relation = 0;
         fact = 0;
         condition = 0;
         action = 0;
         dimension = 0;

         state = KEY_NONE;
         break;

      default:
         if(delimiter = strchr(orgline, CHR_SPACE))
            while(*delimiter == CHR_SPACE)
               delimiter++;
         else
            delimiter = &empty;

         if(RebuildMacro(argument[0], delimiter, argument, file))
         {
            Report(MSG_ERROR, MSG_KEYWORD_UNKNOWN, orgline);

            rule = 0;
            relation = 0;
            fact = 0;
            condition = 0;
            action = 0;
            dimension = 0;

            state = KEY_NONE;
         }
         break;
   }
}



