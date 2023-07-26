--add_includedirs("./inc")

target("log")
    set_kind("static")
    add_files("./*.cpp")
    set_languages("cxx17")

target("test_log")
    add_deps("log")
    set_kind("binary")
    add_files("test.cpp")