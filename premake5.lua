workspace "GEngine"
	startproject "GEngineEditor"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-int/%{cfg.buildcfg}/%{prj.name}"

-- External Dependencies
externals = {}
externals["sdl2"] = "external/sdl2"

project "GEngine"
	location "GEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir(tdir)
	objdir(odir)

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	sysincludedirs
	{
		"%{prj.name}/include/%{prj.name}",
		"%{externals.sdl2}/include"
		--"%{prj.name}/src"

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
		"GENGINE_PLATFORM_WINDOWS"
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
		"GEngine/include"

	}

		-- WIndows
	filter
	{
		"system:windows",
		"configurations:*"
	}

	systemversion "lastest"

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
		"SDL2test"
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
