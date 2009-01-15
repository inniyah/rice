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
   File:   rebuild.c
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
#include "rebuild.h"


/* prototypes of static functions */

PROTOTYPE(static void RebuildFile, (FILE *));

PROTOTYPE(static void RebuildBase, (FILE *, OBJ_BASE *));
PROTOTYPE(static void RebuildLayer, (FILE *, OBJ_LAYER *));
PROTOTYPE(static void RebuildCondition, (FILE *, OBJ_CONDITION *));
PROTOTYPE(static void RebuildAction, (FILE *, OBJ_ACTION *));
PROTOTYPE(static void RebuildDimension, (FILE *, OBJ_DIMENSION *));

PROTOTYPE(static void RebuildKey, (FILE *, char *));

PROTOTYPE(static void RebuildString, (FILE *, char *, ...));


/* file string to file */

FUNCTION(static void RebuildString,
   (FILE *file, char *format, ...),
   (va_alist),
   va_dcl
)
{
   static char string[SIZ_LINE];
   va_list arguments;

   VARARGS(
      FILE *file;
      char *format;
      ,
      VA_START(arguments, format);
      ,
      file = va_arg(arguments, FILE *);
      format = va_arg(arguments, char *);
   );

   vsprintf(string, format, arguments);
   va_end(arguments);

   if(file)
      fprintf(file, string);   /* rebuilding kb to file */
   else
      if(userExplain)   /* use user supplied function */
         (*userExplain)(kbIndex, string);
      else
         printf(string);   /* file to screen */
}


/* main rebuild-function */

FUNCTION(int RebuildKB,
   (int index, char *filename),
   (index, filename),
   int index;
   char *filename;
)
{
   FILE *file;

   if(SwitchES(index))
      return -1;

   if(!(file = fopen(filename, "wt")))
   {
      Report(MSG_ERROR, MSG_FILE_OPEN, filename);
      return -1;
   }

   RebuildFile(file);

   if(fclose(file) == EOF)
   {
      Report(MSG_ERROR, MSG_FILE_CLOSE, filename);
      return -1;
   }

   return 0;
}


/* specific rebuild-functions */

FUNCTION(static void RebuildFile,
   (FILE *file),
   (file),
   FILE *file;
)
{
   if(!objectList)
      return;

   RebuildBase(file, IDX2BAS(0));
}


FUNCTION(static void RebuildBase,
   (FILE *file, OBJ_BASE *base),
   (file, base),
   FILE *file;
   OBJ_BASE *base;
)
{
   register int i;

   if(strlen(base->symbolic))
   {
      RebuildKey(file, STR_BASE);
      RebuildString(file, " %s\n\n", base->symbolic);
   }

   for(i = 1; i <= base->layer[0]; i++)
      RebuildLayer(file, IDX2LAY(base->layer[i]));
}


FUNCTION(static void RebuildLayer,
   (FILE *file, OBJ_LAYER *layer),
   (file, layer),
   FILE *file;
   OBJ_LAYER *layer;
)
{
   register int i;

   /* do not put 'Layer' when it is the first layer and without a name */

   if(layer->number > 2 || strlen(layer->symbolic))
      RebuildKey(file, STR_LAYER);

   if(strlen(layer->symbolic))
   {
      RebuildString(file, " %s", layer->symbolic);

      if(!layer->status.ACTIVE)
      {
         RebuildString(file, " : ");
         RebuildKey(file, STR_OFF);
      }

      RebuildString(file, "\n\n");
   }
   elif(layer->number > 2)   /* prevent unnecessary space at top of file */
      RebuildString(file, "\n\n");

   for(i = 1; i <= layer->init[0]; i++)
      RebuildAction(file, IDX2ACT(layer->init[i]));

   if(layer->init[0])
      RebuildString(file, "\n");

   for(i = 1; i <= layer->data[0]; i++)
   {
      RebuildKey(file, STR_DATA);
      RebuildString(file, " %s\n", IDX2OBJ(layer->data[i])->symbolic);
   }

   if(layer->data[0])
      RebuildString(file, "\n");

   for(i = 1; i <= layer->goal[0]; i++)
   {
      RebuildKey(file, STR_GOAL);
      RebuildString(file, " %s\n", IDX2OBJ(layer->goal[i])->symbolic);
   }

   if(layer->goal[0])
      RebuildString(file, "\n");

   for(i = 1; i <= layer->rule[0]; i++)
      RebuildRule(file, IDX2RUL(layer->rule[i]));

   for(i = 1; i <= layer->relation[0]; i++)
      RebuildRelation(file, IDX2REL(layer->relation[i]));
}


