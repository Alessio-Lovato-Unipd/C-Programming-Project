cmake_minimum_required(VERSION 3.16)

project( Librerie_csv 
	 VERSION 
	 LANGUAGES C
	 DESCRIPTION "Librerie per poter estrarre i dati dai file csv secondo nostre esigenze")
	 
add_library(csv STATIC libcsv/src/csv.c)

target_include_directories(csv PRIVATE libcsv/src)

add_library(lib::csv ALIAS csv)


add_library(libestrazione_csv STATIC libestrazione_csv/src/estrattore_csv.c)

target_include_directories(libestrazione_csv PUBLIC libestrazione_csv/include)

add_library(lib::libestrazione_csv ALIAS libestrazione_csv)
