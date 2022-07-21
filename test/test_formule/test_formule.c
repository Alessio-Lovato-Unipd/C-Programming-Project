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
}

void test_interpolazione_logaritmica()
{
    float x = interpolazione_logaritmica(10, 5.32, 80, 7.81, 20);
    TEST_ASSERT_EQUAL_FLOAT(6.15, x);
}

void test_profilo_logaritmico()
{
    float x = profilo_logaritmico(10, 5.32, 0.15, 5, 20);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6.63494, x);
}

void test_hellman()
{
    float x = hellman(10, 5.32, 0.15, 20);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6.129655, x);
}

void test_gradiente_lineare()
{
    float x = gradiente_lineare(2, 267.6, 20);
    TEST_ASSERT_EQUAL_FLOAT(267.483, x);
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

void test_gas_ideale()
{
    float x = gas_ideale(0, 98405.7, 267.6, 20);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.277, x);
}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_interpolazione_lineare);
    RUN_TEST(test_interpolazione_logaritmica);
    RUN_TEST(test_profilo_logaritmico);
    RUN_TEST(test_hellman);
    RUN_TEST(test_gradiente_lineare);
    RUN_TEST(test_calcolo_pressione);
    RUN_TEST(test_barometrico);
    RUN_TEST(test_gas_ideale);

    return UNITY_END();
}
