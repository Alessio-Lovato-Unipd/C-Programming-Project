cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_gnuplot
	 VERSION 3.0
	 LANGUAGES C
	 DESCRIPTION "Librereria per generazione dei grafici"
	 )
	 
add_library(plot STATIC src/plot.c)

target_link_libraries( plot
	PUBLIC
	lib::estrazione_csv
)

target_include_directories(plot PUBLIC include)

add_library(lib::plot ALIAS plot)