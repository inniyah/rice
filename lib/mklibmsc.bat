rem File:   mklibmsc.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for generating makefile for RICE library, see makelib.doc;
rem         meaning of arguments:
rem            %1 : module name

echo    cl /c /A%RICEMODEL% /I..\include /Foobject\%RICEMODEL%\%1.obj ..\source\%1.c >> makefile
echo    lib rice%RICEMODEL%.lib -+object\%RICEMODEL%\%1.obj >> makefile


