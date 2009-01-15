// File:   simplepp.cpp
// Author: Rene' Jager
// Update: December 11, 1992
// Info:   simple C++ example for RICE


// standard include files

#include <ctype.h>
#include <iostream>
#include <stdio.h>


// include rice.h

#include <rice.h>


// application specific user i/o functions

void ask(int id, int argc, char *argv[], float *grade)
{
   char c, ans[10];
   int i;

   std::cout << argv[0];

   if(argc > 1) std::cout << '(';
   for(i = 1; i < argc - 1; i++) std::cout << argv[i] << ' ';
   if(argc > 1) std::cout << argv[argc - 1] << ") ";
   std::cout << "? ";

   do {
      std::cin >> ans;
      if(sscanf(ans, "%g", grade) != 1)
      {
         sscanf(ans, "%c", &c);
         if(c == 'Y' || c == 'y')
            *grade = RICE_TRUE;
         else
            if(c == 'N' || c == 'n')
               *grade = RICE_FALSE;
      }
   } while(*grade != RICE_UNKNOWN && (*grade < RICE_FALSE || RICE_TRUE < *grade));
}

void inform(int id, int argc, char *argv[], float *grade)
{
   int i;

   std::cout << argv[0];

   if(argc > 1) std::cout << '(';
   for(i = 1; i < argc - 1; i++) std::cout << argv[i] << ' ';
   if(argc > 1) std::cout << argv[argc - 1] << ") ";
   if(*grade == RICE_TRUE)
      std::cout << "!\n";
   else
      std::cout << "! " << *grade << '\n';
}
     
void report(int id, int type, char *msg)
{
   switch(type)
   {
      case RICE_ERROR:   std::cerr << "ERROR: ";   break;
      case RICE_WARNING: std::cerr << "WARNING: "; break;
      case RICE_MESSAGE: std::cerr << "MESSAGE: "; break;
   }

   std::cerr << msg << '\n';
}


// get file name from user

char *get_name(int command, char *filename)
{
   switch(command)
   {
      case '1': std::cout << "File to compile from: "; break;
      case '2': std::cout << "File to load from   : "; break;
      case '3': std::cout << "File to save to     : "; break;
      case '4': std::cout << "File to rebuild to  : "; break;
   }

   std::cin >> filename;
   return filename;
}


/* to prevent possible stack overflow... */

#ifdef __BORLANDC__
extern unsigned _stklen = 10000U;
#endif


/* some class */

class Beeper
{
public:
   void doIt() { std::cout << '\x7'; }
};

Beeper theBeeper;


/* linking facts with C-code */

RICE_Linker(linker)
{
   RICE_Link("beep", theBeeper.doIt());
}

RICE_LINKER linkerPointer[] = {linker};


/* main function */

int main()
{
   int command;
   char filename[13];
   RICE theES;
                        
   // redirect i/o to user i/o functions (see above)
   theES.RedirectAsk(ask);
   theES.RedirectInform(inform);
   theES.RedirectReport(report);

   /* link linker to es */
   theES.UseLinker(1, linkerPointer);

   /* do loop while not exit command or error */
   do
   {
      std::cout << "\n1 : compile\n"
           << "2 : load\n"
           << "3 : save\n"
           << "4 : rebuild\n"
           << "5 : infer\n"
           << "6 : clear\n"
           << "7 : destroy\n\n"
           << "0 : exit\n";

      std::cout.flush();
      command = getchar();

      switch(command)
      {
         case '1': theES.CompileKB(get_name(command, filename)); break;
         case '2': theES.LoadKB(get_name(command, filename));    break;
         case '3': theES.SaveKB(get_name(command, filename));    break;
         case '4': theES.RebuildKB(get_name(command, filename)); break;
         case '5': theES.InferKB();                              break;
         case '6': theES.ClearKB();                              break;
         case '7': theES.DestroyKB();                            break;

         default:
            command = 0;
      }
   }
   while(command);

   return 0;
}

