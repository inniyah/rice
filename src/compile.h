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
   File:   compile.h
   Author: Rene' Jager
   Update: December 22, 1992
   Info:   include file for RICE
*/


/* macro's */

#define AddIndex(ind,lis) \
{ \
   lis[0] += 1; \
   REALLOC(lis, lis[0] + 1, int); \
   lis[lis[0]] = ind; \
}


#define KeyIsString(str,sub)     (!strcmp(str, sub))


#define KeysInString1(str,sub) \
_if(!strncmp(str, sub, sizeof(sub) - 1)) \
   _if(str += sizeof(sub) - 1) \
       1 \
   _else \
      0 \
   _endif \
_else \
   0 \
_endif


#define KeysInString2(str,sub1,sub2) \
_if(!strncmp(str, sub1, sizeof(sub1) - 1)) \
   _if(!strncmp(str + sizeof(sub1) - 1, sub2, sizeof(sub2) - 1)) \
      _if(str += sizeof(sub1) + sizeof(sub2) - 2) \
         1 \
      _else \
         0 \
      _endif \
   _else \
      0 \
   _endif \
_else \
   0 \
_endif


#define KeysInString3(str,sub1,sub2,sub3) \
_if(!strncmp(str, sub1, sizeof(sub1) - 1)) \
   _if(!strncmp(str + sizeof(sub1) - 1, sub2, sizeof(sub2) - 1)) \
      _if(!strncmp(str + sizeof(sub1) + sizeof(sub2) - 2, sub3, sizeof(sub3) - 1)) \
         _if(str += sizeof(sub1) + sizeof(sub2) + sizeof(sub3) - 3) \
            1 \
         _else \
            0 \
         _endif \
      _else \
         0 \
      _endif \
   _else \
      0 \
   _endif \
_else \
   0 \
_endif


/* prototypes of compile functions */

PROTOTYPE(OBJ_BASE      *rice_CompileBase, (char *));
PROTOTYPE(OBJ_LAYER     *rice_CompileLayer, (char *));
PROTOTYPE(OBJ_RULE      *rice_CompileRule, (char *));
PROTOTYPE(OBJ_RELATION  *rice_CompileRelation, (char *));
PROTOTYPE(OBJ_FACT      *rice_CompileFact, (char *));
PROTOTYPE(OBJ_CONDITION *rice_CompileCondition, (char *));
PROTOTYPE(OBJ_ACTION    *rice_CompileAction, (char *));
PROTOTYPE(OBJ_DIMENSION *rice_CompileDimension, (char *));

PROTOTYPE(void rice_CompileConditionKeyword, (OBJ_CONDITION *, char *));
PROTOTYPE(void rice_CompileActionKeyword, (OBJ_ACTION *, char *));
PROTOTYPE(void rice_CompileDimensionKeyword, (OBJ_DIMENSION *, char *));

PROTOTYPE(char **rice_CompileArguments, (int *, char *));
PROTOTYPE(int  rice_StringToKey, (char *));
PROTOTYPE(void rice_AddObjectToList, (OBJ_OBJECT *));

PROTOTYPE(char *rice_StripString, (char *));
PROTOTYPE(char *rice_StringToUpper, (char *));
PROTOTYPE(char *rice_StringToLower, (char *));
PROTOTYPE(char *rice_ReplaceString, (char *, char *, char *));
PROTOTYPE(char *rice_InsertString, (char *, char *));
PROTOTYPE(char *rice_ShiftString, (char *, int));

PROTOTYPE(void rice_DestroyMacro, (TMP_MACRO *));
PROTOTYPE(void rice_DestroyMacroList, (void));

PROTOTYPE(int rice_CompileMacro, (char *, FILE *));
PROTOTYPE(int rice_RebuildMacro, (char *, char *, char *[], FILE *));

PROTOTYPE(void rice_CompileFile, (FILE *));
PROTOTYPE(void rice_CompileLine, (char *, FILE *));


/* make unique names for functions */

#define CompileBase               rice_CompileBase
#define CompileLayer              rice_CompileLayer
#define CompileRule               rice_CompileRule
#define CompileRelation           rice_CompileRelation
#define CompileFact               rice_CompileFact
#define CompileCondition          rice_CompileCondition
#define CompileAction             rice_CompileAction
#define CompileDimension          rice_CompileDimension

#define CompileConditionKeyword   rice_CompileConditionKeyword
#define CompileActionKeyword      rice_CompileActionKeyword
#define CompileDimensionKeyword   rice_CompileDimensionKeyword

#define CompileArguments          rice_CompileArguments
#define StringToKey               rice_StringToKey
#define AddObjectToList           rice_AddObjectToList

#define StripString               rice_StripString
#define StringToUpper             rice_StringToUpper
#define StringToLower             rice_StringToLower
#define ReplaceString             rice_ReplaceString
#define InsertString              rice_InsertString
#define ShiftString               rice_ShiftString

#define DestroyMacro              rice_DestroyMacro
#define DestroyMacroList          rice_DestroyMacroList
#define CompileMacro              rice_CompileMacro
#define RebuildMacro              rice_RebuildMacro

#define CompileFile               rice_CompileFile
#define CompileLine               rice_CompileLine
