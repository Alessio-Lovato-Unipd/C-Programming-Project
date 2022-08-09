#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_WEATHER_DATA_CORRETTO "../../../data/weather.csv"
#define PERCORSO_WEATHER_DATA_ERRATO "./data/weather.csv"

void verifica_svuotamento_liste(void)
{
	int errore = 0;
	struct dati_weather *puntatore = NULL;
	puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_DATA_CORRETTO, &errore);
	puntatore = svuota_dati_weather(puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct dati_weather *puntatore = NULL;
    int errore = 0;
    puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_DATA_CORRETTO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	puntatore = svuota_dati_weather(puntatore);
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct dati_weather *puntatore_errato = NULL;
    int errore = 0;
    puntatore_errato = estrazione_dati_weather(puntatore_errato, PERCORSO_WEATHER_DATA_ERRATO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
}

void verifica_ricerca_data_ora_weather(void)
{
	int errore = 0;
	struct dati_weather *puntatore = NULL;
	puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_DATA_CORRETTO, &errore);
	struct weather *elemento_cercato = cerca_dati_weather("2010-12-30 17:00:00+01:00", puntatore->head_weather);
	TEST_ASSERT_EQUAL_STRING("2010-12-30 17:00:00+01:00", elemento_cercato->orario);
	TEST_ASSERT_EQUAL_FLOAT(101240,elemento_cercato->pressione);
	TEST_ASSERT_EQUAL_FLOAT(264.41,elemento_cercato->temperatura1);
	TEST_ASSERT_EQUAL_FLOAT(2.04681,elemento_cercato->velocita_vento1);
	TEST_ASSERT_EQUAL_FLOAT(0.15,elemento_cercato->rugosita);
	TEST_ASSERT_EQUAL_FLOAT(264.38,elemento_cercato->temperatura2);
	TEST_ASSERT_EQUAL_FLOAT(4.99681,elemento_cercato->velocita_vento2);
	//secondo test
	elemento_cercato = cerca_dati_weather("2010-05-25 18:00:00+02:00", puntatore->head_weather);
	TEST_ASSERT_EQUAL_STRING("2010-05-25 18:00:00+02:00", elemento_cercato->orario);
	TEST_ASSERT_EQUAL_FLOAT(100046,elemento_cercato->pressione);
	TEST_ASSERT_EQUAL_FLOAT(284.65,elemento_cercato->temperatura1);
	TEST_ASSERT_EQUAL_FLOAT(5.37958,elemento_cercato->velocita_vento1);
	TEST_ASSERT_EQUAL_FLOAT(0.15,elemento_cercato->rugosita);
	TEST_ASSERT_EQUAL_FLOAT(284.63,elemento_cercato->temperatura2);
	TEST_ASSERT_EQUAL_FLOAT(7.97958,elemento_cercato->velocita_vento2);
	//terzo test
	elemento_cercato = cerca_dati_weather("2010-03-25 13:00:00+01:00", puntatore->head_weather);
	TEST_ASSERT_EQUAL_STRING("2010-03-25 13:00:00+01:00", elemento_cercato->orario);
	TEST_ASSERT_EQUAL_FLOAT(99748.1,elemento_cercato->pressione);
	TEST_ASSERT_EQUAL_FLOAT(289.23,elemento_cercato->temperatura1);
	TEST_ASSERT_EQUAL_FLOAT(1.73812,elemento_cercato->velocita_vento1);
	TEST_ASSERT_EQUAL_FLOAT(0.15,elemento_cercato->rugosita);
	TEST_ASSERT_EQUAL_FLOAT(289.19,elemento_cercato->temperatura2);
	TEST_ASSERT_EQUAL_FLOAT(4.46812,elemento_cercato->velocita_vento2);
	puntatore = svuota_dati_weather(puntatore);
}

void verifica_estremi_weather(void)
{
	int errore = 0;
	struct dati_weather *puntatore = NULL;
	puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_DATA_CORRETTO, &errore);
	//inizio file
	struct weather *elemento_cercato = cerca_dati_weather("2010-01-01 00:00:00+01:00", puntatore->head_weather);
	TEST_ASSERT_EQUAL_STRING("2010-01-01 00:00:00+01:00", elemento_cercato->orario);
	TEST_ASSERT_EQUAL_FLOAT(98405.7,elemento_cercato->pressione);
	TEST_ASSERT_EQUAL_FLOAT(267.6,elemento_cercato->temperatura1);
	TEST_ASSERT_EQUAL_FLOAT(5.32697,elemento_cercato->velocita_vento1);
	TEST_ASSERT_EQUAL_FLOAT(0.15,elemento_cercato->rugosita);
	TEST_ASSERT_EQUAL_FLOAT(267.57,elemento_cercato->temperatura2);
	TEST_ASSERT_EQUAL_FLOAT(7.80697,elemento_cercato->velocita_vento2);
	//fine file
	elemento_cercato = cerca_dati_weather("2010-12-31 23:00:00+01:00", puntatore->head_weather);
	TEST_ASSERT_EQUAL_STRING("2010-12-31 23:00:00+01:00", elemento_cercato->orario);
	TEST_ASSERT_EQUAL_FLOAT(100840,elemento_cercato->pressione);
	TEST_ASSERT_EQUAL_FLOAT(268.52,elemento_cercato->temperatura1);
	TEST_ASSERT_EQUAL_FLOAT(3.97125,elemento_cercato->velocita_vento1);
	TEST_ASSERT_EQUAL_FLOAT(0.15,elemento_cercato->rugosita);
	TEST_ASSERT_EQUAL_FLOAT(268.45,elemento_cercato->temperatura2);
	TEST_ASSERT_EQUAL_FLOAT(6.73125,elemento_cercato->velocita_vento2);
	puntatore = svuota_dati_weather(puntatore);
}

void stampa(void)
{
	struct dati_weather *puntatore = NULL;
    int errore = 0;
    puntatore = estrazione_dati_weather(puntatore, PERCORSO_WEATHER_DATA_CORRETTO, &errore);
    stampa_lista_weather(puntatore->head_weather);
	puntatore = svuota_dati_weather(puntatore);
}



int main (void)
{
	UNITY_BEGIN();
	
	RUN_TEST(verifica_svuotamento_liste);
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_data_ora_weather);
	RUN_TEST(verifica_estremi_weather);
	RUN_TEST(stampa);
	
	return UNITY_END();
}
