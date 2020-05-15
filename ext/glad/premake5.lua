project "glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "../../include/glad/glad.h",
        "../../include/KHR/khrplatform.h",
        "src/glad.c"
    }

    sysincludedirs
    {
        "../../include"
    }
    
    filter "system:windows"
        systemversion "latest"
    filter "system:macosx"
        systemversion "latest"
        buildoptions
        {
            "-x objective-c++"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"