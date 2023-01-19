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

include "Lotus/vendor/GLFW"

project "Lotus" --项目名称
    location "Lotus" --相对路径
    kind "SharedLib" --表明该项目是dll动态库
    language "c++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")--输出目录
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")--中间临时文件的目录

    pchheader "ltpch.h"
    pchsource "Lotus/src/ltpch.cpp"

    files--该项目的文件
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs--附加包含目录
    { 
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
    }
	
	links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"--windows平台的配置
        cppdialect "c++17"
        staticruntime "On"  
        systemversion "latest"

        defines --预编译宏
        {
            "LT_BUILD_DLL",
            "LT_PLATFORM_WINDOWS",
            "_WINDLL",
            "_UNICODE",
            "UNICODE",
        }

        postbuildcommands -- build后的自定义命令
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"") --拷贝引擎dll库到sanbox.exe的同一目录下去
            --"{COPY} %{cfg.objdir}/output.map %{cfg.targetdir}"
        }

    filter "configurations:Debug"
        defines "LT_DEBUG"
        runtime "Debug"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "LT_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "LT_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "c++"

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
        "Lotus/src"
    }

    links
    {
        "Lotus"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LT_PLATFORM_WINDOWS",
            "_UNICODE",
            "UNICODE",
        }

    filter "configurations:Debug"
        defines "LT_DEBUG"
        runtime "Debug"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "LT_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "LT_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"