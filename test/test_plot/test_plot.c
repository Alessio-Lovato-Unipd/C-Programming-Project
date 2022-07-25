#include"unity.h"
#include"plot.h"


#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_CURVES_CORRETTO "../../../data/power_curves.csv"


void test_plot_curva_potenza()
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

    plot_curva_potenza(puntatore);
    
    svuota_lista_turbine_data(puntatore);
}

int main()
{
    UNITY_BEGIN();



    return UNITY_END();
}
