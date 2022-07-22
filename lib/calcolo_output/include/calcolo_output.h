#ifndef calcolo_output_h
#define calcolo_output_h
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "estrattore_csv.h"
	
	float calcolo_potenza_curve_di_potenza(const char *nome_turbina, const struct turbina *head, float vel_vento);
	
	float calcolo_potenza_curve_coefficienti(const char *nome_turbina, const struct turbina *head, float vel_vento);
	
	void trova_vel_vento_per_interpolazione(int *vel_min, int *vel_max, int vel_vento, const struct turbina *target);
	
#endif