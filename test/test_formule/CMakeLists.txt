cmake_minimum_required( VERSION 3.16.3 )

project( Testing
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Makefile testing formule"
	 )

add_executable(test_formule test_formule.c)

target_link_libraries( test_formule
	PRIVATE 
	lib::formule
	TTS::Unity
)
