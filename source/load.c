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
   File:   load.c
   Author: Rene' Jager
   Update: January 4, 1993
   Info:   source file for RICE
*/


/* hidden include files */

#include "include.h"
#include "define.h"
#include "type.h"
#include "function.h"
#include "compile.h"
#include "variable.h"


/* macro's */

#define ReadObject(obj,typ,fil) \
{ \
   ALLOC(obj, 1, typ); \
   fread(obj, sizeof(typ), 1, fil); \
}

#define ReadArray(arr,fil) \
{ \
   int __num; \
   fread(&__num, sizeof(int), 1, fil); \
   ALLOC(arr, __num, int); \
   fread(arr, sizeof(int), __num, fil); \
}

#define ReadString(str,fil) \
{ \
   int __num; \
   fread(&__num, sizeof(int), 1, fil); \
   ALLOC(str, __num, char); \
   fread(str, sizeof(char), __num, fil); \
}


/* prototypes of statis functions */

PROTOTYPE(static void          LoadObjectList, (FILE *));
PROTOTYPE(static OBJ_OBJECT    *LoadObject,    (FILE *));

PROTOTYPE(static OBJ_BASE      *LoadBase,      (FILE *));
PROTOTYPE(static OBJ_LAYER     *LoadLayer,     (FILE *));
PROTOTYPE(static OBJ_RULE      *LoadRule,      (FILE *));
PROTOTYPE(static OBJ_RELATION  *LoadRelation,  (FILE *));
PROTOTYPE(static OBJ_FACT      *LoadFact,      (FILE *));
PROTOTYPE(static OBJ_CONDITION *LoadCondition, (FILE *));
PROTOTYPE(static OBJ_ACTION    *LoadAction,    (FILE *));
PROTOTYPE(static OBJ_DIMENSION *LoadDimension, (FILE *));

PROTOTYPE(static void LinkFacts, (void));


/* add object to list: should be in file compile2.c, but increases
   executables size because linker includes compile1.obj and compile2.obj
*/

FUNCTION(void AddObjectToList,
   (OBJ_OBJECT *object),
   (object),
   OBJ_OBJECT *object;
)
{
   int number;

   if(!objectList)
   {
      number = 0;
      ALLOC(objectList, number + 1, OBJ_OBJECT *);
   }
   else
   {
      objectList[0]->number++;
      number = objectList[0]->number;
      REALLOC(objectList, number + 1, OBJ_OBJECT *);
   }

   object->number = number;
   objectList[number] = object;
}


/* compile fact: should be in file compile2.c, but increases executables
   size because linker included compile1.obj and compile2.obj
*/

FUNCTION(OBJ_FACT *CompileFact,
   (char *argument),
   (argument),
   char *argument;
)
{
   register int i;
   OBJ_FACT *fact;

   for(i=1; i<=objectList[0]->number; i++)
      if(objectList[i]->type == TYP_FACT)
         if(!strcmp(objectList[i]->symbolic, argument))
            return IDX2FAC(i);

   ALLOC(fact, 1, OBJ_FACT);
   ALLOC(fact->forward, 1, int);
   ALLOC(fact->backward, 1, int);
   ALLOC(fact->symbolic, strlen(argument) + 1, char);

   memset(&fact->status, 0, sizeof(PRP_OBJECT));
   memset(&fact->slot, 0, sizeof(PRP_FACT));

   fact->type = TYP_FACT;
   fact->status.ACTIVE = 1;
   fact->grade = GRD_UNKNOWN;
   fact->sumgrade = GRD_FALSE;
   fact->numgrade = 0;
   fact->forward[0] = 0;
   fact->backward[0] = 0;
   fact->link = 0;

   strcpy(fact->symbolic, argument);

   AddObjectToList(FAC2OBJ(fact));

   return fact;
}


/* link facts */

FUNCTION(static void LinkFacts,
   (void),
   (),
   /* nothing */
)
{
   char *symbolic;
   int i, count, offset, index;

   if(!userRun)
      return;

   for(index = 0, i = 0, count = 0, offset = 0; index < nrUserRun; index++)
   {
      do
      {
         count = offset;
         symbolic = 0;

         (*userRun[index])(kbIndex, ++i, 0, &symbolic, 0, &count);

         if(symbolic)
         {
            OBJ_FACT *fact = CompileFact(symbolic);
            fact->slot.CODE = 1;
            fact->link = count;
         }
         else
            i--;
      }
      while(symbolic);

      (*userRun[index])(kbIndex, -1, 0, 0, 0, &offset);
   }

   for(i = 1; i <= objectList[0]->number; i++)
      if(objectList[i]->type == TYP_FACT)
         if(OBJ2FAC(objectList[i])->slot.CODE && !OBJ2FAC(objectList[i])->link)
            Report(MSG_WARNING, MSG_UNCODED_FACT, objectList[i]->symbolic);
}

