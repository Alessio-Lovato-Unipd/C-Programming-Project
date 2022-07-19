#include "../include/estrattore_csv.h"

#define NUMERO_COLONNE_TURBINA 2
#define NUMERO_COLONNE_WEATHER 7 
#define NUMERO_COLONNE_POWER_COEFFICIENT 54 //è uguale a NUMERO_COLONNE_POWER_CURVES
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
    svuota_lista_turbine_data(puntatore);
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


struct dati_weather *apertura_file_weather(struct csv *file, struct dati_weather *puntatore_dati_weather, char *percorso_file_weather, int *errore)
{
    char** fields;

    *errore = csv_open(file, percorso_file_weather, SEPARATORE, NUMERO_COLONNE_WEATHER);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"weather.csv\" non si ");
        printf("trova nel percorso \"../../data/weather.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
    }
	if(*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}
	
    *errore = csv_read_record(file, &fields); //salto l'intestazione del file csv
	if(*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}
	
	*errore = csv_read_record(file, &fields);	//salvo la struttura con le informazioni di altezza
	if(*errore != CSV_OK){
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
	
	return puntatore_dati_weather;
}

void controllo_csv(int *errore)
{
	char *error;
    csv_error_string(*errore, &error);
    printf("ERROR: %s\n", error);
}

void chiusura_file_weather(struct csv *file, struct dati_weather *altezze)
{
	csv_close(file);
	free(altezze);
}

   

/*****************************************************************************************************
************************    GESTIONE FILE power_coefficient_curves.csv      **************************************
******************************************************************************************************/

struct turbina *estrazione_dati_power_coefficient(struct turbina *puntatore, char *percorso_file_power_coefficient_curves, int *errore)
{
    struct csv file;
	char** fields;
    char* error;

    *errore = csv_open(&file, percorso_file_power_coefficient_curves, SEPARATORE, NUMERO_COLONNE_POWER_COEFFICIENT);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"power_coefficient_curves.csv\" non si ");
        printf("trova nel percorso \"../../data/power_coefficient_curves.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
        return(NULL);
    }
	csv_read_record(&file, &fields); //salto l'intestazione del file csv

	while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
        
            puntatore = salvataggio_coefficienti(puntatore, fields);
        
    }

    if (*errore == CSV_END) {
		csv_close(&file);
		return puntatore;
	}

    csv_error_string(*errore, &error);
	printf("ERROR: %s\n", error);
	csv_close(&file);
    svuota_lista_turbine_data(puntatore);
	return NULL;

}

struct turbina *salvataggio_coefficienti(struct turbina *elemento_attuale_turbina, char** fields)
{
    struct turbina *nuova;
    int i=0;
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
    for(i=1; i<NUMERO_COLONNE_POWER_COEFFICIENT; i++)
        if (strcmp(fields[i], "")!= 0)
        {
            nuova->power_coefficients[i] = atof(fields[i]); 
        }
        else
        {
            nuova->power_coefficients[i] = -1;
        };
    
    //salvo posizione elemento precedente
    nuova->prev = elemento_attuale_turbina;
    return nuova;
   
}

/*****************************************************************************************************
************************    GESTIONE FILE power_curves.csv      **************************************
******************************************************************************************************/

struct turbina *estrazione_dati_power_curves(struct turbina *puntatore, char *percorso_file_power_curves, int *errore)
{
    struct csv file;
	char** fields;
    char* error;

    *errore = csv_open(&file, percorso_file_power_curves, SEPARATORE, NUMERO_COLONNE_POWER_COEFFICIENT);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"power_curves.csv\" non si ");
        printf("trova nel percorso \"../../data/power_curves.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
        return(NULL);
    }
	csv_read_record(&file, &fields); //salto l'intestazione del file csv

	while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
        
            puntatore = salvataggio_potenze(puntatore, fields);
        
    }

    if (*errore == CSV_END) {
		csv_close(&file);
		return puntatore;
	}

    csv_error_string(*errore, &error);
	printf("ERROR: %s\n", error);
	csv_close(&file);
    svuota_lista_turbine_data(puntatore);
	return NULL;

}

struct turbina *salvataggio_potenze(struct turbina *elemento_attuale_turbina, char** fields)
{
    struct turbina *nuova;
    int i=0;
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
    for(i=1; i<NUMERO_COLONNE_POWER_COEFFICIENT; i++)
        if (strcmp(fields[i], "")!= 0)
        {
            nuova->power_curves[i] = atoi(fields[i]); 
        }
        else
        {
            nuova->power_curves[i] = -1;
        }; 
    
    //salvo posizione elemento precedente
    nuova->prev = elemento_attuale_turbina;
    return nuova;
   
}
