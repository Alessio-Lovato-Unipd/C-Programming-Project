#include "external/Unity/src/unity.h"
#include "../lib/lettore_csv/libestrazione_csv/include/estrattore_csv.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../../data/turbine_data.csv"
#define PERCORSO_TURBINE_DATA_ERRATO "./data/turbine_data.csv"


void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct turbina *puntatore = NULL;
    int errore = 0;
    puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_END, errore);
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct turbina *puntatore_errato = NULL;
    int errore = 0;
    puntatore_errato = estrazione_dati_turbine(puntatore_errato, PERCORSO_TURBINE_DATA_ERRATO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
}

void verifica_ricerca_nome_turbina(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("DUMMY 2", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 2", elemento_cercato->nome);
}

void verifica_ricerca_nome_turbina_estremi(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("DUMMY 1", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 1", elemento_cercato->nome);
	elemento_cercato = cerca_dati_turbina("DUMMY 4", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 4", elemento_cercato->nome);
}

void verifica_ricerca_nome_turbina_falso(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("DUMMY 5", puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, elemento_cercato);
}

void verifica_funzione_svuotamento_lista(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	svuota_lista_turbine_data(puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

int main()
{
    UNITY_BEGIN();
	
    RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
    RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_nome_turbina);
	RUN_TEST(verifica_ricerca_nome_turbina_estremi);
	RUN_TEST(verifica_ricerca_nome_turbina_falso);
	RUN_TEST(verifica_funzione_svuotamento_lista);
    return UNITY_END();
}