FUNCTION(void RebuildRule,
   (FILE *file, OBJ_RULE *rule),
   (file, rule),
   FILE *file;
   OBJ_RULE *rule;
)
{
   register int i;

   if(strlen(rule->symbolic))
   {
      RebuildKey(file, STR_RULE);
      RebuildString(file, " %s", rule->symbolic);

      if(!rule->status.ACTIVE)
      {
         RebuildString(file, " : ");
         RebuildKey(file, STR_OFF);
      }

      RebuildString(file, "\n");
   }

   /* so there will be If instead of And or Or in first condition */
   IDX2CON(rule->condition[1])->slot.AND = 0;
   IDX2CON(rule->condition[1])->slot.OR = 0;
   RebuildCondition(file, IDX2CON(rule->condition[1]));

   /* rest of antecedent */
   for(i = 2; i <= rule->condition[0]; i++)
      RebuildCondition(file, IDX2CON(rule->condition[i]));

   /* rebuild consequent */
   for(i = 1; i <= rule->action[0]; i++)
      RebuildAction(file, IDX2ACT(rule->action[i]));

   RebuildString(file, "\n");
}


FUNCTION(void RebuildRelation,
   (FILE *file, OBJ_RELATION *relation),
   (file, relation),
   FILE *file;
   OBJ_RELATION *relation;
)
{
   register int i;

   if(strlen(relation->symbolic))
   {
      RebuildKey(file, STR_RELATION);
      RebuildString(file, " %s", relation->symbolic);

      if(!relation->status.ACTIVE)
      {
         RebuildString(file, " : ");
         RebuildKey(file, STR_OFF);
      }

      RebuildString(file, "\n");
   }

   for(i = 1; i <= relation->dimension[0]; i++)
      RebuildDimension(file, IDX2DIM(relation->dimension[i]));

   RebuildString(file, "\n");
}


FUNCTION(static void RebuildCondition,
   (FILE *file, OBJ_CONDITION *condition),
   (file, condition),
   FILE *file;
   OBJ_CONDITION *condition;
)
{
   register int i;

   if(strlen(condition->symbolic))
   {
      RebuildKey(file, STR_CONDITION);
      RebuildString(file, "%s", condition->symbolic);

      if(!condition->status.ACTIVE)
      {
         RebuildString(file, " : ");
         RebuildKey(file, STR_OFF);
      }

      RebuildString(file, "\n");
   }

   /* Z-type is assumed default */

     if(condition->slot.LHSL) RebuildKey(file, STR_L);
   elif(condition->slot.LHSP) RebuildKey(file, STR_P);
   elif(condition->slot.LHSU)
   {
      RebuildKey(file, STR_U);
      RebuildString(file, "%d", condition->user);
   }

     if(condition->slot.AND)  RebuildKey(file, STR_AND);
   elif(condition->slot.OR)   RebuildKey(file, STR_OR);
   else                       RebuildKey(file, STR_IF);

   if(condition->slot.IF)     RebuildKey(file, STR_IF);

   if(condition->slot.NOT)    RebuildKey(file, STR_NOT);

     if(condition->slot.USR)  RebuildKey(file, STR_ASK);
   elif(condition->slot.RUN)  RebuildKey(file, STR_RUN);

     if(condition->slot.LAY)  RebuildKey(file, STR_LAY);
   elif(condition->slot.RUL)  RebuildKey(file, STR_RUL);
   elif(condition->slot.REL)  RebuildKey(file, STR_REL);
   elif(condition->slot.CON)  RebuildKey(file, STR_CON);
   elif(condition->slot.ACT)  RebuildKey(file, STR_ACT);
   elif(condition->slot.DIM)  RebuildKey(file, STR_DIM);

     if(condition->slot.ON)   RebuildKey(file, STR_ON);
   elif(condition->slot.OFF)  RebuildKey(file, STR_OFF);
   elif(condition->slot.BKW)  RebuildKey(file, STR_BKW);
   elif(condition->slot.FRW)  RebuildKey(file, STR_FRW);
   elif(condition->slot.GRD)  RebuildKey(file, STR_GRD);
   elif(condition->slot.CUT)  RebuildKey(file, STR_CUT);

   RebuildString(file, " %s", IDX2OBJ(condition->object)->symbolic);

   if(condition->argc > 1)
   {
      RebuildString(file, " %c%s", CHR_LEFTPARENT, condition->argv[1]);
      for(i = 2; i < condition->argc; i++)
         RebuildString(file, "%c %s", CHR_COMMA, condition->argv[i]);
      RebuildString(file, "%c", CHR_RIGHTPARENT);
   }

   if(condition->level != GRD_FALSE)
      RebuildString(file, " : %g", condition->level);

   if(!file)   /* rebuilding for explaination */
      if(condition->truth == GRD_UNKNOWN)
         RebuildString(file, " [*]");
      else
         RebuildString(file, " [%g]", condition->truth);

   RebuildString(file, "\n");
}


