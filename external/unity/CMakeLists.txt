cmake_minimum_required( VERSION 3.10.2 )

project( unity_lib
	DESCRIPTION "Unity come libreria"
	)

add_library( Unity STATIC src/unity.c )

target_include_directories( Unity PUBLIC src)

add_library( TTS::Unity ALIAS Unity )