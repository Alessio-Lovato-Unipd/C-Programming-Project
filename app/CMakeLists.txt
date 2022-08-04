cmake_minimum_required( VERSION 3.16.3 )

project( Applicazione_principale
         VERSION 0.1
         LANGUAGES C
         DESCRIPTION "creazione makefile per il file sorgente principale" )

add_executable(main src/main.c)

target_include_directories(main PRIVATE include) 

target_link_libraries( main
	PRIVATE 
	lib::csv
	lib::estrazione_csv
	lib::formule
	lib::parametri
	lib::calcolo_output
)
