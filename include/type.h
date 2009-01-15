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
   File:   type.h
   Author: Rene' Jager
   Update: January 4, 1993
   Info:   include file for RICE
*/


/* type definitions */

PROTOTYPE(typedef float (*RICE_NORM), (float, float));
PROTOTYPE(typedef void (*RICE_LINKER), (int, int, int, char *[], float *, int *));


/* properties */

typedef struct {
   unsigned ACTIVE : 1;
} PRP_OBJECT;


typedef struct {
   unsigned BACKWARD : 1;
   unsigned FORWARD  : 1;
} PRP_LAYER;


typedef struct {
   unsigned FIREABLE     : 1;
   unsigned FIRED        : 1;
   unsigned FIRING       : 1;
   unsigned EXPLAINED    : 1;
   unsigned INTERSECTION : 1;
   unsigned UNION        : 1;
} PRP_RULE;


typedef struct {
   unsigned FIREABLE  : 1;
   unsigned FIRED     : 1;
   unsigned FIRING    : 1;
   unsigned EXPLAINED : 1;
} PRP_RELATION;


typedef struct {
   unsigned CODE      : 1;
   unsigned INFERRING : 1;
} PRP_FACT;


typedef struct {
   unsigned LHSL : 1;
   unsigned LHSP : 1;
   unsigned LHSZ : 1;
   unsigned LHSU : 1;
   unsigned AND  : 1;
   unsigned OR   : 1;
   unsigned IF   : 1;
   unsigned NOT  : 1;
   unsigned LAY  : 1;
   unsigned RUL  : 1;
   unsigned REL  : 1;
   unsigned FAC  : 1;
   unsigned CON  : 1;
   unsigned ACT  : 1;
   unsigned DIM  : 1;
   unsigned BKW  : 1;
   unsigned FRW  : 1;
   unsigned ON   : 1;
   unsigned OFF  : 1;
   unsigned USR  : 1;
   unsigned RUN  : 1;
   unsigned GRD  : 1;
   unsigned CUT  : 1;
   unsigned SHW  : 1;
} PRP_CONDITION;


typedef struct {
   unsigned RHSL : 1;
   unsigned RHSP : 1;
   unsigned RHSZ : 1;
   unsigned RHSU : 1;
   unsigned INIT : 1;
   unsigned THEN : 1;
   unsigned ELSE : 1;
   unsigned NOT  : 1;
   unsigned LAY  : 1;
   unsigned RUL  : 1;
   unsigned REL  : 1;
   unsigned FAC  : 1;
   unsigned CON  : 1;
   unsigned ACT  : 1;
   unsigned DIM  : 1;
   unsigned BKW  : 1;
   unsigned FRW  : 1;
   unsigned ON   : 1;
   unsigned OFF  : 1;
   unsigned USR  : 1;
   unsigned RUN  : 1;
   unsigned GRD  : 1;
   unsigned CUT  : 1;
   unsigned INV  : 1;
   unsigned SHW  : 1;
} PRP_ACTION;


typedef struct {
   unsigned LHSL : 1;
   unsigned LHSP : 1;
   unsigned LHSZ : 1;
   unsigned LHSU : 1;
   unsigned RHSL : 1;
   unsigned RHSP : 1;
   unsigned RHSZ : 1;
   unsigned RHSU : 1;
   unsigned FAC  : 1;
   unsigned NOT  : 1;
   unsigned LAY  : 1;
   unsigned RUL  : 1;
   unsigned REL  : 1;
   unsigned CON  : 1;
   unsigned ACT  : 1;
   unsigned DIM  : 1;
   unsigned BKW  : 1;
   unsigned FRW  : 1;
   unsigned ON   : 1;
   unsigned OFF  : 1;
   unsigned USR  : 1;
   unsigned RUN  : 1;
   unsigned GRD  : 1;
   unsigned CUT  : 1;
   unsigned SHW  : 1;
} PRP_DIMENSION;


/* objects */

typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
} OBJ_OBJECT;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   int *layer;
} OBJ_BASE;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   int *init;
   int *data;
   int *goal;
   int *rule;
   int *relation;
   PRP_LAYER slot;
} OBJ_LAYER;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   int *condition;
   int *action;
   PRP_RULE slot;
} OBJ_RULE;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   int *dimension;
   PRP_RELATION slot;
} OBJ_RELATION;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   float grade;
   float sumgrade;
   int numgrade;
   int *forward;
   int *backward;
   int link;
   PRP_FACT slot;
} OBJ_FACT;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   int object;
   float level;
   int argc;
   char **argv;
   int user;
   float truth;
   RICE_NORM norm;
   PRP_CONDITION slot;
} OBJ_CONDITION;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   int object;
   float grade;
   float level;
   int argc;
   char **argv;
   int user;
   float truth;
   RICE_NORM norm;
   PRP_ACTION slot;
} OBJ_ACTION;


typedef struct {
   int type;
   int number;
   char *symbolic;
   PRP_OBJECT status;
   int object;
   float grade;
   float level;
   int argc;
   char **argv;
   int user[2];
   float truth[2];
   RICE_NORM norm[2];
   PRP_DIMENSION slot;
} OBJ_DIMENSION;


/* temporary macro definition */

typedef struct {
   char *name;
   int nrlines;
   char **line;
} TMP_MACRO;


/* user side of base object */

typedef struct {
   int number;
   PROTOTYPE(void (*function), (int, int, char *[], float *, int *, int *));
} USR_RUN;


typedef struct {
   PROTOTYPE(void (*ask), (int, int, char *[], float *));
   PROTOTYPE(void (*inform), (int, int, char *[], float *));
   PROTOTYPE(void (*report), (int, int, char *));
   PROTOTYPE(void (*explain), (int, char *));
   PROTOTYPE(void (*protect), (int));
   PROTOTYPE(void (*abandon), (void));
   int nrAnd, nrOr, nrRun;
   RICE_NORM *and, *or;
   RICE_LINKER *run;
} USR_FUNCTION;


typedef struct {
   unsigned interactive : 1;
   unsigned recursive   : 1;
   unsigned repetitive  : 1;
   unsigned selective   : 1;
   unsigned adaptive    : 1;
} USR_MODE;


typedef struct {
   int index;
   USR_FUNCTION function;
   USR_MODE mode;
   OBJ_OBJECT **object;
} USR_BASE;


