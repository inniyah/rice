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
   File:   rice3x.h
   Author: Rene' Jager
   Update: March 29, 1992
   Info:   update include file for RICE 3.x, see file rice3x.doc
*/


/* prevent extra compilation */

#ifndef _RICE3X_H_
#define _RICE3X_H_


/* include rice.h */

#include <rice.h>

                 
/* redefine KB macro's and functions */

#define CompileKB(str)   rice3x_CompileKB(str)
#define LoadKB(str)      rice3x_LoadKB(str)

#define SaveKB(str)      rice_SaveKB(1, str)
#define RebuildKB(str)   rice_RebuildKB(1, str)
#define InferKB()        rice_InferKB(1)
#define DestroyKB()      rice_DestroyKB(1)
#define ClearKB()        rice_ClearKB(1)


/* redefine Redirect macro's and functions */

#define Redirect(nam, fnc)     Redirect##nam(fnc)

#define RedirectAbandon(fnc)   rice_RedirectAbandon(1, fnc)
#define RedirectProtect(fnc)   rice_RedirectProtect(1, fnc)

#define RedirectAsk(fnc) \
{ \
   rice3x_CreateES(); \
   rice3x_askPtr = fnc; \
   rice_RedirectAsk(1, rice3x_AskFnc); \
}

#define RedirectInform(fnc) \
{ \
   rice3x_CreateES(); \
   rice3x_informPtr = fnc; \
   rice_RedirectInform(1, rice3x_InformFnc); \
}

#define RedirectReport(fnc) \
{ \
   rice3x_CreateES(); \
   rice3x_reportPtr = fnc; \
   rice_RedirectReport(1, rice3x_ReportFnc); \
}

#define RedirectAnd(fnc) \
{ \
   rice3x_CreateES(); \
   intersectionPtr = fnc; \
   rice_UseIntersection(1, 1, &rice3x_intersectionPtr); \
}

#define RedirectOr(fnc) \
{ \
   rice3x_CreateES(); \
   unionPtr = fnc; \
   rice_UseUnion(1, 1, &rice3x_unionPtr); \
}


/* redefine Set, Reset and Switch macro's and functions */

#define Set(nam)              rice_Set##nam(1, 1)
#define Reset(nam)            rice_Set##nam(1, 0)
#define Switch(nam)           rice_Set##nam(1, -1)

#define SetAdaptive()         rice_SetAdaptive(1,  1)
#define ResetAdaptive()       rice_SetAdaptive(1,  0)
#define SwitchAdaptive()      rice_SetAdaptive(1, -1)

#define SetRepetitive()       rice_SetRepetitive(1,  1)
#define ResetRepetitive()     rice_SetRepetitive(1,  0)
#define SwitchRepetitive()    rice_SetRepetitive(1, -1)

#define SetInteractive()      rice_SetInteractive(1,  1)
#define ResetInteractive()    rice_SetInteractive(1,  0)
#define SwitchInteractive()   rice_SetInteractive(1, -1)

#define SetRecursive()        rice_SetRecursive(1,  1)
#define ResetRecursive()      rice_SetRecursive(1,  0)
#define SwitchRecursive()     rice_SetRecursive(1, -1)

#define SetSelective()        rice_SetSelective(1,  1)
#define ResetSelective()      rice_SetSelective(1,  0)
#define SwitchSelective()     rice_SetSelective(1, -1)


/* declare hidden Ask, Inform and Report function and pointer */

RICE_PROTOTYPE(extern void (*rice3x_askPtr), (char *, float *));
RICE_PROTOTYPE(extern void (*rice3x_informPtr), (char *, float *));
RICE_PROTOTYPE(extern void (*rice3x_reportPtr), (int, char *, void *));

RICE_PROTOTYPE(extern void rice3x_AskFnc, (int, int, char *[], float *));
RICE_PROTOTYPE(extern void rice3x_InformFnc, (int, int, char *[], float *));
RICE_PROTOTYPE(extern void rice3x_ReportFnc, (int, int, char *));


/* declare external main hidden Linker function and pointer to it */

extern RICE_LINKER rice3x_linkerPtr;

RICE_PROTOTYPE(void rice3x_linkerFnc, (int, int, int, char *[], float *, int *));


/* declare external hidden And and Or function pointers */

extern RICE_NORM rice3x_intersectionPtr, rice3x_unionPtr;


/* external upgrade function */

RICE_PROTOTYPE(extern void rice3x_CreateES, (void));
RICE_PROTOTYPE(extern int rice3x_CompileKB, (char *));
RICE_PROTOTYPE(extern int rice3x_LoadKB, (char *));


#endif /* _RICE3X_H_ */


