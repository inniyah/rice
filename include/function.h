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
   File:   function.h
   Author: Rene' Jager
   Update: December 22, 1992
   Info:   include file for RICE
*/


/* communication functions */

PROTOTYPE(void Ask, (int, char *[], float *));
PROTOTYPE(void Inform, (int, char *[], float *));
PROTOTYPE(void Report, (int, char *, ...));
PROTOTYPE(void Explain, (char *, ...));
PROTOTYPE(void Protect, (int));
PROTOTYPE(void Abandon, (void));
PROTOTYPE(void Run, (int, int, char *[], float *));


/* KB functions */

PROTOTYPE(int AppendKB, (int, char *));
PROTOTYPE(int ClearKB, (int));
PROTOTYPE(int CopyKB, (int, int));
PROTOTYPE(int CompileKB, (int, char *));
PROTOTYPE(int DestroyKB, (int));
PROTOTYPE(int InferKB, (int));
PROTOTYPE(int LoadKB, (int, char *));
PROTOTYPE(int MoveKB, (int, int));
PROTOTYPE(int ProcessKB, (int, char *, char *));
PROTOTYPE(int RebuildKB, (int, char *));
PROTOTYPE(int SaveKB, (int, char *));
PROTOTYPE(int SwapKB, (int, PROTOTYPE(void (*func), (void))));


/* ES functions */

PROTOTYPE(int CheckES, (int));
PROTOTYPE(int CopyES, (int, int));
PROTOTYPE(int CreateES, (void));
PROTOTYPE(int DeleteES, (int));
PROTOTYPE(int MoveES, (int, int));
PROTOTYPE(int SwitchES, (int));


/* logic operators */

PROTOTYPE(float LukasiewiczAnd, (float, float));
PROTOTYPE(float LukasiewiczOr, (float, float));

PROTOTYPE(float ProbabilityAnd, (float, float));
PROTOTYPE(float ProbabilityOr, (float, float));

PROTOTYPE(float ZadehAnd, (float, float));
PROTOTYPE(float ZadehOr, (float, float));


/* explaination functions */

PROTOTYPE(void HowFact, (OBJ_FACT *, int));
PROTOTYPE(void WhyFact, (OBJ_FACT *, int));

