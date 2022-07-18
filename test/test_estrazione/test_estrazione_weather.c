#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_WEATHER_DATA_CORRETTO "../../../data/weather.csv"
#define PERCORSO_WEATHER_DATA_ERRATO "./data/weather.csv"
#define PERCORSO_WEATHER_PROVA "../../../data/prova_weather.csv"


void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct dati_weather *puntatore = NULL;
    struct csv file;
	int errore;
	puntatore = apertura_file_weather(&file, puntatore, PERCORSO_WEATHER_PROVA, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_OK, errore);
	chiusura_file_weather(&file, puntatore);
}

void verifica_presenza_file_csv_percorso_errato(void)
{
	struct dati_weather *puntatore = NULL;
    struct csv file;
	int errore;
	puntatore = apertura_file_weather(&file, puntatore, PERCORSO_WEATHER_DATA_ERRATO, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}



int main (void)
{
	UNITY_BEGIN();
	
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	
	return UNITY_END();
}
