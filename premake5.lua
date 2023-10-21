VULKAN_SDK = os.getenv("VULKAN_SDK")

workspace "hg"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
	startproject "HGnut"

--当前路径为premake5.lua所在路径
--create outputdir macro
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--使用submodule的premake5.lua文件
include "hg/vendor/GLFW"
include "hg/vendor/Glad"
include "hg/vendor/imgui"
include "hg/vendor/yaml-cpp"
-- include "Hazel/vendor/box2D"

project "hg"
    location "%{prj.name}" -- 规定了targetdir和objdir还需要这个吗，需要，这里的location是生成的vcproj的位置
    kind "StaticLib"
    language "C++"
	staticruntime "off"
	cppdialect "C++17"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") --记得要加括号
	objdir   ("bin-int/" .. outputdir .. "/%{prj.name}") --这里的中英文括号看上去好像
	links {"GLFW", "opengl32.lib", "Glad", "imgui", "yaml-cpp"}

    pchheader "hgpch.h"
    pchsource "%{prj.name}/src/hgpch.cpp"

	defines
	{
	    "_CRT_SECURE_NO_WARNINGS", "YAML_CPP_STATIC_DEFINE",
	}
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/**.hpp",
		"%{prj.name}/vendor/imguizmo/ImGuizmo.h",
		"%{prj.name}/vendor/imguizmo/ImGuizmo.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{prj.name}/src/Hazel",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/stb_image",
		"%{prj.name}/vendor/entt/include",
		"%{prj.name}/vendor/yaml-cpp/include",
		"%{prj.name}/vendor/imguizmo",
		"%{VULKAN_SDK}/Include",
		--"%{prj.name}/vendor/Mono/include",
		--"%{prj.name}/vendor/box2D/include"
	}
	
	--filter "files:'%{prj.name}'/vendor/imguizmo/ImGuizmo.cpp"
	filter "files:hg/vendor/imguizmo/ImGuizmo.cpp"
	--filter "files:**.cpp"
	flags { "NoPCH" }

	filter { "system:windows" }
	    systemversion "latest"
		defines {"HG_PLATFORM_WINDOWS", "GLFW_INCLUDE_NONE", "HG_ENABLE_ASSERTS"}
		
		postbuildcommands
		{
		    -- "copy default.config bin\\project.config"
			-- copy freom relative path to ... 注意这里的COPY前面没有%
		    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.."\\Sandbox")
		}

    filter { "configurations:Debug" }
        defines { "HG_DEBUG"}
		-- in VS2019 that is Additional Library Directories
		libdirs
		{
			"%{VULKAN_SDK}/Lib",
			--"%{prj.name}/vendor/Mono/lib/Debug"
		}
		
		links
		{
			"spirv-cross-cored.lib",
			"spirv-cross-glsld.lib",
			"SPIRV-Toolsd.lib",
			--"libmono-static-sgen.lib"
		}
		
        symbols "On"
		runtime "Debug" -- 运行时链接的dll是debug类型的	

    filter { "configurations:Release"}
        defines { "HG_RELEASE"}
        optimize "On"
		-- in VS2019 that is Additional Library Directories
		libdirs
		{
			"%{VULKAN_SDK}/Lib",
			--"%{prj.name}/vendor/Mono/lib/Release"
		}
		
		links
		{
			"shaderc_shared.lib",
			"spirv-cross-core.lib",
			"spirv-cross-glsl.lib",
			--"SPIRV-Tools.lib",
			--"libmono-static-sgen.lib"
		}
		runtime "Release" -- 运行时链接的dll是release类型的


    filter { "configurations:Dist"}
		defines { "HG_DIST"}
	    optimize "On"

project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/"..outputdir.."/%{prj.name}")
	objdir  ("bin-int/"..outputdir.."/%{prj.name}")
    
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}

    includedirs
	{
        "hg/vendor/spdlog/include",
		"hg/src",
		"hg/src/Hazel",
		"hg/vendor/glm",
		"hg/vendor/imgui",
		"hg/vendor/entt/include",
		"hg/vendor/yaml-cpp/include",
		--"Hazel/vendor/box2D/include"
	}

	links { "hg" }

    filter { "system:Windows" }
	    systemversion "latest"
		 defines { "HG_PLATFORM_WINDOWS"}

    filter { "configurations:Debug"}
        defines { "DEBUG"}
        symbols "On"

    filter { "configurations:Release"}
        defines { "NDEBUG" }
        optimize "On"

    filter { "configurations:Dist"}
		defines { "NDEBUG"}
		optimize "On"


project "HGnut"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/"..outputdir.."/%{prj.name}")
	objdir  ("bin-int/"..outputdir.."/%{prj.name}")
    
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}

    includedirs
	{
        "hg/vendor/spdlog/include",
		"hg/src",
		"hg/src/hg",
		"hg/vendor/glm",
		"hg/vendor/imgui",
		"hg/vendor/entt/include",
		"hg/vendor/yaml-cpp/include",
		"hg/vendor/imguizmo",
		--"Hazel/vendor/Mono/include",
		--"Hazel/vendor/box2D/include"
	}

	links { "hg" }
	

    filter { "system:Windows" }
	    systemversion "latest"
		 defines { "HG_PLATFORM_WINDOWS"}
		 			
		links
		{
		    -- windows needed libs for mono
			"Ws2_32.lib",
			"Bcrypt.lib",
			"Version.lib",
			"Winmm.lib"
		}
		

    filter { "configurations:Debug"}
        defines { "HG_DEBUG"}
        symbols "On"
		
		libdirs
		{
			"%{VULKAN_SDK}/Lib"
		}
		
		links
		{
			"shaderc_sharedd.lib"
		}
		

    filter { "configurations:Release"}
        defines { "HG_RELEASE" }
        optimize "On"

    filter { "configurations:Dist"}
		defines { "HG_DIST"}
		optimize "On"


-- project "Hazel-ScriptCore"
-- 	location "%{prj.name}"
-- 	kind "SharedLib"
-- 	language "C#"
-- 	dotnetframework "4.7.2"
	
-- 	targetdir ("%{prj.name}/Build")
-- 	objdir ("%{prj.name}/Intermediates")

-- 	files 
-- 	{
-- 		"%{prj.name}/Scripts/**.cs"
-- 	}