FUNCTION(static void RebuildAction,
   (FILE *file, OBJ_ACTION *action),
   (file, action),
   FILE *file;
   OBJ_ACTION *action;
)
{
   register int i;

   if(strlen(action->symbolic))
   {
      RebuildKey(file, STR_ACTION);
      RebuildString(file, " %s", action->symbolic);

      if(!action->status.ACTIVE)
      {
         RebuildString(file, " : ");
         RebuildKey(file, STR_OFF);
      }

      RebuildString(file, "\n");
   }

   if(action->slot.INIT)
      RebuildKey(file, STR_INIT);
   else
   {
      /* P-type is assumed default */

      if(action->slot.RHSL) RebuildKey(file, STR_L);
      elif(action->slot.RHSZ) RebuildKey(file, STR_Z);
      elif(action->slot.RHSU)
      {
         RebuildKey(file, STR_U);
         RebuildString(file, "%d", action->user);
      }

      if(action->slot.THEN) RebuildKey(file, STR_THEN);
         elif(action->slot.ELSE) RebuildKey(file, STR_ELSE);
   }

   if(action->slot.NOT)    RebuildKey(file, STR_NOT);

     if(action->slot.USR)  RebuildKey(file, STR_INF);
   elif(action->slot.RUN)  RebuildKey(file, STR_RUN);
   elif(action->slot.INV)  RebuildKey(file, STR_INV);

     if(action->slot.LAY)  RebuildKey(file, STR_LAY);
   elif(action->slot.RUL)  RebuildKey(file, STR_RUL);
   elif(action->slot.REL)  RebuildKey(file, STR_REL);
   elif(action->slot.CON)  RebuildKey(file, STR_CON);
   elif(action->slot.ACT)  RebuildKey(file, STR_ACT);
   elif(action->slot.DIM)  RebuildKey(file, STR_DIM);

     if(action->slot.ON)   RebuildKey(file, STR_ON);
   elif(action->slot.OFF)  RebuildKey(file, STR_OFF);
   elif(action->slot.BKW)  RebuildKey(file, STR_BKW);
   elif(action->slot.FRW)  RebuildKey(file, STR_FRW);
   elif(action->slot.GRD)  RebuildKey(file, STR_GRD);
   elif(action->slot.CUT)  RebuildKey(file, STR_CUT);

   RebuildString(file, " %s", IDX2OBJ(action->object)->symbolic);

   if(action->argc > 1)
   {
      RebuildString(file, " %c%s", CHR_LEFTPARENT, action->argv[1]);
      for(i = 2; i < action->argc; i++)
         RebuildString(file, "%c %s", CHR_COMMA, action->argv[i]);
      RebuildString(file, "%c", CHR_RIGHTPARENT);
   }

   if(action->grade != GRD_TRUE ||
      (!action->slot.INIT && action->level != (GRD_TRUE + GRD_FALSE)/2))
      RebuildString(file, " : %g", action->grade);

   if(!action->slot.INIT && action->level != (GRD_TRUE + GRD_FALSE)/2)
      RebuildString(file, " : %g", action->level);

   if(!file)   /* rebuilding for explaination */
      if(action->truth == GRD_UNKNOWN)
         RebuildString(file, " [*]");
      else
         RebuildString(file, " [%g]", action->truth);

   RebuildString(file, "\n");
}


