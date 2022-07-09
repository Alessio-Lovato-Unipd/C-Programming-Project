cmake_minimum_required( VERSION 3.10.2 )

project( test_lib_csv
	VERSION 0.2
	DESCRIPTION "Test libreria csv"
	)

add_executable( test_csv src/test_csv.c )

target_link_libraries( test_csv
	PRIVATE
	lib::csv
	TTS::Unity
)


