@echo off
call "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/vcvars32.bat"
cd /d %~dp0
qmake -spec win32-msvc2008 -config release
nmake
if %errorlevel% neq 0 goto End
robocopy "%QTDIR%/bin" release QtCore4.dll QtGui4.dll QtOpenGL4.dll /NP /NJH /NJS 
:End
pause
cd /d %~dp0
