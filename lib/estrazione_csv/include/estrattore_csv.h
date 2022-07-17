#ifndef CSV_EXTRACTOR_H

    #define CSV_EXTRACTOR_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "../../../external/csv/src/csv.h"

    struct turbina {
        char *nome;
        int potenza_nominale;
        struct turbina *prev;
    };

    struct weather {
        int ordine;
        float pressione;
        float temperatura1; //ad altezza=2m
        float velocita_vento1; //ad altezza=10m
        float rugosita;
        float temperatura2; //ad altezza=10m
        float velocita_vento2; //ad altezza=80m
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
    struct turbina *svuota_lista_turbine_data(struct turbina *head_turbina);

    //funzione per ricercare i dati di una turbina, se non trova un elemento ritorna valore nullo
    struct turbina *cerca_dati_turbina(char *nome_modello_turbina,  const struct turbina *head_turbina);

    struct dati_weather *estrazione_dati_weather(struct dati_weather *puntatore_head_weather,  char *const percorso_file_weather, int *errore);

    struct weather *nuovo_elemento_weather(struct weather *elemento_attuale_weather, char** fields, int count);

    struct dati_weather *svuota_dati_weather(struct dati_weather *puntatore_head_weather);

    struct weather *cerca_dati_weather(int ordine_lista, const struct weather *puntatore_head_weather);

#endif
