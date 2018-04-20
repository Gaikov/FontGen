# Microsoft Developer Studio Project File - Name="00_nsLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=00_nsLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "00_nsLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "00_nsLib.mak" CFG="00_nsLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "00_nsLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "00_nsLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "00_nsLib"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "00_nsLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../build_temp/Release_nsLib"
# PROP Intermediate_Dir "../build_temp/Release_nsLib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../SDKLibs/Release/00_nsLib.lib"

!ELSEIF  "$(CFG)" == "00_nsLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../build_temp/nsLib_Debug"
# PROP Intermediate_Dir "../build_temp/nsLib_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../SDKLibs/Debug/00_nsLib.lib"

!ENDIF 

# Begin Target

# Name "00_nsLib - Win32 Release"
# Name "00_nsLib - Win32 Debug"
# Begin Group "math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BBox2.h
# End Source File
# Begin Source File

SOURCE=.\color.cpp
# End Source File
# Begin Source File

SOURCE=.\color.h
# End Source File
# Begin Source File

SOURCE=.\Line2.cpp
# End Source File
# Begin Source File

SOURCE=.\Line2.h
# End Source File
# Begin Source File

SOURCE=.\MathTools.cpp
# End Source File
# Begin Source File

SOURCE=.\MathTools.h
# End Source File
# Begin Source File

SOURCE=.\matrix4.cpp
# End Source File
# Begin Source File

SOURCE=.\matrix4.h
# End Source File
# Begin Source File

SOURCE=.\Vec2.cpp
# End Source File
# Begin Source File

SOURCE=.\Vec2.h
# End Source File
# Begin Source File

SOURCE=.\Vec3.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\comm_types.h
# End Source File
# Begin Source File

SOURCE=.\CycleList.h
# End Source File
# Begin Source File

SOURCE=.\EasyStack.h
# End Source File
# Begin Source File

SOURCE=.\EditString.cpp
# End Source File
# Begin Source File

SOURCE=.\EditString.h
# End Source File
# Begin Source File

SOURCE=.\headers.cpp
# End Source File
# Begin Source File

SOURCE=.\headers.h
# End Source File
# Begin Source File

SOURCE=.\nsLib.h
# End Source File
# Begin Source File

SOURCE=.\StrTools.cpp
# End Source File
# Begin Source File

SOURCE=.\StrTools.h
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\utils.h
# End Source File
# End Target
# End Project
