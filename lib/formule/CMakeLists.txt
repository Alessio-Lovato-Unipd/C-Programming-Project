cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_formule 
	 VERSION 3.0
	 LANGUAGES C
	 DESCRIPTION "Librererie con formule per calcolare i parametri del Vento"
	 )
	 
add_library(formule STATIC src/formule.c)

target_include_directories( formule
	PUBLIC include)

add_library(lib::formule ALIAS formule)
