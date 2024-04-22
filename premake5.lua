workspace "Attractor"
    architecture "x64"
    startproject "attractor"

    configurations
	{
		"Debug",
		"Release"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
LibDirs = {}

IncludeDirs["raylib"] = "%{wks.location}/attractor/vendor/raylib/include"
IncludeDirs["imguiDir"] = "%{wks.location}/attractor/vendor/imgui"
IncludeDirs["rlImgui"] = "attractor/vendor/rlImGui"
LibDirs["raylib"] = "attractor/vendor/raylib/lib"


include "attractor/vendor/imgui"
include "attractor/vendor/rlImGui"

project "attractor"
    location "attractor"
    language "C++"
    cppdialect "C++17"
    kind "ConsoleApp"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDirs.raylib}",
        "%{IncludeDirs.imguiDir}",
        "%{IncludeDirs.rlImgui}",
    }

    libdirs {
        "%{LibDirs.raylib}"
    }


    links {
        "ImGui",
        "raylib",
        "rlImGui",
        "winmm"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"


