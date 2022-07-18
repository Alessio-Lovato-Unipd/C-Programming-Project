#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_WEATHER_DATA_CORRETTO "../../../data/weather.csv"
#define PERCORSO_WEATHER_DATA_ERRATO "./data/weather.csv"
#define PERCORSO_WEATHER_PROVA "../../../data/prova_weather.csv"

void verifica_svuotamento_liste(void)
{
	int errore = 0;
	struct dati_weather *puntatore = NULL;
	puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_PROVA, &errore);
	puntatore = svuota_dati_weather(puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct dati_weather *puntatore = NULL;
    int errore = 0;
    puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_PROVA, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	puntatore = svuota_dati_weather(puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct dati_weather *puntatore_errato = NULL;
    int errore = 0;
    puntatore_errato = estrazione_dati_weather(puntatore_errato, PERCORSO_WEATHER_DATA_ERRATO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore_errato);
}

void verifica_ricerca_data_ora_weather(void)
{
	int errore = 0;
	struct dati_weather *puntatore = NULL;
	puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_PROVA, &errore);
	struct weather *elemento_cercato = cerca_dati_weather("2010-01-01 09:00:00+01:00", puntatore->head_weather);
	TEST_ASSERT_EQUAL_STRING("2010-01-01 09:00:00+01:00", elemento_cercato->orario);
	TEST_ASSERT_EQUAL_INT(0,puntatore->h_pressione);
	puntatore = svuota_dati_weather(puntatore);
}


int main (void)
{
	UNITY_BEGIN();
	
	RUN_TEST(verifica_svuotamento_liste);
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_data_ora_weather);
	
	return UNITY_END();
}