project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

    files 
    {
        "src/glad.c",
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
    }

    includedirs 
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"


    filter "configurations:Debug"
		runtime "Debug"
        buildoptions "/MT"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
        buildoptions "/MT"
		optimize "on"
    
    -- filter { "system:windows", "configurations:Release"}
    --    buildoptions "/MT"