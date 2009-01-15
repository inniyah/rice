rem File:   mkliball.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for generating makefile for RICE library, see makelib.doc;
rem         meaning of arguments:
rem            %1 : source path
rem            %2 : source extension
rem            %3 : include path
rem            %4 : include extension
rem            %5 : object path
rem            %6 : object extension
rem            %7 : compiler type
rem            %8 : library name

echo # makefile for %7 RICE-library > makefile

echo. >> makefile

echo OBJECTS = \        >> makefile
echo    %5compile1.%6 \ >> makefile
echo    %5compile2.%6 \ >> makefile
echo    %5compile3.%6 \ >> makefile
echo    %5compile4.%6 \ >> makefile
echo    %5destroy.%6  \ >> makefile
echo    %5explain.%6  \ >> makefile
echo    %5global.%6   \ >> makefile
echo    %5infer.%6    \ >> makefile
echo    %5load.%6     \ >> makefile
echo    %5rebuild.%6  \ >> makefile
echo    %5save.%6       >> makefile

echo. >> makefile

echo HEADERS = \        >> makefile
echo    %3compile.%4  \ >> makefile
echo    %3define.%4   \ >> makefile
echo    %3function.%4 \ >> makefile
echo    %3include.%4  \ >> makefile
echo    %3rebuild.%4  \ >> makefile
echo    %3type.%4     \ >> makefile
echo    %3variable.%4   >> makefile

echo. >> makefile

echo %8: $(OBJECTS) >> makefile
echo. >> makefile

echo %5compile1.%6: %1compile1.%2 %3compile.%4 $(HEADERS) >> makefile
call mklib%7 compile1

echo. >> makefile

echo %5compile2.%6: %1compile2.%2 %3compile.%4 $(HEADERS) >> makefile
call mklib%7 compile2

echo. >> makefile

echo %5compile3.%6: %1compile3.%2 %3compile.%4 $(HEADERS) >> makefile
call mklib%7 compile3

echo. >> makefile

echo %5compile4.%6: %1compile4.%2 %3compile.%4 $(HEADERS) >> makefile
call mklib%7 compile4

echo. >> makefile

echo %5destroy.%6: %1destroy.%2 $(HEADERS) >> makefile
call mklib%7 destroy

echo. >> makefile

echo %5explain.%6: %1explain.%2 %3rebuild.%4 $(HEADERS) >> makefile
call mklib%7 explain

echo. >> makefile

echo %5global.%6: %1global.%2 $(HEADERS) >> makefile
call mklib%7 global

echo. >> makefile

echo %5infer.%6: %1infer.%2 $(HEADERS) >> makefile
call mklib%7 infer

echo. >> makefile

echo %5load.%6: %1load.%2 $(HEADERS) >> makefile
call mklib%7 load

echo. >> makefile

echo %5rebuild.%6: %1rebuild.%2 %3rebuild.%4 $(HEADERS) >> makefile
call mklib%7 rebuild

echo. >> makefile

echo %5save.%6: %1save.%2 $(HEADERS) >> makefile
call mklib%7 save


