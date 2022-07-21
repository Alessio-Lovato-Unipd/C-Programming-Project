#ifndef CSV_EXTRACTOR_H

    #define CSV_EXTRACTOR_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "../../../external/csv/src/csv.h"
	#define NUMERO_COLONNE_TURBINA 19
	#define NUMERO_COLONNE_WEATHER 7 
    #define NUMERO_COLONNE_POWER_COEFFICIENT_CURVES 60
	#define NUMERO_COLONNE_POWER_CURVES 79 
	#define SEPARATORE ','

    struct turbina {
        char *nome;
        int id;
        int potenza_nominale;
        int diametro_rotore;
        float altezza_mozzo;
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
        struct weather *prev;
    };

    struct dati_weather {
        float h_pressione;
        float h_t1;
        float h_vel1;
        float h_rugosita;
        float h_t2;
        float h_vel2;
        struct weather *head_weather;
    };

    //funzione per estrarre i dati dal file turbine_data.csv
    /* Restituisce il puntatore alla testa della lista, il puntatore a errore serve per gestire gli errori nella lettura del file,
       fare riferimento alla libreria csv per risolvere tali errori */
    struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *percorso_file_turbine_data, int *errore);

    // creazione nuovo elemento lista turbina
    struct turbina *nuovo_elemento_turbina(struct turbina *elemento_attuale_turbina, char **fields);

    //funzione per liberare la memoria heap allocata con la lista
    void svuota_lista_turbine_data(struct turbina *head_turbina);

    //funzione per ricercare i dati di una turbina, se non trova un elemento ritorna valore nullo
    struct turbina *cerca_dati_turbina(const char *nome_modello_turbina,  const struct turbina *head_turbina);
	
	struct turbina *scorri_lista_turbina(struct turbina *puntatore);

    /* GESTIONE DATI WEATHER */

    struct dati_weather *apertura_file_weather(struct csv *file, char** fields, struct dati_weather *puntatore_head_weather,  char *const percorso_file_weather, int *errore);

    struct dati_weather *estrazione_dati_weather(struct dati_weather *puntatore_dati_weather, char *percorso_file_weather, int *errore);

    struct weather *nuovo_elemento_weather(char** fields, struct dati_weather *puntatore_dati_weather);

    struct weather *cerca_dati_weather(char *orario, const struct weather *head_weather);
	
	void svuota_dati_weather(struct dati_weather *puntatore_dati_weather);
	
	void controllo_csv(int *errore);
	
	void chiusura_file_weather(struct csv *file, struct dati_weather *puntatore_dati_weather);


    /* GESTIONE CURVE POTENZA E CURVE COEFFICIENTI DI POTENZA */

    void reading_file_power_coefficient(struct csv *file, struct turbina *const puntatore, char *percorso_file_power_coefficient_curves, int *errore);
	
	void inserimento_power_coefficients(float *array_dati, char **fields);
	
	void reading_file_power_curves(struct csv *file, struct turbina *const puntatore, char *percorso_file_power_curves, int *errore);
	
	void inserimento_power_curves(int *array_dati, char **fields);
    
#endif
