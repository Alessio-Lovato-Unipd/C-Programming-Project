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

	//fare ciclo for con #define RIGHE_DA_SALTARE?
	*errore=csv_read_record(&file, &fields); //salto l'intestazione del file csv
	if(*errore != CSV_OK){
		return NULL;
	}
	
	*errore=csv_read_record(&file, &fields); //salto seconda intestazione
	if(*errore != CSV_OK){
		return NULL;
	}
	//fine possibile ciclo for

	while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
        puntatore = nuovo_elemento_turbina(puntatore, fields, fields[8]);

		if(puntatore->altezza_mozzo == 0.0)
			{
				//un valore di altezza nullo quindi elimino il nodo della lista
				struct turbina *elemento_successivo = puntatore->prev;
				elimina_nodo_turbina(puntatore);
				puntatore = elemento_successivo;
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

struct turbina *nuovo_elemento_turbina(struct turbina *elemento_attuale_turbina, char** fields, char *punto_virgola)
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

    nuova->potenza_nominale = atoi(fields[5]); // conversione del dato da stringa a intero tramite funzione atoi()
	nuova->diametro_rotore = atoi(fields[6]);
	nuova->wind_speed = NULL;
	nuova->power_coefficients = NULL;
	nuova->power_curves = NULL;
	
	nuova->char_p_coefficient=malloc(sizeof(char) * (strlen(fields[16]) +1 ));
	strcpy(nuova->char_p_coefficient, fields[16]);

	nuova->char_p_curves=malloc(sizeof(char) * (strlen(fields[15]) +1 ));
	strcpy(nuova->char_p_curves, fields[15]);

	int num_caratteri=0;
	char *punto_virgola_temp = NULL;
	bool ultima_copia = true;
	char carattere=(char)*punto_virgola;
	nuova->altezza_mozzo = 0.0; //inizializzo la variabile, in questo modo se non trovo un'altezza mozzo numerica posso cancellare il nodo
	
	//estreggo i valori numerici dell'altezza
	while(((carattere < '0') || (carattere > '9')) && (carattere != 0)){	//elimino elementi non numerici prima del valore
			punto_virgola++;
			carattere=(char)*punto_virgola;
		}
	punto_virgola_temp = punto_virgola;

	carattere=(char)*punto_virgola;
	while(((carattere >= '0') && (carattere <= '9') )|| carattere == '.'){	//elimino elementi non numerici dopo del valore
		punto_virgola++;
		carattere=(char)*punto_virgola;
	}
	
	if(carattere == 0)
	{
		num_caratteri=(strlen(punto_virgola_temp));
	}else{
		num_caratteri=(strlen(punto_virgola_temp)-strlen(punto_virgola));
		ultima_copia = false;
	}


	char *temp = calloc((num_caratteri + 1), sizeof(char));

	strncpy(temp, punto_virgola_temp, num_caratteri);
	nuova->altezza_mozzo = atof(temp);

	if(ultima_copia && (punto_virgola_temp == fields[8]))
	{
		//non creo copie
		nuova->id=malloc(sizeof(char) * (strlen(fields[1]) + 1 ));
		strcpy(nuova->id, fields[1]);
	}else{	//ciclo di salvataggio dell'ID nel caso non ci fosse un elemento unico
		nuova->id=malloc(sizeof(char) * (strlen(fields[1]) + num_caratteri + 2 ));
		strcpy(nuova->id, fields[1]);
		strcat(nuova->id, "_");
		strcat(nuova->id, temp);
	}
	
	free(temp);

		if(!ultima_copia)
		{
			elemento_attuale_turbina=nuovo_elemento_turbina(elemento_attuale_turbina, fields, punto_virgola);
			if(elemento_attuale_turbina->altezza_mozzo == 0.0)
			{
				//un valore di altezza era nullo e ha reso l'id nullo, quindi elimino il nodo della lista
				struct turbina *elemento_successivo = elemento_attuale_turbina->prev;
				elimina_nodo_turbina(elemento_attuale_turbina);
				elemento_attuale_turbina = elemento_successivo;
			}
		}	
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
		elimina_nodo_turbina(head_turbina);
        head_turbina = temporaneo_turbina;

    }while(temporaneo_turbina!=NULL);
    head_turbina=NULL;
	return;
}

