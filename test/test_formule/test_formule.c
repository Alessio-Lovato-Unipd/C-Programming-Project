#include "unity.h"
#include "formule.h"
#include <stdbool.h>

bool cerca_errore(const int *const errore)
{
    for (int i = 0; i < NUMERO_ERRORI; i++) {
        if (errore[i] == 1)
            return true;
    }
    return false;
}

void test_interpolazione_lineare()
{
    float y = 0;
    int a = 2; 
    int b = 1;
    int c = 7; 
    int d = 4;
    y = interpolazione_lineare(a, b, c, d, 5);
    TEST_ASSERT_EQUAL_FLOAT(2.8, y);
	y = interpolazione_lineare(1, 0 , 1.5, 0, 1.2);
	TEST_ASSERT_EQUAL_FLOAT(0, y);
}

void test_interpolazione_lineare_limite()
{
	float y;
	y = interpolazione_lineare(1.5, 12, 1.5, 12, 1.5); //interpolazione con x1 e x2 uguali
	TEST_ASSERT_EQUAL_FLOAT(12, y); //non voglio un "nan"
	y = interpolazione_lineare(1.5, 12, 1.6, 13, 1.4); //x<x1
	TEST_ASSERT_EQUAL_FLOAT(11, y);
	y = interpolazione_lineare(1.5, 12, 1.6, 13, 1.7); //x>x2
	TEST_ASSERT_EQUAL_FLOAT(14, y);
	y = interpolazione_lineare(1.5, 1, 1, 0, 1.2); //caso x1>x2
	TEST_ASSERT_EQUAL_FLOAT(0.4, y);
}

void test_interpolazione_logaritmica()
{
    float x = interpolazione_logaritmica(10, 5.32, 80, 7.81, 20);
    TEST_ASSERT_EQUAL_FLOAT(6.15, x);
	x = interpolazione_lineare(1.5, 12, 1.5, 12, 1.5); //interpolazione con x1 e x2 uguali
	TEST_ASSERT_EQUAL_FLOAT(12, x); //non voglio un "nan"
}

void test_interpolazione_logaritmica_input_errati()
{
    float x = interpolazione_logaritmica(-3, 5.32, 80, 7.81, 20);
    TEST_ASSERT_EQUAL_FLOAT(5.32, x);
    x = interpolazione_logaritmica(10, 5.32, -80, 7.81, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = interpolazione_logaritmica(10, 5.32, 80, 7.81, -20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
	x = interpolazione_lineare(1.5, 12, 1.6, 13, 1.4);
	TEST_ASSERT_FLOAT_WITHIN(0.1, 10.93, x);
	x = interpolazione_lineare(1.5, 12, 1.6, 13, 1.7);
	TEST_ASSERT_FLOAT_WITHIN(0.1, 13.94, x);
}

void test_profilo_logaritmico()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = profilo_logaritmico(10, 5.32, 0.15, 5, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6.63494, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));

}

void test_profilo_logaritmico_input_errati()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = profilo_logaritmico(-3, 5.32, 0.15, 5, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_H_DATI] = 0;

    x = profilo_logaritmico(10, 5.32, -0.14, 5, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_RUGOSITA] = 0;

    x = profilo_logaritmico(10, 5.32, 0.15, -3, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_OSTACOLO] = 0;
    
    x = profilo_logaritmico(10, 5.32, 0.15, 5, -20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_H_MOZZO] = 0;
    
    x = profilo_logaritmico(10, 5.32, 0.15, 20, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_OSTACOLO] = 0;
   
    x = profilo_logaritmico(10, -5.32, 0.15, 5, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    
}

void test_hellman()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = hellman(10, 5.32, 0.15, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6.129655, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_hellman_input_errati()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = hellman(-10, 5.32, 0.15, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_H_DATI] = 0;

    x = hellman(10, 5.32, -0.04, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_RUGOSITA] = 0;

    x = hellman(10, 5.32, 0.15, -20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_H_MOZZO] = 0;

    x = hellman(10, -5.32, 0.15, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
}

void test_gradiente_lineare()
{
    int errore[NUMERO_ERRORI] = {0};
    float x = gradiente_lineare(2, 267.6, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(267.483, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_gradiente_lineare_input_errati()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = gradiente_lineare(-2, 267.6, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_H_DATI] = 0;

    x = gradiente_lineare(2, 0, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_TEMP] = 0;

    x = gradiente_lineare(2, 267.6, -30, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
}

void test_calcolo_pressione()
{
    float x = p_x(98405.7 , 0, 20);
    TEST_ASSERT_EQUAL_FLOAT(98155.7, x);
}

void test_barometrico()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = barometrico(0, 98405.7, 267.6, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.277, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_barometrico_input_errati()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = barometrico(-2, 98405.7, 267.6, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_H_DATI] = 0;

    x = barometrico(0, 0, 267.6, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_PRESS] = 0;

    x = barometrico(0, 98405.7, 0, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_TEMP] = 0;

    x = barometrico(0, 98405.7, 267.6, -20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
}

void test_gas_ideale()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = gas_ideale(0, 98405.7, 267.6, 20, errore);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.277, x);
    TEST_ASSERT_FALSE(cerca_errore(errore));
}

void test_gas_ideale_iput_errati()
{
    int errore[NUMERO_ERRORI] = {0};

    float x = gas_ideale(-1, 98405.7, 267.6, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_H_DATI] = 0;

    x = gas_ideale(0, 0, 267.6, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_PRESS] = 0;

    x = gas_ideale(0, 98405.7, 0, 20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
    errore[ERR_TEMP] = 0;

    x = gas_ideale(0, 98405.7, 267.6, -20, errore);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    TEST_ASSERT_TRUE(cerca_errore(errore));
}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_interpolazione_lineare);
	RUN_TEST(test_interpolazione_lineare_limite);
    RUN_TEST(test_interpolazione_logaritmica);
    RUN_TEST(test_interpolazione_logaritmica_input_errati);
    RUN_TEST(test_profilo_logaritmico);
    RUN_TEST(test_profilo_logaritmico_input_errati);
    RUN_TEST(test_hellman);
    RUN_TEST(test_hellman_input_errati);
    RUN_TEST(test_gradiente_lineare);
    RUN_TEST(test_gradiente_lineare_input_errati);
    RUN_TEST(test_calcolo_pressione);
    RUN_TEST(test_barometrico);
    RUN_TEST(test_barometrico_input_errati);
    RUN_TEST(test_gas_ideale);
    RUN_TEST(test_gas_ideale_iput_errati);

    return UNITY_END();
}
