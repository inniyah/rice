rem File:   mklibbdir.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for generating directories for RICE library object
rem         modules, see makelib.doc; meaning of arguments:
rem            %1-%? : directories to be made

:loop
if X%1X==XX goto end
md %1
shift
goto loop
:end

