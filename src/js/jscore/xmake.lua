
add_requires("quickjs")

--add_includedirs("./inc")

target("jsc")
    add_deps("pmalloc", "log")
    set_kind("static")
    add_files("./*.cpp", "./cutils.c")
    set_languages("cxx20")
    if is_plat("linux") then 
        add_packages("quickjs")
    elseif is_plat("windows") then 
        add_files("win/win_def.cpp")
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
        os.cp("$(projectdir)/src/js/jscore/*.js", target:targetdir())
    end)

