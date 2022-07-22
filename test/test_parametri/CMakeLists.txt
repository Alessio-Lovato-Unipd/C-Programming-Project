cmake_minimum_required( VERSION 3.16.3 )

project( Testing
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Makefile testing parametri"
	 )

add_executable(test_parametri test_parametri.c)

target_link_libraries( test_parametri
    PRIVATE 
    lib::parametri
    lib::formule
    TTS::Unity
)