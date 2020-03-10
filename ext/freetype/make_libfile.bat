
@echo off

if not "%Platform%"=="x86" call ..\..\scripts\setup_cl.bat x86

setlocal EnableDelayedExpansion
set EXT_OBJS=
for /r %%a in (*.c) do (
    call set TEMP=%%a
    call set EXT_OBJS=%%EXT_OBJS%% ../!TEMP:~38!
)

if not exist "bin\" mkdir bin
pushd bin
cl /nologo /MP /Fo /c /I..\include /DFT2_BUILD_LIBRARY %EXT_OBJS% /link /nologo

if not exist "out\" mkdir out

set EXT_OBJS=
for /r %%a in (*.obj) do (
    call set TEMP=%%a
    call set EXT_OBJS=%%EXT_OBJS%% !TEMP:~42!
)

echo LINKING LOG > linking_log.txt

lib /OUT:"..\out\freetype.lib" /NODEFAULTLIB:pshinter.obj ftbase.obj pshinter.obj %EXT_OBJS%
popd