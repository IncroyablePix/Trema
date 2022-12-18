set_runtimes(is_mode("debug") and "MDd" or "MD")
add_requires("catch2", "glfw", "tinyxml", "stb", "vulkan-headers", "vulkan-validationlayers", "vulkan-loader")
add_requires("imgui v1.88-docking", {configs = {glfw_vulkan = true}})
set_languages("c++20")
set_policy("build.ccache", false)
-- set_config("glfw_vulkan", true)

add_rules("mode.debug", "mode.release", "mode.coverage")

target("trema", function()
    set_kind("$(kind)")
    add_packages("glfw", "tinyxml", "stb", "imgui", "vulkan-headers", "vulkan-validationlayers", "vulkan-loader", { public = true })
    add_headerfiles("Src/(Trema/**.h)", { prefixdir = "Trema" })
    add_files("Src/Trema/**.cpp")
    set_targetdir("./build/$(plat)/$(arch)/$(mode)/lib")

    --after_build(function (target)
    --    os.mkdir(path.join(target:targetdir(), "../include/Trema"))
    --    os.cp("Src/Trema/**", path.join(target:targetdir(), "../include/Trema"))
    --    os.rm(path.join(target:targetdir(), "../include/Trema/**.cpp"))
    --end)

    on_load(function (target)
        if target:kind() == "static" then
            target:add("defines", "TREMA_STATIC", { public = true })
        end
    end)
end)

target("trema_sample", function()
    set_kind("binary")
    set_optimize("fastest")
    add_deps("trema")
    add_includedirs("Src/Trema")
    add_files("Src/Sample/**.cpp")

    -- Platform specifics
    if is_plat("windows") or is_plat("mingw") then
        add_files("Src/Sample/windows/res.rc")
    end

    if is_plat("windows") then
        add_ldflags("/SUBSYSTEM:WINDOWS")
    elseif is_plat("mingw") then
        add_ldflags("-mwindows")
    end

    set_targetdir("./build/$(plat)/$(arch)/$(mode)/trema_sample")
    after_build(function (target)
        os.cp("Src/Sample/resources", path.join(target:targetdir(), "./resources"))
    end)
end)

target("trema_test", function()
    set_kind("binary")
    add_deps("trema")
    add_packages("catch2")
    add_includedirs("Src/Trema")
    add_files("Src/Test/**.cpp")
    set_targetdir("./build/$(plat)/$(arch)/$(mode)/trema_test")
end)
