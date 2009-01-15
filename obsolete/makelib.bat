@echo off

rem File:   makelib.bat
rem Author: Rene' Jager
rem Update: June 11, 1993
rem Info:   utility for making a makefile for a
rem         RICE library for different compilers

rem            %1 : source path
rem            %2 : source extension
rem            %3 : include path
rem            %4 : include extension
rem            %5 : object path
rem            %6 : object extension
rem            %7 : compiler

if X%1X==XX goto show

rem default memory models
if X%RICEMODEL%%1X==XbccX set RICEMODEL=l
if X%RICEMODEL%%1X==XmscX set RICEMODEL=L

rem object module directory
if X%1X==XbccX call mklibdir object object\%RICEMODEL%
if X%1X==XgccX call mklibdir object
if X%1X==XmscX call mklibdir object object\%RICEMODEL%

rem building makefile
if X%1X==XbccX call mkliball ..\source\ c ..\include\ h object\%RICEMODEL%\ obj bcc ricel.lib
if X%1X==XgccX call mkliball ../source/ c ../include/ h object/ o gcc rice.a
if X%1X==XmscX call mkliball ..\source\ c ..\include\ h object\%RICEMODEL%\ obj msc riceL.lib

if X%1%2X==XbccX make
if X%1%2X==XgccX make
if X%1%2X==XmscX nmake
if X%2X==XX goto end
%2

goto end

:show
echo Use: MakeLib compiler [make]
echo compiler = bcc, gcc or msc
echo make     = you own make-utility

:end
if exist *.bak del *.bak > nul
set RICEMODEL=

