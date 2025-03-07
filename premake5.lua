workspace "Helix"
    architecture "x64"
    startproject "Sandbox"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Dependencies"
	    include "Helix/vendor/GLFW"
	    include "Helix/vendor/Glad"
	    include "Helix/vendor/imgui"

IncludeDir={}
IncludeDir["GLFW"] = "Helix/vendor/GLFW/include"
IncludeDir["Glad"] = "Helix/vendor/Glad/include"
IncludeDir["imgui"] = "Helix/vendor/imgui"
IncludeDir["glm"] = "Helix/vendor/glm/"
IncludeDir["stb_image"] = "Helix/vendor/stb_image"



include "Helix/vendor/GLFW"
include "Helix/vendor/Glad"
include "Helix/vendor/imgui"



project "Helix"
    location "Helix"
    kind "StaticLib"
    language "C++"
    cppdialect"C++17"
    staticruntime "on"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    defines{
		"_CRT_SECURE_NO_WARNINGS"
	}


    pchheader "hxpch.h"
    pchsource "Helix/src/hxpch.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"

    }

    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/spdlog/include/fmt",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"


    }



    libdirs {
        "Helix/vendor/GLFW/lib" 
    }
    
    links {
        "GLFW", 
        "Glad",
        "imgui",
        "opengl32.lib",
        "gdi32.lib",
        "user32.lib",
        "kernel32.lib"

    }

    filter "system:linux"
		removefiles { "src/Platform/Windows/WindowsPlatformUtils.cpp" }

		defines
		{
			"HZ_PLATFORM_LINUX",
		}


    filter "system:windows"
        buildoptions { "/utf-8" }
        systemversion "latest"
        removefiles { "**/Linux/**" }

        defines{
                "HX_PLATFOM_WINDOWS",
                "HX_BUILD_DLL",
                "GLFW_INCLUDE_NONE"
    
        }




    filter "configurations:Debug"
        defines "HX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
      defines "HX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "HX_DIST"
        runtime "Release" 
        optimize "on"







project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "Helix/vendor/spdlog/include",
        "Helix/src",
        "Helix/vendor/imgui",
        "%{IncludeDir.glm}"

    }

    links{
        "Helix"
    }

    filter "system:windows"
        buildoptions { "/utf-8" }
        systemversion "latest"

        defines{
                "HX_PLATFOM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "HX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
      defines "HX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "HX_DIST"
        runtime "Release" 
        optimize "on"
