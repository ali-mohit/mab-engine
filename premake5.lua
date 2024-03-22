workspace "MABEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MABEngine"
	location "MABEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

	pchheader "mabengine_pch.h"
	pchsource "MABEngine/src/mabengine_pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"MABENGINE_PLATFORM_WINDOWS",
			"MABENGINE_BUILD_DLL",
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	
	filter "configurations:Debug"
		defines "MABENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MABENGINE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MABENGINE_DIST"
		optimize "On"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"MABEngine/vendor/spdlog/include",
		"MABEngine/src",
		"%{prj.name}/src",
	}

	links {
		"MABEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"MABENGINE_PLATFORM_WINDOWS"
		}

	
	filter "configurations:Debug"
		defines "MABENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MABENGINE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MABENGINE_DIST"
		optimize "On"