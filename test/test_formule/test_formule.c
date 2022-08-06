#include "unity.h"
#include "formule.h"


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
	y = interpolazione_lineare(1.5, 1, 1, 0, 1.2); //test invertendo x1 e x2
	TEST_ASSERT_EQUAL_FLOAT(0.4, y);
}

void test_interpolazione_lineare_limite()
{
	float y;
	y = interpolazione_lineare(1.5, 12, 1.5, 12, 1.5); //interpolazione con x1 e x2 uguali
	TEST_ASSERT_EQUAL_FLOAT(12, y); //non voglio un "nan"
}

void test_interpolazione_logaritmica()
{
    float x = interpolazione_logaritmica(10, 5.32, 80, 7.81, 20);
    TEST_ASSERT_EQUAL_FLOAT(6.15, x);
}

void test_interpolazione_logaritmica_limite()
{
	float y;
	y = interpolazione_logaritmica(0, 3, 1, 4, 0.5); //x1 = 0, problema di dominio del logaritmo
	TEST_ASSERT_EQUAL_FLOAT(0.0, y);
}

void test_interpolazione_logaritmica_input_errati()
{
    float x = interpolazione_logaritmica(-3, 5.32, 80, 7.81, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = interpolazione_logaritmica(10, 5.32, -80, 7.81, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = interpolazione_logaritmica(10, 5.32, 80, 7.81, -20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
}

void test_profilo_logaritmico()
{
    float x = profilo_logaritmico(10, 5.32, 0.15, 5, 20);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6.63494, x);
}

void test_profilo_logaritmico_input_errati()
{
    float x = profilo_logaritmico(-3, 5.32, 0.15, 5, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = profilo_logaritmico(10, 5.32, -0.14, 5, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = profilo_logaritmico(10, 5.32, 0.15, -3, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = profilo_logaritmico(10, 5.32, 0.15, 5, -20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = profilo_logaritmico(10, 5.32, 0.15, 20, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
}

void test_hellman()
{
    float x = hellman(10, 5.32, 0.15, 20);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6.129655, x);
}

void test_hellman_input_errati()
{
    float x = hellman(-10, 5.32, 0.15, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = hellman(10, 5.32, -0.04, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = hellman(10, 5.32, 0.15, -20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
}

void test_gradiente_lineare()
{
    float x = gradiente_lineare(2, 267.6, 20);
    TEST_ASSERT_EQUAL_FLOAT(267.483, x);
}

void test_gradiente_lineare_input_errati()
{
    float x = gradiente_lineare(-2, 267.6, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = gradiente_lineare(2, 0, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = gradiente_lineare(2, 267.6, -30);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
}

void test_calcolo_pressione()
{
    float x = p_x(98405.7 , 0, 20);
    TEST_ASSERT_EQUAL_FLOAT(98155.7, x);
}

void test_barometrico()
{
    float x = barometrico(0, 98405.7, 267.6, 20);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.277, x);
}

void test_barometrico_input_errati()
{
    float x = barometrico(-2, 98405.7, 267.6, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = barometrico(0, 0, 267.6, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = barometrico(0, 98405.7, 0, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = barometrico(0, 98405.7, 267.6, -20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
}

void test_gas_ideale()
{
    float x = gas_ideale(0, 98405.7, 267.6, 20);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.277, x);
}

void test_gas_ideale_iput_errati()
{
    float x = gas_ideale(-1, 98405.7, 267.6, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = gas_ideale(0, 0, 267.6, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = gas_ideale(0, 98405.7, 0, 20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
    x = gas_ideale(0, 98405.7, 267.6, -20);
    TEST_ASSERT_EQUAL_FLOAT(-1, x);
}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_interpolazione_lineare);
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
