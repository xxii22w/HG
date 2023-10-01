project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

	filter "system:windows"
        buildoptions { "-std=c11", "-lgdi32" }
        systemversion "latest"
    -- 过滤器 Debug配置 仅适用于Debug
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    -- 过滤器 Release配置
    filter "configurations:Release"
        runtime "Release"
        -- 启用优化
        optimize "on"

