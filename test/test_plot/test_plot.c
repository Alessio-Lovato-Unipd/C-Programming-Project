#include<math.h>
#include"unity.h"
#include"plot.h"


#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_CURVES_CORRETTO "../../../data/power_curves.csv"


void test_plot()
{
	struct turbina *head = NULL;
	head = malloc(sizeof(struct turbina));
	head->wind_speed = malloc(sizeof(float) * (NUMERO_COLONNE_POWER_CURVES));
	head->power_curves = malloc(sizeof(int) * (NUMERO_COLONNE_POWER_CURVES));
	for(int i = 1; i < NUMERO_COLONNE_POWER_CURVES; i++) {
		head->wind_speed[i - 1] = i;
		head->power_curves[i - 1] = log(i);
	}

    plot_curva_potenza(head);
    
    svuota_lista_turbine_data(head);
}

void test_plot_curva_potenza()
{
	int errore = 0;
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	struct csv file_potenza;
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	reading_file_power_curves(&file_potenza, head, PERCORSO_POWER_CURVES_CORRETTO, &errore);
	elemento_cercato = cerca_dati_turbina("E-101/3050", 99, head);

	plot_curva_potenza(elemento_cercato);

	svuota_lista_turbine_data(head);
}


int main()
{
    test_plot();
		
}
