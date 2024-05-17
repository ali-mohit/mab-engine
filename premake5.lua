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
IncludeDir["glm"] = "MABEngine/vendor/glm"
IncludeDir["stb_image"] = "MABEngine/vendor/stb_image"



include "MABEngine/vendor/GLFW/premake5-glfw.lua"
include "MABEngine/vendor/Glad/premake5-glad.lua"
include "MABEngine/vendor/ImGUI/premake5-imgui.lua"


project "MABEngine"
	location "MABEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

	pchheader "mabengine_pch.h"
	pchsource "MABEngine/src/mabengine_pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		
		"%{prj.name}/vendor/glm/glm/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"MABENGINE_PLATFORM_WINDOWS",
			--"INSIDE_MABENGINE_DLL",
			--"MABENGINE_INCLUDE_AS_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS",
			"MAB_ENABLE_ASSERTS",
		}
	
	filter "configurations:Debug"
		defines "MABENGINE_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "MABENGINE_RELEASE"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		defines "MABENGINE_DIST"
		buildoptions "/MT"
		optimize "on"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"MABEngine/vendor/spdlog/include",
		"MABEngine/vendor/ImGUI/imgui",
		"MABEngine/src",
		"%{prj.name}/src",
		"%{IncludeDir.glm}",
	}

	links {
		"MABEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"MABENGINE_PLATFORM_WINDOWS",
			--"MABENGINE_INCLUDE_AS_DLL",
		}

	
	filter "configurations:Debug"
		defines "MABENGINE_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "MABENGINE_RELEASE"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		defines "MABENGINE_DIST"
		buildoptions "/MT"
		optimize "on"