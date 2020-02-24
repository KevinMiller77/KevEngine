@echo off

if not "%Platform%"=="x86" call scripts\setup_cl.bat x86

REM TOOD(Adin): Turn off _CRT_SECURE_NO_WARNINGS

setlocal
set COMPILE_FLAGS=/nologo /diagnostics:caret /Zi /W4 /WX /EHsc
set WARNS_DISABLE= /wd4201
set DEFINES=/DGLEW_BUILD=GLEW_STATIC /D_CRT_SECURE_NO_WARNINGS
set INCLUDE_PATH=/I..\include
set LIBRARY_PATH=/libpath:..\lib
set LIBRARIES=glew32s.lib user32.lib gdi32.lib opengl32.lib  
set TARGETS=..\src\Win32Main.cpp ..\src\TLETC.cpp ..\src\utils\FileIO.cpp ..\src\graphics\ShaderProgram.cpp ..\src\graphics\GL2DRenderer.cpp ..\src\graphics\Entity2D.cpp ..\src\graphics\Renderable2D.cpp ..\src\graphics\buffers\Buffer.cpp ..\src\graphics\buffers\IndexBuffer.cpp ..\src\graphics\buffers\VertexArray.cpp ..\src\math\vec2u.cpp ..\src\math\vec2f.cpp ..\src\math\vec3f.cpp ..\src\math\vec4f.cpp ..\src\math\mat2f.cpp ..\src\math\mat4f.cpp

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