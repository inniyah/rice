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
   File:   define.h
   Author: Rene' Jager
   Update: December 22, 1992
   Info:   include file for RICE
*/


/* message types */

#define MSG_ERROR           1
#define MSG_WARNING         2
#define MSG_MESSAGE         3


/* message strings */

#define MSG_MEMORY_ALLOC        "not enough memory"
#define MSG_MEMORY_REALLOC      "not enough memory"

#define MSG_FILE_OPEN           "opening file '%s'"
#define MSG_FILE_CLOSE          "closing file '%s'"
#define MSG_FILE_READ           "reading file '%s'"
#define MSG_FILE_WRITE          "writing file '%s'"
#define MSG_FILE_REMOVE         "removing file '%s'"

#define MSG_KEYWORD_UNEXPECTED  "unexpected keyword in line '%s'"
#define MSG_KEYWORD_UNKNOWN     "unknown keyword in line '%s'"
#define MSG_KEYWORD_MISSING     "missing keyword in line '%s'"

#define MSG_ARGUMENT_MISSING    "missing argument in line '%s'"
#define MSG_ARGUMENT_UNEXPECTED "unexpected argument in line '%s'"
#define MSG_ARGUMENT_RUNNING    "running argument in line '%s'"

#define MSG_BUG_INTERNAL        "internal bug, contact author"
#define MSG_EXPIRED_DATE        "license agreement date expired, %s"

#define MSG_INVALID_BASE        "invalid knowledge base indentifier '%d'"

#define MSG_UNKNOWN_FACT        "unknown fact '%s'"
#define MSG_UNCODED_FACT        "uncoded fact '%s'"

#define MSG_NORM_CHANGED        "user norm changed from %d to %d in line '%s'"
#define MSG_NORM_MISSING        "missing user norm in line '%s'"
#define MSG_NORM_INVALID        "invalid user norm %d in line '%s'"
#define MSG_NORM_UNAVAIL        "unavailable user norm %d when loading"

#define MSG_INVALID_FILE        "file '%s' of incompatible type"


/* grades */

#define GRD_TRUE      1.0
#define GRD_FALSE     0.0
#define GRD_UNKNOWN   (-1.0)


/* modes */

#define MOD_NONE            0
#define MOD_BACKWARD        1
#define MOD_FORWARD         2
#define MOD_BREADTH         3
#define MOD_DEPTH           4


/* types */

#define TYP_NONE            0
#define TYP_BASE            1
#define TYP_LAYER           2
#define TYP_RULE            3
#define TYP_RELATION        4
#define TYP_FACT            5
#define TYP_CONDITION       6
#define TYP_ACTION          7
#define TYP_DIMENSION       8


/* strings */

#define STR_ERROR           "Error"
#define STR_WARNING         "Warning"
#define STR_MESSAGE         "Message"
#define STR_INCLUDE         "include"
#define STR_DEFINE          "define"
#define STR_REM             "rem"
#define STR_BASE            "base"
#define STR_LAYER           "layer"
#define STR_RULE            "rule"
#define STR_RELATION        "relation"
#define STR_FACT            "fact"
#define STR_CONDITION       "condition"
#define STR_ACTION          "action"
#define STR_DIMENSION       "dimension"
#define STR_LAY             "lay"
#define STR_RUL             "rul"
#define STR_REL             "rel"
#define STR_DATA            "data"
#define STR_GOAL            "goal"
#define STR_L               "l"
#define STR_P               "p"
#define STR_Z               "z"
#define STR_U               "u"
#define STR_AND             "and"
#define STR_OR              "or"
#define STR_DIM             "dim"
#define STR_INIT            "init"
#define STR_THEN            "then"
#define STR_ELSE            "else"
#define STR_IF              "if"
#define STR_NOT             "not"
#define STR_ASK             "ask"
#define STR_INF             "inf"
#define STR_USR             "usr"
#define STR_RUN             "run"
#define STR_ON              "on"
#define STR_OFF             "off"
#define STR_BKW             "bkw"
#define STR_FRW             "frw"
#define STR_CON             "con"
#define STR_ACT             "act"
#define STR_GRD             "grd"
#define STR_CUT             "cut"
#define STR_INV             "inv"
#define STR_HOW             "how"
#define STR_WHY             "why"
#define STR_SHW             "shw"