void elimina_nodo_turbina (struct turbina *nodo)
{
	free(nodo->nome);
	free(nodo->wind_speed);
	free(nodo->id);
	if(nodo->power_coefficients != NULL)
		free(nodo->power_coefficients);
	if(nodo->power_curves != NULL)
		free(nodo->power_curves);
	free(nodo);
}


struct turbina *cerca_dati_turbina(const char *nome_modello_turbina, float altezza_mozzo, const struct turbina *head_turbina)
{
	const struct turbina *temporaneo_turbina = head_turbina;
	bool trovato = false;

	if (altezza_mozzo == 0.0)
	{
		//viene ricercata la prima occorrenza del modello della turbina
		while((temporaneo_turbina != NULL) && (strcmp(temporaneo_turbina->nome, nome_modello_turbina)!= 0))
		{
			temporaneo_turbina = scorri_lista_turbina(temporaneo_turbina);
		}
	}else{
		//viene ricercata l'occorrenza con l'altezza del mozzo specifica
		while((temporaneo_turbina != NULL) && (!trovato))
		{
			if((strcmp(temporaneo_turbina->nome, nome_modello_turbina)== 0) && (temporaneo_turbina->altezza_mozzo == altezza_mozzo))
				trovato = true;
			if(!trovato)
				temporaneo_turbina = scorri_lista_turbina(temporaneo_turbina);
		}
	}
        
	return (struct turbina *)temporaneo_turbina;
}

struct turbina *scorri_lista_turbina(const struct turbina *puntatore)
{
	return puntatore->prev;
}

struct turbina *conversione_dati_in_booleano(struct turbina *elemento_attuale_turbina)
{
	if(strncmp(elemento_attuale_turbina->char_p_coefficient, "F", 1)==0)
	{
		elemento_attuale_turbina->bool_p_coefficient=false;
	}
	if(strncmp(elemento_attuale_turbina->char_p_coefficient, "F", 1)!=0)
	{
		elemento_attuale_turbina->bool_p_coefficient=true;
	}

	if(strncmp(elemento_attuale_turbina->char_p_curves, "F", 1)!=0)
	{
		elemento_attuale_turbina->bool_p_curves=true;
	}
	else
	{
		elemento_attuale_turbina->bool_p_curves=false;
	}
	return elemento_attuale_turbina;
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


void controllo_csv(int *errore)
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
    *errore = csv_open(file, percorso_file_power_coefficient_curves, SEPARATORE, NUMERO_COLONNE_POWER_COEFFICIENT_CURVES);
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
		for(int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT_CURVES; i++)
			temp->wind_speed[i - 1] = atof(fields[i]);
	}while((temp = scorri_lista_turbina(temp)) != NULL);
	
	temp = puntatore;
	while ((*errore = csv_read_record(file, &fields)) == CSV_OK) {
		while(temp != NULL){//faccio scorrere la lista per inserire in ogni turbina i dati delle curve
			if(strcmp(temp->nome, fields[0]) == 0){
				temp->power_coefficients = malloc(sizeof(float) * (NUMERO_COLONNE_POWER_COEFFICIENT_CURVES - 1));
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
	for(int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT_CURVES; i++){
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
	
    *errore = csv_open(file, percorso_file_power_curves, SEPARATORE, NUMERO_COLONNE_POWER_CURVES);
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
		for(int i = 1; i < NUMERO_COLONNE_POWER_CURVES; i++)
			temp->wind_speed[i - 1] = atof(fields[i]);
	}while((temp = scorri_lista_turbina(temp)) != NULL);
	
	temp = puntatore;
	while ((*errore = csv_read_record(file, &fields)) == CSV_OK) {
		while(temp != NULL){ //faccio scorrere la lista per inserire in ogni turbina i dati delle curve
			if(strcmp(temp->nome, fields[0]) == 0){
				temp->power_curves = malloc(sizeof(int) * (NUMERO_COLONNE_POWER_CURVES - 1));
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
	for(int i = 1; i < NUMERO_COLONNE_POWER_CURVES; i++){
		if (strcmp(fields[i], "")!= 0)
				array_dati[i - 1] = atoi(fields[i]); 
			else
				array_dati[i - 1] = -1;
	}
}

