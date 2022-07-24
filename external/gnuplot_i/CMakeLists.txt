cmake_minimum_required( VERSION 3.16.3 )

project( libreria_gnuplot_i
	VERSION 0.1
	LANGUAGES C
	DESCRIPTION "Libreria gnuplot ANSI C"
	)

add_library( gnuplot_i STATIC src/gnuplot_i.c )

target_include_directories( gnuplot_i
	PUBLIC src
	)

add_library( TTS::gnuplot_i ALIAS gnuplot_i )
