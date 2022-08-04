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

/*
void test_plot_potenza()
{
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	int errore = 0;
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	struct dati_weather *h_meteo = NULL;
	struct tipo_metodo *metodo_calcolo = malloc(sizeof(struct tipo_metodo*));
	struct parametro *h_parametri = NULL;
	struct potenza_out *h_potenza = NULL;
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	elemento_cercato = cerca_dati_turbina("E-70/2300", 85, head);	

	h_meteo = estrazione_dati_weather(h_meteo, PERCORSO_WEATHER_DATA_CORRETTO, &errore);

	metodo_calcolo->vento = INTERPOLAZIONE_LINEARE_V;
	metodo_calcolo->temperatura = INTERPOLAZIONE_LINEARE_T;
	metodo_calcolo->densita = BAROMETRICO;

	h_parametri = calcolo_parametri(h_meteo, metodo_calcolo, 0, 95, h_parametri);

	h_potenza = calcolo_potenza(CURVA_POTENZA, INTERPOLAZIONE_LINEARE_O, elemento_cercato->nome, head, 95, array_vento_curves, h_parametri, h_potenza);

	plot_potenza(h_meteo->head_weather, h_potenza, 30);

	svuota_lista_turbine_data(head);
	svuota_dati_weather(h_meteo);
}
*/


int main()
{
    test_plot_curva_potenza();
	test_plot_curva_coefficienti();

		
}
