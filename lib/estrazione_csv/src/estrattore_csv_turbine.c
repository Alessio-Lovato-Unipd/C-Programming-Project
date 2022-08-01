#include "../include/estrattore_csv.h"

/*****************************************************************************************************
************************    GESTIONE FILE turbine_data.csv      **************************************
******************************************************************************************************/

struct turbina *estrazione_dati_turbine(struct turbina *puntatore, char *percorso_file_turbine_data, int *errore) 
{
    struct csv file;
	char** fields;

    *errore = csv_open(&file, percorso_file_turbine_data, SEPARATORE, NUMERO_COLONNE_TURBINA);
    if (*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}

	*errore=csv_read_record(&file, &fields); //salto l'intestazione del file csv
    if (*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}
	
	*errore=csv_read_record(&file, &fields); //salto seconda intestazione
    if (*errore != CSV_OK){
		controllo_csv(errore);
		return NULL;
	}
        

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

	csv_close(&file);

	if (*errore != CSV_END){
		controllo_csv(errore);
		svuota_lista_turbine_data(puntatore);
		return NULL;
	} else {
		return puntatore;
	} 

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

	//allocazione memoria wind_speed in base alla presenza delle curve
	conversione_dati_in_booleano(nuova);
	if(nuova->bool_p_curves)
		nuova->wind_speed = malloc(sizeof(float) * (LUNGHEZZA_VETTORE_POWER_CURVES + 1));
	if(nuova->bool_p_coefficient && !(nuova->bool_p_curves))
		nuova->wind_speed = malloc(sizeof(float) * (LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1));
	
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
	if(nodo->wind_speed != NULL)
		free(nodo->wind_speed);
	free(nodo->id);
	if(nodo->power_coefficients != NULL)
		free(nodo->power_coefficients);
	if(nodo->power_curves != NULL)
		free(nodo->power_curves);
	free(nodo->char_p_coefficient);
	free(nodo->char_p_curves);
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

	if(strncmp(elemento_attuale_turbina->char_p_curves, "F", 1)==0)
	{
		elemento_attuale_turbina->bool_p_curves=false;
	}
	if(strncmp(elemento_attuale_turbina->char_p_curves, "F", 1)!=0)
	{
		elemento_attuale_turbina->bool_p_curves=true;
	}

	return elemento_attuale_turbina;
}