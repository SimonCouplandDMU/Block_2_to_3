project "SoLoud"
    kind "StaticLib"
    language "C++"
    
	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/audiosource/**.c*",
		"src/filter/**.c*",
		"src/core/**.c*",
		"src/backend/null/**.c*",
		"src/backend/winmm/**.c*"
	}

	includedirs
	{
		"src/**",
		"include"
	}
	    
	filter "system:windows"
        buildoptions { "-std=c17", "-lgdi32" }
        systemversion "latest"
        staticruntime "On"
		defines { "WITH_WINMM" }
		defines { "WITH_NULL" }
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

--project "Simplest"
--	kind "ConsoleApp"
--    language "C++"
--	staticruntime "off"
--    
--	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
--    objdir ("build/" .. outputdir .. "/%{prj.name}")
--	
--	files
--	{
--		"demos/simplest/*.cpp"
--	}
--	includedirs
--	{
--		"include"
--	}
--	
--	links
--	{
--		"SoLoud"
--	}
--	
--	filter "system:windows"
--        buildoptions { "-std=c17", "-lgdi32" }
--        systemversion "latest"
--        staticruntime "On"
--		defines { "_CRT_SECURE_NO_WARNINGS" }
--     
--	filter "configurations:Debug"
--		runtime "Debug"
--		symbols "On"
--
--	filter "configurations:Release"
--		runtime "Release"
--		optimize "On"
--	
			
	