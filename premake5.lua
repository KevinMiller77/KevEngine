workspace "KevEngine"
    startproject "Game"
    configurations 
    { 
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}/%{cfg.system}%{cfg.architecture}"

    
    group "Dependencies"
        include "ext/glfw"
        include "ext/glad"
        include "ext/imgui"
        include "ext/freetype"
        include "ext/freetype-gl"
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
        "ext/freetype-gl"
    }

    links
    {
        "imgui",
        "glfw",
        "glad",
        "freetype",
        "freetype-gl"
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

        targetdir ("./")
	    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "game/**.h",
            "game/**.cpp"
        }

        includedirs
        {
            "src",
            "include"
        }

        links
        {
            "Engine"
        }