FUNCTION(static void RebuildDimension,
   (FILE *file, OBJ_DIMENSION *dimension),
   (file, dimension),
   FILE *file;
   OBJ_DIMENSION *dimension;
)
{
   register int i;

   if(strlen(dimension->symbolic))
   {
      RebuildKey(file, STR_DIMENSION);
      RebuildString(file, " %s", dimension->symbolic);

      if(!dimension->status.ACTIVE)
      {
         RebuildString(file, " : ");
         RebuildKey(file, STR_OFF);
      }

      RebuildString(file, "\n");
   }

   if(!(dimension->slot.LHSZ && dimension->slot.RHSZ))
   {
      /* Z-type is assumed default */

        if(dimension->slot.LHSL) RebuildKey(file, STR_L);
      elif(dimension->slot.LHSP) RebuildKey(file, STR_P);
      elif(dimension->slot.LHSU)
      {
         RebuildKey(file, STR_U);
         RebuildString(file, "%d", dimension->user[0]);
      }

      /* P-type is assumed default */

        if(dimension->slot.RHSL) RebuildKey(file, STR_L);
      elif(dimension->slot.RHSZ) RebuildKey(file, STR_Z);
      elif(dimension->slot.RHSU)
      {
         RebuildKey(file, STR_U);
         RebuildString(file, "%d", dimension->user[1]);
      }
   }

   RebuildKey(file, STR_DIM);

   if(dimension->slot.NOT)    RebuildKey(file, STR_NOT);

     if(dimension->slot.USR)  RebuildKey(file, STR_USR);
   elif(dimension->slot.RUN)  RebuildKey(file, STR_RUN);

     if(dimension->slot.LAY)  RebuildKey(file, STR_LAY);
   elif(dimension->slot.RUL)  RebuildKey(file, STR_RUL);
   elif(dimension->slot.REL)  RebuildKey(file, STR_REL);
   elif(dimension->slot.CON)  RebuildKey(file, STR_CON);
   elif(dimension->slot.ACT)  RebuildKey(file, STR_ACT);
   elif(dimension->slot.DIM)  RebuildKey(file, STR_DIM);

     if(dimension->slot.ON)   RebuildKey(file, STR_ON);
   elif(dimension->slot.OFF)  RebuildKey(file, STR_OFF);
   elif(dimension->slot.BKW)  RebuildKey(file, STR_BKW);
   elif(dimension->slot.FRW)  RebuildKey(file, STR_FRW);
   elif(dimension->slot.GRD)  RebuildKey(file, STR_GRD);
   elif(dimension->slot.CUT)  RebuildKey(file, STR_CUT);

   RebuildString(file, " %s", IDX2OBJ(dimension->object)->symbolic);

   if(dimension->argc > 1)
   {
      RebuildString(file, " %c%s", CHR_LEFTPARENT, dimension->argv[1]);
      for(i = 2; i < dimension->argc; i++)
         RebuildString(file, "%c %s", CHR_COMMA, dimension->argv[i]);
      RebuildString(file, "%c", CHR_RIGHTPARENT);
   }

   if(dimension->grade != GRD_TRUE || dimension->level != GRD_FALSE)
      RebuildString(file, " : %g", dimension->grade);

   if(dimension->level != GRD_FALSE)
      RebuildString(file, " : %g", dimension->level);

   if(!file)   /* rebuilding for explaination */
   {
      if(dimension->truth[0] == GRD_UNKNOWN)
         RebuildString(file, " [*");
      else
         RebuildString(file, "[%g", dimension->truth[0]);

      RebuildString(file, ", ");

      if(dimension->truth[1] == GRD_UNKNOWN)
         RebuildString(file, "*]");
      else
         RebuildString(file, "%g]", dimension->truth[1]);
   }

   RebuildString(file, "\n");
}


/* rebuild keyword in nice way */

FUNCTION(static void RebuildKey,
   (FILE *file, char *key),
   (file, key),
   FILE *file;
   char *key;
)
{
   RebuildString(file, "%c%s", toupper(*key), key + 1);
}

