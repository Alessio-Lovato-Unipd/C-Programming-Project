#include "unity.h"
#include "calcolo_output.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_CURVES_CORRETTO "../../../data/power_curves.csv"

void ricerca_turbina(void)
{
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	elemento_cercato = cerca_dati_turbina("E-101/3050", 99, head);
	TEST_ASSERT_EQUAL_STRING("E-101/3050", elemento_cercato->nome);
	elemento_cercato = cerca_dati_turbina("E-126/7500", 0.0, head);
	TEST_ASSERT_EQUAL_STRING("E-126/7500", elemento_cercato->nome);
	svuota_lista_turbine_data(head);
}

void lettura_interpolazione_curve_interpolazione_lineare(void)
{
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	elemento_cercato = cerca_dati_turbina("E-101/3050", 99, head);
	
	calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15);
	TEST_ASSERT_EQUAL_FLOAT(0, elemento_cercato->power_curves[0]);
	TEST_ASSERT_EQUAL_FLOAT(189000, elemento_cercato->power_curves[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_curves[LUNGHEZZA_VETTORE_POWER_CURVES]);
	
	calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15, 1.225);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.385, elemento_cercato->power_coefficients[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.3985, elemento_cercato->power_coefficients[10]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[20]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[21]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[22]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[LUNGHEZZA_VETTORE_POWER_COEFFICIENT]);
	svuota_lista_turbine_data(head);
}

void lettura_interpolazione_curve_interpolazione_logaritmica(void)
{
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	elemento_cercato = cerca_dati_turbina("E-101/3050", 99, head);
	
	calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LOGARITMICA_O, "E-101/3050", head, 99, 15);
	TEST_ASSERT_EQUAL_FLOAT(0, elemento_cercato->power_curves[0]);
	TEST_ASSERT_EQUAL_FLOAT(190210.2, elemento_cercato->power_curves[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_curves[LUNGHEZZA_VETTORE_POWER_CURVES]);
	
	calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15, 1.225);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.3858, elemento_cercato->power_coefficients[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.3997, elemento_cercato->power_coefficients[10]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[20]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[21]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[22]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[LUNGHEZZA_VETTORE_POWER_COEFFICIENT]);
	svuota_lista_turbine_data(head);
}

void prova_calcolo_potenza_precisa(void)
{
	struct turbina *head = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	float potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15);
	TEST_ASSERT_EQUAL_FLOAT(3000000.0, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15, 1.225);
	TEST_ASSERT_EQUAL_FLOAT(3047406.027, potenza);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "VS112/2500", head, 0.0, 4.0);
	TEST_ASSERT_EQUAL_FLOAT(154200.0, potenza);
	svuota_lista_turbine_data(head);
}

void prova_calcolo_potenza_interpolazione_lineare(void)
{
	struct turbina *head = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	float potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-115/3200", head, 92, 4.1);
	TEST_ASSERT_EQUAL_FLOAT(137850, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "E-115/3200", head, 92, 4.1, 1.225);
	TEST_ASSERT_EQUAL_FLOAT(171314.74, potenza);
	svuota_lista_turbine_data(head);
}

void prova_calcolo_potenza_interpolazione_logaritmica(void)
{
	struct turbina *head = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	float potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LOGARITMICA_O, "E-115/3200", head, 92, 4.1);
	TEST_ASSERT_EQUAL_FLOAT(140232, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LOGARITMICA_O, "E-115/3200", head, 92, 4.1, 1.225);
	TEST_ASSERT_EQUAL_FLOAT(171493.2, potenza);
	svuota_lista_turbine_data(head);
}

void prova_calcolo_valori_ai_limiti(void)
{
	struct turbina *head = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	float potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "VS112/2500", head, 0.0, 35.0);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "VS112/2500", head, 0.0, 36.0);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "V112/3300", head, 0.0, 26.0, 1.225);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "V112/3300", head, 0.0, 35.0, 1.225);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	svuota_lista_turbine_data(head);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(ricerca_turbina);
	RUN_TEST(lettura_interpolazione_curve_interpolazione_lineare);
	RUN_TEST(lettura_interpolazione_curve_interpolazione_logaritmica);
	RUN_TEST(prova_calcolo_potenza_precisa);
	RUN_TEST(prova_calcolo_potenza_interpolazione_lineare);
	RUN_TEST(prova_calcolo_potenza_interpolazione_logaritmica);
	return UNITY_END();
}