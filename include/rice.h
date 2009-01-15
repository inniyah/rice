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
   File:   rice.h
   Author: Rene' Jager
   Update: January 4, 1993
   Info:   main include file for RICE, see file rice.doc
*/


/* prevent extra compilation */

#ifndef _RICE_H_
#define _RICE_H_


/* include header files */

#include <stdlib.h>
#include <string.h>


/* compiler characteristics */

#include <ricecomp.h>


/* define version and author */

#define RICE_NAME      "RICE"
#define RICE_VERSION   4.0
#define RICE_AUTHOR    "Ren\x82 Jager"
#define RICE_EMAIL     "R.Jager@ET.TUDelft.NL"


/* type definitions */

typedef RICE_PROTOTYPE(float (*RICE_NORM), (float, float));
typedef RICE_PROTOTYPE(void (*RICE_LINKER), (int, int, int, char *[], float *, int *));


/* linker macro's */

#define RICE_Linker(func)   RICE_FUNCTION(void func, \
(int rice_id, int rice_func, int rice_argc, char *rice_argv[], \
float *rice_grade, int *rice_num), (rice_id, rice_func, rice_argc, \
rice_argv, rice_grade, rice_num), int rice_id; int rice_func; \
int rice_argc; char *rice_argv[]; float *rice_grade; int *rice_num;)

#define RICE_Link(str, code) \
if(rice_func == ++(*rice_num)) \
{ \
   rice_argv[0] = str; \
   if(rice_argc) \
   { \
      code; \
   } \
   return; \
}


/* truth values */

#define RICE_FALSE     0.0
#define RICE_TRUE      1.0
#define RICE_UNKNOWN   (-1.0)


/* message types */

#define RICE_ERROR     1
#define RICE_WARNING   2
#define RICE_MESSAGE   3


/* argument macro's */

#define RICE_grade   (*rice_grade)
#define RICE_argc    rice_argc
#define RICE_argv    rice_argv
#define RICE_id      rice_id


/* adjustment macro's */

#define RICE_Explain(kb, typ, fct, dpt)   RICE_MERGE(rice_Explain, typ(kb, fct, dpt))
#define RICE_Redirect(kb, nam, fnc)       RICE_MERGE(rice_Redirect, nam(kb, fnc))
#define RICE_Set(kb, nam)                 RICE_MERGE(rice_Set, nam(kb, 1))
#define RICE_Reset(kb, nam)               RICE_MERGE(rice_Set, nam(kb, 0))
#define RICE_Switch(kb, nam)              RICE_MERGE(rice_Set, nam(kb, -1))
#define RICE_Use(kb, nam, num, ptr)       RICE_MERGE(rice_Use, nam(kb, num, ptr))


/* for C++ applications */

#ifdef __cplusplus
extern "C" {
#endif


/* redirection functions */

RICE_PROTOTYPE(int rice_RedirectAsk, (int, RICE_PROTOTYPE(void (*), (int, int, char *[], float *))));
RICE_PROTOTYPE(int rice_RedirectInform, (int, RICE_PROTOTYPE(void (*), (int, int, char *[], float *))));
RICE_PROTOTYPE(int rice_RedirectReport, (int, RICE_PROTOTYPE(void (*), (int, int, char *))));
RICE_PROTOTYPE(int rice_RedirectExplain, (int, RICE_PROTOTYPE(void (*), (int, char *))));
RICE_PROTOTYPE(int rice_RedirectProtect, (int, RICE_PROTOTYPE(void (*), (int))));
RICE_PROTOTYPE(int rice_RedirectAbandon, (int, RICE_PROTOTYPE(void (*), (void))));


/* set functions */

RICE_PROTOTYPE(int rice_SetAdaptive, (int, int));
RICE_PROTOTYPE(int rice_SetInteractive, (int, int));
RICE_PROTOTYPE(int rice_SetRecursive, (int, int));
RICE_PROTOTYPE(int rice_SetRepetitive, (int, int));
RICE_PROTOTYPE(int rice_SetSelective, (int, int));


/* use functions */

RICE_PROTOTYPE(int rice_UseLinker, (int, int, RICE_LINKER *));
RICE_PROTOTYPE(int rice_UseIntersection, (int, int, RICE_NORM *));
RICE_PROTOTYPE(int rice_UseUnion, (int, int, RICE_NORM *));


/* explaination functions */

RICE_PROTOTYPE(int rice_ExplainWhy, (int, char *, int));
RICE_PROTOTYPE(int rice_ExplainHow, (int, char *, int));


/* interfacing KB functions */

RICE_PROTOTYPE(int rice_AppendKB, (int, char *));
RICE_PROTOTYPE(int rice_ClearKB, (int));
RICE_PROTOTYPE(int rice_CompileKB, (int, char *));
RICE_PROTOTYPE(int rice_CopyKB, (int, int));
RICE_PROTOTYPE(int rice_DestroyKB, (int));
RICE_PROTOTYPE(int rice_InferKB, (int));
RICE_PROTOTYPE(int rice_LoadKB, (int, char *));
RICE_PROTOTYPE(int rice_MoveKB, (int, int));
RICE_PROTOTYPE(int rice_ProcessKB, (int, char *, char *));
RICE_PROTOTYPE(int rice_RebuildKB, (int, char *));
RICE_PROTOTYPE(int rice_SaveKB, (int, char *));
RICE_PROTOTYPE(int rice_SwapKB, (int, RICE_PROTOTYPE(void (*), (void))));


/* interfacing ES functions */

RICE_PROTOTYPE(int rice_CheckES, (int));
RICE_PROTOTYPE(int rice_CopyES, (int, int));
RICE_PROTOTYPE(int rice_CreateES, (void));
RICE_PROTOTYPE(int rice_DeleteES, (int));
RICE_PROTOTYPE(int rice_MoveES, (int, int));
RICE_PROTOTYPE(int rice_SwitchES, (int));


/* for C++ applications */

#ifdef __cplusplus
}
#endif


/* in case of upgrading include RICE 3.x compatible header file rice3x.h */

#ifdef RICE_UPGRADE
#   include <rice3x.h>
#endif


/* in case of C++ compiler also include RICE class if necessary */

#ifdef __cplusplus
#   ifndef _RICE_HPP_
#      include <rice.hpp>
#   endif
#endif


#endif /* _RICE_H_ */



