cmake_minimum_required( VERSION 3.16.3 )

project( Testing
	 VERSION 0.1
	 LANGUAGES C
	 DESCRIPTION "Inserimento makefile testing"
	 )

add_subdirectory(test_estrazione)

add_subdirectory(test_csv)

add_subdirectory(test_formule)

add_subdirectory(test_parametri)

add_subdirectory(test_calcolo_output)
