cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_csv 
	 VERSION 
	 LANGUAGES C
	 DESCRIPTION "Librerie per poter estrarre i dati dai file csv secondo nostre esigenze"
	 )
	 
add_library(csv STATIC libcsv/src/csv.c)

target_include_directories(csv PUBLIC libcsv/src)

add_library(lib::csv ALIAS csv)

add_library(estrazione_csv STATIC libestrazione_csv/src/estrattore_csv.c)

target_link_libraries( estrazione_csv
	PUBLIC
	lib::csv
)

target_include_directories(estrazione_csv PUBLIC libestrazione_csv/include)

add_library(lib::estrazione_csv ALIAS estrazione_csv)
