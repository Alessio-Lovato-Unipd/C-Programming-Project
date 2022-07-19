#ifndef CSV_EXTRACTOR_H

    #define CSV_EXTRACTOR_H
    #define N 54
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "../../../external/csv/src/csv.h"

    struct turbina {
        char *nome;
        int potenza_nominale;
        float power_coefficients[N];
        int power_curves[N];
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
    struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *const percorso_file_turbine_data, int *errore);

    // creazione nuovo elemento lista turbina
    struct turbina *nuovo_elemento_turbina(struct turbina *elemento_attuale_turbina, char **fields);

    //funzione per liberare la memoria heap allocata con la lista
    void svuota_lista_turbine_data(struct turbina *head_turbina);

    //funzione per ricercare i dati di una turbina, se non trova un elemento ritorna valore nullo
    struct turbina *cerca_dati_turbina(char *nome_modello_turbina,  const struct turbina *head_turbina);

    /* GESTIONE DATI WEATHER */

    struct dati_weather *apertura_file_weather(struct csv *file, char** fields, struct dati_weather *puntatore_head_weather,  char *const percorso_file_weather, int *errore);

    struct dati_weather *estrazione_dati_weather(struct dati_weather *puntatore_dati_weather, char *percorso_file_weather, int *errore);

    struct weather *nuovo_elemento_weather(char** fields, struct dati_weather *puntatore_dati_weather);

    struct weather *cerca_dati_weather(char *orario, const struct weather *head_weather);

    void svuota_dati_weather(struct dati_weather *puntatore_dati_weather);
	
	void controllo_csv(int *errore);

	void chiusura_file_weather(struct csv *file, struct dati_weather *puntatore_head_weather);

    /* GESTIONE CURVE POTENZA E CURVE COEFFICIENTI DI POTENZA */

    struct turbina *estrazione_dati_power_coefficient(struct turbina *puntatore, char *percorso_file_power_coefficient_curves, int *errore);

    struct turbina *salvataggio_coefficienti(struct turbina *elemento_attuale_turbina, char** fields);

    struct turbina *estrazione_dati_power_curves(struct turbina *puntatore, char *percorso_file_power_curves, int *errore);

    struct turbina *salvataggio_potenze(struct turbina *elemento_attuale_turbina, char** fields);
    
#endif
