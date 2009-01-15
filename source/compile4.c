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
   File:   compile4.c
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


/* compile functions */

FUNCTION(int StringToKey,
   (char *string),
   (string),
   char *string;
)
{
   int key = -1;

   if(!strlen(string))
      return KEY_NONE;

   StringToLower(string);

     if(KeyIsString(string, STR_DEFINE))    return KEY_DEFINE;
   elif(KeyIsString(string, STR_INCLUDE))   return KEY_INCLUDE;
   elif(KeyIsString(string, STR_BASE))      return KEY_BASE;
   elif(KeyIsString(string, STR_LAYER))     return KEY_LAYER;
   elif(KeyIsString(string, STR_RULE))      return KEY_RULE;
   elif(KeyIsString(string, STR_RELATION))  return KEY_RELATION;
   elif(KeyIsString(string, STR_CONDITION)) return KEY_CONDITION;
   elif(KeyIsString(string, STR_ACTION))    return KEY_ACTION;
   elif(KeyIsString(string, STR_DIMENSION)) return KEY_DIMENSION;
   elif(KeyIsString(string, STR_DATA))      return KEY_DATA;
   elif(KeyIsString(string, STR_GOAL))      return KEY_GOAL;
   elif(KeyIsString(string, STR_REM))       return KEY_REM;

     if(KeysInString1(string, STR_INIT))              key = KEY_INITx;
   elif(KeysInString1(string, STR_IF))                key = KEY_ZIFx;
   elif(KeysInString1(string, STR_AND))               key = KEY_ZANDx;
   elif(KeysInString1(string, STR_OR))                key = KEY_ZORx;
   elif(KeysInString1(string, STR_THEN))              key = KEY_xTHENx;
   elif(KeysInString1(string, STR_ELSE))              key = KEY_xELSEx;
   elif(KeysInString1(string, STR_DIM))               key = KEY_ZxDIMx;
   elif(KeysInString2(string, STR_L, STR_AND))        key = KEY_LANDx;
   elif(KeysInString2(string, STR_P, STR_AND))        key = KEY_PANDx;
   elif(KeysInString2(string, STR_Z, STR_AND))        key = KEY_ZANDx;
   elif(KeysInString2(string, STR_L, STR_OR))         key = KEY_LORx;
   elif(KeysInString2(string, STR_P, STR_OR))         key = KEY_PORx;
   elif(KeysInString2(string, STR_Z, STR_OR))         key = KEY_ZORx;
   elif(KeysInString2(string, STR_L, STR_THEN))       key = KEY_xTHENx;
   elif(KeysInString2(string, STR_P, STR_THEN))       key = KEY_xTHENx;
   elif(KeysInString2(string, STR_Z, STR_THEN))       key = KEY_xTHENx;
   elif(KeysInString2(string, STR_L, STR_ELSE))       key = KEY_xELSEx;
   elif(KeysInString2(string, STR_P, STR_ELSE))       key = KEY_xELSEx;
   elif(KeysInString2(string, STR_Z, STR_ELSE))       key = KEY_xELSEx;
   elif(KeysInString3(string, STR_L, STR_L, STR_DIM)) key = KEY_LxDIMx;
   elif(KeysInString3(string, STR_L, STR_P, STR_DIM)) key = KEY_LxDIMx;
   elif(KeysInString3(string, STR_L, STR_Z, STR_DIM)) key = KEY_LxDIMx;
   elif(KeysInString2(string, STR_L, STR_U))
   {
      while(isdigit(*string)) string++;
      if(KeysInString1(string, STR_DIM)) key = KEY_LxDIMx;
   }
   elif(KeysInString3(string, STR_P, STR_L, STR_DIM)) key = KEY_PxDIMx;
   elif(KeysInString3(string, STR_P, STR_P, STR_DIM)) key = KEY_PxDIMx;
   elif(KeysInString3(string, STR_P, STR_Z, STR_DIM)) key = KEY_PxDIMx;
   elif(KeysInString2(string, STR_P, STR_U))
   {
      while(isdigit(*string)) string++;
      if(KeysInString1(string, STR_DIM)) key = KEY_PxDIMx;
   }
   elif(KeysInString3(string, STR_Z, STR_L, STR_DIM)) key = KEY_ZxDIMx;
   elif(KeysInString3(string, STR_Z, STR_P, STR_DIM)) key = KEY_ZxDIMx;
   elif(KeysInString3(string, STR_Z, STR_Z, STR_DIM)) key = KEY_ZxDIMx;
   elif(KeysInString2(string, STR_Z, STR_U))
   {
      while(isdigit(*string)) string++;
      if(KeysInString1(string, STR_DIM)) key = KEY_ZxDIMx;
   }
   elif(KeysInString1(string, STR_U))
   {
      while(isdigit(*string)) string++;

        if(KeysInString1(string, STR_IF))         key = KEY_UIFx;
      elif(KeysInString1(string, STR_OR))         key = KEY_UORx;
      elif(KeysInString1(string, STR_AND))        key = KEY_UANDx;
      elif(KeysInString1(string, STR_THEN))       key = KEY_xTHENx;
      elif(KeysInString1(string, STR_ELSE))       key = KEY_xELSEx;
      elif(KeysInString2(string, STR_L, STR_DIM)) key = KEY_UxDIMx;
      elif(KeysInString2(string, STR_P, STR_DIM)) key = KEY_UxDIMx;
      elif(KeysInString2(string, STR_Z, STR_DIM)) key = KEY_UxDIMx;
      elif(KeysInString1(string, STR_U))
      {
         while(isdigit(*string)) string++;
         if(KeysInString1(string, STR_DIM)) key = KEY_UxDIMx;
      }
   }

   if(!strlen(string))
      return key;

   switch(key)
   {
      case KEY_LIFx:
      case KEY_PIFx:
      case KEY_ZIFx:
      case KEY_UIFx:
      case KEY_LANDx:
      case KEY_PANDx:
      case KEY_ZANDx:
      case KEY_UANDx:
      case KEY_LORx:
      case KEY_PORx:
      case KEY_ZORx:
      case KEY_UORx:
         if(KeysInString1(string, STR_IF));
         if(KeysInString1(string, STR_NOT));

         if(!strlen(string))
            return key;

         if(KeyIsString(string, STR_ASK) ||
            KeyIsString(string, STR_USR) ||
            KeyIsString(string, STR_WHY) ||
            KeyIsString(string, STR_SHW) ||
            KeyIsString(string, STR_RUN))
            return key;

         if(KeyIsString(string, STR_ON) ||
            KeyIsString(string, STR_OFF))
            return key;

         if(KeysInString1(string, STR_LAY))
         {
            if(KeyIsString(string, STR_ON)  ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_BKW) ||
               KeyIsString(string, STR_FRW))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_RUL))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_REL))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_CON))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_ACT))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_GRD) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_DIM))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_GRD) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         return -1;

      case KEY_LxDIMx:
      case KEY_PxDIMx:
      case KEY_ZxDIMx:
      case KEY_UxDIMx:

         if(KeysInString1(string, STR_NOT));

         if(!strlen(string))
            return key;

         if(KeyIsString(string, STR_USR) ||
            KeyIsString(string, STR_SHW) ||
            KeyIsString(string, STR_RUN))
            return key;

         if(KeyIsString(string, STR_ON) ||
            KeyIsString(string, STR_OFF))
            return key;

         if(KeyIsString(string, STR_BKW) ||
            KeyIsString(string, STR_FRW))
            return key;

         if(KeysInString1(string, STR_LAY))
         {
            if(KeyIsString(string, STR_ON)  ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_BKW) ||
               KeyIsString(string, STR_FRW))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_RUL))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_REL))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF))
               return key;

            return -1;
         }
         elif(KeysInString1(string, STR_CON)) {

            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_ACT))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_GRD) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_DIM))
         {
            if(KeyIsString(string, STR_ON)  ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_GRD) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         return -1;

      case KEY_INITx:
      case KEY_xTHENx:
      case KEY_xELSEx:
         if(KeysInString1(string, STR_NOT));

         if(!strlen(string))
            return key;

         if(KeyIsString(string, STR_ON) ||
            KeyIsString(string, STR_OFF))
            return key;

         if(KeyIsString(string, STR_INF) ||
            KeyIsString(string, STR_USR) ||
            KeyIsString(string, STR_HOW) ||
            KeyIsString(string, STR_SHW) ||
            KeyIsString(string, STR_RUN))
            return key;

         if(KeysInString1(string, STR_INV))
            if(KeyIsString(string, STR_LAY))
               return key;
            else
               return -1;

         if(KeysInString1(string, STR_LAY))
         {
            if(KeyIsString(string, STR_ON)  ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_BKW) ||
               KeyIsString(string, STR_FRW))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_RUL))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_REL))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_CON))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_ACT))
         {
            if(KeyIsString(string, STR_ON) ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_GRD) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         if(KeysInString1(string, STR_DIM))
         {
            if(KeyIsString(string, STR_ON)  ||
               KeyIsString(string, STR_OFF) ||
               KeyIsString(string, STR_GRD) ||
               KeyIsString(string, STR_CUT))
               return key;

            if(!strlen(string))
               return key;

            return -1;
         }

         return -1;

      default:
         return -1;
   }
}


