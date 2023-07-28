add_requires("mimalloc")

target("pmalloc")
    set_kind("static")
    add_files("./normal.c")
    add_packages("mimalloc")

target("test_pmalloc")
    add_deps("pmalloc")
    set_kind("binary")
    add_files("./test.c")
