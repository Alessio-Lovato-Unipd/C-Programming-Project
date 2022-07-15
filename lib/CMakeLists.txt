cmake_minimum_required( VERSION 3.16.3 )

project( Librerie
	 VERSION 3.0
	 LANGUAGES C
	 DESCRIPTION "Creazione makefile per riunire i makefile delle librerie"
	 )

add_subdirectory(estrazione_csv)

add_subdirectory(formule)