#ifndef CSV_EXTRACTOR_H

    #define CSV_EXTRACTOR_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "../../../external/csv/src/csv.h"
	#define NUMERO_COLONNE_TURBINA 2
	#define NUMERO_COLONNE_WEATHER 7 
	#define NUMERO_COLONNE_POWER_COEFFICIENT 54 //è uguale a NUMERO_COLONNE_POWER_CURVES
	#define SEPARATORE ','

    struct turbina {
        char *nome;
        int potenza_nominale;
		float *wind_speed;
        float *power_coefficients;
        int *power_curves;
        struct turbina *prev;
    };

    struct weather {
        char *orario;
        float pressione;
        float temperatura1; //ad altezza = 2m
        float velocita_vento1; //ad altezza = 10m
        float rugosita;
        float temperatura2; //ad altezza = 10m
        float velocita_vento2; //ad altezza = 80m
    };

    struct dati_weather {
        float h_pressione;
        float h_t1;
        float h_vel1;
        float h_rugosita;
        float h_t2;
        float h_vel2;
    };

    //funzione per estrarre i dati dal file turbine_data.csv
    /* Restituisce il puntatore alla testa della lista, il puntatore a errore serve per gestire gli errori nella lettura del file,
       fare riferimento alla libreria csv per risolvere tali errori */
    struct turbina *estrazione_dati_turbine(struct csv *file_coefficient, struct csv *file_power, struct turbina *puntatore, char *percorso_file_turbine_data, int *errore);

    // creazione nuovo elemento lista turbina
    struct turbina *nuovo_elemento_turbina(struct turbina *elemento_attuale_turbina, char **fields);

    //funzione per liberare la memoria heap allocata con la lista
    struct turbina *svuota_lista_turbine_data(struct turbina *head_turbina);

    //funzione per ricercare i dati di una turbina, se non trova un elemento ritorna valore nullo
    struct turbina *cerca_dati_turbina(char *nome_modello_turbina,  const struct turbina *head_turbina);

    struct dati_weather *apertura_file_weather(struct csv *file, struct dati_weather *puntatore_head_weather,  char *const percorso_file_weather, int *errore);
	
	void controllo_csv(int *errore);

	void chiusura_file_weather(struct csv *file, struct dati_weather *altezze);

    /*struct weather *cerca_dati_weather(char *orario, const struct weather *puntatore_head_weather);*/

    void apertura_file_power_coefficient(struct csv *file, char *percorso_file_power_coefficient_curves, int *errore);
	
	int salvataggio_power_coefficient(struct csv *file, struct turbina *puntatore, int *errore);
	
	void inserimento_power_coefficients(float *array_dati, char **fields);
	
	void apertura_file_power_curves(struct csv *file, char *percorso_file_power_curves, int *errore);
	
	int salvataggio_power_curves(struct csv *file, struct turbina *puntatore, int *errore);
	
	void inserimento_power_curves(int *array_dati, char **fields);
    
#endif
