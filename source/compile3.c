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
   File:   compile3.c
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


/* include local header file */

#include "compile.h"


/* preprocess stuff */

static TMP_MACRO **macroList = 0;
static int       nrMacros = 0;


/* preprocess-functions */

FUNCTION(void DestroyMacro,
   (TMP_MACRO *macro),
   (macro),
   TMP_MACRO *macro;
)
{
   register int i;

   if(macro) {
      FREE(macro->name);
      if(macro->line)
         for(i = 0; i < macro->nrlines; i++)
            FREE(macro->line[i]);
      FREE(macro->line);
      FREE(macro);
   }
}


FUNCTION(void DestroyMacroList,
   (void),
   (),
   /* nothing */
)
{
   register int i;

   for(i = 0; i < nrMacros; i++)
      DestroyMacro(macroList[i]);
   FREE(macroList);

   nrMacros = 0;
   macroList = 0;
}


FUNCTION(int CompileMacro,
   (char *name, FILE *file),
   (name, file),
   char *name;
   FILE *file;
)
{
   register int i;
   int err = 0;
   char line[SIZ_LINE];

   for(i = 0; i < nrMacros; i++)
      if(!strcmp(macroList[i]->name, name))
      {
         DestroyMacro(macroList[i]);
         err = 1;
         break;
      }

   if(i == nrMacros)
   {
      REALLOC(macroList, nrMacros + 1, TMP_MACRO *);
      nrMacros++;
   }

   ALLOC(macroList[i], 1, TMP_MACRO);
   ALLOC(macroList[i]->name, strlen(name) + 1, char);
   strcpy(macroList[i]->name, StringToLower(name));
   macroList[i]->nrlines = 0;
   macroList[i]->line = 0;

   while(fgets(line, SIZ_LINE - 1, file)) {

      if(!strlen(StripString(line)))
         break;

      REALLOC(macroList[i]->line, macroList[i]->nrlines + 1, char *);
      ALLOC(macroList[i]->line[macroList[i]->nrlines], strlen(line) + 1, char);
      strcpy(macroList[i]->line[macroList[i]->nrlines], line);
      macroList[i]->nrlines++;
   }

   return err;
}


FUNCTION(int RebuildMacro,
   (char *name, char *arglist, char *argument[], FILE *file),
   (name, arglist, argument, file),
   char *name;
   char *arglist;
   char *argument[];
   FILE *file;
)
{
   register int i, j;
   int index, len;
   char *delimiter, line[SIZ_LINE];

   for(i = 0; i < nrMacros; i++)
      if(!strcmp(macroList[i]->name, name))
         break;

   if(i >= nrMacros)
      return 1;

   for(j = 0; j < macroList[i]->nrlines; j++)
   {
      if(strncmp(macroList[i]->line[j], STR_REM, sizeof(STR_REM) - 1))
      {
         strcpy(line, macroList[i]->line[j]);
         delimiter = line;

         while(delimiter = strchr(delimiter, CHR_HASH))
         {
            if(*(delimiter + 1) == CHR_AT)
               InsertString(ShiftString(delimiter + 2, -2), arglist);
            else
            {
               sscanf(delimiter + 1, "%d", &index);
               index = 1 + abs(index - 1)%(SIZ_LINE/2 - 1);
               len = 1;
               while(isdigit(delimiter[len]))
                  len++;
               InsertString(ShiftString(delimiter + len, -len), argument[index]);
            }
         }
      }
      else
         line[0] = 0;

      CompileLine(line, file);
   }

   return 0;
}


