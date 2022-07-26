#include<math.h>
#include"unity.h"
#include"plot.h"


#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_CURVES_CORRETTO "../../../data/power_curves.csv"


void test_plot_curva_potenza()
{
	int errore = 0;
	struct turbina *head = NULL;
	
	struct csv file_coefficienti;
	struct csv file_potenza;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_coefficient(&file_coefficienti, head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);

    plot_curva_potenza(head);
    
    svuota_lista_turbine_data(head);
}

int main()
{
    test_plot_curva_potenza();

	
	
}
