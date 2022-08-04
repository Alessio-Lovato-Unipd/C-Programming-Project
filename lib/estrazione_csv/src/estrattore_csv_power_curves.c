#include "../include/estrattore_csv.h"

/*****************************************************************************************************
************************    GESTIONE FILE power_curves.csv      **************************************
******************************************************************************************************/

void lettura_file_power_curves(struct turbina *const puntatore, char *percorso_file_power_curves, int *errore, float *array_vento)
{
	struct turbina *temp = puntatore;
	struct csv file;
	
    *errore = csv_open(&file, percorso_file_power_curves, SEPARATORE, NUMERO_COLONNE_POWER_CURVES);
    if (*errore != CSV_OK){
		controllo_csv(errore);
		return;
	}
	char **fields;
	
	*errore=csv_read_record(&file, &fields); //salvo le velocità del vento per avere corrispondenza con i coefficienti
	if (*errore != CSV_OK){
		controllo_csv(errore);
		return;
	}
	for(int i = 1; i < NUMERO_COLONNE_POWER_CURVES; i++){
		array_vento[i - 1] = atof(fields[i]);
	}
	
	temp = puntatore;
	while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
		while(temp != NULL){ //faccio scorrere la lista per inserire in ogni turbina i dati delle curve
			if(strcmp(temp->nome, fields[0]) == 0){
				temp->power_curves = malloc(sizeof(float) * (NUMERO_COLONNE_POWER_CURVES - 1));
				if (temp->power_curves == NULL){
					printf("Error: malloc() failed in salvataggio_power_curves\n");
					svuota_lista_turbine_data(puntatore);
					exit(EXIT_FAILURE);
				}
				inserimento_power_curves(temp->power_curves, fields);
			}
			temp = scorri_lista_turbina(temp);
		}
		temp = puntatore;
    }
	
	if (*errore != CSV_END){
		controllo_csv(errore);
		svuota_lista_turbine_data(puntatore);
	}

	csv_close(&file);

}

void inserimento_power_curves(float *array_dati, char **fields)
{
	for(int i = 1; i < NUMERO_COLONNE_POWER_CURVES; i++){
		if (strcmp(fields[i], "")!= 0)
				array_dati[i - 1] = atoi(fields[i]); 
			else
				array_dati[i - 1] = -1;
	}
}

