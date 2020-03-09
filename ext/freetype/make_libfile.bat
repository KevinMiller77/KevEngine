
@echo off

if not "%Platform%"=="x86" call ..\..\scripts\setup_cl.bat x86

setlocal EnableDelayedExpansion
set EXT_OBJS=
for /r %%a in (*.c) do (
    call set TEMP=%%a
    call set EXT_OBJS=%%EXT_OBJS%% ../!TEMP:~52!
)

if not exist "bin\" mkdir bin
pushd bin
cl /nologo /MP /Fo /c /I..\include /DFT2_BUILD_LIBRARY %EXT_OBJS% /link /nologo
popd

if not exist "out\" mkdir out
pushd out

set EXT_OBJS=
for /r %%a in (../bin/*.obj) do (
    call set TEMP=%%a
    call set EXT_OBJS=%%EXT_OBJS%% ..\bin\!TEMP:~56!
)

echo LINKING LOG > linking_log.txt
lib /OUT:freetype.lib %EXT_OBJS% >> linking_log.txt
popd