#ifndef calcolo_output_h
#define calcolo_output_h
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "estrattore_csv.h"
	#include "formule.h"
	#include "parametri.h"
	
	typedef enum {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O} tipo_calcolo_output;
	
	float calcolo_potenza_curve_di_potenza(tipo_calcolo_output metodo, const char *nome_turbina, const struct turbina *head, float vel_vento);
	
	float calcolo_potenza_curve_coefficienti(tipo_calcolo_output metodo, const char *nome_turbina, const struct turbina *head, float vel_vento, float densita_aria);
	
	int trova_vel_vento_per_interpolazione(float *vel_min, float *vel_max, float vel_vento, const struct turbina *target, int lunghezza_vettore);
	
	float interpolazione_potenza_per_valori_mancanti(tipo_calcolo_output metodo, const struct turbina *puntatore, int i);
	
	float interpolazione_coefficienti_per_valori_mancanti(tipo_calcolo_output metodo, const struct turbina *puntatore, int i);
	
#endif