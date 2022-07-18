#include "unity.h"
#include "parametri.h"


void test_calcolo_vento()
{
    float i = calcolo_vel_vento(INTERPOLAZIONE_LINEARE, 10, 5.32697, 80, 7.80697, 0, 0, 30);
    TEST_ASSERT_EQUAL_FLOAT(34, i);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_calcolo_vento);

    return UNITY_END();
}
