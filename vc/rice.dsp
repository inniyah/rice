# Microsoft Developer Studio Project File - Name="rice" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=rice - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rice.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rice.mak" CFG="rice - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rice - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "rice - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rice - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0xc0a
# ADD RSC /l 0xc0a
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\rice.lib"

!ELSEIF  "$(CFG)" == "rice - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0xc0a
# ADD RSC /l 0xc0a
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\riced.lib"

!ENDIF 

# Begin Target

# Name "rice - Win32 Release"
# Name "rice - Win32 Debug"
# Begin Source File

SOURCE=..\include\compile.h
# End Source File
# Begin Source File

SOURCE=..\source\compile1.c
# End Source File
# Begin Source File

SOURCE=..\source\compile2.c
# End Source File
# Begin Source File

SOURCE=..\source\compile3.c
# End Source File
# Begin Source File

SOURCE=..\source\compile4.c
# End Source File
# Begin Source File

SOURCE=..\include\define.h
# End Source File
# Begin Source File

SOURCE=..\source\destroy.c
# End Source File
# Begin Source File

SOURCE=..\source\explain.c
# End Source File
# Begin Source File

SOURCE=..\include\function.h
# End Source File
# Begin Source File

SOURCE=..\source\global.c
# End Source File
# Begin Source File

SOURCE=..\include\include.h
# End Source File
# Begin Source File

SOURCE=..\source\infer.c
# End Source File
# Begin Source File

SOURCE=..\source\load.c
# End Source File
# Begin Source File

SOURCE=..\source\rebuild.c
# End Source File
# Begin Source File

SOURCE=..\include\rebuild.h
# End Source File
# Begin Source File

SOURCE=..\source\save.c
# End Source File
# Begin Source File

SOURCE=..\include\type.h
# End Source File
# Begin Source File

SOURCE=..\include\variable.h
# End Source File
# End Target
# End Project
