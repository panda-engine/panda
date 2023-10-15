add_rules("mode.debug", "mode.release")

add_includedirs("src")

-- includes("src/log/**xmake.lua", "src/malloc/**xmake.lua",
--         "src/js/**xmake.lua", "src/tp/**xmake.lua")

includes("src/*/xmake.lua")
