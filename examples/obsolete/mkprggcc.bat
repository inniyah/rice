rem File:   mkprggcc.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for making Gnu C MAKE-file
rem         or making one of the RICE examples:
rem            %1    : program name
rem            %2    : source file extension
rem            %3-%9 : extra compiler options

echo %1.exe: %1 > makefile
echo    aout2exe %1 >> makefile
echo    if exist %1 del %1 >> makefile

echo. >> makefile

echo %1: %1.o >> makefile
echo    gcc -o %1 %1.o ../lib/rice.a -lpc -lm >> makefile

echo. >> makefile

echo %1.o: %1.%2 >> makefile
if X%1X==Xsimple3xX echo    copy simple3x.lnk rice.lnk >> makefile
if X%1X==Xsimple3xX echo    copy simple3x.cod rice.cod >> makefile
echo    gcc -c -I../include %3 %4 %5 %6 %7 %8 %9 %1.%2 >> makefile
if X%1X==Xsimple3xX echo    del rice.lnk >> makefile
if X%1X==Xsimple3xX echo    del rice.cod >> makefile

