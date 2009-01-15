/*
   File:   simple3x.c
   Author: Rene' Jager
   Update: December 11, 1992
   Info:   simple upgrade example RICE 3.x application, see file rice3x.doc
*/


/* standard include files */

#include <conio.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>


/* include rice.c so it will always be compiled along with this file... */

#include <rice.c>


/* application specific user i/o functions */

void ask(char *fact, float *grade)
{
   char c, ans[10];
   printf("%s ? ", fact);
   do {
      scanf("%5s", ans);
      if(sscanf(ans, "%g", grade) != 1)
      {
         sscanf(ans, "%c", &c);
         if(c == 'Y' || c == 'y')
            *grade = 1.0;
         else
            if(c == 'N' || c == 'n')
               *grade = 0.0;
      }
   } while(*grade != -1.0 && (*grade < 0.0 || 1.0 < *grade));
}

void inform(char *fact, float *grade)
{
   printf("%s ", fact);
   if(*grade == 1.0)
      printf("!\n");
   else
      printf("! %g\n", *grade);
}
     
void report(int type, char *msg, void *data)
{
   switch(type)
   {
      case 1: printf("ERROR: ");   break;
      case 2: printf("WARNING: "); break;
      case 3: printf("MESSAGE: "); break;
   }

   printf("%s", msg);
   if(data) printf(" (%s)", (char *) data);
   printf("\n");
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


/* in this example not really possible to have stack overflow... */

#ifdef __BORLANDC__
extern unsigned _stklen = 10000U;
#endif


/* main function */

int main(void)
{
   int command;
   char filename[13];

   /* redirect i/o to user i/o functions (see above) */

   RedirectAsk(ask);
   RedirectInform(inform);
   RedirectReport(report);

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
         case '1': CompileKB(get_name(command, filename)); break;
         case '2': LoadKB(get_name(command, filename));    break;
         case '3': SaveKB(get_name(command, filename));    break;
         case '4': RebuildKB(get_name(command, filename)); break;
         case '5': InferKB();                              break;
         case '6': ClearKB();                              break;
         case '7': DestroyKB();                            break;

         default:
            command = 0;
      }
   }
   while(command);

   return 0;
}

