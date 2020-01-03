workspace "OpenGL"
    architecture "x64"

    configurations { "Debug",  "Release"}
    outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "OpenGL"
    location "OpenGL"
    kind "ConsoleApp"
    language "c++"

    targetdir("bin/" ..outputdir.."/%{prj.name}")
    objdir("bin/intermediates" ..outputdir.."/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c"
    }

    includedirs
    {
        "%{prj.name}/src",
         "Depend/Include"
	}

    libdirs
    {
         "Depend/Libraries"
	}

    links
    {
        "opengl32.lib",
        "glfw3.lib"
	}

    filter "system:windows"
        cppdialect "c++17"
        systemversion "latest"

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "on"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "on"
            