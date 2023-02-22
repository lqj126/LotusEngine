workspace "Lotus" --�����������
    architecture "x86_64" --����ƽ̨ ֻ��64λ--(x86,x86_64,ARM)
        startproject "Sandbox" 

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }
--��ʱ���� ���� ���Ŀ¼
--��ϸ������֧�ֵ�tokens �ɲο� [https://github.com/premake/premake-core/wiki/Tokens]
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

project "Lotus" --��Ŀ����
    location "Lotus" --���·��
    kind "StaticLib" --��������Ŀ��lib��̬��
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")--���Ŀ¼
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")--�м���ʱ�ļ���Ŀ¼

    pchheader "ltpch.h"
    pchsource "Lotus/src/ltpch.cpp"

    files--����Ŀ���ļ�
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

    includedirs--���Ӱ���Ŀ¼
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

    filter "system:windows"--windowsƽ̨������
        systemversion "latest"

        defines --Ԥ�����
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