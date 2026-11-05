# Microsoft Developer Studio Project File - Name="JSONtrial" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=JSONtrial - Win32 Release
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "JSONtrial.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "JSONtrial.mak" CFG="JSONtrial - Win32 Release"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "JSONtrial - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "JSONtrial - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JSONtrial - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../Support"
# PROP Intermediate_Dir "../Object"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../Support" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../Support\JSONtri06x86.lib"

!ELSEIF  "$(CFG)" == "JSONtrial - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../Support"
# PROP Intermediate_Dir "../Object"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../Support" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../Support\JSONtri06x86d.lib"

!ENDIF 

# Begin Target

# Name "JSONtrial - Win32 Release"
# Name "JSONtrial - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Base Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Source\BJSONNodeCollection.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\Source\CJSONDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\CJSONValue.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Support.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Global Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Support\JSONtrial.h
# End Source File
# Begin Source File

SOURCE=..\..\Support\WINtrial.h
# End Source File
# End Group
# Begin Group "Local Headers"

# PROP Default_Filter ""
# Begin Group "Base Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\INCLUDE\BArray.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\BJSONNodeCollection.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\BParseControl.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\BString.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\BStringControl.h
# End Source File
# End Group
# Begin Group "Derived Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\INCLUDE\VJSONAnchor.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\VJSONMember.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\VJSONNode.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\INCLUDE\CJSONDocument.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CJSONValue.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\StdHead.h
# End Source File
# End Group
# End Group
# End Target
# End Project
