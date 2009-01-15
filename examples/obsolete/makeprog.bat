@echo off

rem File:   MakeProg.bat
rem Author: Rene' Jager
rem Date:   June 11, 1993
rem Info:   Batch-file for building a makefile for one of the RICE examples.
rem         The Borland and Microsoft directory are set to \borlandc and
rem         \c700; do a global search-and-replace to adjust... Also the
rem         memory models (for bcc and msc) are  set to large (l and L);
rem         replace if other memory model wanted...

if X%2X==XgameX     goto compiler
if X%2X==XminimalX  goto compiler
if X%2X==XsimpleX   goto compiler
if X%2X==XsimpleecX goto compiler
if X%2X==XsimpleppX goto compiler
if X%2X==Xsimple3xX goto compiler
goto show

:compiler
if X%1X==XbccX goto bcc
if X%1X==XgccX goto gcc
if X%1X==XmscX goto msc
goto show

:bcc
if X%2X==XgameX     call mkprgbcc %2 c   l \borlandc
if X%2X==XminimalX  call mkprgbcc %2 c   l \borlandc
if X%2X==XsimpleX   call mkprgbcc %2 c   l \borlandc
if X%2X==XsimpleecX call mkprgbcc %2 c   l \borlandc
if X%2X==XsimpleppX call mkprgbcc %2 cpp l \borlandc
if X%2X==Xsimple3xX call mkprgbcc %2 c   l \borlandc -I..\upgrade -DRICE_UPGRADE
goto make

:gcc
if X%2X==XgameX     call mkprggcc %2 c
if X%2X==XminimalX  call mkprggcc %2 c
if X%2X==XsimpleX   call mkprggcc %2 c
if X%2X==XsimpleecX call mkprggcc %2 c
if X%2X==XsimpleppX call mkprggcc %2 cxx
if X%2X==Xsimple3xX call mkprggcc %2 c   -I ../upgrade -DRICE_UPGRADE
goto make

:msc
if X%2X==XgameX     call mkprgmsc %2 c   L \c700
if X%2X==XminimalX  call mkprgmsc %2 c   L \c700
if X%2X==XsimpleX   call mkprgmsc %2 c   L \c700
if X%2X==XsimpleecX call mkprgmsc %2 c   L \c700
if X%2X==XsimpleppX call mkprgmsc %2 cpp L \c700
if X%2X==Xsimple3xX call mkprgmsc %2 c   L \c700 /I..\upgrade /DRICE_UPGRADE
goto make

:make
if X%1%3X==XbccX make
if X%1%3X==XgccX make
if X%1%3X==XmscX nmake
if X%3X==XX goto end
%3
goto end

:show
echo Use: MakeProg compiler program [make]
echo compiler = bcc, gcc or msc
echo program  = game, minimal, simple, simpleec, simplepp or simple3x
echo make     = your make utility

:end


