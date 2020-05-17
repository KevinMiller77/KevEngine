workspace "KevEngine"
    startproject "Game"
    configurations 
    { 
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}/%{cfg.system}%{cfg.architecture}"

    
    group "Dependencies"
        include "ext/glfw"
        include "ext/glad"
        include "ext/imgui"
        include "ext/freetype"
    group ""
    
project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    

    files
    {
        "src/**.h",
        "src/**.cpp",
        "ext/stb_image/**.cpp",
        "ext/freetype-gl/**.c"
    }

    removefiles
    {
        "src/utils/Memorytracker.cpp",
        "src/utils/Memorytracker.h"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "FT2_BUILD_LIBRARY"
    }

    sysincludedirs
    {
        "src",
        "include",
		"ext/glfw/include",
        "ext/glad/include",
        "ext/imgui",
        "ext/freetype/include",
    }

    links
    {
        "glad",
        "glfw",
        "imgui",
        "freetype"
    }

    filter "system:windows"
        systemversion "latest"
        links
        {
            "user32", 
            "gdi32", 
            "opengl32", 
            "shell32"
        }

    filter "system:macosx"
        systemversion "10.13"
        files
        {
            "src/**.m",
            "src/**.mm"
        }
        removefiles
        {
            "ext/freetype-gl/**.c"
        }
        buildoptions
        {
            "-x objective-c++"
        }
        links
        {
            "IOKit.framework", 
            "OpenGL.framework",
            "Cocoa.framework",
            "CoreVideo.framework"
        }
        prebuildcommands
        {
            "./scripts/compile_metal_shaders.sh"
        }

    filter "system:linux"
        systemversion "latest"
        defines
        {
            "GLFW_SUPPLIED",
            "_LIBS_SUPPLIED"
        }
        links
        {
            "X11",
            "GL",
            "GLU",
            "dl"
        }

    filter "configurations:Debug"
        defines "KEV_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "KEV_RELEASE"
        runtime "Release"
        optimize "on"

project "Game"
        location "Game"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetname("KevGame")
	    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        debugdir "./"

        files
        {
            "game/**.h",
            "game/**.cpp",
        }

        sysincludedirs
        {
            "src",
            "include",
            "ext/glfw/include",
            "ext/glad/include",
            "ext/imgui",
            "ext/freetype/include"
        }

        links
        {
            "Engine"
        }

        filter "system:windows"
            targetdir("./")

        filter "system:linux"
            targetdir("")
            links
            {
                "X11",
                "GL",
                "GLU",
                "dl",
                "glad",
                "glfw",
                "imgui",
                "freetype",
                "pthread"
            }
            defines
            {
                "_GLFW_X11"
            }
        filter "system:macosx"
            systemversion "10.13"
            
            buildoptions
            {
                "-x objective-c++"
            }
            links
            {
                "IOKit.framework", 
                "AppKit.framework",
                "Cocoa.framework",
                "CoreVideo.framework",
                "Metal.framework",
                "QuartzCore.framework"
            }       
project "Aux Files"
    kind "None"
    files
    {
        "scripts/**",
        "resources/**"
    }
        