#include "../include/estrattore_csv.h"



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
    nuova->nome=malloc(sizeof(char) * (strlen(fields[0]) +1 ));
    strcpy(nuova->nome, fields[0]);
    nuova->potenza_nominale = atoi(fields[1]); // conversione del dato da stringa a intero tramite funzione atoi()
	nuova->wind_speed = malloc(sizeof(float) * (NUMERO_COLONNE_POWER_COEFFICIENT - 1));
	if(nuova->wind_speed == NULL){
		printf("Malloc error\n");
		exit(EXIT_FAILURE);
	}
	nuova->power_coefficients = NULL;
	nuova->power_curves = NULL;
	
    //salvo posizione elemento precedente
    nuova->prev = elemento_attuale_turbina;
    return nuova;
   
}


void svuota_lista_turbine_data(struct turbina *head_turbina)
{
    struct turbina *temporaneo_turbina = head_turbina;
	
	if(head_turbina == NULL){
		return;
	}
	
    do
    {
        temporaneo_turbina = head_turbina->prev;
        free(head_turbina->nome);
		free(head_turbina->wind_speed);
		if(head_turbina->power_coefficients != NULL)
			free(head_turbina->power_coefficients);
		if(head_turbina->power_curves != NULL)
			free(head_turbina->power_curves);
        free(head_turbina);
        head_turbina = temporaneo_turbina;

    }while(temporaneo_turbina!=NULL);
    head_turbina=NULL;
	return;
}


struct turbina *cerca_dati_turbina(const char *nome_modello_turbina, const struct turbina *head_turbina)
{
	const struct turbina *temporaneo_turbina = head_turbina;
        
	while((temporaneo_turbina != NULL) && (strcmp(temporaneo_turbina->nome, nome_modello_turbina)!= 0))
	{
		temporaneo_turbina = temporaneo_turbina->prev;
	}

	return (struct turbina *)temporaneo_turbina;
}

struct turbina *scorri_lista_turbina(struct turbina *puntatore)
{
	return puntatore->prev;
}


/*****************************************************************************************************
************************    GESTIONE FILE weather.csv      **************************************
******************************************************************************************************/


struct dati_weather *apertura_file_weather(struct csv *file, char** fields, struct dati_weather *puntatore_dati_weather, char *percorso_file_weather, int *errore)
{

    *errore = csv_open(file, percorso_file_weather, SEPARATORE, NUMERO_COLONNE_WEATHER);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"weather.csv\" non si ");
        printf("trova nel percorso \"../../data/weather.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
    }
	if(*errore != CSV_OK){
		return NULL;
	}
	
    *errore = csv_read_record(file, &fields); //salto l'intestazione del file csv
	if(*errore != CSV_OK){
		return NULL;
	}
	
	*errore = csv_read_record(file, &fields);	//salvo la struttura con le informazioni di altezza
	if(*errore != CSV_OK){
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


struct weather *nuovo_elemento_weather(struct weather *elemento_attuale_weather, char** fields, int count)


struct dati_weather *estrazione_dati_weather(struct dati_weather *puntatore_dati_weather, char *percorso_file_weather, int *errore)
{
    struct csv file;
    char** fields=NULL;

    puntatore_dati_weather=apertura_file_weather(&file, fields, puntatore_dati_weather, percorso_file_weather, errore);
	
    if (*errore ==  CSV_OK)
    {
        while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
            if (cerca_dati_weather(fields[0], puntatore_dati_weather->head_weather) == NULL) // verifico che non esista un elemento con stesso identificativo
            {
                puntatore_dati_weather->head_weather = nuovo_elemento_weather(fields, puntatore_dati_weather);
            }
        }

        if (*errore == CSV_END) {
            csv_close(&file);
            return puntatore_dati_weather;
        }
    }

    controllo_csv(errore);
    svuota_dati_weather(puntatore_dati_weather);
    return NULL;

}


struct weather *nuovo_elemento_weather(char** fields, struct dati_weather *puntatore_dati_weather)
{
    struct weather *nuova;
    nuova = malloc(sizeof(struct weather));

