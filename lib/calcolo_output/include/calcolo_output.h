#ifndef calcolo_output_h
#define calcolo_output_h
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "estrattore_csv.h"
	#include "formule.h"
	#include "parametri.h"
	
	//metodo utilizzato sia per l'interpolazione delle curve grezze, sia per il calcolo dell'output finale
	typedef enum {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O} tipo_calcolo_output;
	
	//funzioni che richiamano l'interpolazione delle curve grezze estratte dai file csv e calcolano l'output di potenza a partire da esse
	//l'altezza del mozzo in queste funzioni serve solo ad identificare la turbina, non influisce nel calcolo dei parametri atmosferici
	float calcolo_potenza_curve_di_potenza(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float altezza_mozzo, float vel_vento, const float *array_vento);
	
	float calcolo_potenza_curve_coefficienti(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float altezza_mozzo, float vel_vento, float densita_aria, const float *array_vento);
	
	//funzione interna utile per effettuare l'interpolazione delle curve in caso di valori di velocità del vento non presenti nelle curve
	int trova_vel_vento_per_interpolazione(float *vel_min, float *vel_max, float vel_vento, int lunghezza_vettore, const float *array_vento);
	
	//funzioni che effettuano l'interpolazione dei valori nulli delle curve grezze estratte dai file csv
	void interpolazione_potenza_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt, const float *array_vento);
	
	void interpolazione_coefficienti_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt, const float *array_vento);
	
#endif