@echo off
call "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/vcvars32.bat"
cd /d %~dp0
qmake -spec win32-msvc2008 -config release
nmake
if %errorlevel% neq 0 goto End
robocopy "%QTDIR%/bin" release QtCore4.dll QtGui4.dll QtOpenGL4.dll /NP /NJH /NJS 
robocopy . release README.txt /NP /NJH /NJS 
if defined MSVC90_REDIST_DIR robocopy "%MSVC90_REDIST_DIR%/x86/Microsoft.VC90.CRT" release/Microsoft.VC90.CRT /NP /NJH /NJS /XD .svn 
del /Q gpuakf.zip
cd release
"C:/Program Files/7-zip/7z.exe" a ../gpuakf.zip *.exe *.dll *.txt Microsoft.VC90.CRT
:End
pause
cd /d %~dp0
