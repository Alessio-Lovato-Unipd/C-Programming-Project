#include "../include/estrattore_csv.h"

#define NUMERO_COLONNE_TURBINA 2
#define NUMERO_COLONNE_WEATHER 7 //da rivedere
#define SEPARATORE ','
#define CHIAVE_DATABASE fields[0]
#define POTENZA_NOMINALE fields[1]

/*****************************************************************************************************
************************    GESTIONE FILE turbine_data.csv      **************************************
******************************************************************************************************/


struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *percorso_file_turbine_data, int *errore)
{
    struct csv file;
	char** fields;
    char* error;

    *errore = csv_open(&file, percorso_file_turbine_data, SEPARATORE, NUMERO_COLONNE_TURBINA);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"turbine_data.csv\" non si ");
        printf("trova nel percorso \"../../data/turbine_data.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
        return(NULL);
    }
	csv_read_record(&file, &fields); //salto l'intestazione del file csv

	while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
        if (cerca_dati_turbina(CHIAVE_DATABASE,puntatore)==NULL) // verifico che non esista un elemento con lo stesso identificativo "turbine_type"
        {
            puntatore = nuovo_elemento(puntatore, fields);
        }
    }

    if (*errore == CSV_END) {
		csv_close(&file);
		return puntatore;
	}

    csv_error_string(*errore, &error);
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
        svuota_lista_turbine_data(elemento_attuale);
        exit(EXIT_FAILURE);
    }

    //salvataggio dati
    nuova->nome = (CHIAVE_DATABASE);
    nuova->potenza_nominale = atoi(POTENZA_NOMINALE); // conversione del dato da stringa a intero tramite funzione atoi()
    
    //salvo posizione elemento precedente
    nuova->prev = elemento_attuale;
    return nuova;
   
}


struct turbina *svuota_lista_turbine_data(struct turbina *head_turbina)
{
    struct turbina *temporaneo = head_turbina;
	
	if(head_turbina == NULL){
		return head_turbina;
	}
	
    do
    {
        temporaneo = head_turbina->prev;
        free(head_turbina);
        head_turbina = temporaneo;

    }while(temporaneo!=NULL);
	return head_turbina;
}


struct turbina *cerca_dati_turbina(char *nome_modello_turbina, const struct turbina *head_turbina)
{
	const struct turbina *temporaneo = head_turbina;
        
	while((temporaneo != NULL) && (strcmp(temporaneo->nome, nome_modello_turbina)!= 0))
	{
		temporaneo = temporaneo->prev;
	}

	return (struct turbina *)temporaneo;
}


/*****************************************************************************************************
************************    GESTIONE FILE weather.csv      **************************************
******************************************************************************************************/


struct weather *estrazione_dati_weather(struct weather *puntatore, char *percorso_file_weather, int *errore)
{
    struct csv file;
    char** fields;
    char* error;

    *errore = csv_open(&file, percorso_file_weather, SEPARATORE, NUMERO_COLONNE_WEATHER);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"weather.csv\" non si ");
        printf("trova nel percorso \"../../data/weather.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
        return(NULL);
    }
    csv_read_record(&file, &fields); //salto l'intestazione del file csv

    while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
        if (cerca_dati_weather(CHIAVE_DATABASE,puntatore)==NULL) // verifico che non esista un elemento con lo stesso identificativo "turbine_type"
        {
            puntatore = nuovo_elemento(puntatore, fields);
        }
    }

    if (*errore == CSV_END) {
        csv_close(&file);
        return puntatore;
    }

    csv_error_string(*errore, &error);
    printf("ERROR: %s\n", error);
    csv_close(&file);
    return NULL;

}
