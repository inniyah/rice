rem File:   mkprgmsc.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for making Microsoft C MAKE-file
rem         or making one of the RICE examples:
rem            %1    : program name
rem            %2    : source file extension
rem            %3    : memory model
rem            %4    : compiler directory
rem            %5-%9 : extra compiler options

echo %1.exe: %1.obj > makefile
echo    link /STACK:10000 @response >> makefile

echo %1.obj > response
echo %1 >> response
echo. >> reponse
echo ..\lib\rice%3.lib+ >> response
echo %4\lib\%4libce.lib+ >> response
echo %4\lib\graphics.lib+ >> response
echo %4\lib\oldnames.lib; >> response

echo. >> makefile

echo %1.obj: %1.%2 >> makefile
if X%1X==Xsimple3xX echo    copy simple3x.lnk rice.lnk >> makefile
if X%1X==Xsimple3xX echo    copy simple3x.cod rice.cod >> makefile
echo    cl /c /A%3 /I%4\include /I..\include %5 %6 %7 %8 %9 %1.%2 >> makefile
if X%1X==Xsimple3xX echo    del rice.lnk >> makefile
if X%1X==Xsimple3xX echo    del rice.cod >> makefile

