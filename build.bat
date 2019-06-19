@echo off

IF NOT "%Platform%"=="x86" call scripts\setup_cl.bat x86

setlocal
set COMPILE_FLAGS=/nologo /diagnostics:caret /Zi /W4 /WX /EHsc
set WARNS_DISABLE=
set DEFINES=
set LIBRARIES=

IF NOT EXIST "bin\" mkdir bin

pushd bin
echo.
echo Compiling:
echo -------
cl %COMPILE_FLAGS%  %WARNS_DISABLE% %DEFINES% ..\src\win32main.cpp /link %LIBRARIES%
echo.
popd

