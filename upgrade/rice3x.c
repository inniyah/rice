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
   File:   rice3x.c
   Author: Rene' Jager
   Update: March 29, 1992
   Info:   update source file for RICE 3.x, see file rice3.doc
*/


/* include update include file */

#include <rice3x.h>


/* include code file of RICE 3.x */

#include "rice.cod"


/* include link file of RICE 3.x into hidden linker function */

RICE_LINKER rice3x_linkerPtr;

RICE_Linker(rice3x_LinkerFnc)
{

#define LINK   RICE_Link
#define link   RICE_Link
#define Link   RICE_Link

#define GRADE   (*rice_grade)
#define grade   rice_grade

#include "rice.lnk"

#undef LINK
#undef link
#undef Link

#undef GRADE
#undef grade

}


/* global hidden pointers to linker, intersection and union function  */

RICE_LINKER rice3x_linkerPtr;

RICE_NORM rice3x_intersectionPtr, rice3x_unionPtr;


/* hidden create function */

RICE_FUNCTION(void rice3x_CreateES,
   (void),
   (),
   /* nothing */
)
{
   if(rice_CheckES(1))
   {
      rice_CreateES();
      rice3x_linkerPtr = rice3x_LinkerFnc;
      rice_UseLinker(1, 1, &rice3x_linkerPtr);
   }
}

RICE_FUNCTION(int rice3x_CompileKB,
   (char *str),
   (str),
   char *str
)
{
   rice3x_CreateES();
   return (rice_CompileKB(1, str) < 0);
}


RICE_FUNCTION(int rice3x_LoadKB,
   (char *str),
   (str),
   char *str
)
{
   rice3x_CreateES();
   return (rice_LoadKB(1, str) < 0);
}


/* hidden Ask, Inform and Report functions */

RICE_PROTOTYPE(void (*rice3x_askPtr), (char *, float *)) = 0;
RICE_PROTOTYPE(void (*rice3x_informPtr), (char *, float *)) = 0;
RICE_PROTOTYPE(void (*rice3x_reportPtr), (int, char *, void *)) = 0;


RICE_FUNCTION(void rice3x_AskFnc,
   (int kb, int argc, char *argv[], float *grade),
   (kb, argc, argv, grade),
   int kb;
   int argc;
   char *argv[];
   float *grade;
)
{
   if(rice3x_askPtr)
      (*rice3x_askPtr)(argv[0], grade);
}


RICE_FUNCTION(void rice3x_InformFnc,
   (int kb, int argc, char *argv[], float *grade),
   (kb, argc, argv, grade),
   int kb;
   int argc;
   char *argv[];
   float *grade;
)
{
   if(rice3x_informPtr)
      (*rice3x_informPtr)(argv[0], grade);
}


RICE_FUNCTION(void rice3x_ReportFnc,
   (int kb, int type, char *msg),
   (kb, type, msg),
   int kb;
   int type;
   char *msg;
)
{
   if(rice3x_reportPtr)
      (*rice3x_reportPtr)(type, msg, 0);
}


/* hidden redirect And and Or function pointers */

RICE_NORM rice3x_intersectionPtr, rice3x_unionPtr;



