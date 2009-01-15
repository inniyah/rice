rem File:   mkprgbcc.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for making Borland C MAKE-file
rem         or making one of the RICE examples:
rem            %1    : program name
rem            %2    : source file extension
rem            %3    : memory model
rem            %4    : compiler directory
rem            %5-%9 : extra compiler options

echo %1.exe: %1.obj > makefile
echo    tlink /s @response >> makefile

echo %4\lib\c0%3.obj+ > response
echo %1.obj >> response
echo %1 >> response
echo. >> response
echo ..\lib\rice%3.lib+ >> response
echo %4\lib\emu.lib+ >> response
echo %4\lib\math%3.lib+ >> response
echo %4\lib\c%3.lib+ >> response
echo %4\lib\graphics.lib >> response

echo. >> makefile

echo %1.obj: %1.%2 >> makefile
if X%1X==Xsimple3xX echo    copy simple3x.lnk rice.lnk >> makefile
if X%1X==Xsimple3xX echo    copy simple3x.cod rice.cod >> makefile
echo    bcc -c -m%3 -I%4\include -I..\include %5 %6 %7 %8 %9 %1.%2 >> makefile
if X%1X==Xsimple3xX echo    del rice.lnk >> makefile
if X%1X==Xsimple3xX echo    del rice.cod >> makefile

