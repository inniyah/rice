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
   File:   save.c
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


/* macro's */

#define WriteObject(obj,typ,fil) \
{ \
   fwrite(obj, sizeof(typ), 1, fil); \
}

#define WriteArray(arr,fil) \
{ \
   int __num = arr[0] + 1; \
   fwrite(&__num, sizeof(int), 1, fil); \
   fwrite(arr, sizeof(int), __num, fil); \
}

#define WriteString(str,fil) \
{ \
   int __num = strlen(str) + 1; \
   fwrite(&__num, sizeof(int), 1, fil); \
   fwrite(str, sizeof(char), __num, fil); \
}


/* prototypes of static functions */

PROTOTYPE(static void SaveObjectList, (FILE *));
PROTOTYPE(static void SaveObject, (FILE *, OBJ_OBJECT *));

PROTOTYPE(static void SaveBase, (FILE *, OBJ_BASE *));
PROTOTYPE(static void SaveLayer, (FILE *, OBJ_LAYER *));
PROTOTYPE(static void SaveRule, (FILE *, OBJ_RULE *));
PROTOTYPE(static void SaveRelation, (FILE *, OBJ_RELATION *));
PROTOTYPE(static void SaveFact, (FILE *, OBJ_FACT *));
PROTOTYPE(static void SaveCondition, (FILE *, OBJ_CONDITION *));
PROTOTYPE(static void SaveAction, (FILE *, OBJ_ACTION *));
PROTOTYPE(static void SaveDimension, (FILE *, OBJ_DIMENSION *));


/* save kb */

FUNCTION(int SaveKB,
   (int index, char *filename),
   (index, filename),
   int index;
   char *filename;
)
{
   FILE *file;

   if(SwitchES(index))
      return -1;

   if(!(file = fopen(filename, "wb")))
   {
      Report(MSG_ERROR, MSG_FILE_OPEN, filename);
      return -1;
   }

   fwrite(STR_FILEMARK, sizeof(char), sizeof(STR_FILEMARK), file);

   SaveObjectList(file);

   if(fclose(file))
   {
      Report(MSG_ERROR, MSG_FILE_CLOSE, filename);
      return -1;
   }

   return 0;
}


/* static save-functions */

FUNCTION(static void SaveObjectList,
   (FILE *file),
   (file),
   FILE *file;
)
{
   int i, number;

   number = objectList[0]->number + 1;

   fwrite(&number, sizeof(int), 1, file);

   for(i = 0; i < number; i++)
      SaveObject(file, objectList[i]);
}


FUNCTION(static void SaveObject,
   (FILE *file, OBJ_OBJECT *object),
   (file, object),
   FILE *file;
   OBJ_OBJECT *object;
)
{
   fwrite(&object->type, sizeof(int), 1, file);

   switch(object->type)
   {
      case TYP_BASE:
         SaveBase(file, OBJ2BAS(object));
         break;

      case TYP_LAYER:
         SaveLayer(file, OBJ2LAY(object));
         break;

      case TYP_RULE:
         SaveRule(file, OBJ2RUL(object));
         break;

      case TYP_RELATION:
         SaveRelation(file, OBJ2REL(object));
         break;

      case TYP_FACT:
         SaveFact(file, OBJ2FAC(object));
         break;

      case TYP_CONDITION:
         SaveCondition(file, OBJ2CON(object));
         break;

      case TYP_ACTION:
         SaveAction(file, OBJ2ACT(object));
         break;

      case TYP_DIMENSION:
         SaveDimension(file, OBJ2DIM(object));
         break;

      default:
         Report(MSG_ERROR, MSG_BUG_INTERNAL);
         Abandon();
   }
}


FUNCTION(static void SaveBase,
   (FILE *file, OBJ_BASE *base),
   (file, base),
   FILE *file;
   OBJ_BASE *base;
)
{
   WriteObject(base, OBJ_BASE, file);
   WriteArray(base->layer, file);
   WriteString(base->symbolic, file);
}


FUNCTION(static void SaveLayer,
   (FILE *file, OBJ_LAYER *layer),
   (file, layer),
   FILE *file;
   OBJ_LAYER *layer;
)
{
   WriteObject(layer, OBJ_LAYER, file);
   WriteArray(layer->init, file);
   WriteArray(layer->data, file);
   WriteArray(layer->goal, file);
   WriteArray(layer->rule, file);
   WriteArray(layer->relation, file);
   WriteString(layer->symbolic, file);
}


FUNCTION(static void SaveRule,
   (FILE *file, OBJ_RULE *rule),
   (file, rule),
   FILE *file;
   OBJ_RULE *rule;
)
{
   WriteObject(rule, OBJ_RULE, file);
   WriteArray(rule->condition, file);
   WriteArray(rule->action, file);
   WriteString(rule->symbolic, file);
}


FUNCTION(static void SaveRelation,
   (FILE *file, OBJ_RELATION *relation),
   (file, relation),
   FILE *file;
   OBJ_RELATION *relation;
)
{
   WriteObject(relation, OBJ_RELATION, file);
   WriteArray(relation->dimension, file);
   WriteString(relation->symbolic, file);
}


FUNCTION(static void SaveFact,
   (FILE *file, OBJ_FACT *fact),
   (file, fact),
   FILE *file;
   OBJ_FACT *fact;
)
{
   WriteObject(fact, OBJ_FACT, file);
   WriteArray(fact->backward, file);
   WriteArray(fact->forward, file);
   WriteString(fact->symbolic, file);
}


FUNCTION(static void SaveCondition,
   (FILE *file, OBJ_CONDITION *condition),
   (file, condition),
   FILE *file;
   OBJ_CONDITION *condition;
)
{
   int i;

   WriteObject(condition, OBJ_CONDITION, file);
   WriteString(condition->symbolic, file);
   fwrite(&condition->argc, sizeof(int), 1, file);
   for(i = 1; i < condition->argc; i++)
      WriteString(condition->argv[i], file);
}


FUNCTION(static void SaveAction,
   (FILE *file, OBJ_ACTION *action),
   (file, action),
   FILE *file;
   OBJ_ACTION *action;
)
{
   int i;

   WriteObject(action, OBJ_ACTION, file);
   WriteString(action->symbolic, file);
   fwrite(&action->argc, sizeof(int), 1, file);
   for(i = 1; i < action->argc; i++)
      WriteString(action->argv[i], file);
}


FUNCTION(static void SaveDimension,
   (FILE *file, OBJ_DIMENSION *dimension),
   (file, dimension),
   FILE *file;
   OBJ_DIMENSION *dimension;
)
{
   int i;

   WriteObject(dimension, OBJ_DIMENSION, file);
   WriteString(dimension->symbolic, file);
   fwrite(&dimension->argc, sizeof(int), 1, file);
   for(i = 1; i < dimension->argc; i++)
      WriteString(dimension->argv[i], file);
}


