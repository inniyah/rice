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
   File:   global.c
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


/* kb variables */

USR_BASE *theBase = 0;

static int nrBases = 0;
static USR_BASE **baseList = 0;


/* redirection-functions */

FUNCTION(int RedirectAsk,
   (int index, PROTOTYPE(void (*func), (int, int, char *[], float *))),
   (index, func),
   int index;
   PROTOTYPE(void (*func), (int, int, char *[], float *));
)
{
   if(SwitchES(index))
      return -1;

   userAsk = func;

   return 0;
}


FUNCTION(int RedirectInform,
   (int index, PROTOTYPE(void (*func), (int, int, char *[], float *))),
   (index, func),
   int index;
   PROTOTYPE(void (*func), (int, int, char *[], float *));
)
{
   if(SwitchES(index))
      return -1;

   userInform = func;

   return 0;
}


FUNCTION(int RedirectReport,
   (int index, PROTOTYPE(void (*func), (int, int, char *))),
   (index, func),
   int index;
   PROTOTYPE(void (*func), (int, int, char *));
)
{
   if(SwitchES(index))
      return -1;

   userReport = func;

   return 0;
}


FUNCTION(int RedirectExplain,
   (int index, PROTOTYPE(void (*func), (int, char *))),
   (index, func),
   int index;
   PROTOTYPE(void (*func), (int, char *));
)
{
   if(SwitchES(index))
      return -1;

   userExplain = func;

   return 0;
}


FUNCTION(int RedirectProtect,
   (int index, PROTOTYPE(void (*func), (int))),
   (index, func),
   int index;
   PROTOTYPE(void (*func), (int));
)
{
   if(SwitchES(index))
      return -1;

   userProtect = func;

   return 0;
}


FUNCTION(int RedirectAbandon,
   (int index, PROTOTYPE(void (*func), (void))),
   (index, func),
   int index;
   PROTOTYPE(void (*func), (void));
)
{
   if(SwitchES(index))
      return -1;

   userAbandon = func;

   return 0;
}


/* use-functions */

FUNCTION(int UseLinker,
   (int index, int num, RICE_LINKER *run),
   (index, num, run),
   int index;
   int num;
   RICE_LINKER *run;
)
{
   if(SwitchES(index))
      return -1;

   nrUserRun = num;
   userRun = run;

   return 0;
}


FUNCTION(int UseIntersection,
   (int index, int num, RICE_NORM *and),
   (index, num, and),
   int index; int num; RICE_NORM *and;
)
{
   if(SwitchES(index))
      return -1;

   nrUserAnd = num;
   userAnd = and;

   return 0;
}


FUNCTION(int UseUnion,
   (int index, int num, RICE_NORM *or),
   (index, num, or),
   int index; int num; RICE_NORM *or;
)
{
   if(SwitchES(index))
      return -1;

   nrUserOr = num;
   userOr = or;

   return 0;
}


/* environment-dependent-functions */

FUNCTION(void Ask,
   (int argc, char *argv[], float *grade),
   (argc, argv, grade),
   int argc; char *argv[]; float *grade;
)
{
   do
   {
      if(userAsk)
         (*userAsk)(kbIndex, argc, argv, grade);
      else
      {
         printf("%s ", argv[0]);

         if(argc > 1)
         {
            int i;

            printf("(");

            for(i = 1; i < argc - 1; i++)
               printf("%s, ", argv[i]);

            printf("%s) ", argv[argc - 1]);
         }

         printf("? ");
         scanf("%g", grade);
      }
   }
   while((*grade < GRD_FALSE || GRD_TRUE < *grade) && *grade != GRD_UNKNOWN);
}


FUNCTION(void Inform,
   (int argc, char *argv[], float *grade),
   (argc, argv, grade),
   int argc; char *argv[]; float *grade;
)
{
   if(userInform)
      (*userInform)(kbIndex, argc, argv, grade);
   else
   {
      printf("%s ", argv[0]);

      if(argc > 1)
      {
         int i;

         printf("(");

         for(i = 1; i < argc - 1; i++)
            printf("%s, ", argv[i]);

         printf("%s) ", argv[argc - 1]);
      }

      printf("! %g\n", *grade);
   }
}


FUNCTION(void Report,
   (int type, char *format, ...),
   (va_alist),
   va_dcl
)
{
   char message[SIZ_LINE];
   va_list arguments;

   VARARGS(
      int type;
      char *format;
      ,
      VA_START(arguments, format);
      ,
      type = va_arg(arguments, int);
      format = va_arg(arguments, char *);
   );

   vsprintf(message, format, arguments);
   va_end(arguments);

   if(userReport)
      (*userReport)(kbIndex, type, message);
   else
   {
      switch(type)
      {
         case MSG_ERROR:
            printf("%s: %s\n", STR_ERROR, message);
            break;

         case MSG_WARNING:
            printf("%s: %s\n", STR_WARNING, message);
            break;

         default:
            printf("%s: %s\n", STR_MESSAGE, message);
            break;
      }
   }
}


