#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_WEATHER_DATA_CORRETTO "../../../data/weather.csv"
#define PERCORSO_WEATHER_DATA_ERRATO "./data/weather.csv"
#define PERCORSO_WEATHER_PROVA1 "../../../test/test_estrazione/files/prova_weather1.csv"
#define PERCORSO_WEATHER_PROVA2 "../../../test/test_estrazione/files/prova_weather2.csv"



void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct dati_weather *puntatore = NULL;
    struct csv file;
	int errore;
	puntatore = apertura_file_weather(&file, puntatore, PERCORSO_WEATHER_PROVA1, &errore);
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

void verifica_salvataggio_corretto_dati(void)
{
	struct dati_weather *puntatore = NULL;
    struct csv file;
	int errore;
	puntatore = apertura_file_weather(&file, puntatore, PERCORSO_WEATHER_PROVA1, &errore);
	TEST_ASSERT_EQUAL_INT(0, puntatore->h_pressione);
	TEST_ASSERT_EQUAL_INT(2, puntatore->h_t1);
	TEST_ASSERT_EQUAL_INT(10, puntatore->h_vel1);
	TEST_ASSERT_EQUAL_INT(0, puntatore->h_rugosita);
	TEST_ASSERT_EQUAL_INT(10, puntatore->h_t2);
	TEST_ASSERT_EQUAL_INT(80, puntatore->h_vel2);
	chiusura_file_weather(&file, puntatore);
}

void verifica_file_con_troppe_colonne(void)
{
	struct dati_weather *puntatore = NULL;
    struct csv file;
	int errore;
	puntatore = apertura_file_weather(&file, puntatore, PERCORSO_WEATHER_PROVA2, &errore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
	chiusura_file_weather(&file, puntatore);
}


int main (void)
{
	UNITY_BEGIN();
	
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_salvataggio_corretto_dati);
	RUN_TEST(verifica_file_con_troppe_colonne);
	
	return UNITY_END();
}