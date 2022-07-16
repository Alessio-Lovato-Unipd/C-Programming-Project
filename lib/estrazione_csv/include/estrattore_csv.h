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
        char *nome;
        float pressione;
        float temperatura1; //ad altezza=2m
        float velocita_vento1; //ad altezza=10m
        float rugosita;
        float temperatura2; //ad altezza=10m
        float velocita_vento2; //ad altezza=80m
        struct weather *prev;
    };

    struct altezze {
        float h_pressione;
        float h_t1;
        float h_vel1;
        float h_rugosita;
        float h_t2;
        float h_vel2;
    }

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

    struct weather *estrazione_dati_weather(struct weather *puntatore, char *const percorso_file_weather, int *errore);

    struct weather *nuovo_elemento_weather(struct weather *elemento_attuale_weather, char** fields);

    struct weather *svuota_lista_weather(struct weather *head_weather);

    struct weather *cerca_dati_weather(char *giorno_orario_weather, const struct weather *head_weather);


#endif
