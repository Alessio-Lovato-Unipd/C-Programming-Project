cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_csv 
	 VERSION 3.0
	 LANGUAGES C
	 DESCRIPTION "Librereria per calcolare parametri per calcolo potenza"
	 )
	 
add_library(formule STATIC src/parametri.c)

target_include_directories( parametri
	PUBLIC include)

add_library(lib::parametri ALIAS parametri)