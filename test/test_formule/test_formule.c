#include "../external/Unity/src/unity.h"
#include "../lib/formule/include/formule.h"


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


int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_interpolazione_lineare);

    return UNITY_END();
}