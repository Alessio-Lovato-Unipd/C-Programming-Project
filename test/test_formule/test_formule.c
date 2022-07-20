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
    float x = interpolazione_logaritmica()
}

void test_profilo_logaritmico()
{

}

void test_hellman()
{

}

void test_gradiente_lineare()
{

}

void test_calcolo_pressione()
{

}

void test_barometrico()
{

}

void test_gas_ideale()
{

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
