cmake_minimum_required( VERSION 3.16.3 )

project( Librerie

	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Creazione makefile per riunire i makefile delle librerie"
	 )

add_subdirectory(estrazione_csv)

add_subdirectory(formule)

add_subdirectory(parametri)

add_subdirectory(calcolo_output)