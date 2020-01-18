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
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/vendor/stb_image/**.h",
        "%{prj.name}/src/vendor/stb_image/**.c",
        "%{prj.name}/src/vendor/glm/**.hpp",
        "%{prj.name}/src/vendor/glm/**.inl",
        "%{prj.name}/res/shaders/**.glsl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/src/vendor",
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
            