workspace "MABEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "SandBox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder {solution directory}
IncludeDir = {}
IncludeDir["GLFW"] = "MABEngine/vendor/GLFW/GLFW/include"
IncludeDir["Glad"] = "MABEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "MABEngine/vendor/ImGUI/imgui"


include "MABEngine/vendor/GLFW/premake5-glfw.lua"
include "MABEngine/vendor/Glad/premake5-glad.lua"
include "MABEngine/vendor/ImGUI/premake5-imgui.lua"


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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"MABENGINE_PLATFORM_WINDOWS",
			"MABENGINE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			-- "MAB_ENABLE_ASSERTS",
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	
	filter "configurations:Debug"
		defines "MABENGINE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MABENGINE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MABENGINE_DIST"
		buildoptions "/MD"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MABENGINE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MABENGINE_DIST"
		buildoptions "/MD"
		optimize "On"