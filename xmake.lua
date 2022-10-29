add_requires("catch2", "glfw", "vulkan-headers", "vulkan-validationlayers", "vulkan-loader")
set_languages("c++20")
set_policy("build.ccache", false)

add_rules("mode.debug", "mode.release")

target("trema_lib", function()
    set_kind("static")
    add_packages("glfw", "vulkan-headers", "vulkan-validationlayers", "vulkan-loader", { public = true })
    add_headerfiles("Src/Trema/**.h", { prefixdir = "Trema" })
    add_files("Src/Trema/**.cpp")
    set_targetdir("./build/$(plat)/$(arch)/$(mode)/lib")

    after_build(function (target)
        os.mkdir(path.join(target:targetdir(), "../include/Trema"))
        os.cp("Src/Trema/**", path.join(target:targetdir(), "../include/Trema"))
        os.rm(path.join(target:targetdir(), "../include/Trema/**.cpp"))
    end)
end)

target("trema", function()
    set_kind("shared")
    add_packages("glfw", "vulkan-headers", "vulkan-validationlayers", "vulkan-loader", { public = true })
    add_headerfiles("Src/Trema/**.h", { prefixdir = "Trema" })
    add_files("Src/Trema/**.cpp")

    set_targetdir("./build/$(plat)/$(arch)/$(mode)/bin")
end)

target("trema_sample", function()
    set_kind("binary")
    set_optimize("fastest")
    add_deps("trema_lib")
    add_includedirs("Src/Trema")
    add_files("Src/Sample/**.cpp")

    -- Platform specifics
    if is_plat("windows") or is_plat("mingw") then
        add_files("Src/Sample/windows/res.rc")
    end

    set_targetdir("./build/$(plat)/$(arch)/$(mode)/trema_sample")
    after_build(function (target)
        os.cp("Src/Sample/resources", path.join(target:targetdir(), "./resources"))
    end)
end)

target("trema_test", function()
    set_kind("binary")
    add_deps("trema_lib")
    add_packages("catch2")
    add_includedirs("Src/Trema")
    add_files("Src/Test/**.cpp")
    set_targetdir("./build/$(plat)/$(arch)/$(mode)/trema_test")
end)