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
   File:   riceeasy.h
   Author: Rene' Jager
   Update: December 30, 1992
   Info:   include file for easy use of RICE, see file rice.doc
*/


/* prevent unnecessary compilation */

#ifndef _RICEEASY_H_
#define _RICEEASY_H_


/* include rice.h */

#include <rice.h>


/* truth constants */

#if defined(TRUE) || defined(FALSE) || defined(UNKNOWN)
#   error RICE easy macro's conflict with environment.
#endif

#define TRUE      RICE_TRUE
#define FALSE     RICE_FALSE
#define UNKNOWN   RICE_UNKNOWN


/* message constants */

#if defined(ERROR) || defined(WARNING) || defined(MESSAGE)
#   error RICE easy macro's conflict with environment.
#endif

#define ERROR     RICE_ERROR
#define WARNING   RICE_WARNING
#define MESSAGE   RICE_MESSAGE


/* linker macro's */

#if defined(NORM) || defined(LINKER) || defined(Linker) || defined(Link)
#   error RICE easy macro's conflict with environment.
#endif

#define NORM     RICE_NORM
#define LINKER   RICE_LINKER
#define Linker   RICE_Linker
#define Link     RICE_Link


/* arguments macro's */

#if defined(grade) || defined(argc) || defined(argv)
#   error RICE easy macro's conflict with environment.
#endif

#define GRADE   RICE_grade
#define ARGC    RICE_argc
#define ARGV    RICE_argv


/* adjustment macro's */

#if defined(Set) || defined(Reset) || defined(Switch)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(Redirect) || defined(Use) || defined(Explain)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(SetAdaptive) || defined(ResetAdaptive) || defined(SwitchAdaptive)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(SetRepetitive) || defined(ResetRepetitive) || defined(SwitchRepetitive)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(SetInteractive) || defined(ResetInteractive) || defined(SwitchInteractive)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(SetRecursive) || defined(ResetRecursive) || defined(SwitchRecursive)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(SetSelective) || defined(ResetSelective) || defined(SwitchSelective)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(UseLinker) || defined(UseIntersection) || defined(UseUnion)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(ExplainHow) || defined(ExplainWhy)
#   error RICE easy macro's conflict with environment.
#endif

#define Explain(kb, typ, fct, dpt)      RICE_MERGE(rice_Explain, typ(kb, fct, dpt))
#define Redirect(kb, nam, fnc)          RICE_MERGE(rice_Redirect, nam(kb, fnc))
#define Set(kb, nam)                    RICE_MERGE(rice_Set, nam(kb, 1))
#define Reset(kb, nam)                  RICE_MERGE(rice_Set, nam(kb, 0))
#define Switch(kb, nam)                 RICE_MERGE(rice_Set, nam(kb, -1))
#define Use(kb, nam, num, ptr)          RICE_MERGE(rice_Use, nam(kb, num, ptr))
#define SetAdaptive(kb)                 rice_SetAdaptive(kb,  1)
#define ResetAdaptive(kb)               rice_SetAdaptive(kb,  0)
#define SwitchAdaptive(kb)              rice_SetAdaptive(kb, -1)
#define SetRepetitive(kb)               rice_SetRepetitive(kb,  1)
#define ResetRepetitive(kb)             rice_SetRepetitive(kb,  0)
#define SwitchRepetitive(kb)            rice_SetRepetitive(kb, -1)
#define SetInteractive(kb)              rice_SetInteractive(kb,  1)
#define ResetInteractive(kb)            rice_SetInteractive(kb,  0)
#define SwitchInteractive(kb)           rice_SetInteractive(kb, -1)
#define SetRecursive(kb)                rice_SetRecursive(kb,  1)
#define ResetRecursive(kb)              rice_SetRecursive(kb,  0)
#define SwitchRecursive(kb)             rice_SetRecursive(kb, -1)
#define SetSelective(kb)                rice_SetSelective(kb,  1)
#define ResetSelective(kb)              rice_SetSelective(kb,  0)
#define SwitchSelective(kb)             rice_SetSelective(kb, -1)
#define UseLinker(kb, num, lnk)         rice_UseLinker(kb, num, lnk)
#define UseIntersection(kb, num, lnk)   rice_UseIntersection(kb, num, lnk)
#define UseUnion(kb, num, lnk)          rice_UseUnion(kb, num, lnk)
#define ExplainHow(kb, fct, dpt)        rice_ExplainHow(kb, fct, dpt)
#define ExplainWhy(kb, fct, dpt)        rice_ExplainWhy(kb, fct, dpt)


/* redirection macro's */

#if defined(RedirectAsk) || defined(RedirectInform) || defined(RedirectReport)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(RedirectProtect) || defined(RedirectAbandon)
#   error RICE easy macro's conflict with environment.
#endif

#define RedirectAsk(kb, fnc)       rice_RedirectAsk(kb, fnc)
#define RedirectInform(kb, fnc)    rice_RedirectInform(kb, fnc)
#define RedirectReport(kb, fnc)    rice_RedirectReport(kb, fnc)
#define RedirectExplain(kb, fnc)   rice_RedirectExplain(kb, fnc)
#define RedirectProtect(kb, fnc)   rice_RedirectProtect(kb, fnc)
#define RedirectAbandon(kb, fnc)   rice_RedirectAbandon(kb, fnc)


/* KB interfacing macro's */

#if defined(CompileKB) || defined(AppendKB) || defined(SwapKB)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(LoadKB) || defined(SaveKB) || defined(RebuildKB)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(DestroyKB) || defined(ClearKB) || defined(InferKB)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(CopyKB) || defined(MoveKB)
#   error RICE easy macro's conflict with environment.
#endif

#define AppendKB(kb, str)    rice_AppendKB(kb, str)
#define ClearKB(kb)          rice_ClearKB(kb)
#define CompileKB(kb, str)   rice_CompileKB(kb, str)
#define CopyKB(kb1, kb2)     rice_CopyKB(kb1, kb2)
#define DestroyKB(kb)        rice_DestroyKB(kb)
#define InferKB(kb)          rice_InferKB(kb)
#define LoadKB(kb, str)      rice_LoadKB(kb, str)
#define MoveKB(kb1, kb2)     rice_MoveKB(kb1, kb2)
#define RebuildKB(kb, str)   rice_RebuildKB(kb, str)
#define SaveKB(kb, str)      rice_SaveKB(kb, str)
#define SwapKB(kb)           rice_SwapKB(kb)


/* ES interfacing macro's */

#if defined(SwitchES) || defined(CopyES) || defined(MoveES)
#   error RICE easy macro's conflict with environment.
#endif

#if defined(CheckES) || defined(DeleteES) || defined(CreateES)
#   error RICE easy macro's conflict with environment.
#endif

#define CheckES(es)          rice_CheckES(es)
#define CopyES(es1, es2)     rice_CopyES(es1, es2)
#define CreateES()           rice_CreateES()
#define DeleteES(es)         rice_DeleteES(es)
#define MoveES(es1, es2)     rice_MoveES(es1, es2)
#define SwitchES(es)         rice_SwitchES(es)


#endif /* _RICEEASY_H_ */

