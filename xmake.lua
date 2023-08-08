add_rules("mode.debug", "mode.release")

add_includedirs("src/log/inc", "src/js/inc", 
                "src/malloc/inc", "src/scene/inc", "src/tp/inc")

includes("src/log/**xmake.lua", "src/malloc/**xmake.lua", 
        "src/js/**xmake.lua", "src/tp/**xmake.lua")

target("panda")
    set_kind("phony")
    add_deps("tp")
    add_deps("jsc", "pmalloc", "log")

target("test_all")
    set_kind("phony")
    add_deps("test_js", "test_log", "test_pmalloc")