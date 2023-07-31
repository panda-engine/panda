
add_requires("quickjs")

--add_includedirs("./inc")

target("jsc")
    add_deps("pmalloc", "log", "quickjspp")
    set_kind("static")
    add_files("./jscore/*.cpp")
    set_languages("cxx20")
    add_cflags("-DJS_STRICT_NAN_BOXING")
    -- if is_plat("linux") then 
    --     add_packages("quickjs")
    -- elseif is_plat("windows") then 
    --     add_files("./jscore/win/win_def.cpp")
    --     after_build(function (target)
    --         os.cp("$(projectdir)/src/bin/jsc.dll", path.join(target:targetdir(), "./engine/bin/jsc.dll"))
    --     end)
    -- end

target("ffi")
    add_deps("jsc", "pmalloc", "log")
    set_kind("static")
    add_files("./ffi/*.cpp")
    set_languages("cxx20")
    add_cflags("-DJS_STRICT_NAN_BOXING")

target("test_dynamic")
    add_deps("jsc")
    set_kind("shared")
    --add_links("../bin/jsc")
    --add_languages("c++20")
    add_files("test/test_dynamic.c")
    add_cflags("-DJS_STRICT_NAN_BOXING")

target("test_js")
    set_kind("binary")
    add_deps("jsc", "ffi")
    add_files("test/test.c")
    after_build(function (target)
        os.cp("$(projectdir)/src/js/test/*.js", target:targetdir())
    end)