FUNCTION(void Protect,
   (int status),
   (status),
   int status;
)
{
   if(userProtect)
      (*userProtect)(status);
}


FUNCTION(void Abandon,
   (void),
   (),
   /* nothing */
)
{
   if(userAbandon)
      (*userAbandon)();

   exit(1);
}


FUNCTION(void Run,
   (int link, int argc, char *argv[], float *grade),
   (link, argc, argv, grade),
   int link;
   int argc;
   char *argv[];
   float *grade;
)
{
   int count, index;

   if(!userRun)
      return;

   for(index = 0, count = 0, argv[0] = 0; index < nrUserRun && !argv[0]; index++)
      (*userRun[index])(kbIndex, link, argc, argv, grade, &count);
}


/* set-functions */

FUNCTION(int SetAdaptive,
   (int index, int act),
   (index, act),
   int index;
   int act;
)
{
   if(SwitchES(index))
      return -1;

   if(act < 0)
      adaptiveMode = !adaptiveMode;
   elif(act > 0)
      adaptiveMode = 1;
   else
      adaptiveMode = 0;

   return 0;
}


FUNCTION(int SetInteractive,
   (int index, int act),
   (index, act),
   int index;
   int act;
)
{
   if(SwitchES(index))
      return -1;

   if(act < 0)
      interactiveMode = !interactiveMode;
   elif(act > 0)
      interactiveMode = 1;
   else
      interactiveMode = 0;

   return 0;
}


FUNCTION(int SetRecursive,
   (int index, int act),
   (index, act),
   int index;
   int act;
)
{
   if(SwitchES(index))
      return -1;

   if(act < 0)
      recursiveMode = !recursiveMode;
   elif(act > 0)
      recursiveMode = 1;
   else
      recursiveMode = 0;

   return 0;
}


FUNCTION(int SetRepetitive,
   (int index, int act),
   (index, act),
   int index;
   int act;
)
{
   if(SwitchES(index))
      return -1;

   if(act < 0)
      repetitiveMode = !repetitiveMode;
   elif(act > 0)
      repetitiveMode = 1;
   else
      repetitiveMode = 0;

   return 0;
}


FUNCTION(int SetSelective,
   (int index, int act),
   (index, act),
   int index;
   int act;
)
{
   if(SwitchES(index))
      return -1;

   if(act < 0)
      selectiveMode = !selectiveMode;
   elif(act > 0)
      selectiveMode = 1;
   else
      selectiveMode = 0;

   return 0;
}


/* create kb */

FUNCTION(int CreateES,
   (void),
   (),
   /* nothing */
)
{
   int i;
   USR_BASE *aBase;

   ALLOC(aBase, 1, USR_BASE);

   aBase->object = 0;

   aBase->mode.interactive = 1;
   aBase->mode.recursive = 0;
   aBase->mode.repetitive = 1;
   aBase->mode.selective = 0;
   aBase->mode.adaptive = 0;

   aBase->function.ask = 0;
   aBase->function.inform = 0;
   aBase->function.report = 0;
   aBase->function.explain = 0;
   aBase->function.protect = 0;
   aBase->function.abandon = 0;
   aBase->function.and = 0;
   aBase->function.or = 0;
   aBase->function.run = 0;

   aBase->function.nrAnd = 0;
   aBase->function.nrOr = 0;
   aBase->function.nrRun = 0;

   for(i = 0; i < nrBases; i++)
      if(!baseList[i])
         break;

   if(i == nrBases)
   {
      nrBases++;
      REALLOC(baseList, nrBases, USR_BASE *);
   }

   theBase = baseList[i] = aBase;

   return theBase->index = ++i;
}


/* delete kb */

FUNCTION(int DeleteES,
   (int index),
   (index),
   int index;
)
{
   if(CheckES(index))
   {
      Report(MSG_WARNING, MSG_INVALID_BASE, index);
      return -1;
   }

   DestroyKB(index);
   FREE(baseList[--index]);
   baseList[index] = 0;

   return 0;
}


/* check kb */

FUNCTION(int CheckES,
   (int index),
   (index),
   int index;
)
{
   if(index < 1 || nrBases < index || !baseList[--index])
      return -1;

   return 0;
}


/* switch kb */

FUNCTION(int SwitchES,
   (int index),
   (index),
   int index;
)
{
   if(CheckES(index))
   {
      Report(MSG_WARNING, MSG_INVALID_BASE, index);
      return -1;
   }

   theBase = baseList[--index];

   return 0;
}