/* sizes */

#define SIZ_NONE            0
#define SIZ_NAME            8
#define SIZ_EXT             3
#define SIZ_LINE            256


/* characters */

#define CHR_AT              '@'
#define CHR_AMPERSAND       '&'
#define CHR_ASTERISK        '*'
#define CHR_COLON           ':'
#define CHR_COMMA           ','
#define CHR_DOLLAR          '$'
#define CHR_HASH            '#'
#define CHR_PERIOD          '.'
#define CHR_SEMICOLON       ';'
#define CHR_SPACE           ' '
#define CHR_UNDERSCORE      '_'
#define CHR_BACKSLASH       '\\'
#define CHR_BACKSPACE       '\b'
#define CHR_BELL            '\a'
#define CHR_DOUBLEQUOTE     '\"'
#define CHR_FORMFEED        '\f'
#define CHR_NEWLINE         '\n'
#define CHR_NULL            '\0'
#define CHR_QUESTION        '\?'
#define CHR_RETURN          '\r'
#define CHR_SINGLEQUOTE     '\''
#define CHR_TAB             '\t'
#define CHR_LEFTPARENT      '('
#define CHR_RIGHTPARENT     ')'


/* key's */

#define KEY_NONE            0
#define KEY_BASE            1
#define KEY_DEFINE          2
#define KEY_INCLUDE         3
#define KEY_LAYER           4
#define KEY_RULE            5
#define KEY_RELATION        6
#define KEY_INITx           7
#define KEY_DATA            8
#define KEY_GOAL            9
#define KEY_LANDx           10
#define KEY_PANDx           11
#define KEY_ZANDx           12
#define KEY_LORx            13
#define KEY_PORx            14
#define KEY_ZORx            15
#define KEY_LxDIMx          16
#define KEY_PxDIMx          17
#define KEY_ZxDIMx          18
#define KEY_xTHENx          19
#define KEY_xELSEx          20
#define KEY_REM             21
#define KEY_CONDITION       22
#define KEY_ACTION          23
#define KEY_DIMENSION       24
#define KEY_UANDx           25
#define KEY_UORx            26
#define KEY_UxDIMx          27
#define KEY_LIFx            28
#define KEY_PIFx            29
#define KEY_ZIFx            30
#define KEY_UIFx            31
#define KEY_ANDx            32
#define KEY_ORx             33


/* some global strings */

#define STR_SWAPFILE   "rice.swp"
#define STR_FILEMARK   "RICE 4.0"


/* macro's for easy handling of (?:)-statements */

#define _if(c)   ((c) ? (
#define _else    ) : (
#define _endif   ))


/* macro's for convenience */

#define ABS(v) \
_if((v) < 0) \
   (-(v)) \
_else \
   (v) \
_endif


#define MAX(v1,v2) \
_if((v1) > (v2)) \
   (v1) \
_else \
   (v2) \
_endif


#define MIN(v1,v2) \
_if((v1) < (v2)) \
   (v1) \
_else \
   (v2) \
_endif


#define LIM(v,l,u) \
_if((v) < (l)) \
   (l) \
_else \
   _if((v) > (u)) \
      (u) \
   _else \
      (v) \
   _endif \
_endif


/* macro's for fuzzy logic */

#define FCUT(g,l) \
_if((g) == GRD_UNKNOWN || (g) >= (l)) \
   (g) \
_else \
   GRD_FALSE \
_endif


#define FNOT(g) \
_if((g) == GRD_UNKNOWN) \
   GRD_UNKNOWN \
_else \
   GRD_TRUE + GRD_FALSE - (g) \
_endif


