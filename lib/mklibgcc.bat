rem File:   mklibgcc.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for generating makefile for RICE library, see makelib.doc;
rem         meaning of arguments:
rem            %1 : module name

echo    gcc -c -I../include -o object/%1.o ../source/%1.c >> makefile
echo    ar r rice.a object/%1.o                 >> makefile


