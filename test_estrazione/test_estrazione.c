#include "external/Unity/src/unity.h"
#include "../lib/lettore_csv/libestrazione_csv/include/estrattore_csv.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../data/turbine_data.csv"
#define PERCORSO_TURBINE_DATA_ERRATO "./data/turbine_data.csv"


void verifica_presenza_file_csv_percorso_corretto(void){
    struct turbina *puntatore=NULL;
    TEST_ASSERT_EQUAL_INT(1,estrazione_dati_turbine(puntatore,PERCORSO_TURBINE_DATA_CORRETTO));
}

void verifica_presenza_file_csv_percorso_errato(void){
    struct turbina *puntatore_errato=NULL;
    TEST_ASSERT_EQUAL_INT(5,estrazione_dati_turbine(puntatore_errato,PERCORSO_TURBINE_DATA_ERRATO));
}


int main()
{
    UNITY_BEGIN();
    RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
    RUN_TEST(verifica_presenza_file_csv_percorso_errato);
   
    return UNITY_END();
}