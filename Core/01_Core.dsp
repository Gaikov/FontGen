# Microsoft Developer Studio Project File - Name="01_Core" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=01_Core - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "01_Core.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "01_Core.mak" CFG="01_Core - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "01_Core - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "01_Core - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "01_Core"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "01_Core - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../build_temp/Release_Core"
# PROP Intermediate_Dir "../build_temp/Release_Core"
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
# ADD LIB32 /nologo /out:"../SDKLibs/Release/01_Core.lib"

!ELSEIF  "$(CFG)" == "01_Core - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../build_temp/Debug_Core"
# PROP Intermediate_Dir "../build_temp/Debug_Core"
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
# ADD LIB32 /nologo /out:"../SDKLibs/Debug/01_Core.lib"

!ENDIF 

# Begin Target

# Name "01_Core - Win32 Release"
# Name "01_Core - Win32 Debug"
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Args.cpp
# End Source File
# Begin Source File

SOURCE=.\Args.h
# End Source File
# Begin Source File

SOURCE=.\FastMem.h
# End Source File
# Begin Source File

SOURCE=.\HashMap.h
# End Source File
# Begin Source File

SOURCE=.\RegCrypt.c
# End Source File
# Begin Source File

SOURCE=.\RegCrypt.h
# End Source File
# Begin Source File

SOURCE=.\StructUt.h
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ParseFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseFile.h
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\ScriptSaver.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptSaver.h
# End Source File
# End Group
# Begin Group "FileSystem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Package.cpp
# End Source File
# Begin Source File

SOURCE=.\Package.h
# End Source File
# Begin Source File

SOURCE=.\PackArch.h
# End Source File
# End Group
# Begin Group "Config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\Var.cpp
# End Source File
# Begin Source File

SOURCE=.\Var.h
# End Source File
# End Group
# Begin Group "WinGUI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WinDialog.h
# End Source File
# End Group
# Begin Group "Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataWriter.h
# End Source File
# Begin Source File

SOURCE=.\FileReader.cpp
# End Source File
# Begin Source File

SOURCE=.\FileReader.h
# End Source File
# Begin Source File

SOURCE=.\FileWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\FileWriter.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AppInfo.h
# End Source File
# Begin Source File

SOURCE=.\Core.cpp
# End Source File
# Begin Source File

SOURCE=.\Core.h
# End Source File
# Begin Source File

SOURCE=.\headers.cpp
# End Source File
# Begin Source File

SOURCE=.\headers.h
# End Source File
# Begin Source File

SOURCE=.\log.cpp
# End Source File
# Begin Source File

SOURCE=.\log.h
# End Source File
# Begin Source File

SOURCE=.\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\Memory.h
# End Source File
# Begin Source File

SOURCE=.\Name.cpp
# End Source File
# Begin Source File

SOURCE=.\Name.h
# End Source File
# Begin Source File

SOURCE=.\Net.cpp
# End Source File
# Begin Source File

SOURCE=.\Net.h
# End Source File
# Begin Source File

SOURCE=.\ResourceManager.h
# End Source File
# Begin Source File

SOURCE=.\SmartPtr.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartPtr.h
# End Source File
# Begin Source File

SOURCE=.\sys.cpp
# End Source File
# Begin Source File

SOURCE=.\sys.h
# End Source File
# End Target
# End Project
