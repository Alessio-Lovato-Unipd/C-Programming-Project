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
        float temperatura1;
        float velocità_vento1;
        float rugosità;
        float temperatura2;
        float velocità_vento2;
        struct weather *prev;
    }


    //funzione per estrarre i dati dal file turbine_data.csv
    /* Restituisce il puntatore alla testa della lista, il puntatore a errore serve per gestire gli errori nella lettura del file,
       fare riferimento alla libreria csv per risolvere tali errori */
    struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *const percorso_file_turbine_data, int *errore);

    // creazione nuovo elemento lista turbina
    struct turbina *nuovo_elemento(struct turbina *elemento_attuale, char **fields);

    //funzione per liberare la memoria heap allocata con la lista
    struct turbina *svuota_lista_turbine_data(struct turbina *head_turbina);

    //funzione per ricercare i dati di una turbina, se non trova un elemento ritorna valore nullo
    struct turbina *cerca_dati_turbina(char *nome_modello_turbina,  const struct turbina *head_turbina);

    struct weather *estrazione_dati_weather(struct weather *puntatore, char *const percorso_file_weather, int *errore);


#endif