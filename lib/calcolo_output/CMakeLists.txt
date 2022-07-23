cmake_minimum_required( VERSION 3.16.3 )

project( Libreria_calcolo_output 
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Libreria per calcolare la potenza in uscita in certe condizioni meteo"
	 )
	 
add_library(calcolo_output STATIC src/calcolo_output.c)

target_link_libraries( calcolo_output
	PUBLIC
	lib::estrazione_csv
	lib::formule
	lib::parametri
)

target_include_directories(calcolo_output PUBLIC include)

add_library(lib::calcolo_output ALIAS calcolo_output)