/* static string-functions */

FUNCTION(char *StringToUpper,
   (char *string),
   (string),
   char *string;
)
{
   char *c;

   for(c = string; *c = toupper(*c); c++);

   return string;
}


FUNCTION(char *StringToLower,
   (char *string),
   (string),
   char *string;
)
{
   char *c;

   for(c = string; *c = tolower(*c); c++);

   return string;
}


FUNCTION(char *StripString,
   (char *string),
   (string),
   char *string;
)
{
   int index, length;

   if(!string || !(length = strlen(string)))
      return string;

   index = 0;

   while(isspace(string[index]) && index < length)
      index++;

   memmove(&string[0], &string[index], (length - index + 1)*sizeof(char));

   if((length = strlen(string)) == 0)
      return string;

   index = length - 1;

   while(isspace(string[index]) && index >= 0)
      index--;

   string[index + 1] = 0;

   return string;
}


FUNCTION(char *InsertString,
   (char *string, char *substr),
   (string, substr),
   char *string;
   char *substr;
)
{
   int len;
   char *str;

   str = string;
   len = strlen(substr);

   memmove(string + len, string, (strlen(string) + 1)*sizeof(char));

   while(len--)
      *str++ = *substr++;

   return string;
}


FUNCTION(char *ShiftString,
   (char *string, int pos),
   (string, pos),
   char *string;
   int pos;
)
{
   int len;

   len = strlen(string) + 1;

   if(pos)
      memmove(string + pos, string, len*sizeof(char));

   if(pos > 0)
      memset(string, CHR_SPACE, pos*sizeof(char));

   return string + pos;
}


FUNCTION(char *ReplaceString,
   (char *string, char *oldstr, char *newstr),
   (string, oldstr, newstr),
   char *string;
   char *oldstr;
   char *newstr;
)
{
   char *start, *rest;
   int length;

   if((start = strstr(string, oldstr)) != NULL) {

      rest = start + strlen(oldstr);

      length = strlen(string) - strlen(oldstr) + strlen(newstr);

      memmove(start + strlen(newstr), start + strlen(oldstr), strlen(rest));

      string[length] = 0;

      while(*newstr)
         *start++ = *newstr++;
   }

   return string;
}


