workspace "GEngine"
	startproject "GEngineEditor"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-int/%{cfg.buildcfg}/%{prj.name}"


-- External Dependencies
externals = {}
externals["sdl2"] = "external/sdl2"
externals["spdlog"] = "external/spdlog"
externals["glad"] = "external/glad"

include "external/glad"

--process glad before anything

project "GEngine"
	location "GEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir(tdir)
	objdir(odir)

	pchheader "gepch.h"
	pchsource "%{prj.name}/src/gepch.cpp"


	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/include/**.cpp",
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	sysincludedirs
	{
		"%{prj.name}/include/%{prj.name}",
		"%{prj.name}/include/external",
		"%{externals.sdl2}/include",
		"%{externals.spdlog}/include",
		"%{externals.glad}/include"
		--"%{prj.name}/src"

	}

	defines
	{
		--Ensures glad doesn't include glfw
		"GLFW_INCLUDE_NONE"
	}

	-- Windows
	filter
	{
		"system:windows",
		"configurations:*"
	}

	systemversion "lastest"

	defines
	{
		"GENGINE_PLATFORM_WINDOWS",
		"GENGINE_WINDOW_SDL"
	}

	-- Linux
	filter
	{
		"system:linux",
		"configurations:*"
	}

		defines
		{
			"GENGINE_PLATFORM_LINUX"
		}


	-- MACOS
	filter
	{
		"system:macosx",
		"configurations:*"
	}

		xcodebuildsettings
		{
			["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
			["UseModernBuildSystem"] = "NO"

		}

		defines
		{
			"GENGINE_PLATFORM_MAC"
		}

	-- DEBUG
	filter "configurations:Debug"
		defines
		{
			"GENGINE_CONFIG_DEBUG"
		}

		runtime "Debug"
		symbols "on"

	-- RELEASE
	filter "configurations:Release"
		defines
		{
			"GENGINE_CONFIG_RELEASE"
		}

		runtime "Release"
		symbols "off"
		optimize "on"


project "GEngineEditor"
	location "GEngineEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	links "GEngine"

	targetdir(tdir)
	objdir(odir)



	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	
	sysincludedirs
	{
		"GEngine/include",
		"GEngine/include/external",
		"GEngine/include/GEngine"
		--"%{externals.glad}/include"
		--"%{externals.spdlog}/include"

	}

	-- Windows
	filter
	{
		"system:windows",
		"configurations:*"
	}

	systemversion "10.0"

	defines
	{
		"GENGINE_PLATFORM_WINDOWS"
	}

	libdirs
	{
		"%{externals.sdl2}/lib"
	}

	links
	{
		"SDL2",
		"SDL2main",
		"SDL2test",
		"glad"
	}

	-- Linux
	filter
	{
		"system:linux",
		"configurations:*"
	}

		defines
		{
			"GENGINE_PLATFORM_LINUX"
		}

		links
		{
			"SDL2",
			"glad"
		}

	-- MACOS
	filter
	{
		"system:macosx",
		"configurations:*"
	}

		xcodebuildsettings
		{
			["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
			["UseModernBuildSystem"] = "NO"

		}

		defines
		{
			"GENGINE_PLATFORM_MAC"
		}

		links
		{
			"SDL2.framework",
			"glad"
		}

	filter "configurations:Debug"
		defines
		{
			"GENGINE_CONFIG_DEBUG"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"GENGINE_CONFIG_RELEASE"
		}
		runtime "Release"
		symbols "off"
		optimize "on"
