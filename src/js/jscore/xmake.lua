
add_requires("quickjs")

add_includedirs("./inc")

target("jsc")
    set_kind("static")
    add_files("./jsc.c", "./cutils.c")
    if is_plat("linux") then 
        add_packages("quickjs")
    elseif is_plat("windows") then 
        add_files("win_def.c")
        after_build(function (target)
            os.cp("$(projectdir)/src/bin/jsc.dll", path.join(target:targetdir(), "./engine/bin/jsc.dll"))
        end)
    end


target("test_jsc")
    set_kind("binary")
    add_deps("jsc")
    add_files("test.c")
    if is_plat("linux") then 
        add_packages("quickjs")
    end
    after_build(function (target)
        os.cp("$(projectdir)/src/js/jscore/hello.js", target:targetdir())
    end)

