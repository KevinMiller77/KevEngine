@echo off

IF NOT "%Platform%"=="x86" call scripts\setup_cl.bat x86

REM TOOD(Adin): Turn off _CRT_SECURE_NO_WARNINGS

setlocal
set COMPILE_FLAGS=/nologo /diagnostics:caret /Zi /W4 /WX /EHsc
set WARNS_DISABLE= /wd4201
set DEFINES=/DGLEW_BUILD=GLEW_STATIC /D_CRT_SECURE_NO_WARNINGS
set INCLUDE_PATH=/I..\include
set LIBRARY_PATH=/libpath:..\lib
set LIBRARIES=user32.lib gdi32.lib opengl32.lib glew32s.lib 

IF NOT EXIST "bin\" mkdir bin

pushd bin
echo.
echo Compiling:
echo -------
cl %COMPILE_FLAGS% %INCLUDE_PATH% %WARNS_DISABLE% %DEFINES% ..\src\win32main.cpp /link %LIBRARY_PATH% %LIBRARIES%
echo.
popd

