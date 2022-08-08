#ifndef calcolo_output_h
#define calcolo_output_h
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "estrattore_csv.h"
	#include "formule.h"
	#include "parametri.h"
	
	typedef enum {CURVA_POTENZA, CURVA_COEFFICIENTI_POTENZA} tipo_curva;

	typedef enum {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O} tipo_calcolo_output;

	
	/*
	 * Funzione che conta il numero di elementi all'interno della lista parametri.
	 * Comincia a contare dal nodo corrispondente al puntatore passato.
	*/
	int conta_elementi(struct parametro *head_parametri);


	/*
	 * Funzione per il calcolo della potenza istantaneo.
	 * I Parametri selezionabili sono:
	 * curva: CURVA_POTENZA, CURVA_COEFFICIENTI_POTENZA
	 * 		default: ?
	 * metodo_interpolazione: INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O
	 * 		default: INTERPOLAZIONE_LINEARE_O
	 * Restituisce -1 se ci sono errori nell'esecuzione
	*/
	float *calcolo_potenza(tipo_curva curva, tipo_calcolo_output metodo_interpolazione, const char *nome_turbina, struct turbina *head, float h_mozzo, const float *array_vento, struct parametro *in);


	/*
	 *fFunzione che richiamano l'interpolazione delle curve grezze estratte dai file csv
	 * e calcola l'output di potenza a partire da esse.
	 * L'altezza del mozzo in queste funzioni serve solo ad identificare la turbina,
	 * non influisce nel calcolo dei parametri atmosferici.
	*/
	float calcolo_potenza_curve_di_potenza(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float altezza_mozzo, float vel_vento, const float *array_vento);


	/*
	 *fFunzione che richiamano l'interpolazione delle curve grezze estratte dai file csv
	 * e calcola l'output di potenza a partire da esse.
	 * L'altezza del mozzo in queste funzioni serve solo ad identificare la turbina,
	 * non influisce nel calcolo dei parametri atmosferici.
	*/
	float calcolo_potenza_curve_coefficienti(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float altezza_mozzo, float vel_vento, float densita_aria, const float *array_vento);
	

	/*
	 * Funzione interna utile per effettuare l'interpolazione delle curve in caso di valori
	 * di velocità del vento non presenti nelle curve.
	*/
	int trova_vel_vento_per_interpolazione(float *vel_min, float *vel_max, float vel_vento, int lunghezza_vettore, const float *array_vento);
	
	
	/*
	 * Funzione che effettua l'interpolazione dei valori nulli delle curve grezze estratte dai file csv
	*/
	void interpolazione_potenza_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt, const float *array_vento);
	

	/*
	 * Funzione che effettua l'interpolazione dei valori nulli delle curve grezze estratte dai file csv
	*/
	void interpolazione_coefficienti_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt, const float *array_vento);
	
#endif
