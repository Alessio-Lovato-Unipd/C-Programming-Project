#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO "./data/power_coefficient_curves.csv"


void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct turbina *puntatore = NULL;
    int errore = 0;
    puntatore = estrazione_dati_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	svuota_lista_turbine_data(puntatore);
	
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct turbina *puntatore_errato = NULL;
    int errore = 0;
    puntatore_errato = estrazione_dati_power_coefficient(puntatore_errato, PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	svuota_lista_turbine_data(puntatore_errato);
}

void verifica_ricerca_nome_turbina(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("DUMMY 1", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 1", elemento_cercato->nome);
	svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_nome_turbina_falso(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("DUMMY 5", puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, elemento_cercato);
	svuota_lista_turbine_data(puntatore);
}

void verifica_due_valori_intermedi(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("DUMMY 1", puntatore);
    TEST_ASSERT_EQUAL_INT(0.470000, elemento_cercato->power_coefficients[17]);
    TEST_ASSERT_EQUAL_INT(0.140000, elemento_cercato->power_coefficients[35]);
	svuota_lista_turbine_data(puntatore);
}

void verifica_funzione_svuotamento_lista(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	svuota_lista_turbine_data(puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

int main()
{
    UNITY_BEGIN();
	
    RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
    RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_nome_turbina);
	RUN_TEST(verifica_ricerca_nome_turbina_falso);
    RUN_TEST(verifica_due_valori_intermedi);
	RUN_TEST(verifica_funzione_svuotamento_lista);
    return UNITY_END();
}