    //verifico riuscita allocazione
    if (nuova == NULL)
    {
        printf("Error: malloc() failed in nuovo_elemento\n");
        svuota_dati_weather(puntatore_dati_weather);
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


void svuota_dati_weather(struct dati_weather *puntatore_dati_weather)
{
    if(puntatore_dati_weather == NULL){
		return;
	}
    struct weather *temporaneo_weather = puntatore_dati_weather->head_weather;
		
	do{
        temporaneo_weather = puntatore_dati_weather->head_weather->prev;
        free(puntatore_dati_weather->head_weather->orario);
        free(puntatore_dati_weather->head_weather);
        puntatore_dati_weather->head_weather = temporaneo_weather;

    }while(temporaneo_weather!=NULL);
    free(puntatore_dati_weather);
	return;
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



>>>>>>> e2fd97b5e4ccafac58d9f7c27cbea5e5bb060d2b
void controllo_csv(int *errore)
>>>>>>> main
{
	char *error;
    csv_error_string(*errore, &error);
    printf("ERROR: %s\n", error);
}



void chiusura_file_weather(struct csv *file, struct dati_weather *puntatore_dati_weather)
{
	csv_close(file);
    svuota_dati_weather(puntatore_dati_weather);
}

   

   

/*****************************************************************************************************
************************    GESTIONE FILE power_coefficient_curves.csv      **************************************
******************************************************************************************************/

void reading_file_power_coefficient(struct csv *file, struct turbina *const puntatore, char *percorso_file_power_coefficient_curves, int *errore)
{
	char *error;
	struct turbina *temp = puntatore;
    *errore = csv_open(file, percorso_file_power_coefficient_curves, SEPARATORE, NUMERO_COLONNE_POWER_COEFFICIENT);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"power_coefficient_curves.csv\" non si ");
        printf("trova nel percorso \"../../data/power_coefficient_curves.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
		csv_error_string(*errore, &error);
		printf("ERROR: %s\n", error);
		return;
	}
	
	char **fields = NULL;
	
	csv_read_record(file, &fields); //salvo le velocità del vento per avere corrispondenza con i coefficienti
	do{
		for(int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT; i++)
			temp->wind_speed[i - 1] = atof(fields[i]);
	}while((temp = scorri_lista_turbina(temp)) != NULL);
	
	temp = puntatore;
	while ((*errore = csv_read_record(file, &fields)) == CSV_OK) {
		while(temp != NULL){//faccio scorrere la lista per inserire in ogni turbina i dati delle curve
			if(strcmp(temp->nome, fields[0]) == 0){
				temp->power_coefficients = malloc(sizeof(float) * (NUMERO_COLONNE_POWER_COEFFICIENT - 1));
				if (temp->power_coefficients == NULL){
					printf("Error: malloc() failed in salvataggio_power_coefficient\n");
					exit(EXIT_FAILURE);
				}
				inserimento_power_coefficients(temp->power_coefficients, fields);
			}
			temp = scorri_lista_turbina(temp);
		}
		temp = puntatore;
	}
	
    if (*errore == CSV_END) {
		csv_close(file);
	}else{
		csv_error_string(*errore, &error);
		printf("ERROR: %s\n", error);
		csv_close(file);
		svuota_lista_turbine_data(puntatore);
	}
}

void inserimento_power_coefficients(float *array_dati, char **fields)
{
	for(int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT; i++){
		if (strcmp(fields[i], "")!= 0)
				array_dati[i - 1] = atof(fields[i]); 
			else
				array_dati[i - 1] = -1;
	}
}


/*****************************************************************************************************
************************    GESTIONE FILE power_curves.csv      **************************************
******************************************************************************************************/

void reading_file_power_curves(struct csv *file, struct turbina *const puntatore, char *percorso_file_power_curves, int *errore)
{
    char* error;
	struct turbina *temp = puntatore;
	
    *errore = csv_open(file, percorso_file_power_curves, SEPARATORE, NUMERO_COLONNE_POWER_COEFFICIENT);
    if (*errore == CSV_E_IO)
    {
        printf("\n ATTENZIONE!\nLa cartella contenente il file \"power_coefficient_curves.csv\" non si ");
        printf("trova nel percorso \"../../data/power_curves.csv\" rispetto a dove è stato lanciato l'eseguibile\n\n");
		csv_error_string(*errore, &error);
		printf("ERROR: %s\n", error);
		return;
    }
	
	char **fields = NULL;
	
	csv_read_record(file, &fields); //salvo le velocità del vento per avere corrispondenza con i coefficienti
	do{
		for(int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT; i++)
			temp->wind_speed[i - 1] = atof(fields[i]);
	}while((temp = scorri_lista_turbina(temp)) != NULL);
	
	temp = puntatore;
	while ((*errore = csv_read_record(file, &fields)) == CSV_OK) {
		while(temp != NULL){ //faccio scorrere la lista per inserire in ogni turbina i dati delle curve
			if(strcmp(temp->nome, fields[0]) == 0){
				temp->power_curves = malloc(sizeof(int) * (NUMERO_COLONNE_POWER_COEFFICIENT - 1));
				if (temp->power_curves == NULL){
					printf("Error: malloc() failed in salvataggio_power_curves\n");
					exit(EXIT_FAILURE);
				}
				inserimento_power_curves(temp->power_curves, fields);
			}
			temp = scorri_lista_turbina(temp);
		}
		temp = puntatore;
    }

    if (*errore == CSV_END) {
		csv_close(file);
	}else{
		csv_error_string(*errore, &error);
		printf("ERROR: %s\n", error);
		csv_close(file);
		svuota_lista_turbine_data(puntatore);
	}
}

void inserimento_power_curves(int *array_dati, char **fields)
{
	for(int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT; i++){
		if (strcmp(fields[i], "")!= 0)
				array_dati[i - 1] = atoi(fields[i]); 
			else
				array_dati[i - 1] = -1;
	}
}

