#ifndef calcolo_output_h
#define calcolo_output_h
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "estrattore_csv.h"
	#include "formule.h"
	#include "parametri.h"

	struct potenza_out{
		float potenza;
		struct potenza_out *next;
	};
	
	typedef enum {CURVA_POTENZA, CURVA_COEFFICIENTI_POTENZA} tipo_curva;

	typedef enum {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O} tipo_calcolo_output;

	struct potenza_out *aggiungi_potenza(struct potenza_out *elemento_attuale, float p);

	struct potenza_out *calcolo_potenza(tipo_curva curva, tipo_calcolo_output metodo_interpolazione, const char *nome_turbina, struct turbina *head, float h_mozzo, float *array_vento, struct parametro *in, struct potenza_out *hp);

	float calcolo_potenza_curve_di_potenza(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float altezza_mozzo, float vel_vento, float *array_vento);
	
	float calcolo_potenza_curve_coefficienti(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float altezza_mozzo, float vel_vento, float densita_aria, float *array_vento);
	
	int trova_vel_vento_per_interpolazione(float *vel_min, float *vel_max, float vel_vento, int lunghezza_vettore, float *array_vento);
	
	void interpolazione_potenza_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt, float *array_vento);
	
	void interpolazione_coefficienti_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt, float *array_vento);
	
#endif
