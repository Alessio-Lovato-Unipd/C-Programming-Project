cmake_minimum_required( VERSION 3.16.3 )

project( test_lib_csv
	VERSION 0.2
	LANGUAGES C
	DESCRIPTION "Test libreria csv"
	)

add_executable( test2 src/test2.c )

target_link_libraries( test2
	PRIVATE
	lib::csv
)


