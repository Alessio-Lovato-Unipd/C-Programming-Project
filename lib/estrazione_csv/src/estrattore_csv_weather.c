#include "../include/estrattore_csv.h"


/*****************************************************************************************************
************************    STAMPA ERRORI FILE CSV    **************************************
******************************************************************************************************/


void controllo_csv(int *errore)
{
	char *error;
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nI file necessari:\n");
        printf("\tturbine_data.csv\n\tweather.csv\n\tpower_curves.csv\n\tpower_coefficient_curves.csv\n\n");
        printf("non si trovano nella cartella \"../../data/\" rispetto a dove è stato lanciato l'eseguibile\n\n");
    } else {
        csv_error_string(*errore, &error);
        printf("ERROR: %s\n", error);
    }
    return;
}

/*****************************************************************************************************
************************    GESTIONE FILE weather.csv      **************************************
******************************************************************************************************/


struct dati_weather *apertura_file_weather(struct csv *file, char** fields, struct dati_weather *puntatore_dati_weather, char *percorso_file_weather, int *errore)
{

    *errore = csv_open(file, percorso_file_weather, SEPARATORE, NUMERO_COLONNE_WEATHER);
    if (*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}
	
    *errore = csv_read_record(file, &fields); //salto l'intestazione del file csv
	if (*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}
	
	*errore = csv_read_record(file, &fields);	//salvo la struttura con le informazioni di altezza
	if (*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}

	puntatore_dati_weather = malloc(sizeof(struct dati_weather));
	//verifico riuscita allocazione
    if (puntatore_dati_weather == NULL)
    {
        printf("Error: malloc() failed in estrazione_dati_weather\n");
        exit(EXIT_FAILURE);
    }
	puntatore_dati_weather->h_pressione = atof(fields[1]);
	puntatore_dati_weather->h_t1 = atof(fields[2]);
	puntatore_dati_weather->h_vel1 = atof(fields[3]);
	puntatore_dati_weather->h_rugosita = atof(fields[4]);
	puntatore_dati_weather->h_t2 = atof(fields[5]);
	puntatore_dati_weather->h_vel2 = atof(fields[6]);
    puntatore_dati_weather->head_weather=NULL;
	
	return puntatore_dati_weather;
}


struct dati_weather *estrazione_dati_weather(struct dati_weather *puntatore_dati_weather, char *percorso_file_weather, int *errore)
{
    struct csv file;
    char** fields=NULL;

    puntatore_dati_weather=apertura_file_weather(&file, fields, puntatore_dati_weather, percorso_file_weather, errore);

    if (puntatore_dati_weather == NULL)
        return NULL;
	
    while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
        if (cerca_dati_weather(fields[0], puntatore_dati_weather->head_weather) == NULL) // verifico che non esista un elemento con stesso identificativo
        {
            puntatore_dati_weather->head_weather = nuovo_elemento_weather(fields, puntatore_dati_weather);
        }
   }

    csv_close(&file);

    if (*errore != CSV_END){
        controllo_csv(errore);
        svuota_dati_weather(puntatore_dati_weather);
        return NULL;
    }else{
        return puntatore_dati_weather;
    }

}


struct weather *nuovo_elemento_weather(char** fields, struct dati_weather *puntatore_dati_weather)
{
    struct weather *nuova;
    nuova = malloc(sizeof(struct weather));

    //verifico riuscita allocazione
    if (nuova == NULL)
    {
        printf("Error: malloc() failed in nuovo_elemento\n");
        exit(EXIT_FAILURE);
    }

    //salvataggio dati
    nuova->orario=malloc(sizeof(char) * (strlen(fields[0]) +1 ));

    strcpy(nuova->orario, fields[0]);
    nuova->pressione = atof(fields[1]); // conversione del dato da stringa a float tramite funzione atof()
    nuova->temperatura1 = atof(fields[2]);
    nuova->velocita_vento1 = atof(fields[3]);
    nuova->rugosita = atof(fields[4]);
    nuova->temperatura2 = atof(fields[5]);
    nuova->velocita_vento2 = atof(fields[6]);
    
    //salvo posizione elemento precedente
    nuova->prev = puntatore_dati_weather->head_weather;
    return nuova;
}


struct dati_weather *svuota_dati_weather(struct dati_weather *puntatore_dati_weather)
{
    if(puntatore_dati_weather == NULL){
		return NULL;
	}
    struct weather *temporaneo_weather = puntatore_dati_weather->head_weather;
		
	do{
        temporaneo_weather = puntatore_dati_weather->head_weather->prev;
        free(puntatore_dati_weather->head_weather->orario);
        free(puntatore_dati_weather->head_weather);
        puntatore_dati_weather->head_weather = temporaneo_weather;

    }while(temporaneo_weather!=NULL);
    free(puntatore_dati_weather);
    puntatore_dati_weather = NULL;
    
	return puntatore_dati_weather;
}



struct weather *cerca_dati_weather(char *orario, const struct weather *head_weather)
{
	const struct weather *temporaneo_weather = head_weather;
        
	while((temporaneo_weather != NULL) && (strcmp(temporaneo_weather->orario, orario)!=0))
	{
		temporaneo_weather = temporaneo_weather->prev;
	}

	return (struct weather *)temporaneo_weather;
}

