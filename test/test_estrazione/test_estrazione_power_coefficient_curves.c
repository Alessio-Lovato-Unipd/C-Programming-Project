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

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct turbina *puntatore = NULL;
    int errore = 0;
	struct csv file;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_nome_turbina_e_alcuni_valori(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct csv file;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	puntatore = cerca_dati_turbina("DUMMY 1", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 1", puntatore->nome);
	TEST_ASSERT_EQUAL_FLOAT(0.13, puntatore->power_coefficients[8]);
	TEST_ASSERT_EQUAL_FLOAT(0, puntatore->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(-1, puntatore->power_coefficients[1]);
	TEST_ASSERT_EQUAL_FLOAT(0, puntatore->power_coefficients[NUMERO_COLONNE_POWER_COEFFICIENT - 1]);
	svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_nome_turbina_vero_ma_no_curva(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct csv file;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	puntatore = cerca_dati_turbina("DUMMY 4", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 4", puntatore->nome);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore->power_coefficients);
	svuota_lista_turbine_data(puntatore);
}
/*
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
	RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_nome_turbina_e_alcuni_valori);
	RUN_TEST(verifica_ricerca_nome_turbina_vero_ma_no_curva);
	
    return UNITY_END();
}