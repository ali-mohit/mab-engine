project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

    files 
    {
        "imgui/imconfig.h",
        "imgui/imgui.cpp",
        "imgui/imgui.h",
        "imgui/imgui_demo.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_internal.h",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
        "imgui/imstb_rectpack.h",
        "imgui/imstb_textedit.h",
        "imgui/imstb_truetype.h",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
        buildoptions "/MT"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
        buildoptions "/MT"
		optimize "on"
