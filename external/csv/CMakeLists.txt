cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_csv 
<<<<<<< HEAD
<<<<<<< HEAD
	 VERSION 3.0
=======
	 VERSION 0.1
>>>>>>> main
=======
	 VERSION 0.1
>>>>>>> testing_formule
	 LANGUAGES C
	 DESCRIPTION "Librerie esterna per poter estrarre i dati dai file csv"
	 )

add_library(csv STATIC src/csv.c)

target_include_directories(csv PUBLIC src)

add_library(lib::csv ALIAS csv)
