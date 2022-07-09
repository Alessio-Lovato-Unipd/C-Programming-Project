#ifndef CSV_EXTRACTOR_H

    #define CSV_EXTRACTOR_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "../../libcsv/src/csv.h"

    struct turbina {
        char *nome;
        float potenza_nominale;
        struct turbina *next;
    };

    //funzione per estrarre i dati dal file turbine_data.csv
    struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *percorso_file_turbine_data);

    // creazione nuovo elemento lista turbina
    struct turbina *nuovo_elemento(struct turbina *elemento_attuale, char **fields);

#endif