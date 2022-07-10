#include "../include/estrattore_csv.h"


/*****************************************************************************************************
************************    GESTIONE FILE TURBINE_DATA.CSV      **************************************
******************************************************************************************************/


struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *percorso_file_turbine_data)
{
    struct csv file;
	char** fields;
    char* error;
	int ret;

    csv_open(&file, percorso_file_turbine_data, ',', 2);
	csv_read_record(&file, &fields); //salto l'intestazione del file csv

	while ((ret = csv_read_record(&file, &fields)) == CSV_OK) {
        if (cerca_dati_turbina(fields[0],puntatore)==NULL) // verifico che non esista un elemento con lo stesso identificativo "turbine_type"
        {
            puntatore = nuovo_elemento(puntatore, fields);
        }
    }

    if (ret == CSV_END) {
		csv_close(&file);
		return puntatore;
	}

    csv_error_string(ret, &error);
	printf("ERROR: %s\n", error);
	csv_close(&file);
	return NULL;

}

struct turbina *nuovo_elemento(struct turbina *elemento_attuale, char** fields)
{
    struct turbina *nuova;
    nuova = malloc(sizeof(struct turbina));

    //verifico riuscita allocazione
    if (nuova == NULL)
    {
        printf("Error: malloc() failed in nuovo_elemento\n");
        exit(EXIT_FAILURE);
    }

    //salvataggio dati
    nuova->nome = (fields[0]);
    nuova->potenza_nominale = atoi(fields[1]); // conversione del dato da stringa a intero tramite funzione atoi()
    
    //salvo posizione elemento precedente
    nuova->next = elemento_attuale;
    return nuova;
   
}

//funzione per liberare la memoria heap allocata con la lista
void svuota_lista_turbine_data(struct turbina *head_turbina)
{
    struct turbina *temporaneo;

    do
    {
        temporaneo = head_turbina->next;
        free(head_turbina);
        head_turbina = temporaneo;

    }while(temporaneo!=NULL);
}

//funzione per ricercare i dati di una turbina, se non trova un elemento ritorna valore nullo
struct turbina *cerca_dati_turbina(char *nome_modello_turbina, struct turbina *const head_turbina)
    {
        struct turbina *temporaneo;
        temporaneo = head_turbina;
        
        while((temporaneo != NULL) && (strcmp(temporaneo->nome, nome_modello_turbina)!= 0))
        {
            temporaneo = temporaneo->next;
        }

        return temporaneo;
    }