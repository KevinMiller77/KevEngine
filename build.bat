@echo off

if not "%Platform%"=="x86" call scripts\setup_cl.bat x86

REM TOOD(Adin): Turn off _CRT_SECURE_NO_WARNINGS

setlocal
set COMPILE_FLAGS=/nologo /diagnostics:caret /Zi /W4 /WX /EHsc
set WARNS_DISABLE= /wd4201
set DEFINES=/DGLEW_BUILD=GLEW_STATIC /D_CRT_SECURE_NO_WARNINGS
set INCLUDE_PATH=/I..\include
set LIBRARY_PATH=/libpath:..\lib
set LIBRARIES=user32.lib gdi32.lib opengl32.lib glew32s.lib 
set TARGETS=..\src\win32main.cpp ..\src\glrenderer.cpp

if not exist "bin\" mkdir bin

pushd bin
echo.
echo Compiling:
echo -------

IF "%1%"=="mathtest" (
REM Mathtest build
cl %COMPILE_FLAGS% %WARNS_DISABLE% ..\src\mathtest.cpp ..\src\math\*.cpp

) ELSE (
REM Normal build
cl %COMPILE_FLAGS% %INCLUDE_PATH% %WARNS_DISABLE% %DEFINES% %TARGETS% /link %LIBRARY_PATH% %LIBRARIES%
)

echo.
popd