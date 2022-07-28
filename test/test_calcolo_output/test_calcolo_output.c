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

void lettura_interpolazione_curve(void)
{
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	struct csv file_coefficienti;
	struct csv file_potenza;
	float potenza;
	int errore = 0;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15);
	TEST_ASSERT_EQUAL_FLOAT(30000000, potenza);
	TEST_ASSERT_EQUAL_FLOAT(0, elemento_cercato->power_curves[0]);
	TEST_ASSERT_EQUAL_FLOAT(158400, elemento_cercato->power_curves[9]);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(ricerca_turbina);
	return UNITY_END();
}