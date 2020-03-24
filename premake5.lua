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
        "ext/stb_image/**.cpp"
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

    includedirs
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
        targetdir("")
	    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "game/**.h",
            "game/**.cpp"
        }

        includedirs
        {
            "src",
            "include",
            "ext/glfw/include",
            "ext/glad/include",
            "ext/imgui",
            "ext/freetype/include"
        }


        filter "system:linux"
            files
            {
                "ext/freetype-gl/vector.c",
                "ext/freetype-gl/texture-atlas.c",
                "ext/freetype-gl/texture-font.c"
            }
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

        links
        {
            "Engine"
        }
