@echo off

if not "%Platform%"=="x86" call scripts\setup_cl.bat x86

REM TOOD(Adin): Turn off _CRT_SECURE_NO_WARNINGS

setlocal
set COMPILE_FLAGS=/nologo /diagnostics:caret /Zi /W0 /WX /EHsc /MP /Ox
set WARNS_DISABLE= /wd4201
set DEFINES=/D_CRT_SECURE_NO_WARNINGS /DFT2_BUILD_LIBRARY /D_GLFW_WIN32
set INCLUDE_PATH=/I..\include /I..\ext\freetype\include /I..\ext\imgui /I..\src
set LIBRARY_PATH=/libpath:..\lib
set LIBRARIES=user32.lib gdi32.lib opengl32.lib shell32.lib

rem EXT LIBRARIES TO BUILD
set STB_IMAGE=      ..\ext\stb_image\stb_image.cpp
set FREETYPE_GL=    ..\ext\freetype-gl\vector.c ..\ext\freetype-gl\texture-atlas.c ..\ext\freetype-gl\texture-font.c
set FREETYPE=       ..\ext\freetype\src\base\ftsystem.c ..\ext\freetype\src\base\ftlcdfil.c ..\ext\freetype\src\base\ftstroke.c ..\ext\freetype\src\base\ftbitmap.c ..\ext\freetype\src\smooth\smooth.c ..\ext\freetype\src\sfnt\sfnt.c ..\ext\freetype\src\truetype\truetype.c ..\ext\freetype\src\base\ftinit.c ..\ext\freetype\src\base\ftdebug.c ..\ext\freetype\src\base\ftbase.c ..\ext\freetype\src\base\ftbbox.c    ..\ext\freetype\src\base\ftglyph.c  ..\ext\freetype\src\bdf\bdf.c ..\ext\freetype\src\winfonts\winfnt.c
set GLAD=           ..\ext\glad\src\glad_wgl.c ..\ext\glad\src\glad.c
set GLFW=           ..\ext\glfw\src\init.c ..\ext\glfw\src\input.c ..\ext\glfw\src\context.c ..\ext\glfw\src\monitor.c ..\ext\glfw\src\vulkan.c ..\ext\glfw\src\glfw_window.c ..\ext\glfw\src\win32_init.c ..\ext\glfw\src\win32_joystick.c ..\ext\glfw\src\win32_monitor.c ..\ext\glfw\src\win32_time.c ..\ext\glfw\src\win32_thread.c ..\ext\glfw\src\win32_window.c ..\ext\glfw\src\wgl_context.c ..\ext\glfw\src\egl_context.c ..\ext\glfw\src\osmesa_context.c
set IMGUI=          ..\ext\imgui\imgui.cpp ..\ext\imgui\imgui_demo.cpp ..\ext\imgui\imgui_draw.cpp ..\ext\imgui\imgui_widgets.cpp ..\src\imgui\ImGuiBuild.cpp
set KEV_ENGINE_SRC= ..\src\imgui\ImGuiLayer.cpp ..\src\graphics\layers\LayerStack.cpp ..\src\platform\Windows\WindowsWindow.cpp ..\src\core\KevInput.cpp ..\src\graphics\GLContext.cpp ..\src\graphics\RenderableManager.cpp ..\src\graphics\cameras\OrthographicCamera.cpp ..\src\graphics\cameras\FollowRenderableCamera.cpp ..\src\graphics\cameras\OrthographicCameraController.cpp ..\src\graphics\Window.cpp ..\src\core\KevEngine.cpp ..\src\utils\FileIO.cpp ..\src\utils\MemoryTracker.cpp ..\src\graphics\BetterGL2DRenderer.cpp ..\src\graphics\ShaderManager.cpp ..\src\graphics\FontManager.cpp ..\src\graphics\TextureManager.cpp ..\src\graphics\ShaderProgram.cpp ..\src\graphics\TextureProgram.cpp ..\src\graphics\layers\Layer.cpp ..\src\graphics\layers\Group.cpp ..\src\graphics\renderables\Sprite2D.cpp ..\src\graphics\renderables\Label.cpp ..\src\graphics\buffers\Buffer.cpp ..\src\graphics\buffers\IndexBuffer.cpp ..\src\graphics\buffers\VertexArray.cpp ..\src\math\vec2u.cpp ..\src\math\vec2f.cpp ..\src\math\vec3f.cpp ..\src\math\vec4f.cpp ..\src\math\mat2f.cpp ..\src\math\mat4f.cpp
set KEV_GAME_SRC=   ..\game\KevGame.cpp ..\game\GameLayer.cpp ..\game\HUD.cpp

set TARGETS= %IMGUI% %GLFW% %GLAD% %STB_IMAGE% %FREETYPE% %FREETYPE_GL% %KEV_ENGINE_SRC%
if not exist "bin\" mkdir bin

pushd bin

echo.
echo Compiling:
echo -------
    
set EXT_OBJS=
for /r %%a in (./*.obj) do (
    call set TEMP=%%a
    call set EXT_OBJS=%%TEMP:~29%% %%EXT_OBJS%%
)

IF "%1%"=="mathtest" (
REM Mathtest build
cl %COMPILE_FLAGS% %WARNS_DISABLE% ..\src\core\mathtest.cpp ..\src\core\math\*.cpp
) 
IF "%1%"=="testbuild" (
REM Test out building freetype
    cl /c %COMPILE_FLAGS% -I..\include %WARNS_DISABLE% %GLAD%
) 
IF "%1%"=="build.lib" (
REM Build static lib
    echo BUILDING STATIC LIB
    cl /nologo /MP /Fo /c %COMPILE_FLAGS% %INCLUDE_PATH% %WARNS_DISABLE% %DEFINES% %TARGETS%
    lib /OUT:KevEngine_WIN32.lib %EXT_OBJS% 
)
REM echo here
IF "%1%" == "detatched" (
    echo "" > OBJS.txt
    cl %COMPILE_FLAGS% /c %INCLUDE_PATH% %WARNS_DISABLE% %DEFINES% %TARGETS% >> OBJS.txt
)
IF "%1%" == ""  (
echo NORMAL BUILD
REM Normal build
cl %COMPILE_FLAGS% %INCLUDE_PATH% %WARNS_DISABLE% %DEFINES% %TARGETS% %KEV_GAME_SRC% /link /OUT:"..\KevEngine.exe" %LIBRARY_PATH% %LIBRARIES% 
)

echo.
popd