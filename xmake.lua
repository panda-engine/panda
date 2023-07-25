add_rules("mode.debug", "mode.release")

includes("src/**.lua")

-- target("panda")
--     add_deps("jsc")

target("test_all")
    add_deps("test_jsc")