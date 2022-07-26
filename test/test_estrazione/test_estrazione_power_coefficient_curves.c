#include "unity.h"
#include "estrattore_csv.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO "./data/power_coefficient_curves.csv"
#define PERCORSO_POWER_CURVES_CORRETTO "../../../data/power_curves.csv"


void verifica_presenza_file_csv_percorso_corretto(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	reading_file_power_curves(&file_potenza, puntatore, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	svuota_lista_turbine_data(puntatore);
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct turbina *puntatore = NULL;
    int errore = 0;
	struct csv file_coefficienti;
	struct csv file_potenza;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	reading_file_power_curves(&file_potenza, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO, &errore);
	TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_nome_turbina_e_alcuni_coefficienti(void)
{/*
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct turbina *elemento_cercato = NULL;
	struct csv file;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	elemento_cercato = cerca_dati_turbina("DUMMY 1", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 1", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_FLOAT(0.13, elemento_cercato->power_coefficients[8]);
	TEST_ASSERT_EQUAL_FLOAT(0, elemento_cercato->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(-1, elemento_cercato->power_coefficients[1]);
	TEST_ASSERT_EQUAL_FLOAT(0, elemento_cercato->power_coefficients[NUMERO_COLONNE_POWER_COEFFICIENT - 2]); //l'ultimo elemento dell'array si trova in posizione 52
	svuota_lista_turbine_data(puntatore);*/
}

void verifica_ricerca_nome_turbina_vero_ma_no_curva_coefficienti(void)
{
	/*int errore = 0;
	struct turbina *puntatore = NULL;
	struct turbina *elemento_cercato = NULL;
	struct csv file;
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file, puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	elemento_cercato = cerca_dati_turbina("DUMMY 4", puntatore);
	TEST_ASSERT_EQUAL_STRING("DUMMY 4", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_PTR(NULL, elemento_cercato->power_coefficients);
	svuota_lista_turbine_data(puntatore);*/
}

void verifica_valori_su_curve_diverse(void)
{
	/*int errore = 0;
	struct turbina *head = NULL;
	struct turbina *cerca_coefficienti = NULL;
	struct turbina *cerca_curva_potenza = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	cerca_coefficienti = cerca_dati_turbina("DUMMY 2", head);
	cerca_curva_potenza = cerca_dati_turbina("DUMMY 3", head);
	TEST_ASSERT_EQUAL_STRING("DUMMY 2", cerca_coefficienti->nome);
	TEST_ASSERT_EQUAL_STRING("DUMMY 3", cerca_curva_potenza->nome);
	TEST_ASSERT_EQUAL_FLOAT(0, cerca_coefficienti->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.41, cerca_coefficienti->power_coefficients[11]);
	TEST_ASSERT_EQUAL_FLOAT(0, cerca_coefficienti->power_coefficients[NUMERO_COLONNE_POWER_COEFFICIENT_CURVES - 2]);
	TEST_ASSERT_EQUAL_INT(0, cerca_curva_potenza->power_curves[0]);
	TEST_ASSERT_EQUAL_INT(34000, cerca_curva_potenza->power_curves[8]);
	TEST_ASSERT_EQUAL_INT(-1, cerca_curva_potenza->power_curves[NUMERO_COLONNE_POWER_COEFFICIENT - 2]);
	svuota_lista_turbine_data(head);*/
}

void verifica_lettura_vel_vento(void)
{
	int errore = 0;
	struct turbina *head = NULL;
	struct turbina *temp = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	temp = head;
	while(temp != NULL){
		TEST_ASSERT_EQUAL_FLOAT(0, temp->wind_speed[0]);
		TEST_ASSERT_EQUAL_FLOAT(0.5, temp->wind_speed[1]);
		TEST_ASSERT_EQUAL_FLOAT(26, temp->wind_speed[NUMERO_COLONNE_POWER_COEFFICIENT_CURVES - 2]);
		temp = scorri_lista_turbina(temp);
	}
	svuota_lista_turbine_data(head);
}

int main()
{
    UNITY_BEGIN();
	
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_nome_turbina_e_alcuni_coefficienti);
	RUN_TEST(verifica_ricerca_nome_turbina_vero_ma_no_curva_coefficienti);
	RUN_TEST(verifica_valori_su_curve_diverse);
	RUN_TEST(verifica_lettura_vel_vento);
	
    return UNITY_END();
}
