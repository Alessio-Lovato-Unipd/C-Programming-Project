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
    struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *percorso_file_turbine_data);

    // creazione nuovo elemento lista turbina
    struct turbina *nuovo_elemento(struct turbina *elemento_attuale, char **fields);

    //funzione per liberare la memoria heap allocata con la lista
    void svuota_lista_turbine_data(struct turbina *head_turbina);

#endif