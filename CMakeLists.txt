cmake_minimum_required( VERSION 3.10.2 )

project( SudoPassExamLII2122
	VERSION 0.3
	DESCRIPTION "SudoPassExamLII2122"
	)


if (MSVC)
	# warning level 4 and all warnings as errors
	add_compile_options(/W4 /WX)
else()
	# lots of warnings and all warnings as errors
	add_compile_options(-Wall -Wextra -pedantic)
endif()

set(TARGET_GROUP test CACHE STRING "Group to build") 

if(TARGET_GROUP STREQUAL production)
	add_subdirectory(app)
elseif(TARGET_GROUP STREQUAL test)
	include(CTest)

	add_subdirectory(external/Unity)
	add_subdirectory(test/test_csv)
else()
	message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()
