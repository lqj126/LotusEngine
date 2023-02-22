workspace "Lotus" --解决方案名称
    architecture "x86_64" --编译平台 只编64位--(x86,x86_64,ARM)
        startproject "Sandbox" 

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }
--临时变量 定义 输出目录
--详细的所有支持的tokens 可参考 [https://github.com/premake/premake-core/wiki/Tokens]
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
  
-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Lotus/vendor/GLFW/include"
IncludeDir["Glad"] = "Lotus/vendor/Glad/include"
IncludeDir["ImGui"] = "Lotus/vendor/imgui"
IncludeDir["glm"] = "Lotus/vendor/glm"

include "Lotus/vendor/GLFW"
include "Lotus/vendor/Glad"
include "Lotus/vendor/imgui"

project "Lotus" --项目名称
    location "Lotus" --相对路径
    kind "StaticLib" --表明该项目是lib静态库
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")--输出目录
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")--中间临时文件的目录

    pchheader "ltpch.h"
    pchsource "Lotus/src/ltpch.cpp"

    files--该项目的文件
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }
	
		defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs--附加包含目录
    { 
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{prj.name}/Resources/Texture",
		"%{prj.name}/Resources/Shader"
    }
	
	links
    {
        "GLFW",
		"Glad",
		"ImGui",
        "opengl32.lib"
    }

    filter "system:windows"--windows平台的配置
        systemversion "latest"

        defines --预编译宏
        {
			"LT_PLATFORM_WINDOWS",
			"LT_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "LT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LT_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Lotus/vendor/spdlog/include",
        "Lotus/src",
        "Lotus/vendor",
		"%{IncludeDir.glm}"
    }

    links
    {
        "Lotus"
    }

    filter "system:windows"
        systemversion "latest"

		defines
		{
			"LT_PLATFORM_WINDOWS"
		}

    filter "configurations:Debug"
        defines "LT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LT_DIST"
        runtime "Release"
        optimize "on"