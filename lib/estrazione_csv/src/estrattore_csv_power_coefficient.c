#include "estrattore_csv.h"

/*****************************************************************************************************
************************    GESTIONE FILE power_coefficient_curves.csv      **************************
******************************************************************************************************/

void lettura_file_power_coefficient(struct turbina *const puntatore, const char *const percorso_file_power_coefficient_curves, int *const errore, float *const array_vento)
{
	struct csv file;
    *errore = csv_open(&file, (char *) percorso_file_power_coefficient_curves, SEPARATORE, NUMERO_COLONNE_POWER_COEFFICIENT_CURVES);
    if (*errore != CSV_OK) {
		controllo_csv(errore);
		return;
	}
	
	char **fields = NULL;
	*errore = csv_read_record(&file, &fields); //salvo le velocità del vento per avere corrispondenza con i coefficienti
	if (*errore != CSV_OK) {
		controllo_csv(errore);
		return;
	}
	for (int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT_CURVES; i++)
		array_vento[i - 1] = atof(fields[i]);
	
	struct turbina *temp = puntatore;
	while ((*errore = csv_read_record(&file, &fields)) == CSV_OK) {
		while (temp != NULL){ //faccio scorrere la lista per inserire in ogni turbina i dati delle curve
			if (strcmp(temp->nome, fields[0]) == 0) {
				temp->power_coefficients = malloc(sizeof(float) * (NUMERO_COLONNE_POWER_COEFFICIENT_CURVES - 1));
				if (temp->power_coefficients == NULL) {
					printf("Errore: malloc() ha fallito nel salvataggio_power_curves\n");
					*errore = ERRORE_MALLOC;
					break;
				}
				inserimento_power_coefficients(temp->power_coefficients, fields);
			}
			temp = scorri_lista_turbina(temp);
		}
		if (*errore == ERRORE_MALLOC)
			break;
		temp = puntatore;
    }
	
	if (*errore != CSV_END) {
		controllo_csv(errore);
		svuota_lista_turbine_data(puntatore);
	}

	csv_close(&file);
}

void inserimento_power_coefficients(float *const array_dati, char **fields)
{
	for (int i = 1; i < NUMERO_COLONNE_POWER_COEFFICIENT_CURVES; i++) {
		if (strcmp(fields[i], "")!= 0)
				array_dati[i - 1] = atof(fields[i]); 
			else
				array_dati[i - 1] = -1;
	}
}
