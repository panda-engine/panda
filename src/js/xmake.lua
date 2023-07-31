

target("jsc")
    add_deps("pmalloc", "log", "quickjspp")
    set_kind("static")
    add_files("./jscore/*.cpp")
    set_languages("cxx20")
    add_cxflags("-DJS_STRICT_NAN_BOXING")

target("ffi")
    add_deps("jsc", "pmalloc", "log")
    set_kind("static")
    add_files("./ffi/*.cpp")
    set_languages("cxx20")
    add_cxflags("-DJS_STRICT_NAN_BOXING")

target("test_dynamic")
    add_deps("jsc")
    set_kind("shared")
    add_files("test/test_dynamic.c")
    add_cxflags("-DJS_STRICT_NAN_BOXING")

target("test_js")
    set_kind("binary")
    add_deps("jsc", "ffi")
    add_files("test/test.c")
    after_build(function (target)
        os.cp("$(projectdir)/src/js/test/*.js", target:targetdir())
    end)

