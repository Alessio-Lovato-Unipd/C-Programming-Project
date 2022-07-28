cmake_minimum_required( VERSION 3.16.3 )

project( Testing
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Inserimento makefile testing"
	 )

add_executable(test_estrazione_turbine test_estrazione_turbine.c)

target_link_libraries( test_estrazione_turbine
	PRIVATE 
	lib::csv
	lib::estrazione_csv
	TTS::Unity
)

add_executable(test_estrazione_weather test_estrazione_weather.c)

target_link_libraries( test_estrazione_weather
	PRIVATE 
	lib::csv
	lib::estrazione_csv
	TTS::Unity
)

add_executable(test_estrazione_curve test_estrazione_curve.c)

target_link_libraries( test_estrazione_curve
	PRIVATE 
	lib::csv
	lib::estrazione_csv
	TTS::Unity
)