/* main-load function */

FUNCTION(int LoadKB,
   (int index, char *filename),
   (index, filename),
   int index;
   char *filename;
)
{
   FILE *file;
   char ident[sizeof(STR_FILEMARK)];

   if(SwitchES(index))
      return -1;

   if(!(file = fopen(filename, "rb")))
   {
      Report(MSG_ERROR, MSG_FILE_OPEN, filename);
      return -1;
   }

   fread(ident, sizeof(char), sizeof(STR_FILEMARK), file);
   if(strcmp(ident, STR_FILEMARK))
   {
      Report(MSG_ERROR, MSG_INVALID_FILE, file);
      return -1;
   }

   DestroyKB(index);
   LoadObjectList(file);
   LinkFacts();

   if(fclose(file))
   {
      Report(MSG_ERROR, MSG_FILE_CLOSE, filename);
      return -1;
   }

   return 0;
}


/* static load-functions */

FUNCTION(static void LoadObjectList,
   (FILE *file),
   (file),
   FILE *file;
)
{
   int i, number;

   fread(&number, sizeof(int), 1, file);
   ALLOC(objectList, number, OBJ_OBJECT *);

   for(i = 0; i < number; i++)
      objectList[i] = LoadObject(file);
}


FUNCTION(static OBJ_OBJECT *LoadObject,
   (FILE *file),
   (file),
   FILE *file;
)
{
   int type;

   fread(&type, sizeof(int), 1, file);

   switch(type) {

      case TYP_BASE:
         return BAS2OBJ(LoadBase(file));

      case TYP_LAYER:
         return LAY2OBJ(LoadLayer(file));

      case TYP_RULE:
         return RUL2OBJ(LoadRule(file));

      case TYP_RELATION:
         return REL2OBJ(LoadRelation(file));

      case TYP_FACT:
         return FAC2OBJ(LoadFact(file));

      case TYP_CONDITION:
         return CON2OBJ(LoadCondition(file));

      case TYP_ACTION:
         return ACT2OBJ(LoadAction(file));

      case TYP_DIMENSION:
         return DIM2OBJ(LoadDimension(file));

      default:
         Report(MSG_ERROR, MSG_BUG_INTERNAL);
         Abandon();
   }

   return NULL;
}


FUNCTION(static OBJ_BASE *LoadBase,
   (FILE *file),
   (file),
   FILE *file;
)
{
   OBJ_BASE *base;

   ReadObject(base, OBJ_BASE, file);
   ReadArray(base->layer, file);
   ReadString(base->symbolic, file);

   return base;
}


FUNCTION(static OBJ_LAYER *LoadLayer,
   (FILE *file),
   (file),
   FILE *file;
)
{
   OBJ_LAYER *layer;

   ReadObject(layer, OBJ_LAYER, file);
   ReadArray(layer->init, file);
   ReadArray(layer->data, file);
   ReadArray(layer->goal, file);
   ReadArray(layer->rule, file);
   ReadArray(layer->relation, file);
   ReadString(layer->symbolic, file);

   return layer;
}


FUNCTION(static OBJ_RULE *LoadRule,
   (FILE *file),
   (file),
   FILE *file;
)
{
   OBJ_RULE *rule;

   ReadObject(rule, OBJ_RULE, file);
   ReadArray(rule->condition, file);
   ReadArray(rule->action, file);
   ReadString(rule->symbolic, file);

   return rule;
}


FUNCTION(static OBJ_RELATION *LoadRelation,
   (FILE *file),
   (file),
   FILE *file;
)
{
   OBJ_RELATION *relation;

   ReadObject(relation, OBJ_RELATION, file);
   ReadArray(relation->dimension, file);
   ReadString(relation->symbolic, file);

   return relation;
}


FUNCTION(static OBJ_FACT *LoadFact,
   (FILE *file),
   (file),
   FILE *file;
)
{
   OBJ_FACT *fact;

   ReadObject(fact, OBJ_FACT, file);
   ReadArray(fact->backward, file);
   ReadArray(fact->forward, file);
   ReadString(fact->symbolic, file);

   return fact;
}


