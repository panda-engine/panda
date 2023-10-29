


target("id")
    set_kind("static")
    add_files("./*.c")
    set_languages("c99")
    add_packages("mimalloc")