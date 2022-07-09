cmake_minimum_required(VERSION 3.16)

project( Calcolo_potenza_turbine
	 VERSION 
	 LANGUAGES C
	 DESCRIPTION "Assegnamento di informatica 2021-2022")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(main src/main.c lib/lettore_csv/libcsv/src/csv.c lib/lettore_csv/libestrazione_csv/src/estrattore_csv.c)

target_include_directories(main PUBLIC include) 

add_subdirectory(lib)