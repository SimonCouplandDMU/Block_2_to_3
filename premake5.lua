workspace "Application"
	architecture "x64"
	startproject "Application"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "Engine"

project "Engine"
	location "engine"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")
	
	pchheader "engine_pch.h"
	pchsource "engine/precompiled/engine_pch.cpp"
	
	files
	{
		"%{prj.name}/enginecode/**.h",
		"%{prj.name}/enginecode/**.cpp",
		"engine/precompiled/engine_pch.h",
		"engine/precompiled/engine_pch.cpp"
	}

	includedirs
	{
		"%{prj.name}/enginecode/",
		"%{prj.name}/enginecode/include/independent",
		"%{prj.name}/enginecode/include/",
		"%{prj.name}/precompiled/",
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/Glad/include",
		"vendor/glm/",
		"vendor/STBimage",
		"vendor/freetype2/include",
		"vendor/IMGui",
		"vendor/enTT/single_include",
		"vendor/box2d/include",
		"vendor/soLoud/include"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"Freetype",
		"IMGui",
		"box2d",
		"SoLoud"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

project "Application"
	location "application"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/include",
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/enginecode/include/",
		"engine/precompiled/",
		"vendor/glfw/include",
		"vendor/glm/",
		"vendor/spdlog/include",
		"vendor/json/single_include/nlohmann",
		"vendor/IMGui",
		"vendor/enTT/single_include",
		"vendor/luaBridge/Source",
		"vendor/box2d/include",
		"vendor/lua",
		"%{prj.name}/assets/scripts",
		"vendor/soLoud/include"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

 
group "Vendor"



	include "vendor/glfw"
	include "vendor/googletest"
	include "vendor/Glad"
	include "vendor/freetype2"
	include "vendor/IMGui"
	include "vendor/box2d"
	include "vendor/soLoud"