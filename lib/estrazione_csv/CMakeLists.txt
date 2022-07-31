cmake_minimum_required( VERSION 3.16.3 )

project( Librerie_csv 
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Librerie per poter estrarre i dati dai file csv secondo nostre esigenze"
	 )
	 
add_library(estrazione_csv STATIC src/estrattore_csv_turbine.c src/estrattore_csv_weather.c src/estrattore_csv_power_coefficient.c src/estrattore_csv_power_curves.c)

target_link_libraries( estrazione_csv
	PUBLIC
	lib::csv
)

target_include_directories(estrazione_csv PUBLIC include)

add_library(lib::estrazione_csv ALIAS estrazione_csv)
