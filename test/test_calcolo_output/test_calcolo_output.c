#include "unity.h"
#include "estrattore_csv.h"
#include "formule.h"
#include "parametri.h"

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

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(ricerca_turbine);
	return UNITY_END();
}