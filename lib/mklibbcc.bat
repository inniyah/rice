rem File:   mklibbcc.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for generating makefile for RICE library, see makelib.doc;
rem         meaning of arguments:
rem            %1 : module name

echo    bcc -c -m%RICEMODEL% -I..\include -oobject\%RICEMODEL%\%1.obj ..\source\%1.c >> makefile
echo    tlib rice%RICEMODEL%.lib -+object\%RICEMODEL%\%1.obj >> makefile

