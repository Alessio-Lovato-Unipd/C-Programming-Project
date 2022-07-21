cmake_minimum_required( VERSION 3.16.3 )

project( Calcolo_potenza_turbine
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Assegnamento di informatica 2021-2022"
	 )

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(TARGET_GROUP stable CACHE STRING "Gruppo di sorgenti da compilare")

add_subdirectory(lib)
add_subdirectory(external/csv)

if(TARGET_GROUP STREQUAL stable)
	add_subdirectory(app)
elseif(TARGET_GROUP STREQUAL test)
	include(CTest)

	add_subdirectory(test)
	add_subdirectory(external/Unity)
else()
	message(FATAL_ERROR " TARGET_GROUP sconosciuto")
endif() 
