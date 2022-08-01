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
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	lettura_file_power_curves(puntatore, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	TEST_ASSERT_EQUAL_INT(CSV_END, errore);
	svuota_lista_turbine_data(puntatore);
}

void verifica_presenza_file_csv_percorso_errato(void)
{
    struct turbina *puntatore = NULL;
    int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO, &errore, array_vento_coeff);
	TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	lettura_file_power_curves(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_ERRATO, &errore, array_vento_curves);
	TEST_ASSERT_EQUAL_INT(CSV_E_IO, errore);
	svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_nome_turbina_e_alcuni_coefficienti(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct turbina *elemento_cercato = NULL;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	//float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	elemento_cercato = cerca_dati_turbina("E-70/2300", 85, puntatore);
	TEST_ASSERT_EQUAL_STRING("E-70/2300", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_FLOAT(0.36, elemento_cercato->power_coefficients[8]);
	TEST_ASSERT_EQUAL_FLOAT(-1, elemento_cercato->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(-1, elemento_cercato->power_coefficients[1]);
	TEST_ASSERT_EQUAL_FLOAT(0.06, elemento_cercato->power_coefficients[LUNGHEZZA_VETTORE_POWER_COEFFICIENT - 1]);
	svuota_lista_turbine_data(puntatore);
}

void verifica_ricerca_nome_turbina_vero_ma_no_curva_coefficienti(void)
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct turbina *elemento_cercato = NULL;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	//float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	elemento_cercato = cerca_dati_turbina("AW100/3000", 0.0, puntatore);
	TEST_ASSERT_EQUAL_STRING("AW100/3000", elemento_cercato->nome);
	TEST_ASSERT_EQUAL_PTR(NULL, elemento_cercato->power_coefficients);
	svuota_lista_turbine_data(puntatore);
}

void verifica_valori_su_curve_diverse(void)
{
	/*int errore = 0;
	struct turbina *head = NULL;
	struct turbina *cerca_coefficienti = NULL;
	struct turbina *cerca_curva_potenza = NULL;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1];
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1];
	struct csv file_coefficienti;
	struct csv file_potenza;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	lettura_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	cerca_coefficienti = cerca_dati_turbina("DUMMY 2", head);
	cerca_curva_potenza = cerca_dati_turbina("DUMMY 3", head);
	TEST_ASSERT_EQUAL_STRING("DUMMY 2", cerca_coefficienti->nome);
	TEST_ASSERT_EQUAL_STRING("DUMMY 3", cerca_curva_potenza->nome);
	TEST_ASSERT_EQUAL_FLOAT(0, cerca_coefficienti->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.41, cerca_coefficienti->power_coefficients[11]);
	TEST_ASSERT_EQUAL_FLOAT(0, cerca_coefficienti->power_coefficients[NUMERO_COLONNE_POWER_COEFFICIENT - 2]);
	TEST_ASSERT_EQUAL_INT(0, cerca_curva_potenza->power_curves[0]);
	TEST_ASSERT_EQUAL_INT(34000, cerca_curva_potenza->power_curves[8]);
	TEST_ASSERT_EQUAL_INT(-1, cerca_curva_potenza->power_curves[NUMERO_COLONNE_POWER_COEFFICIENT - 2]);
	svuota_lista_turbine_data(head);*/
}

void verifica_lettura_vel_vento(void)
{
	int errore = 0;
	struct turbina *head = NULL;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient( head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(0, array_vento_coeff[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.5, array_vento_coeff[1]);
	TEST_ASSERT_EQUAL_FLOAT(15, array_vento_coeff[37]);
	TEST_ASSERT_EQUAL_FLOAT(25, array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT - 1]);
	TEST_ASSERT_EQUAL_FLOAT(26, array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT]);
	TEST_ASSERT_EQUAL_FLOAT(0, array_vento_curves[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.5, array_vento_curves[1]);
	TEST_ASSERT_EQUAL_FLOAT(15, array_vento_curves[37]);
	TEST_ASSERT_EQUAL_FLOAT(25.5, array_vento_curves[58]);
	TEST_ASSERT_EQUAL_FLOAT(26, array_vento_curves[59]);
	TEST_ASSERT_EQUAL_FLOAT(34.5, array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES - 1]);
	TEST_ASSERT_EQUAL_FLOAT(35, array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES]);
	
	svuota_lista_turbine_data(head);
}

int main()
{
    UNITY_BEGIN();
	
	RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
	RUN_TEST(verifica_presenza_file_csv_percorso_errato);
	RUN_TEST(verifica_ricerca_nome_turbina_e_alcuni_coefficienti);
	RUN_TEST(verifica_ricerca_nome_turbina_vero_ma_no_curva_coefficienti);
	//RUN_TEST(verifica_valori_su_curve_diverse);
	//RUN_TEST(verifica_lettura_vel_vento);
	
    return UNITY_END();
}
