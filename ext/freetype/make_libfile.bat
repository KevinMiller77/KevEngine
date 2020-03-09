
@echo off

if not "%Platform%"=="x86" call ..\..\scripts\setup_cl.bat x86

setlocal EnableDelayedExpansion
set EXT_OBJS=
for /r %%a in (*.c) do (
    call set TEMP=%%a
    call set EXT_OBJS=%%EXT_OBJS%% ..!TEMP:~37!
)

if not exist "bin\" mkdir bin
pushd bin
cl /nologo /MP /Fo /c /I..\include /DFT2_BUILD_LIBRARY %EXT_OBJS% /link /nologo


echo %EXT_OBJS%

if not exist "out\" mkdir out

set EXT_OBJS=
for /r %%a in (*.obj) do (
    call set TEMP=%%a
    if "!TEMP:~-10!" neq "ftbase.obj" ( 
        echo "!TEMP:~-10!"
        call set EXT_OBJS=%%EXT_OBJS%% ..\bin\!TEMP:~41!
    )
)
pushd "..\out"

echo LINKING LOG > linking_log.txt
lib /OUT:freetype.lib /NODEFAULTLIB:pshinter.obj %EXT_OBJS% >> linking_log.txt
popd
popd