workspace "hg"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 导入GLFW库  
-- IncludeDir 只需要添加为编译器的包含目录
IncludeDir = {}
IncludeDir["GLFW"] = "hg/vendor/GLFW/include"

include "hg/vendor/GLFW"

project "hg"
	location "hg"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hgpch.h"
	pchsource "hg/src/hgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"hg/vendor/spdlog/include",
		"hg/src",
		-- 添加
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"Dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HG_PLATFORM_WINDOWS",
			"HG_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .."/SandBox")
		}

		filter "configurations:Debug"
		defines "HG_DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "HG_RELEASE"
		optimize "On"


	filter "configurations:Dist"
		defines "HG_DIST"
		optimize "On"




project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}

	includedirs
	{
		"hg/vendor/spdlog/include",
		"hg/src"
	}

	links
	{
		"hg"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HG_PLATFORM_WINDOWS",
		}


		filter "configurations:Debug"
			defines "HG_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "HG_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "HG_DIST"
			optimize "On"