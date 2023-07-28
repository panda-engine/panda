add_requires("mimalloc")

target("pmalloc")
    set_kind("static")
    add_files("./normal.c")
    add_packages("mimalloc")