/* copy es */

FUNCTION(int CopyES,
   (int index1, int index2),
   (index1, index2),
   int index1;
   int index2;
)
{
   int index = 0;

   if(!index1)
      index = index1 = CreateES();
   else
      if(CheckES(index1))
         return -1;
      else
         DeleteES(index1);

   memcpy(&baseList[index1 - 1]->function, &baseList[index2 - 1]->function, sizeof(USR_FUNCTION));
   memcpy(&baseList[index1 - 1]->mode, &baseList[index2 - 1]->mode, sizeof(USR_MODE));

   if(CopyKB(index1, index2))
      return -1;

   /* success code or ES identifier when index1 was 0 */
   return index;
}


/* copy kb */

FUNCTION(int CopyKB,
   (int index1, int index2),
   (index1, index2),
   int index1;
   int index2;
)
{
   if(CheckES(index1) || SaveKB(index2, STR_SWAPFILE))
      return -1;

   if(LoadKB(index1, STR_SWAPFILE))
      return -1;

   if(remove(STR_SWAPFILE))
      return -1;

   return 0;
}


/* move es */

FUNCTION(int MoveES,
   (int index1, int index2),
   (index1, index2),
   int index1;
   int index2;
)
{
   int index = 0;

   if(!index1)
      index = index1 = CreateES();
   else
      if(CheckES(index1))
         return -1;
      else
         DeleteES(index1);

   memcpy(&baseList[index1 - 1]->function, &baseList[index2 - 1]->function, sizeof(USR_FUNCTION));
   memcpy(&baseList[index1 - 1]->mode, &baseList[index2 - 1]->mode, sizeof(USR_MODE));

   if(MoveKB(index1, index2))
      return -1;

   if(DeleteES(index2))
      return -1;

   /* success code or ES identifier when index1 was 0 */
   return index;
}


/* move kb */

FUNCTION(int MoveKB,
   (int index1, int index2),
   (index1, index2),
   int index1;
   int index2;
)
{
   if(CheckES(index2) || DestroyKB(index1))
      return -1;

   baseList[index1 - 1]->object = baseList[index2 - 1]->object;
   baseList[index1 - 1]->index = index1;
   baseList[index2 - 1]->object = 0;

   if(DestroyKB(index2))
      return -1;

   return 0;
}


/* clear kb */

FUNCTION(int ClearKB,
   (int index),
   (index),
   int index;
)
{
   int i;

   if(SwitchES(index))
      return -1;

   for(i = 1; i <= IDX2OBJ(0)->number; i++)
   {
      switch(IDX2OBJ(i)->type)
      {
         case TYP_FACT:
            if(IDX2OBJ(i)->status.ACTIVE)
            {
               IDX2FAC(i)->grade = GRD_UNKNOWN;
               IDX2FAC(i)->sumgrade = GRD_FALSE;
               IDX2FAC(i)->numgrade = 0;
            }
            break;

         case TYP_RULE:
            IDX2RUL(i)->slot.FIRED = 0;
            break;

         case TYP_RELATION:
            IDX2REL(i)->slot.FIRED = 0;
            break;

         case TYP_CONDITION:
            IDX2CON(i)->truth = GRD_UNKNOWN;
            break;

         case TYP_ACTION:
            IDX2ACT(i)->truth = GRD_UNKNOWN;
            break;

         case TYP_DIMENSION:
            IDX2DIM(i)->truth[0] = GRD_UNKNOWN;
            IDX2DIM(i)->truth[1] = GRD_UNKNOWN;
            break;
      }
   }

   return 0;
}


/* basic logic operators */

FUNCTION(float LukasiewiczAnd,
   (float g1, float g2),
   (g1, g2),
   float g1;
   float g2;
)
{
   return LAND(g1, g2);
}


FUNCTION(float LukasiewiczOr,
   (float g1, float g2),
   (g1, g2),
   float g1;
   float g2;
)
{
   return LOR(g1, g2);
}


FUNCTION(float ProbabilityAnd,
   (float g1, float g2),
   (g1, g2),
   float g1;
   float g2;
)
{
   return PAND(g1, g2);
}


FUNCTION(float ProbabilityOr,
   (float g1, float g2),
   (g1, g2),
   float g1;
   float g2;
)
{
   return POR(g1, g2);
}


FUNCTION(float ZadehAnd,
   (float g1, float g2),
   (g1, g2),
   float g1;
   float g2;
)
{
   return ZAND(g1, g2);
}


FUNCTION(float ZadehOr,
   (float g1, float g2),
   (g1, g2),
   float g1;
   float g2;
)
{
   return ZOR(g1, g2);
}




