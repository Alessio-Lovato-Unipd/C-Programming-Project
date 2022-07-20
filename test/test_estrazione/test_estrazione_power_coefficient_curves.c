#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO "./data/power_coefficient_curves.csv"


void verifica_presenza_file_csv_percorso_corretto(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct csv file;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	svuota_lista_turbine_data(puntatore);
}

/*void verifica_presenza_file_csv_percorso_errato(void)
{
    struct turbina *puntatore_errato = NULL;
    int errore = 0;
   
	svuota_lista_turbine_data(puntatore_errato);
}

void verifica_ricerca_nome_turbina(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	
	svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_nome_turbina_falso(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	
	svuota_lista_turbine_data(puntatore);
}

void verifica_due_valori_intermedi(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	
	svuota_lista_turbine_data(puntatore);
}

void verifica_funzione_svuotamento_lista(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
}*/

int main()
{
    UNITY_BEGIN();
	
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	
    return UNITY_END();
}