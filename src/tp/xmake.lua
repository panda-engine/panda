target("quickjspp")
    before_build(function (target) 
        os.trycp("src/tp/quickjspp/cutils.h", "src/tp/inc/quickjspp/")
        os.trycp("src/tp/quickjspp/quickjs.h", "src/tp/inc/quickjspp/")
        os.trycp("src/tp/quickjspp/quickjs-libc.h", "src/tp/inc/quickjspp/")
        local file = io.open("src/tp/quickjspp/VERSION", "r")
        local vers = file:read()
        file:close()
        vars = vers:gsub("%s+", "")
        file = io.open("src/tp/inc/quickjspp/quickjs-version.h", "w+")
        file:write("#define QUICKJS_VERSION \"" .. vers .. "\"")
        file:close()
    end)
    set_kind("static")
    add_cxflags("-DJS_STRICT_NAN_BOXING")
    add_files("quickjspp/lib*.c", "quickjspp/quickjs*.c", "quickjspp/cutils.c")


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

target("bullet")
    set_kind("phony")
    --add_links("Bullet2FileLoader", "Bullet3Collision", "Bullet3Common", "Bullet3Dynamics", "Bullet3Geometry", "Bullet3OpenCL_clew", "BulletDynamics", "BulletCollision", "BulletInverseDynamics", "BulletSoftBody", "LinearMath")
    before_build(function (target) 
        os.cd("src/tp/bullet")
        os.trycp("./src/", "../inc/bullet")
        if not os.isdir("./build") then 
            os.mkdir("./build")
        end
        local configs = {"-DBUILD_CPU_DEMOS=OFF", "-DBUILD_OPENGL3_DEMOS=OFF", "-DBUILD_BULLET2_DEMOS=OFF", "-DBUILD_UNIT_TESTS=OFF", "-DINSTALL_LIBS=ON", "-DCMAKE_DEBUG_POSTFIX="}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (is_mode("debug") and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=OFF")
        table.insert(configs, "-DUSE_DOUBLE_PRECISION=OFF")
        table.insert(configs, "-DBUILD_EXTRAS=OFF")
        if is_plat("windows") then
            table.insert(configs, "-DUSE_MSVC_RUNTIME_LIBRARY_DLL=OFF")
        end
        os.cd("./build")
        local str = ""
        for i, c in ipairs(configs) do
            str = str .. c .. " "
        end
        os.exec("cmake .. " .. str)
        os.exec("cmake --build . --config " .. (is_mode("debug") and "Debug" or "Release"))
        os.addenv("PATH", "./lib/" .. (is_mode("debug") and "Debug/" or "Release/"))
    end)

target("tp")
    set_kind("phony")
    add_deps("bgfx", "bullet")