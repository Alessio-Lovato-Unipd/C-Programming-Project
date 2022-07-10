cmake_minimum_required( VERSION 3.16.3 )

project( Testing
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Inserimento makefile testing"
	 )

add_subdirectory(external/Unity)

add_executable(test_est test_estrazione.c)

target_link_libraries( test_est
	PRIVATE 
	lib::csv
	lib::estrazione_csv
	TTS::Unity
)
