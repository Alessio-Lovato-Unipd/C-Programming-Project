cmake_minimum_required( VERSION 3.16.3 )

project( Applicazione_principale
         VERSION 0.1
         LANGUAGES C
         DESCRIPTION "creazione makefile per il file sorgente principale" )

add_executable(potenze_tot src/potenze_tot.c)

target_include_directories(potenze_tot PRIVATE include) 

target_link_libraries( potenze_tot
	PRIVATE 
	lib::csv
	lib::gnuplot_i
	lib::estrazione_csv
	lib::formule
	lib::parametri
	lib::calcolo_output
	lib::plot
)

add_executable(potenze_giorno src/potenze_giorno.c)

target_include_directories(potenze_giorno PRIVATE include) 

target_link_libraries( potenze_giorno
	PRIVATE 
	lib::csv
	lib::gnuplot_i
	lib::estrazione_csv
	lib::formule
	lib::parametri
	lib::calcolo_output
	lib::plot
)

add_executable(potenze_parco_eolico src/potenze_parco_eolico.c)

target_include_directories(potenze_parco_eolico PRIVATE include) 

target_link_libraries( potenze_parco_eolico
	PRIVATE 
	lib::csv
	lib::gnuplot_i
	lib::estrazione_csv
	lib::formule
	lib::parametri
	lib::calcolo_output
	lib::plot
)

