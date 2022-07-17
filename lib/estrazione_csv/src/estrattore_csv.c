#include "../include/estrattore_csv.h"

#define NUMERO_COLONNE_TURBINA 2
#define NUMERO_COLONNE_WEATHER 7 //da rivedere
#define SEPARATORE ','

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
        if (cerca_dati_turbina(fields[0],puntatore)==NULL) // verifico che non esista un elemento con lo stesso identificativo "turbine_type"
        {
            puntatore = nuovo_elemento_turbina(puntatore, fields);
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

struct turbina *nuovo_elemento_turbina(struct turbina *elemento_attuale_turbina, char** fields)
{
    struct turbina *nuova;
    nuova = malloc(sizeof(struct turbina));

    //verifico riuscita allocazione
    if (nuova == NULL)
    {
        printf("Error: malloc() failed in nuovo_elemento\n");
        svuota_lista_turbine_data(elemento_attuale_turbina);
        exit(EXIT_FAILURE);
    }

    //salvataggio dati
    nuova->nome = (fields[0]);
    nuova->potenza_nominale = atoi(fields[1]); // conversione del dato da stringa a intero tramite funzione atoi()
    
    //salvo posizione elemento precedente
    nuova->prev = elemento_attuale_turbina;
    return nuova;
   
}


struct turbina *svuota_lista_turbine_data(struct turbina *head_turbina)
{
    struct turbina *temporaneo_turbina = head_turbina;
	
	if(head_turbina == NULL){
		return head_turbina;
	}
	
    do
    {
        temporaneo_turbina = head_turbina->prev;
        free(head_turbina);
        head_turbina = temporaneo_turbina;

    }while(temporaneo_turbina!=NULL);
	return head_turbina;
}


struct turbina *cerca_dati_turbina(char *nome_modello_turbina, const struct turbina *head_turbina)
{
	const struct turbina *temporaneo_turbina = head_turbina;
        
	while((temporaneo_turbina != NULL) && (strcmp(temporaneo_turbina->nome, nome_modello_turbina)!= 0))
	{
		temporaneo_turbina = temporaneo_turbina->prev;
	}

	return (struct turbina *)temporaneo_turbina;
}


/*****************************************************************************************************
************************    GESTIONE FILE weather.csv      **************************************
******************************************************************************************************/


struct weather *estrazione_dati_weather(struct weather *puntatore, struct altezze *valori_altezze, char *percorso_file_weather, int *errore)
{
    struct csv file;
    char** fields;
    char* error;
	int count = 1;

    *errore = csv_open(&file, percorso_file_weather, SEPARATORE, NUMERO_COLONNE_WEATHER);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"weather.csv\" non si ");
        printf("trova nel percorso \"../../data/weather.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
        return(NULL);
    }
    csv_read_record(&file, &fields); //salto l'intestazione del file csv

	csv_read_record(&file, &fields);	//salvo la struttura con le informazioni di altezza
	valori_altezze = malloc(sizeof(struct weather));
	//verifico riuscita allocazione
    if (valori_altezze == NULL)
    {
        printf("Error: malloc() failed in estrazione_dati_weather\n");
        exit(EXIT_FAILURE);
    }
	valori_altezze->h_pressione = atoi(fields[1]);
	valori_altezze->h_t1 = atoi(fields[2]);
	valori_altezze->h_vel1 = atoi(fields[3]);
	valori_altezze->h_rugosita = atoi(fields[4]);
	valori_altezze->h_t2 = atoi(fields[5]);
	valori_altezze->h_vel2 = atoi(fields[6]);
	
    while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
        if (cerca_dati_weather(count, puntatore) == NULL) // verifico che non esista un elemento con stessa data e ora
        {
            puntatore = nuovo_elemento_weather(puntatore, fields, count);
			count++;
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

struct weather *nuovo_elemento_weather(struct weather *elemento_attuale_weather, char** fields, int count)
{
    struct weather *nuova;
    nuova = malloc(sizeof(struct weather));

    //verifico riuscita allocazione
    if (nuova == NULL)
    {
        printf("Error: malloc() failed in nuovo_elemento\n");
        //******************serve svuotare la lista??********************** 
        exit(EXIT_FAILURE);
    }

    //salvataggio dati
    nuova->ordine = count;
    nuova->pressione = atof(fields[1]); // conversione del dato da stringa a float tramite funzione atof()
    nuova->temperatura1 = atof(fields[2]);
    nuova->velocita_vento1 = atof(fields[3]);
    nuova->rugosita = atof(fields[4]);
    nuova->temperatura2 = atof(fields[5]);
    nuova->velocita_vento2 = atof(fields[6]);
    
    //salvo posizione elemento precedente
    nuova->prev = elemento_attuale_weather;
    return nuova;
   
}

struct weather *svuota_lista_weather(struct weather *head_weather, struct altezze *valori_altezze)
{
    struct weather *temporaneo_weather = head_weather;
	
	free(valori_altezze);
	
	if(head_weather == NULL){
		return head_weather;
	}
	
    do
    {
        temporaneo_weather = head_weather->prev;
        free(head_weather);
        head_weather = temporaneo_weather;

    }while(temporaneo_weather!=NULL);
	return head_weather;
}

struct weather *cerca_dati_weather(int ordine_lista, const struct weather *head_weather)
{
	const struct weather *temporaneo_weather = head_weather;
        
	while((temporaneo_weather != NULL) && (temporaneo_weather->ordine != ordine_lista))
	{
		temporaneo_weather = temporaneo_weather->prev;
	}

	return (struct weather *)temporaneo_weather;
}
