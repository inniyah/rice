/*
   File:   game.c
   Author: Rene' Jager
   Update: June 17, 1993
   Info:   game example for RICE
*/


/* header files */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include <rice.h>


/* global variables */

int stopGame = 0, autoGame = 0;
int myMark, yourMark, emptyMark = ' ';
int xTable[] = {0, 36, 40, 44}, yTable[] = {0, 10, 12, 14};
int fieldTable[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int nrOfMoves = 0;


/* compiler dependent functions, for different compilers: adjust code */

#if defined(_MSC_VER) || defined(_QC)
#   define __MICROSOFTC__
#endif


#if defined(__MICROSOFTC__)

/* this part is coded for use with Microsoft C(++) 7.00 compiler */

#if defined(_WIN32)

#include <windows.h>

/* hiding and showing cursor */

#define hideCursor()   ShowCursor(FALSE)
#define showCursor()   ShowCursor(TRUE)

/* clear screen */

#define clearScreen() _clearscreen(_GCLEARSCREEN)

#else

#include <graph.h>

/* hiding and showing cursor */

#define hideCursor()   _displaycursor(_GCURSOROFF)
#define showCursor()   _displaycursor(_GCURSORON)

/* clear screen */

#define clearScreen() _clearscreen(_GCLEARSCREEN)
 
#endif

/* goto position on screen */

#define gotoPos(x, y) _settextposition(y, x)


/* goto position and put character */

#define putChar(x, y, c) gotoPos(x, y); _putch(c)


/* write mark to screen */

void putMark(int x, int y, int c)
{
   putChar(xTable[x], yTable[y], c);
   fieldTable[x - 1][y - 1] = c;
}

#elif defined(__BORLANDC__)


/* this part is coded for use with Borland C(++) 3.1 compiler */

#include <conio.h>


/* hiding and showing cursor */

#define hideCursor()   _setcursortype(_NOCURSOR)
#define showCursor()   _setcursortype(_NORMALCURSOR)
 

/* goto position on screen */

#define gotoPos(x, y) gotoxy(x, y)


/* goto position and put character */

#define putChar(x, y, c) gotoPos(x, y); putchar(c)


/* write mark to screen */

void putMark(int x, int y, int c)
{
   unsigned char buf[2];
   gettext(xTable[x], yTable[y], xTable[x], yTable[y], buf);
   fieldTable[x - 1][y - 1] = buf[0] = c;
   puttext(xTable[x], yTable[y], xTable[x], yTable[y], buf);
}


/* clear screen */

#define clearScreen() clrscr()


/* increase stack length */

extern unsigned _stklen = 10000U;

#elif defined(__GNUC__) & defined(__MSDOS__)


/* this part is coded for use with Gnu C++ (DJGPP 2.4.1) compiler */

#include <conio.h>   /* dummy header file including gppconio.h */


/* hiding and showing cursor */

#define hideCursor()   _setcursortype(_NOCURSOR)
#define showCursor()   _setcursortype(_NORMALCURSOR)
 

/* goto position on screen */

#define gotoPos(x, y) gotoxy(x, y)


/* goto position and put character */

#define putChar(x, y, c) gotoPos(x, y); putch(c)


/* write mark to screen */

void putMark(int x, int y, int c)
{
   unsigned char buf[2];
   gettext(xTable[x], yTable[y], xTable[x], yTable[y], buf);
   fieldTable[x - 1][y - 1] = buf[0] = c;
   puttext(xTable[x], yTable[y], xTable[x], yTable[y], buf);
}


/* clear screen */

#define clearScreen() clrscr()


#else
#   error Compiler should be Microsoft C/C++ 7.0 or Borland C++ 3.1
#endif


/* prototypes */

void printMsg(char *, ...);


/* get mark from field */

int getMark(int x, int y)
{
   return fieldTable[x - 1][y - 1];
}


/* sawp marks */

void SwapMark(int *m1, int *m2)
{
   int m;

   m = *m1;
   *m1 = *m2;
   *m2 = m;
}


/* do error */

void doError(char *msg)
{
   gotoPos(1, 15);
   printMsg(0);
   gotoPos(1, 15);
   printMsg("\x7Error: %s\n", msg);
}

void redirError(int kb, int type, char *msg)
{
   doError(msg);
}


/* show message from kb */

void showInfo(char *msg)
{
   if(autoGame)   /* just play, don't talk */
      return;

   gotoPos(1, 15);
   printMsg(0);
   gotoPos(1, 15);
   printMsg(msg);
}

void redirInfo(int kb, int argc, char *argv[], float *grade)
{
   showInfo(argv[0]);
}


/* show field on screen */

void makeField(void)
{
   int x, y;

   x = xTable[2];
   y = yTable[2];

   putChar(x - 7, y - 2, 'a');
   putChar(x - 7, y,     'b');
   putChar(x - 7, y + 2, 'c');

   putChar(x - 4, y - 3, '1');
   putChar(x,     y - 3, '2');
   putChar(x + 4, y - 3, '3');

   putChar(x - 2, y - 2, 179);
   putChar(x - 2, y - 1, 179);
   putChar(x - 2, y,     179);
   putChar(x - 2, y + 1, 179);
   putChar(x - 2, y + 2, 179);
   putChar(x + 2, y - 2, 179);
   putChar(x + 2, y - 1, 179);
   putChar(x + 2, y    , 179);
   putChar(x + 2, y + 1, 179);
   putChar(x + 2, y + 2, 179);

   putChar(x - 5, y - 1, 196);
   putChar(x - 4, y - 1, 196);
   putChar(x - 3, y - 1, 196);
   putChar(x - 3, y + 1, 196);
   putChar(x - 4, y + 1, 196);
   putChar(x - 5, y + 1, 196);
   putChar(x - 1, y - 1, 196);
   putChar(x,     y - 1, 196);
   putChar(x + 1, y + 1, 196);
   putChar(x - 1, y + 1, 196);
   putChar(x,     y + 1, 196);
   putChar(x + 1, y - 1, 196);
   putChar(x + 5, y - 1, 196);
   putChar(x + 4, y - 1, 196);
   putChar(x + 3, y - 1, 196);
   putChar(x + 3, y + 1, 196);
   putChar(x + 4, y + 1, 196);
   putChar(x + 5, y + 1, 196);

   putChar(x - 2, y - 1, 197);
   putChar(x - 2, y + 1, 197);
   putChar(x + 2, y - 1, 197);
   putChar(x + 2, y + 1, 197);
}


/* get position */

int getPos(int argc, char *argv[], int *x, int *y)
{
   if(argc != 2)
   {
      doError("incomplete position");
      return -1;
   }
   *x = argv[1][1] - '1' + 1;
   *y = argv[1][0] - 'a' + 1;
   if(*x < 1 || 3 < *x || *y < 1 || 3 < *y)
   {
      doError("incorrect position");
      return -1;
   }
   return 0;
}


/* print a message */

void printMsg(char *msg, ...)
{
   va_list arguments;

   if(!msg)    /* clear line: dirty, but working */
      printf("                                       ");
   else
   {
      va_start(arguments, msg);
      vprintf(msg, arguments);
      va_end(arguments);
   }
   fflush(stdout);
}


/* get your mark */

void getYourMark(void)
{
   do {
      gotoPos(1, 25);
      printMsg(0);
      gotoPos(1, 25);
      showCursor();
      printMsg("Put your mark (o/x): ");
      yourMark = getche();
      hideCursor();
   } while(yourMark != 'o' && yourMark != 'x');

   myMark = (yourMark == 'o') ? 'x' : 'o';
}


/* get your move */

void getMove(void)
{
   int x, y;
   do {
      do {
         gotoPos(1, 25);
         printMsg(0);
         gotoPos(1, 25);
         showCursor();
         printMsg("Your move [a..c][1..3]: ");
         fflush(stdout);
         y = getche();
         y -= 'a' - 1;
         x = getche();
         x -= '1' - 1;
         hideCursor();
      } while(x < 1 || x > 3 || y < 1 || y > 3);
   } while(getMark(x, y) != emptyMark);

   putMark(x, y, yourMark);
   nrOfMoves++;
   gotoPos(1, 25);
   printMsg(0);
}


/* linker function */

RICE_Linker(theLinkerFunction)
{
   RICE_Link("put me on",
   {
      int x; int y;
      if(getPos(rice_argc, rice_argv, &x, &y)) return;
      putMark(x, y, myMark);
      nrOfMoves++;
   });

   RICE_Link("I am on",
   {
      int x; int y;
      if(getPos(rice_argc, rice_argv, &x, &y)) return;
      *rice_grade = (getMark(x, y) == myMark) ? 1.0 : 0.0;
   });

   RICE_Link("you are on",
   {
      int x; int y;
      if(getPos(rice_argc, rice_argv, &x, &y)) return;
      *rice_grade = (getMark(x, y) == yourMark) ? 1.0 : 0.0;
   });

   RICE_Link("is empty",
   {
      int x; int y;
      if(getPos(rice_argc, rice_argv, &x, &y)) return;
      *rice_grade = (getMark(x, y) == emptyMark) ? 1.0 : 0.0;
   });

   RICE_Link("put me somewhere",
      putMark(1 + rand()%3, 1 + rand()%3, myMark);
      nrOfMoves++;
   );

   RICE_Link("stop the game", stopGame = 1);
}

RICE_LINKER theLinker = theLinkerFunction;


/* main function */

#define GAME_KB "game.kb"

int main(int argc, char *argv[])
{
   int theES, theOtherES = 0;

   /* init dice */
   srand(time(0));

   /* auto game */
   autoGame = (argc > 1);

   /* put field on screen */
   hideCursor();
   clearScreen();
   makeField();

   /* create and set up knowledge base */
   theES = rice_CreateES();
   rice_SetInteractive(theES, 0);
   rice_RedirectReport(theES, redirError);
   rice_RedirectInform(theES, redirInfo);
   rice_UseLinker(theES, 1, &theLinker);
   if(rice_CompileKB(theES, GAME_KB))
   {
      showCursor();
      exit(1);
   }

   if(autoGame)   /* if autonomous game */
   {
      theOtherES = rice_CopyES(0, theES);
      if(argc > 1 && rice_CompileKB(theOtherES, (argc > 1) ? argv[1] : GAME_KB))
      {
         showCursor();
         exit(1);
      }
   }

   /* get your mark */
   if(autoGame)
   {
      yourMark = 'x';
      myMark = 'o';
   }
   else
      getYourMark();

   /* throw dice for starting */
   if(rand() > RAND_MAX/2)   /* other is first */
      if(autoGame)
      {
         SwapMark(&yourMark, &myMark);
         rice_InferKB(theOtherES);
         SwapMark(&yourMark, &myMark);
      }
      else
         getMove();

   /* play game */
   while(!stopGame && nrOfMoves < 9)
   {
      rice_ClearKB(theES);
      rice_InferKB(theES);

      if(!stopGame && nrOfMoves < 9)
         if(autoGame)
         {
            SwapMark(&yourMark, &myMark);
            rice_ClearKB(theOtherES);
            rice_InferKB(theOtherES);
            SwapMark(&yourMark, &myMark);
         }
         else
            getMove();
   }

   /* goto bottom of screen */
   gotoPos(1, 25);

   /* clean up expert systems */
   rice_DeleteES(theES);
   if(theOtherES) rice_DeleteES(theOtherES);

   showCursor();

   return 0;
}

