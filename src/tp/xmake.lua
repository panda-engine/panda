
target("bgfx")
    set_kind("phony")
    before_build(function (target) 
        if target:is_plat("windows") then
            import("package.tools.msbuild")
            import("core.tool.toolchain")
            local msvc = toolchain.load("msvc")
            local num = msvc:config("vs")
            local mode = (is_mode("debug") and "Debug" or "Release")
            os.cd("src/tp/bgfx")
            os.exec("..\\bx\\tools\\bin\\windows\\genie vs".. num )--.."-".. mode .."64"
            local configs = {}
            table.insert(configs, "/p:Configuration=" .. mode)
            table.insert(configs, "/p:Platform=" .. (target:is_arch("x64") and "x64" or "Win32"))
            table.insert(configs, "bgfx.sln")
            os.cd(format(".build/projects/vs%s", num))
            print("\nbuilding bgfx...")
            msbuild.build(target, configs)
            print("build OK!")
            os.addenv("PATH", "../../win*_vs*/bin/")
            os.cd("../../../../")
            os.trycp("./bgfx/include/", "./inc")
            os.trycp("./bimg/include/*/", "./inc")
            os.trycp("./bx/include/*/", "./inc")
        else
            --todo
        end
        --os.cd("../../../../../../")
    end)
    -- after_build(function (target)
    --     if target:is_plat("windows") then
    --         os.trycp("$(projectdir)/src/tp/bgfx/.build/win*_vs*/bin/*.lib|*example*", target:targetdir())
    --         os.trycp("$(projectdir)/src/tp/bgfx/.build/win*_vs*/bin/*.dll", target:targetdir())
    --         os.trycp("$(projectdir)/src/tp/bgfx/.build/win*_vs*/bin/*.lib", target:targetdir())
    --         os.trycp("$(projectdir)/src/tp/bgfx/.build/win*_vs*/bin/*.exe", target:targetdir())
    --     end
    -- end)

target("tp")
    set_kind("phony")
    add_deps("bgfx")