#define LAND(g1,g2) \
_if((g1) == GRD_FALSE || (g2) == GRD_FALSE) \
   GRD_FALSE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      MAX((g1) + (g2) - GRD_TRUE, GRD_FALSE) \
   _endif \
_endif


#define LOR(g1,g2) \
_if((g1) == GRD_TRUE || (g2) == GRD_TRUE) \
   GRD_TRUE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      MIN((g1) + (g2), GRD_TRUE) \
   _endif \
_endif


#define PAND(g1,g2) \
_if((g1) == GRD_FALSE || (g2) == GRD_FALSE) \
   GRD_FALSE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      ((g1)*(g2)) \
   _endif \
_endif


#define POR(g1,g2) \
_if((g1) == GRD_TRUE || (g2) == GRD_TRUE) \
   GRD_TRUE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      ((g1) + (g2) - (g1)*(g2)) \
   _endif \
_endif


#define ZAND(g1,g2) \
_if((g1) == GRD_FALSE || (g2) == GRD_FALSE) \
   GRD_FALSE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      MIN((g1), (g2)) \
   _endif \
_endif


#define ZOR(g1,g2) \
_if((g1) == GRD_TRUE || (g2) == GRD_TRUE) \
   GRD_TRUE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      MAX((g1), (g2)) \
   _endif \
_endif


#define UAND(g1,g2) \
_if((g1) == GRD_FALSE || (g2) == GRD_FALSE) \
   GRD_FALSE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      And(g1, g2) \
   _endif \
_endif


#define UOR(g1,g2) \
_if((g1) == GRD_TRUE || (g2) == GRD_TRUE) \
   GRD_TRUE \
_else \
   _if((g1) == GRD_UNKNOWN || (g2) == GRD_UNKNOWN) \
      GRD_UNKNOWN \
   _else \
      Or(g1, g2) \
   _endif \
_endif



/* allocation macro's */

#define ALLOC(a,n,t)     if(!(a = (t*)malloc((n)*sizeof(t)))) \
                         { \
                            Report(MSG_ERROR, MSG_MEMORY_ALLOC, ""); \
                            Abandon(); \
                         } else {}

#define REALLOC(a,n,t)   if(a) { if(!(a = (t*)realloc(a,(n)*sizeof(t)))) \
                         { Report(MSG_ERROR, MSG_MEMORY_REALLOC, ""); \
                           Abandon(); } \
                         } else { ALLOC(a, n, t); }

#define FREE(a)          if(a) free(a); else {}


/* help macro's */

#define elif                      else if
#define forever                   for(;;)


/* type conversion macro's */

#define OBJ2BAS(obj)   ((OBJ_BASE      *) (obj))
#define OBJ2LAY(obj)   ((OBJ_LAYER     *) (obj))
#define OBJ2RUL(obj)   ((OBJ_RULE      *) (obj))
#define OBJ2REL(obj)   ((OBJ_RELATION  *) (obj))
#define OBJ2FAC(obj)   ((OBJ_FACT      *) (obj))
#define OBJ2CON(obj)   ((OBJ_CONDITION *) (obj))
#define OBJ2ACT(obj)   ((OBJ_ACTION    *) (obj))
#define OBJ2DIM(obj)   ((OBJ_DIMENSION *) (obj))

#define BAS2OBJ(bas)   ((OBJ_OBJECT *) (bas))
#define LAY2OBJ(lay)   ((OBJ_OBJECT *) (lay))
#define RUL2OBJ(rul)   ((OBJ_OBJECT *) (rul))
#define REL2OBJ(rel)   ((OBJ_OBJECT *) (rel))
#define FAC2OBJ(fac)   ((OBJ_OBJECT *) (fac))
#define CON2OBJ(con)   ((OBJ_OBJECT *) (con))
#define ACT2OBJ(act)   ((OBJ_OBJECT *) (act))
#define DIM2OBJ(dim)   ((OBJ_OBJECT *) (dim))

