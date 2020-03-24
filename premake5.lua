workspace "KevEngine"
    configurations 
    { 
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ext/glfw/include"
IncludeDir["Glad"] = "ext/glad/include"
IncludeDir["ImGui"] = "ext/imgui"
IncludeDir["Freetype"] = "ext/freetype/include"
IncludeDir["Freetype-GL"] = "ext/freetype-gl" 
IncludeDir["stb_image"] = "ext/stb_image/"

    platforms { "Win32", "Linux"}

    filter { "platforms:Win32"}
        system "windows"
        architecture "x86"
        defines { "KEV_PLATFORM_WINDOWS" }

    filter { "platforms:Linux" }
        system "linux"
        architecture "x86"

    project "Engine"
        kind "WindowedApp"
        language "C++"
        location "build/KevEngine"

