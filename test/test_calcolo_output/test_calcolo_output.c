
#include "unity.h"
#include "calcolo_output.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../../../data/turbine_data.csv"
#define PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO "../../../data/power_coefficient_curves.csv"
#define PERCORSO_POWER_CURVES_CORRETTO "../../../data/power_curves.csv"
#define PERCORSO_WEATHER_DATA_CORRETTO "../../../data/weather.csv"


void ricerca_turbina(void)
{
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
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
	int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	elemento_cercato = cerca_dati_turbina("E-101/3050", 99, head);
	
	calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(0, elemento_cercato->power_curves[0]);
	TEST_ASSERT_EQUAL_FLOAT(189000, elemento_cercato->power_curves[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_curves[LUNGHEZZA_VETTORE_POWER_CURVES]);
	
	calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15, 1.225, array_vento_coeff);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.385, elemento_cercato->power_coefficients[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.3985, elemento_cercato->power_coefficients[10]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[20]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[21]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[22]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[LUNGHEZZA_VETTORE_POWER_COEFFICIENT]);
	
	elemento_cercato = cerca_dati_turbina("E-101/3500", 0.0, head);
	calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-101/3500", head, 0.0, 15, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_curves[LUNGHEZZA_VETTORE_POWER_CURVES - 1]); //ultimi valori nulli sono tutti uguali a 0
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_curves[LUNGHEZZA_VETTORE_POWER_CURVES - 2]);
	
	svuota_lista_turbine_data(head);
}

void lettura_interpolazione_curve_interpolazione_logaritmica(void)
{
	struct turbina *head = NULL;
	struct turbina *elemento_cercato = NULL;
	int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	elemento_cercato = cerca_dati_turbina("E-101/3050", 99, head);
	
	calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LOGARITMICA_O, "E-101/3050", head, 99, 15, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(0, elemento_cercato->power_curves[0]);
	TEST_ASSERT_EQUAL_FLOAT(190210.2, elemento_cercato->power_curves[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_curves[LUNGHEZZA_VETTORE_POWER_CURVES]);
	
	calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LOGARITMICA_O, "E-101/3050", head, 99, 15, 1.225, array_vento_coeff);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[0]);
	TEST_ASSERT_EQUAL_FLOAT(0.385839, elemento_cercato->power_coefficients[9]);
	TEST_ASSERT_EQUAL_FLOAT(0.399752, elemento_cercato->power_coefficients[10]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[20]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[21]);
	TEST_ASSERT_EQUAL_FLOAT(0.478, elemento_cercato->power_coefficients[22]);
	TEST_ASSERT_EQUAL_FLOAT(0.0, elemento_cercato->power_coefficients[LUNGHEZZA_VETTORE_POWER_COEFFICIENT]);
	
	svuota_lista_turbine_data(head);
}

void prova_calcolo_potenza_precisa(void)
{
	struct turbina *head = NULL;
	float potenza;
	int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(3000000.0, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, 15, 1.225, array_vento_coeff);
	TEST_ASSERT_EQUAL_FLOAT(3047406.027, potenza);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "VS112/2500", head, 0.0, 4.0, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(154200.0, potenza);
	
	svuota_lista_turbine_data(head);
}

void prova_calcolo_potenza_interpolazione_lineare(void)
{
	struct turbina *head = NULL;
	float potenza;
	int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "E-115/3200", head, 92, 4.1, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(173400, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "E-115/3200", head, 92, 4.1, 1.225, array_vento_coeff);
	TEST_ASSERT_EQUAL_FLOAT(171751, potenza);
	
	svuota_lista_turbine_data(head);
}

void prova_calcolo_potenza_interpolazione_logaritmica(void)
{
	struct turbina *head = NULL;
	float potenza;
	int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LOGARITMICA_O, "E-115/3200", head, 92, 4.1, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(175360.8, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LOGARITMICA_O, "E-115/3200", head, 92, 4.1, 1.225, array_vento_coeff);
	TEST_ASSERT_EQUAL_FLOAT(172106.8, potenza);
	
	svuota_lista_turbine_data(head);
}

void prova_calcolo_valori_ai_limiti(void)
{
	struct turbina *head = NULL;
	float potenza;
	int errore = 0;
	float array_vento_coeff[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
	float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
	
	head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
	lettura_file_power_coefficient(head, PERCORSO_POWER_COEFFICIENT_CURVES_CORRETTO, &errore, array_vento_coeff);
	lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
	
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "VS112/2500", head, 0.0, 35.0, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LINEARE_O, "VS112/2500", head, 0.0, 34.5, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	potenza = calcolo_potenza_curve_coefficienti(INTERPOLAZIONE_LINEARE_O, "V112/3300", head, 0.0, 26.0, 1.225, array_vento_coeff);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	potenza = calcolo_potenza_curve_di_potenza(INTERPOLAZIONE_LOGARITMICA_O, "AD116/5000", head, 0.0, 35.0, array_vento_curves);
	TEST_ASSERT_EQUAL_FLOAT(0.0, potenza);
	
	svuota_lista_turbine_data(head);
}



void test_calcolo_potenza()
{
    struct turbina *head = NULL;

    //struct turbina *elemento_cercato = NULL;
    int errore = 0;
    float array_vento_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};
    struct dati_weather *h_meteo = NULL;
    struct tipo_metodo metodo_calcolo = {INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LINEARE_T, BAROMETRICO};
    struct parametro *h_parametri = NULL;
	float *potenza = NULL;
    
    head = estrazione_dati_turbine(head, PERCORSO_TURBINE_DATA_CORRETTO, &errore);
    lettura_file_power_curves(head, PERCORSO_POWER_CURVES_CORRETTO, &errore, array_vento_curves);
    //elemento_cercato = cerca_dati_turbina("V164/9500", 0.0, head);

    h_meteo = estrazione_dati_weather(h_meteo, PERCORSO_WEATHER_DATA_CORRETTO, &errore);

    h_parametri = calcolo_parametri(h_meteo, &metodo_calcolo, 0, 95, h_parametri);

    potenza = calcolo_potenza(CURVA_POTENZA, INTERPOLAZIONE_LINEARE_O, "E-101/3050", head, 99, array_vento_curves, h_parametri);
	
	TEST_ASSERT_EQUAL_FLOAT(1732412.2, potenza[0]);
	TEST_ASSERT_EQUAL_FLOAT(1752941.6, potenza[1]);
	TEST_ASSERT_EQUAL_FLOAT(2206846.5, potenza[2]);
	TEST_ASSERT_EQUAL_FLOAT(1748581.6, potenza[3]);

    svuota_lista_turbine_data(head);
    svuota_dati_weather(h_meteo);
	svuota_parametri(h_parametri);
	free(potenza);
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
	RUN_TEST(prova_calcolo_valori_ai_limiti);
	RUN_TEST(test_calcolo_potenza);
	return UNITY_END();

}

