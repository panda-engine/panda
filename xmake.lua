add_rules("mode.debug", "mode.release")

add_includedirs("src/log/inc", "src/js/jscore/inc")

add_requires("fmt")
add_packages("fmt")

includes("src/**.lua")

-- target("panda")
--     add_deps("jsc")

target("test_all")
    add_deps("test_jsc", "test_log")