#define IDX2OBJ(idx)    ((OBJ_OBJECT    *) objectList[idx])
#define IDX2BAS(idx)    ((OBJ_BASE      *) objectList[idx])
#define IDX2LAY(idx)    ((OBJ_LAYER     *) objectList[idx])
#define IDX2RUL(idx)    ((OBJ_RULE      *) objectList[idx])
#define IDX2REL(idx)    ((OBJ_RELATION  *) objectList[idx])
#define IDX2FAC(idx)    ((OBJ_FACT      *) objectList[idx])
#define IDX2CON(idx)    ((OBJ_CONDITION *) objectList[idx])
#define IDX2ACT(idx)    ((OBJ_ACTION    *) objectList[idx])
#define IDX2DIM(idx)    ((OBJ_DIMENSION *) objectList[idx])


/* synonyms for making RICE-functions and -variables unique */

#define theBase           rice_theBase
#define objectList        rice_theBase->object
#define kbIndex           rice_theBase->index

#define interactiveMode   rice_theBase->mode.interactive
#define recursiveMode     rice_theBase->mode.recursive
#define repetitiveMode    rice_theBase->mode.repetitive
#define selectiveMode     rice_theBase->mode.selective
#define adaptiveMode      rice_theBase->mode.adaptive

#define Ask               rice_Ask
#define Inform            rice_Inform
#define Report            rice_Report
#define Explain           rice_Explain
#define Protect           rice_Protect
#define Abandon           rice_Abandon
#define Run               rice_Run

#define ExplainHow        rice_ExplainHow
#define ExplainWhy        rice_ExplainWhy

#define RedirectAsk       rice_RedirectAsk
#define RedirectInform    rice_RedirectInform
#define RedirectReport    rice_RedirectReport
#define RedirectExplain   rice_RedirectExplain
#define RedirectAbandon   rice_RedirectAbandon
#define RedirectProtect   rice_RedirectProtect

#define UseIntersection   rice_UseIntersection
#define UseUnion          rice_UseUnion
#define UseLinker         rice_UseLinker

#define userAsk           rice_theBase->function.ask
#define userInform        rice_theBase->function.inform
#define userReport        rice_theBase->function.report
#define userProtect       rice_theBase->function.protect
#define userAbandon       rice_theBase->function.abandon
#define userExplain       rice_theBase->function.explain
#define userAnd           rice_theBase->function.and
#define userOr            rice_theBase->function.or
#define userRun           rice_theBase->function.run

#define nrUserAnd         rice_theBase->function.nrAnd
#define nrUserOr          rice_theBase->function.nrOr
#define nrUserRun         rice_theBase->function.nrRun

#define AppendKB          rice_AppendKB
#define ClearKB           rice_ClearKB
#define CompileKB         rice_CompileKB
#define CopyKB            rice_CopyKB
#define DestroyKB         rice_DestroyKB
#define InferKB           rice_InferKB
#define LoadKB            rice_LoadKB
#define MoveKB            rice_MoveKB
#define ProcessKB         rice_ProcessKB
#define RebuildKB         rice_RebuildKB
#define SaveKB            rice_SaveKB
#define SwapKB            rice_SwapKB

#define CheckES           rice_CheckES
#define CreateES          rice_CreateES
#define CopyES            rice_CopyES
#define DeleteES          rice_DeleteES
#define MoveES            rice_MoveES
#define SwitchES          rice_SwitchES

#define ZadehAnd          rice_ZadehAnd
#define LukasiewiczAnd    rice_LukasiewiczAnd
#define ProbabilityAnd    rice_ProbabilityAnd

#define ZadehOr           rice_ZadehOr
#define LukasiewiczOr     rice_LukasiewiczOr
#define ProbabilityOr     rice_ProbabilityOr

#define HowFact           rice_HowFact
#define WhyFact           rice_WhyFact

#define SetAdaptive       rice_SetAdaptive
#define SetInteractive    rice_SetInteractive
#define SetRecursive      rice_SetRecursive
#define SetRepetitive     rice_SetRepetitive
#define SetSelective      rice_SetSelective



