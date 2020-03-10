@echo off

if not "%Platform%"=="x86" call scripts\setup_cl.bat x86

REM TOOD(Adin): Turn off _CRT_SECURE_NO_WARNINGS

setlocal
set COMPILE_FLAGS=/nologo /diagnostics:caret /Zi /W0 /WX /EHsc /MP
set WARNS_DISABLE= /wd4201
set DEFINES=/DGLEW_BUILD=GLEW_STATIC /D_CRT_SECURE_NO_WARNINGS 
set INCLUDE_PATH=/I..\include /I..\ext\freetype\include
set LIBRARY_PATH=/libpath:..\lib
set LIBRARIES=glew32s.lib user32.lib gdi32.lib opengl32.lib FreeImaged.lib FreeImageLib.lib freetype.lib

set TARGETS=..\src\Win32Main.cpp ..\src\TLETC.cpp ..\src\utils\FileIO.cpp ..\src\utils\MemoryTracker.cpp ..\src\graphics\BetterGL2DRenderer.cpp ..\src\graphics\ShaderManager.cpp ..\src\graphics\FontManager.cpp ..\src\graphics\TextureManager.cpp ..\src\graphics\ShaderProgram.cpp ..\src\graphics\TextureProgram.cpp ..\src\graphics\layers\Layer.cpp ..\src\graphics\layers\Group.cpp ..\src\graphics\layers\TileLayer.cpp  ..\src\graphics\renderables\Sprite2D.cpp ..\src\graphics\renderables\Label.cpp ..\src\graphics\buffers\Buffer.cpp ..\src\graphics\buffers\IndexBuffer.cpp ..\src\graphics\buffers\VertexArray.cpp ..\src\math\vec2u.cpp ..\src\math\vec2f.cpp ..\src\math\vec3f.cpp ..\src\math\vec4f.cpp ..\src\math\mat2f.cpp ..\src\math\mat4f.cpp ..\ext\freetype-gl\vector.c ..\ext\freetype-gl\texture-atlas.c ..\ext\freetype-gl\texture-font.c 

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
cl %COMPILE_FLAGS% %INCLUDE_PATH% %WARNS_DISABLE% %DEFINES% %TARGETS% /link /OUT:TLETC_WIN32.exe /NODEFAULTLIB:pshinter.obj %LIBRARY_PATH% %LIBRARIES%
)

echo.
popd