/*
   File:   simpleec.c
   Author: Rene' Jager
   Update: December 11 1992
   Info:   simple example for RICE
*/


/* standard include files */

#include <conio.h>
#include <stdio.h>
#include <ctype.h>

/* include riceeasy.h */

#include <riceeasy.h>


/* application specific user i/o functions */

void ask(int kb, int argc, char *argv[], float *grade)
{
   char c, ans[10];
   int i;

   printf("%s ", argv[0]);
   if(argc > 1) printf("(");
   for(i = 1; i < argc - 1; i++) printf("%s, ", argv[i]);
   if(argc > 1) printf("%s) ", argv[argc - 1]);
   printf("? ");

   do {
      scanf("%5s", ans);
      if(sscanf(ans, "%g", grade) != 1)
      {
         sscanf(ans, "%c", &c);
         if(c == 'Y' || c == 'y')
            *grade = RICE_TRUE;
         else
            if(c == 'N' || c == 'n')
               *grade = RICE_FALSE;
      }
   } while(*grade != UNKNOWN && (*grade < FALSE || TRUE < *grade));
}

void inform(int kb, int argc, char *argv[], float *grade)
{
   int i;

   printf("%s ", argv[0]);
   if(argc > 1) printf("(");
   for(i = 1; i < argc - 1; i++) printf("%s, ", argv[i]);
   if(argc > 1) printf("%s) ", argv[argc - 1]);
   if(*grade == TRUE)
      printf("!\n");
   else
      printf("! %g\n", *grade);
}
     
void report(int kb, int type, char *msg)
{
   switch(type)
   {
      case ERROR:   printf("ERROR: ");   break;
      case WARNING: printf("WARNING: "); break;
      case MESSAGE: printf("MESSAGE: "); break;
   }

   printf("%s\n", msg);
}


/* get file name from user */

char *get_name(int command, char *filename)
{
   switch(command)
   {
      case '1': printf("File to compile from: "); break;
      case '2': printf("File to load from   : "); break;
      case '3': printf("File to save to     : "); break;
      case '4': printf("File to rebuild to  : "); break;
   }

   scanf("%s", filename);
   return filename;
}


/* to prevent possible stack overflow... */

#ifdef __BORLANDC__
extern unsigned _stklen = 10000U;
#endif


/* linking facts with C-code */

Linker(linker)
{
   Link("beep", printf("\x7"));
}

LINKER linkerPointer[] = {linker};


/* main function */

int main(void)
{
   int command, theES;
   char filename[13];

   /* create es */
   theES = CreateES();

   /* redirect i/o to user i/o functions (see above) */
   RedirectAsk(theES, ask);
   RedirectInform(theES, inform);
   RedirectReport(theES, report);

   /* link linker to es */
   UseLinker(theES, 1, linkerPointer);

   /* do loop while not exit command or error */
   do
   {
      printf("\n1 : compile\n");
      printf("2 : load\n");
      printf("3 : save\n");
      printf("4 : rebuild\n");
      printf("5 : infer\n");
      printf("6 : clear\n");
      printf("7 : destroy\n\n");
      printf("0 : exit\n");

      command = getch();

      switch(command)
      {
         case '1': CompileKB(theES, get_name(command, filename)); break;
         case '2': LoadKB(theES, get_name(command, filename));    break;
         case '3': SaveKB(theES, get_name(command, filename));    break;
         case '4': RebuildKB(theES, get_name(command, filename)); break;
         case '5': InferKB(theES);                                break;
         case '6': ClearKB(theES);                                break;
         case '7': DestroyKB(theES);                              break;

         default:
            command = 0;
      }
   }
   while(command);

   return 0;
}

