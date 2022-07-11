#ifndef CSV_EXTRACTOR_H

    #define CSV_EXTRACTOR_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "../../libcsv/src/csv.h"

    struct turbina {
        char *nome;
        int potenza_nominale;
        struct turbina *next;
    };


    //funzione per estrarre i dati dal file turbine_data.csv
    /* Se funziona correttamente ritorna 1, altrimenti restituisce errori secondo definizione della libreria csv */ 
    int estrazione_dati_turbine(struct turbina *puntatore, char *const percorso_file_turbine_data);

    // creazione nuovo elemento lista turbina
    struct turbina *nuovo_elemento(struct turbina *elemento_attuale, char **fields);

    //funzione per liberare la memoria heap allocata con la lista
    void svuota_lista_turbine_data(struct turbina *head_turbina);

    //funzione per ricercare i dati di una turbina, se non trova un elemento ritorna valore nullo
    struct turbina *cerca_dati_turbina(char *nome_modello_turbina,  struct turbina *const head_turbina);

#endif