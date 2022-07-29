cmake_minimum_required( VERSION 3.10.2 )

project( test_calcolo_output
	VERSION 0.2
	LANGUAGES C
	DESCRIPTION "Test libreria calcolo output"
	)

add_executable( test_calcolo_output test_calcolo_output.c )

target_link_libraries( test_calcolo_output
	PRIVATE
	TTS::Unity
	lib::calcolo_output
	lib::estrazione_csv
	lib::formule
	lib::parametri
)
