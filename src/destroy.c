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
   File:   destroy.c
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


/* prototypes of static functions */

PROTOTYPE(static void DestroyObjectList, (void));
PROTOTYPE(static void DestroyObject, (OBJ_OBJECT *));

PROTOTYPE(static void DestroyBase, (OBJ_BASE *));
PROTOTYPE(static void DestroyLayer, (OBJ_LAYER *));
PROTOTYPE(static void DestroyRule, (OBJ_RULE *));
PROTOTYPE(static void DestroyRelation, (OBJ_RELATION *));
PROTOTYPE(static void DestroyFact, (OBJ_FACT *));
PROTOTYPE(static void DestroyCondition, (OBJ_CONDITION *));
PROTOTYPE(static void DestroyAction, (OBJ_ACTION *));
PROTOTYPE(static void DestroyDimension, (OBJ_DIMENSION *));


/* main destroy-function */

FUNCTION(int DestroyKB,
   (int index),
   (index),
   int index;
)
{
   if(SwitchES(index))
      return -1;

   DestroyObjectList();

   return 0;
}


/* static destroy-functions */

FUNCTION(static void DestroyObjectList,
   (void),
   (),
   /* nothing */
)
{
   register int i;
   int number;

   if(!objectList)
      return;

   number = objectList[0]->number;

   for(i = 0; i <= number; i++)
      DestroyObject(objectList[i]);

   FREE(objectList);

   objectList = 0;
}


FUNCTION(static void DestroyObject,
   (OBJ_OBJECT *object),
   (object),
   OBJ_OBJECT *object;
)
{
   switch(object->type) {

      case TYP_BASE:
         DestroyBase(OBJ2BAS(object));
         break;

      case TYP_LAYER:
         DestroyLayer(OBJ2LAY(object));
         break;

      case TYP_RULE:
         DestroyRule(OBJ2RUL(object));
         break;

      case TYP_RELATION:
         DestroyRelation(OBJ2REL(object));
         break;

      case TYP_FACT:
         DestroyFact(OBJ2FAC(object));
         break;

      case TYP_CONDITION:
         DestroyCondition(OBJ2CON(object));
         break;

      case TYP_ACTION:
         DestroyAction(OBJ2ACT(object));
         break;

      case TYP_DIMENSION:
         DestroyDimension(OBJ2DIM(object));
         break;

      default:
         Report(MSG_ERROR, MSG_BUG_INTERNAL);
         Abandon();
   }
}


FUNCTION(static void DestroyBase,
   (OBJ_BASE *base),
   (base),
   OBJ_BASE *base;
)
{
   if(!base)
      return;

   FREE(base->layer);
   FREE(base->symbolic);

   FREE(base);
}


FUNCTION(static void DestroyLayer,
   (OBJ_LAYER *layer),
   (layer),
   OBJ_LAYER *layer;
)
{
   if(!layer)
      return;

   FREE(layer->init);
   FREE(layer->data);
   FREE(layer->goal);
   FREE(layer->rule);
   FREE(layer->relation);
   FREE(layer->symbolic);

   FREE(layer);
}


FUNCTION(static void DestroyRule,
   (OBJ_RULE *rule),
   (rule),
   OBJ_RULE *rule;
)
{
   if(!rule)
      return;

   FREE(rule->condition);
   FREE(rule->action);

   FREE(rule);
}


FUNCTION(static void DestroyRelation,
   (OBJ_RELATION *relation),
   (relation),
   OBJ_RELATION *relation;
)
{
   if(!relation)
      return;

   FREE(relation->dimension);
   FREE(relation->symbolic);

   FREE(relation);
}


FUNCTION(static void DestroyFact,
   (OBJ_FACT *fact),
   (fact),
   OBJ_FACT *fact;
)
{
   if(!fact)
      return;

   FREE(fact->symbolic);

   FREE(fact);
}


FUNCTION(static void DestroyCondition,
   (OBJ_CONDITION *condition),
   (condition),
   OBJ_CONDITION *condition;
)
{
   if(!condition)
      return;

   FREE(condition->symbolic);

   if(condition->argc)
   {
      while(--condition->argc)
         FREE(condition->argv[condition->argc]);
      FREE(condition->argv);
   }

   FREE(condition);
}


FUNCTION(static void DestroyAction,
   (OBJ_ACTION *action),
   (action),
   OBJ_ACTION *action;
)
{
   if(!action)
      return;

   FREE(action->symbolic);

   if(action->argc)
   {
      while(--action->argc)
         FREE(action->argv[action->argc]);
      FREE(action->argv);
   }

   FREE(action);
}


FUNCTION(static void DestroyDimension,
   (OBJ_DIMENSION *dimension),
   (dimension),
   OBJ_DIMENSION *dimension;
)
{
   if(!dimension)
      return;

   FREE(dimension->symbolic);

   if(dimension->argc)
   {
      while(--dimension->argc)
         FREE(dimension->argv[dimension->argc]);
      FREE(dimension->argv);
   }

   FREE(dimension);
}


