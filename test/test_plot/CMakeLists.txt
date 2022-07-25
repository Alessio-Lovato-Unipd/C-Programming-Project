cmake_minimum_required( VERSION 3.16.3 )

project( Testing
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Makefile test plot grafici"
	 )

add_executable(test_plot test_plot.c)

target_link_libraries( test_plot
    PRIVATE 
    lib::plot
    TTS::Unity
)
