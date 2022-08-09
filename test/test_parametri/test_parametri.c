#include "unity.h"
#include "parametri.h"
#include <stdbool.h>

#define PERCORSO_WEATHER "../../../data/weather.csv"

bool cerca_errore(const int *const errore)
{
    for (int i = 0; i < NUMERO_ERRORI; i++) {
        if (errore[i] == 1)
            return true;
    }
    return false;
}

void test_calcolo_vento_int_lin()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_vel_vento(INTERPOLAZIONE_LINEARE_V, 10, 5.32697, 80, 7.80697, 0.15, 5, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 5.6812557, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_calcolo_vento_int_log()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_vel_vento(INTERPOLAZIONE_LOGARITMICA, 10, 5.32697, 80, 7.80697, 0.15, 5, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.15, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_calcolo_vento_profilo_logaritmico()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_vel_vento(PROFILO_LOGARITMICO, 10, 5.32697, 80, 7.80697, 0.15, 5, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.63494, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_calcolo_vento_hellmann()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_vel_vento(HELLMAN, 10, 5.32697, 80, 7.80697, 0.15, 5, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.129655, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_calcolo_temperatura_int_lin()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_temperatura_aria(INTERPOLAZIONE_LINEARE_T, 2, 267.6, 10, 267.57, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 267.5325, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_calcolo_temperatura_gradiente()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_temperatura_aria(GRADIENTE_LINEARE, 2, 267.6, 10, 267.57, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(267.483, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_calcolo_densita_barometrico()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_densita_aria(BAROMETRICO, 0, 98405.7, 267.6, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.277, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_calcolo_densita_gas_ideale()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = calcolo_densita_aria(GAS_IDEALE, 0, 98405.7, 267.6, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.277, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_aggiungi_elemento()
{
    struct parametro *p = NULL;
    p = aggiungi_elemento("data", p, 5, 3);
    TEST_ASSERT((p->vento == 5) && (p->densita_aria == 3));
	svuota_parametri(p);
}

void test_calcolo_parametri()
{
    int errore = 0;
	struct dati_weather *puntatore_dati_weather = NULL;
    struct tipo_metodo metodi_calcolo = {INTERPOLAZIONE_LOGARITMICA, INTERPOLAZIONE_LINEARE_T, GAS_IDEALE};
    struct parametro *head_uscita = NULL;
	puntatore_dati_weather = estrazione_dati_weather(puntatore_dati_weather, PERCORSO_WEATHER, &errore);
    head_uscita = calcolo_parametri(puntatore_dati_weather, &metodi_calcolo, 5, 20, head_uscita);

    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.15, head_uscita->vento);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.28, head_uscita->densita_aria);

    svuota_parametri(head_uscita);
	svuota_dati_weather(puntatore_dati_weather);
}

void stampa(void)
{
    int errore = 0;
	struct dati_weather *puntatore_dati_weather = NULL;
    struct tipo_metodo metodi_calcolo = {INTERPOLAZIONE_LOGARITMICA, INTERPOLAZIONE_LINEARE_T, GAS_IDEALE};
    struct parametro *head_uscita = NULL;
	puntatore_dati_weather = estrazione_dati_weather(puntatore_dati_weather, PERCORSO_WEATHER, &errore);
    head_uscita = calcolo_parametri(puntatore_dati_weather, &metodi_calcolo, 5, 20, head_uscita);
    stampa_lista_weather(puntatore_dati_weather->head_weather);
    svuota_dati_weather(puntatore_dati_weather);
    stampa_lista_parametri(head_uscita);
    svuota_parametri(head_uscita);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_calcolo_vento_int_lin);
    RUN_TEST(test_calcolo_vento_int_log);
    RUN_TEST(test_calcolo_vento_profilo_logaritmico);
    RUN_TEST(test_calcolo_vento_hellmann);
    RUN_TEST(test_calcolo_temperatura_int_lin);
    RUN_TEST(test_calcolo_temperatura_gradiente);
    RUN_TEST(test_calcolo_densita_barometrico);
    RUN_TEST(test_calcolo_densita_gas_ideale);
    RUN_TEST(test_aggiungi_elemento);  
    RUN_TEST(test_calcolo_parametri);  
    RUN_TEST(stampa);

    return UNITY_END();
}
