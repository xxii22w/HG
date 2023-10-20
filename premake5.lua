-- 工作空间名称
workspace "hg"
	-- 架构
	architecture "x64"
	startproject "HGnut"
	-- 配置
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

-- 自定义变量 输出目录
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 导入GLFW库  
-- IncludeDir 只需要添加为编译器的包含目录
IncludeDir = {}
IncludeDir["GLFW"] = "hg/vendor/GLFW/include"
IncludeDir["Glad"] = "hg/vendor/Glad/include"
IncludeDir["Imgui"] = "hg/vendor/imgui"
IncludeDir["glm"] = "hg/vendor/glm"
IncludeDir["stb_image"] = "hg/vendor/stb_image"
IncludeDir["entt"] = "hg/vendor/entt/include"
IncludeDir["yaml_cpp"] = "hg/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "hg/vendor/ImGuizmo"



include "hg/vendor/GLFW"
include "hg/vendor/Glad"
include "hg/vendor/imgui"
include "hg/vendor/yaml-cpp"

-- 项目 Hazel
project "hg"
	-- 位置
	location "hg"
	-- 项目类型
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hgpch.h"
	pchsource "hg/src/hgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp",
		"%{prj.name}/src/vendor/glm/glm/**.hpp",
		"%{prj.name}/src/vendor/glm/glm/**.inl"

	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	-- 包含路径
	includedirs
	{
		-- 日志库 spdlog
		"hg/vendor/spdlog/include",
		"hg/src",
		-- 添加
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"

	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"yaml-cpp",
		"opengl32.lib",
		"Dwmapi.lib"
	}

	filter "files:hg/vendor/ImGuizmo/**.cpp"
		flags { "NoPCH" }


	-- 过滤器 windows
	filter "system:windows"

		-- WinSDK版本 这个需要本地化设置 这里保持最新版本
		systemversion "latest"

		defines
		{
			"HG_PLATFORM_WINDOWS",
			"HG_BUILD_DLL",
			"_WINDLL",
			"GLFW_INCLUDE_NONE", -- 那将不会包含任何glfw，他将不报行任何opengl头文件
			
		}


	-- 过滤器 Debug配置 仅适用于Debug
	filter "configurations:Debug"
		defines "HG_DEBUG"
		runtime "Debug"
		symbols "on"
	-- 过滤器 Release配置
	filter "configurations:Release"
		defines "HG_RELEASE"
		runtime "Release"
		-- 启用优化
		optimize "on"
	-- 过滤器 Dist配置
	filter "configurations:Dist"
		defines "HG_DIST"
		runtime "Release"
		optimize "on"


project "HGnut"
	location "HGnut"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"hg/vendor/spdlog/include",
		"hg/src",
		"hg/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"

	}

	links
	{
		"hg"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HG_PLATFORM_WINDOWS",
		}


		filter "configurations:Debug"
			defines "HG_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "HG_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "HG_DIST"
			runtime "Release"
			optimize "on"


project "SandBox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"
		
		
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
		}
		
		includedirs
		{
			"hg/vendor/spdlog/include",
			"hg/src",
			"hg/vendor",
			"%{IncludeDir.glm}"
		}
		
		links
		{
			"hg"
		}
		
		filter "system:windows"
			systemversion "latest"
		
			defines
			{
				"HG_PLATFORM_WINDOWS",
			}
		
		
			filter "configurations:Debug"
				defines "HG_DEBUG"
				runtime "Debug"
				symbols "on"
		
			filter "configurations:Release"
				defines "HG_RELEASE"
				runtime "Release"
				optimize "on"
		
			filter "configurations:Dist"
				defines "HG_DIST"
				runtime "Release"
				optimize "on"