FUNCTION(static OBJ_CONDITION *LoadCondition,
   (FILE *file),
   (file),
   FILE *file;
)
{
   register int i;
   OBJ_CONDITION *condition;

   ReadObject(condition, OBJ_CONDITION, file);
   ReadString(condition->symbolic, file);
   fread(&condition->argc, sizeof(int), 1, file);

   if(condition->argc)
   {
      ALLOC(condition->argv, condition->argc + 1, char *);
      condition->argv[0] = 0;
      for(i = 1; i < condition->argc; i++)
         ReadString(condition->argv[i], file);
   }

   if(condition->slot.AND)
   {
      if(condition->slot.LHSL)
         condition->norm = LukasiewiczAnd;
      elif(condition->slot.LHSP)
         condition->norm = ProbabilityAnd;
      elif(condition->slot.LHSU)
      {
         if(condition->user >= nrUserAnd)
            Report(MSG_ERROR, MSG_NORM_UNAVAIL, condition->user);
         condition->norm = userAnd[condition->user];
      }
      else
        condition->norm = ZadehAnd;   /* default condition norm */
   }
   elif(condition->slot.OR)
   {
      if(condition->slot.LHSL)
         condition->norm = LukasiewiczOr;
      elif(condition->slot.LHSP)
         condition->norm = ProbabilityOr;
      elif(condition->slot.LHSU)
      {
         if(condition->user >= nrUserOr)
            Report(MSG_ERROR, MSG_NORM_UNAVAIL, condition->user);
         condition->norm = userOr[condition->user];
      }
      else
        condition->norm = ZadehOr;   /* default condition norm */
   }

   return condition;
}


FUNCTION(static OBJ_ACTION *LoadAction,
   (FILE *file),
   (file),
   FILE *file;
)
{
   register int i;
   OBJ_ACTION *action;

   ReadObject(action, OBJ_ACTION, file);
   ReadString(action->symbolic, file);
   fread(&action->argc, sizeof(int), 1, file);

   if(action->argc)
   {
      ALLOC(action->argv, action->argc + 1, char *);
      action->argv[0] = 0;
      for(i = 1; i < action->argc; i++)
         ReadString(action->argv[i], file);
   }

   if(action->slot.RHSL)
      action->norm = LukasiewiczAnd;
   elif(action->slot.RHSZ)
      action->norm = ZadehAnd;
   elif(action->slot.RHSU)
   {
      if(action->user >= nrUserAnd)
         Report(MSG_ERROR, MSG_NORM_UNAVAIL, action->user);
      action->norm = userAnd[action->user];
   }
   else
     action->norm = ProbabilityAnd;   /* default action norm */

   return action;
}


FUNCTION(static OBJ_DIMENSION *LoadDimension,
   (FILE *file),
   (file),
   FILE *file;
)
{
   register int i;
   OBJ_DIMENSION *dimension;

   ReadObject(dimension, OBJ_DIMENSION, file);
   ReadString(dimension->symbolic, file);
   fread(&dimension->argc, sizeof(int), 1, file);

   if(dimension->argc)
   {
      ALLOC(dimension->argv, dimension->argc + 1, char *);
      dimension->argv[0] = 0;
      for(i = 1; i < dimension->argc; i++)
         ReadString(dimension->argv[i], file);
   }

   if(dimension->slot.LHSL)
      dimension->norm[0] = LukasiewiczAnd;
   elif(dimension->slot.LHSP)
      dimension->norm[0] = ProbabilityAnd;
   elif(dimension->slot.LHSU)
   {
      if(dimension->user[0] >= nrUserAnd)
         Report(MSG_ERROR, MSG_NORM_UNAVAIL, dimension->user[0]);
      dimension->norm[0] = userAnd[dimension->user[0]];
   }
   else
     dimension->norm[0] = ZadehAnd;   /* default condition norm */

   if(dimension->slot.RHSL)
      dimension->norm[1] = LukasiewiczAnd;
   elif(dimension->slot.RHSZ)
      dimension->norm[1] = ZadehAnd;
   elif(dimension->slot.RHSU)
   {
      if(dimension->user[1] >= nrUserAnd)
         Report(MSG_ERROR, MSG_NORM_UNAVAIL, dimension->user[1]);
      dimension->norm[1] = userAnd[dimension->user[1]];
   }
   else
     dimension->norm[1] = ProbabilityAnd;   /* default action norm */

   return dimension;
}


