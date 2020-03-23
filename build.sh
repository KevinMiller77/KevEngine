STB_IMAGE="ext/stb_image/stb_image.cpp"
FREETYPE_GL="ext/freetype-gl/vector.c ext/freetype-gl/texture-atlas.c ext/freetype-gl/texture-font.c"
FREETYPE="ext/freetype/src/base/ftsystem.c ext/freetype/src/base/ftlcdfil.c ext/freetype/src/base/ftstroke.c ext/freetype/src/base/ftbitmap.c ext/freetype/src/smooth/smooth.c ext/freetype/src/sfnt/sfnt.c ext/freetype/src/truetype/truetype.c ext/freetype/src/base/ftinit.c ext/freetype/src/base/ftdebug.c ext/freetype/src/base/ftbase.c ext/freetype/src/base/ftbbox.c  ext/freetype/src/base/ftglyph.c  ext/freetype/src/bdf/bdf.c ext/freetype/src/winfonts/winfnt.c"
GLAD="ext/glad/src/glad.c"
GLFW="ext/glfw/src/vulkan.c ext/glfw/src/init.c ext/glfw/src/input.c ext/glfw/src/context.c ext/glfw/src/monitor.c ext/glfw/src/glfw_window.c ext/glfw/src/x11_init.c ext/glfw/src/linux_joystick.c ext/glfw/src/x11_monitor.c ext/glfw/src/posix_time.c ext/glfw/src/posix_thread.c ext/glfw/src/x11_window.c ext/glfw/src/egl_context.c ext/glfw/src/glx_context.c ext/glfw/src/osmesa_context.c ext/glfw/src/xkb_unicode.c"
IMGUI="ext/imgui/imgui.cpp ext/imgui/imgui_demo.cpp ext/imgui/imgui_draw.cpp ext/imgui/imgui_widgets.cpp src/imgui/ImGuiBuild.cpp"
KEV_ENGINE_SRC="src/imgui/ImGuiLayer.cpp src/graphics/layers/LayerStack.cpp src/platform/Windows/WindowsWindow.cpp src/platform/Linux/LinuxWindow.cpp  src/core/KevInput.cpp src/graphics/GLContext.cpp src/graphics/RenderableManager.cpp src/graphics/cameras/OrthographicCamera.cpp src/graphics/cameras/FollowRenderableCamera.cpp src/graphics/cameras/OrthographicCameraController.cpp src/graphics/Window.cpp src/core/KevEngine.cpp src/utils/FileIO.cpp src/utils/MemoryTracker.cpp src/graphics/BetterGL2DRenderer.cpp src/graphics/ShaderManager.cpp src/graphics/FontManager.cpp src/graphics/TextureManager.cpp src/graphics/ShaderProgram.cpp src/graphics/TextureProgram.cpp src/graphics/layers/Layer.cpp src/graphics/layers/Group.cpp src/graphics/renderables/Sprite2D.cpp src/graphics/renderables/Label.cpp src/graphics/buffers/Buffer.cpp src/graphics/buffers/IndexBuffer.cpp src/graphics/buffers/VertexArray.cpp src/math/vec2u.cpp src/math/vec2f.cpp src/math/vec3f.cpp src/math/vec4f.cpp src/math/mat2f.cpp src/math/mat4f.cpp"
KEV_GAME_SRC="game/KevGame.cpp game/GameLayer.cpp game/HUD.cpp"
TARGETS="$GLAD $GLFW $IMGUI $FREETYPE $FREETYPE_GL $STB_IMAGE $KEV_ENGINE_SRC $KEV_GAME_SRC"

g++ -pthread -fno-diagnostics-show-caret -fpermissive -std=c++17 -Iinclude -Isrc -Iext/imgui -Iext/freetype/include -Iext/freetype-gl -D_GLFW_X11 -DFT2_BUILD_LIBRARY -DGLFW_SUPPLIED -D_LIBS_SUPPLIED -DD_CRT_SECURE_NO_WARNINGS $TARGETS -lX11 -lGL -lGLU -ldl