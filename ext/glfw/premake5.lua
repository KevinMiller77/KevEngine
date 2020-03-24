project "glfw"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/vulkan.c",
        "src/init.c",
        "src/input.c", 
        "src/context.c",
        "src/monitor.c",
        "src/glfw_window.c",
        "src/egl_context.c"
    }
    
    includedirs
    {
        "include/GLFW",
        "../../include"
    }
    
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_GLFW_WIN32"
        }

        files
        {
            "src/win32_init.c", 
            "src/win32_joystick.c", 
            "src/win32_monitor.c", 
            "src/win32_time.c", 
            "src/win32_thread.c", 
            "src/win32_window.c", 
            "src/wgl_context.c", 
            "src/osmesa_context.c"
        }

    filter "system:linux"
        defines
        {
            "_GLFW_X11"
        }

        files
        {
            "src/x11_init.c",
            "src/linux_joystick.c", 
            "src/x11_monitor.c", 
            "src/posix_time.c", 
            "src/posix_thread.c", 
            "src/x11_window.c", 
            "src/osmesa_context.c", 
            "src/xkb_unicode.c", 
            "src/glx_context.c"
        }

    filter "configurations:Debug"
    runtime "Debug"
    symbols "on"
    
    filter "configurations:Release"
    runtime "Release"
    optimize "on"