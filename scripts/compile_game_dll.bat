@echo off

if not "%Platform%"=="x86" call setup_cl.bat x86

pushd "../"

setlocal
set COMPILE_FLAGS=/nologo /diagnostics:caret /Zi /W0 /WX /EHsc /MP /MD /Ox /c
set WARNS_DISABLE= /wd4201
set DEFINES=/D_CRT_SECURE_NO_WARNINGS
set INCLUDE_PATH=/I..\include /I..\src
set LIBRARIES=user32.lib gdi32.lib opengl32.lib shell32.lib

set KEV_GAME_SRC=..\game\KevGame.cpp ..\game\GameLayer.cpp ..\game\HUD.cpp

if not exist "dll\" mkdir dll
pushd dll

echo.
echo Compiling:
echo -------

if not exist "..\lib" mkdir "..\lib"
cl %COMPILE_FLAGS% /I..\src /I..\include %WARNS_DISABLE% %KEV_GAME_SRC% > objects.txt
rem /link /OUT:..\lib\NewKevGameLib.dll /DLL /NOENTRY %LIBRARIES%

echo.
popd