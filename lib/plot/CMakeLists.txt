cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_gnuplot
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Librereria per generazione dei grafici"
	 )
	 
add_library(plot STATIC src/plot.c)

target_link_libraries( plot
	PUBLIC
	lib::estrazione_csv
	lib::gnuplot_i
	lib::calcolo_output
)

target_link_libraries( formule
	PUBLIC
	m #link alla libreria libm.so (math.h)
)

target_include_directories(plot PUBLIC include)

add_library(lib::plot ALIAS plot)