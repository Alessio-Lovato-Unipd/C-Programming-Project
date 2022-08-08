#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_TURBINE_DATA_ERRATO "./data/turbine_data.csv"


void verifica_presenza_file_csv_percorso_corretto(void)
{
    struct turbina *puntatore = NULL;
    int errore = 0;
    puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	puntatore = svuota_lista_turbine_data(puntatore);
	
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct turbina *puntatore_errato = NULL;
    int errore = 0;
    puntatore_errato = estrazione_dati_turbine(puntatore_errato, PERCORSO_TURBINE_DATA_ERRATO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	puntatore_errato = svuota_lista_turbine_data(puntatore_errato);
}


void verifica_funzione_cerca_elemento(void)
{
	int errore = 0, numero_occorrenze = 0;
	struct turbina *puntatore = NULL, *elemento_cercato = NULL;

	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	elemento_cercato = puntatore;
	while(elemento_cercato != NULL){
		if (strcmp(elemento_cercato->nome, "SWT120/3600") == 0)
			numero_occorrenze++;
		elemento_cercato = scorri_lista_turbina(elemento_cercato);
	}
	TEST_ASSERT_EQUAL_INT(1,numero_occorrenze);

	//RICERCA TREMITE ALTEZZA_MOZZO CASO UNICO
	elemento_cercato = cerca_dati_turbina("ENO100/2200", 99.0, puntatore);
	TEST_ASSERT_EQUAL_STRING("ENO100/2200", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("128", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(99.0, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(100, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2200000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	//RICERCA_PRIMA OCCORRENZA CASO UNICO
	elemento_cercato = cerca_dati_turbina("ENO100/2200", 0.0, puntatore);
	TEST_ASSERT_EQUAL_STRING("ENO100/2200", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("128", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(99.0, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(100, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2200000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	//RICERCA TREMITE ALTEZZA_MOZZO CASO COPIE
	elemento_cercato = cerca_dati_turbina("GE103/2750", 0.0, puntatore);
	TEST_ASSERT_EQUAL_STRING("GE103/2750", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("117_75", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(75.0, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(103, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2750000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	//RICERCA_PRIMA OCCORRENZA CASO COPIE
	elemento_cercato = cerca_dati_turbina("GE103/2750", 98.3, puntatore);
	TEST_ASSERT_EQUAL_STRING("GE103/2750", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("117_98.3", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(98.3, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(103, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2750000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_altezza_mozzo_unica(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("ENO100/2200", 99, puntatore);
	TEST_ASSERT_EQUAL_STRING("ENO100/2200", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("128", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(99, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(100, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2200000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_altezza_mozzo_multipla(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("GE103/2750", 75, puntatore);

	//PRIMO ELEMENTO
	TEST_ASSERT_EQUAL_STRING("GE103/2750", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("117_75", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(75, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(103, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2750000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO
	elemento_cercato = cerca_dati_turbina("GE103/2750", 85, puntatore);
	TEST_ASSERT_EQUAL_STRING("GE103/2750", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("117_85", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(85, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(103, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2750000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	//TERZO ELEMENTO
	elemento_cercato = cerca_dati_turbina("GE103/2750", 98.3, puntatore);
	TEST_ASSERT_EQUAL_STRING("GE103/2750", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("117_98.3", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(98.3, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(103, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2750000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	//QUARTO ELEMENTO
	elemento_cercato = cerca_dati_turbina("GE103/2750", 123.5, puntatore);
	TEST_ASSERT_EQUAL_STRING("GE103/2750", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("117_123.5", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(123.5, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(103, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2750000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);
	
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_altezza_mozzo_multipla_senza_spazi(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("VS109/2500", 95, puntatore);
	
	//PRIMO ELEMENTO
	TEST_ASSERT_EQUAL_STRING("VS109/2500", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("104_95", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(95, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(109, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2500000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO
	elemento_cercato = cerca_dati_turbina("VS109/2500", 145.0, puntatore);
	TEST_ASSERT_EQUAL_STRING("VS109/2500", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("104_145", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(145.0, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(109, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2500000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_spazio_prima_della_seconda_altezza_mozzo(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("V116/2100", 84, puntatore);
	
	//PRIMO ELEMENTO
	TEST_ASSERT_EQUAL_STRING("V116/2100", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("39_84", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(84, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(116, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2100000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO
	elemento_cercato = cerca_dati_turbina("V116/2100", 94, puntatore);
	TEST_ASSERT_EQUAL_STRING("V116/2100", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("39_94", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(94, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(116, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2100000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);
	
	puntatore = svuota_lista_turbine_data(puntatore);
}


void verifica_turbina_virgolette_altezza_mozzo(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("MM92/2050", 68.5, puntatore);
	
	//PRIMO ELEMENTO
	TEST_ASSERT_EQUAL_STRING("MM92/2050", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("97_68.5", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(68.5, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(93, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2050000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO
	elemento_cercato = cerca_dati_turbina("MM92/2050", 80, puntatore);
	TEST_ASSERT_EQUAL_STRING("MM92/2050", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("97_80.0", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(80, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(93, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2050000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//TERZO ELEMENTO
	elemento_cercato = cerca_dati_turbina("MM92/2050", 100, puntatore);
	TEST_ASSERT_EQUAL_STRING("MM92/2050", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("97_100.0", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(100, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(93, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(2050000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_seconda_altezza_mozzo_nulla(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("SWT120/3600", 90, puntatore);

	//PRIMO ELEMENTO
	TEST_ASSERT_EQUAL_STRING("SWT120/3600", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("61_90", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(90, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(120, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(3600000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO (inesistente)
	int numero_occorrenze = 0;
	elemento_cercato = puntatore;
	while(elemento_cercato != NULL){
		if (strcmp(elemento_cercato->nome, "SWT120/3600")==0)
			numero_occorrenze++;
		elemento_cercato = scorri_lista_turbina(elemento_cercato);
	}
	TEST_ASSERT_EQUAL_INT(1,numero_occorrenze);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_altezza_mozzo_nulla(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("V112/3000", 0, puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, elemento_cercato);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_altezza_mozzo_testuale(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("GE150/6000",100, puntatore);

	//PRIMO ELEMENTO
	TEST_ASSERT_EQUAL_STRING("GE150/6000", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("110_100", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(100, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(151, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(6000000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO (inesistente)
	int numero_occorrenze = 0;
	elemento_cercato = puntatore;
	while(elemento_cercato != NULL){
		if (strcmp(elemento_cercato->nome, "GE150/6000") == 0)
			numero_occorrenze++;
		elemento_cercato = scorri_lista_turbina(elemento_cercato);
	}
	TEST_ASSERT_EQUAL_INT(1,numero_occorrenze);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_turbina_altezza_mozzo_con_separatore_non_punto_virgola(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("SWT62/1300", 68, puntatore);
	
	//PRIMO ELEMENTO
	TEST_ASSERT_EQUAL_STRING("SWT62/1300", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("78_68", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(68, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(62, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(1300000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO
	elemento_cercato = cerca_dati_turbina("SWT62/1300", 90, puntatore);
	TEST_ASSERT_EQUAL_STRING("SWT62/1300", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("78_90", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(90, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(62, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(1300000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_turbina_estremi(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("AD116/5000", 90, puntatore);

	//PRIMO ELEMENTO INIZIO LISTA
	TEST_ASSERT_EQUAL_STRING("AD116/5000", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("82_90", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(90, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(116, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(5000000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO INIZIO LISTA
	elemento_cercato = cerca_dati_turbina("AD116/5000", 102, puntatore);
	TEST_ASSERT_EQUAL_STRING("AD116/5000", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("82_102", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(102, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(116, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(5000000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//PRIMO ELEMENTO FINE LISTA
	elemento_cercato = cerca_dati_turbina("VS87/1500", 85, puntatore);
	TEST_ASSERT_EQUAL_STRING("VS87/1500", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("106_85", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(85, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(87, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(1500000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);

	//SECONDO ELEMENTO FINE LISTA
	elemento_cercato = cerca_dati_turbina("VS87/1500", 100, puntatore);
	TEST_ASSERT_EQUAL_STRING("VS87/1500", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("106_100", elemento_cercato->id);
	TEST_ASSERT_EQUAL_FLOAT(100, elemento_cercato->altezza_mozzo);
	TEST_ASSERT_EQUAL_FLOAT(87, elemento_cercato->diametro_rotore);
	TEST_ASSERT_EQUAL_INT(1500000, elemento_cercato->potenza_nominale);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);
	
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_turbina_falso(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	struct turbina *elemento_cercato = cerca_dati_turbina("DUMMY", 0, puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, elemento_cercato);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_funzione_svuotamento_lista(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	puntatore = svuota_lista_turbine_data(puntatore);
	TEST_ASSERT_EQUAL_PTR(NULL, puntatore);
}

void verifica_funzione_conversione_bool_FF(void) //nel caso di char False-False
{
	int errore = 0;
	struct turbina *puntatore = NULL, *elemento_cercato = NULL;

	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	elemento_cercato = puntatore;

	elemento_cercato = cerca_dati_turbina("AW100/3000", 100, puntatore);
	TEST_ASSERT_EQUAL_STRING("AW100/3000", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("29_100", elemento_cercato->id); //perché considero la prima altezza del mozzo
	TEST_ASSERT_EQUAL_STRING("False", elemento_cercato->char_p_coefficient);
	TEST_ASSERT_EQUAL_STRING("False", elemento_cercato->char_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_curves);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_funzione_conversione_bool_TT(void) //nel caso di char True-True
{
	int errore = 0;
	struct turbina *puntatore = NULL, *elemento_cercato = NULL;

	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	elemento_cercato = puntatore;

	elemento_cercato = cerca_dati_turbina("V126/3300", 117, puntatore);
	elemento_cercato = conversione_dati_in_booleano(elemento_cercato);
	TEST_ASSERT_EQUAL_STRING("V126/3300", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("43_117", elemento_cercato->id); //perché considero la prima altezza del mozzo
	TEST_ASSERT_EQUAL_STRING("True", elemento_cercato->char_p_coefficient);
	TEST_ASSERT_EQUAL_STRING("True", elemento_cercato->char_p_curves);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_coefficient);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	puntatore = svuota_lista_turbine_data(puntatore);
}

void verifica_funzione_conversione_bool_FT(void) //nel caso di char False-True
{
	int errore = 0;
	struct turbina *puntatore = NULL, *elemento_cercato = NULL;

	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	elemento_cercato = puntatore;

	elemento_cercato = cerca_dati_turbina("S152/6330", 121, puntatore);
	elemento_cercato = conversione_dati_in_booleano(elemento_cercato);
	TEST_ASSERT_EQUAL_STRING("S152/6330", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_STRING("84_121", elemento_cercato->id);
	TEST_ASSERT_EQUAL_STRING("False", elemento_cercato->char_p_coefficient);
	TEST_ASSERT_EQUAL_STRING("True", elemento_cercato->char_p_curves);
	TEST_ASSERT_FALSE(elemento_cercato->bool_p_coefficient);
	TEST_ASSERT_TRUE(elemento_cercato->bool_p_curves);
	puntatore = svuota_lista_turbine_data(puntatore);
}

//non ho trovato nessuna turbina per il caso TF

int main()
{
    UNITY_BEGIN();
	
    RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
   /* RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_funzione_svuotamento_lista);
	RUN_TEST(verifica_funzione_conversione_bool_FF);
	RUN_TEST(verifica_funzione_conversione_bool_TT);
	RUN_TEST(verifica_funzione_conversione_bool_FT);
	RUN_TEST(verifica_funzione_cerca_elemento);
	RUN_TEST(verifica_turbina_altezza_mozzo_unica);
	RUN_TEST(verifica_turbina_altezza_mozzo_multipla);
	RUN_TEST(verifica_turbina_altezza_mozzo_multipla_senza_spazi);
	RUN_TEST(verifica_turbina_spazio_prima_della_seconda_altezza_mozzo);
	RUN_TEST(verifica_turbina_virgolette_altezza_mozzo);
	RUN_TEST(verifica_turbina_seconda_altezza_mozzo_nulla);
	RUN_TEST(verifica_turbina_altezza_mozzo_nulla);
	RUN_TEST(verifica_turbina_altezza_mozzo_testuale);
	RUN_TEST(verifica_turbina_altezza_mozzo_con_separatore_non_punto_virgola);
	RUN_TEST(verifica_ricerca_turbina_estremi);
	RUN_TEST(verifica_ricerca_turbina_falso);
	*/
    return UNITY_END();
}
