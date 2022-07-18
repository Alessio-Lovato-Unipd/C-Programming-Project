cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_csv 
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Librerie esterna per poter estrarre i dati dai file csv"
	 )

add_library(csv STATIC src/csv.c)

target_include_directories(csv PUBLIC src)

add_library(lib::csv ALIAS csv)
