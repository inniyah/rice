/*
   File:   minimal.c
   Author: Rene' Jager
   Update: December 20, 1992
   Info:   minimal example for RICE
*/


/* standard include files */

#include <stdio.h>
#include <ctype.h>


/* include rice.h */

#include <rice.h>


/* increase stack length for Borland compiler */

#ifdef __BORLANDC__
extern unsigned _stklen = 10000U;
#endif


/* main function */

int main(int argc, char *argv[])
{
   int theES = rice_CreateES();
   rice_LoadKB(theES, argv[1]);
   rice_InferKB(theES);
   return 0;
}

