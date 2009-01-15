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

// File:   rice.hpp
// Author: Rene' Jager
// Update: December 6, 1992
// Info:   C++ include file for RICE, see file rice.doc


// check compiler type

#ifndef __cplusplus
#   error C++ compiler required for RICE class.
#endif


// prevent extra compilation

#ifndef _RICE_HPP_
#define _RICE_HPP_


// include C header file if not already done

#ifndef _RICE_H_
#   include <rice.h>
#endif


// class definition

class RICE
{
protected:

   int id;

public:

   // constructors

   RICE()
   {
      id = rice_CreateES();
   }

   RICE(RICE& es)
   {
      id = rice_CopyES(0, es.id);
   }

   // destructor

   ~RICE()
   {
      rice_DeleteES(id);
   }

   // operators

   RICE& operator =(RICE& es)
   {
      rice_CopyES(id, es.id); return *this;
   }

   RICE& operator =(char *str)
   {
      rice_CompileKB(id, str); return *this;
   }

   RICE& operator +=(char *str)
   {
      rice_AppendKB(id, str); return *this;
   }

   // redirection functions

   int RedirectAsk(void (*fnc)(int, int, char *[], float *))
   {
      return rice_RedirectAsk(id, fnc);
   }

   int RedirectInform(void (*fnc)(int, int, char *[], float *))
   {
      return rice_RedirectInform(id, fnc);
   }

   int RedirectReport(void (*fnc)(int, int, char *))
   {
      return rice_RedirectReport(id, fnc);
   }

   int RedirectExplain(void (*fnc)(int, char *))
   {
      return rice_RedirectExplain(id, fnc);
   }

   int RedirectProtect(void (*fnc)(int))
   {
      return rice_RedirectProtect(id, fnc);
   }

   int RedirectAbandon(void (*fnc)(void))
   {
      return rice_RedirectAbandon(id, fnc);
   }

   // explaination functions

   int ExplainHow(char *fct, int dpt)
   {
      return rice_ExplainHow(id, fct, dpt);
   }

   int ExplainWhy(char *fct, int dpt)
   {
      return rice_ExplainWhy(id, fct, dpt);
   }

   // set, reset and switch functions

   int SetAdaptive(int act = 1)    { return rice_SetAdaptive(id, act);    }
   int SetInteractive(int act = 1) { return rice_SetInteractive(id, act); }
   int SetRecursive(int act = 1)   { return rice_SetRecursive(id, act);   }
   int SetRepetitive(int act = 1)  { return rice_SetRepetitive(id, act);  }
   int SetSelective(int act = 1)   { return rice_SetSelective(id, act);   }

   int ResetAdaptive()    { return rice_SetAdaptive(id, 0);    }
   int ResetInteractive() { return rice_SetInteractive(id, 0); }
   int ResetRecursive()   { return rice_SetRecursive(id, 0);   }
   int ResetRepetitive()  { return rice_SetRepetitive(id, 0);  }
   int ResetSelective()   { return rice_SetSelective(id, 0);   }

   int SwitchAdaptive()    { return rice_SetAdaptive(id, -1);    }
   int SwitchInteractive() { return rice_SetInteractive(id, -1); }
   int SwitchRecursive()   { return rice_SetRecursive(id, -1);   }
   int SwitchRepetitive()  { return rice_SetRepetitive(id, -1);  }
   int SwitchSelective()   { return rice_SetSelective(id, -1);   }

   // use functions

   int UseLinker(int num, RICE_LINKER *lnk)
   {
      return rice_UseLinker(id, num, lnk);
   }

   int UseIntersection(int num, RICE_NORM *nrm)
   {
      return rice_UseIntersection(id, num, nrm);
   }

   int UseUnion(int num, RICE_NORM *nrm)
   {
      return rice_UseUnion(id, num, nrm);
   }

   // interfacing functions

   int AppendKB(char *str)   { return rice_AppendKB(id, str);  }
   int ClearKB()             { return rice_ClearKB(id);        }
   int CompileKB(char *str)  { return rice_CompileKB(id, str); }
   int DestroyKB()           { return rice_DestroyKB(id);      }
   int InferKB()             { return rice_InferKB(id);        }
   int LoadKB(char *str)     { return rice_LoadKB(id, str);    }
   int RebuildKB(char *str)  { return rice_RebuildKB(id, str); }
   int SaveKB(char *str)     { return rice_SaveKB(id, str);    }
   int SwapKB(void (*fnc)()) { return rice_SwapKB(id, fnc);    }
   int CopyKB(RICE& es)      { return rice_CopyKB(id, es.id);  }
   int MoveKB(RICE& es)      { return rice_MoveKB(id, es.id);  }
};

                                        
#endif // _RICE_HPP_

