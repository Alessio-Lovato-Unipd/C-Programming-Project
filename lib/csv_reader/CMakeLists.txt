
add_library(csv STATIC libcsv/src/csv.c)

target_include_directories(csv PUBLIC libcsv/src)

add_library(lib::csv ALIAS csv)
