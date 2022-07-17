#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_WEATHER_DATA_CORRETTO "../../../data/weather.csv"
#define PERCORSO_WEATHER_DATA_ERRATO "./data/weather.csv"
#define PERCORSO_WEATHER_PROVA "../../../data/prova_weather.csv"


void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct weather *puntatore = NULL;
	struct altezze *valori_alt = NULL;
    int errore = 0;
    puntatore = estrazione_dati_weather(puntatore, valori_alt, PERCORSO_WEATHER_PROVA, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	svuota_lista_weather(puntatore, valori_alt);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct weather *puntatore_errato = NULL;
	struct altezze *valori_alt = NULL;
    int errore = 0;
    puntatore_errato = estrazione_dati_weather(puntatore_errato, valori_alt, PERCORSO_WEATHER_DATA_ERRATO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	svuota_lista_weather(puntatore_errato, valori_alt);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore_errato);
}

void verifica_ricerca_data_ora_weather(void)
{
	int errore = 0;
	struct weather *puntatore = NULL;
	struct altezze *valori_alt = NULL;
	puntatore = estrazione_dati_weather(puntatore, valori_alt, PERCORSO_WEATHER_PROVA, &errore);
	struct weather *elemento_cercato = cerca_dati_weather(2, puntatore);
	TEST_ASSERT_EQUAL_INT(2, elemento_cercato->ordine);
	svuota_lista_weather(puntatore, valori_alt);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

int main (void)
{
	UNITY_BEGIN();
	
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	/*RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_data_ora_weather);*/
	
	return UNITY_END();
}