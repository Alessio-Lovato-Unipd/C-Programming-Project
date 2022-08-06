#include<math.h>
#include"unity.h"
#include"plot.h"


#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_CURVES_CORRETTO "../../../data/power_curves.csv"
#define PERCORSO_WEATHER_DATA_CORRETTO "../../../data/weather.csv"


void test_plot()
{
	struct turbina *head = NULL;
	head = malloc(sizeof(struct turbina));
	float *x_vento = malloc(sizeof(float) * (NUMERO_COLONNE_POWER_CURVES));
	head->power_curves = malloc(sizeof(int) * (NUMERO_COLONNE_POWER_CURVES));
	for(int i = 1; i < NUMERO_COLONNE_POWER_CURVES; i++) {
		x_vento[i - 1] = i;
		head->power_curves[i - 1] = log(i);
	}

    plot_curva_potenza(x_vento, head);
    
    svuota_lista_turbine_data(head);
}


void test_plot_curva_potenza()
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct turbina *elemento_cercato = NULL;
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_curves(puntatore, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	elemento_cercato = cerca_dati_turbina("V164/9500", 0.0, puntatore);

	interpolazione_potenza_per_valori_mancanti(INTERPOLAZIONE_LINEARE_O, elemento_cercato, array_vento_curves);

	plot_curva_potenza(array_vento_curves, elemento_cercato);


	svuota_lista_turbine_data(puntatore);
}

void test_plot_curva_coefficienti()
{
	int errore = 0;
	struct turbina *puntatore = NULL;
	struct turbina *elemento_cercato = NULL;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	
	puntatore = estrazione_dati_turbine(puntatore, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(puntatore, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	elemento_cercato = cerca_dati_turbina("E-70/2300", 85, puntatore);

	interpolazione_coefficienti_per_valori_mancanti(INTERPOLAZIONE_LINEARE_O, elemento_cercato, array_vento_coeff);

	plot_curva_coefficienti(array_vento_coeff, elemento_cercato);

	svuota_lista_turbine_data(puntatore);	
}


int main()
{
    test_plot_curva_potenza();
	test_plot_curva_coefficienti();	
}
