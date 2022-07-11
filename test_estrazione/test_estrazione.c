#include "external/Unity/src/unity.h"
#include "../lib/lettore_csv/libestrazione_csv/include/estrattore_csv.h"

#define PERCORSO_TURBINE_DATA_CORRETTO "../../data/turbine_data.csv"
#define PERCORSO_TURBINE_DATA_ERRATO "./data/turbine_data.csv"


void verifica_presenza_file_csv_percorso_corretto(void){
    struct turbina *puntatore=NULL;
    int errore = 0;
    puntatore = estrazione_dati_turbine(puntatore,PERCORSO_TURBINE_DATA_CORRETTO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_END,errore);
}

void verifica_presenza_file_csv_percorso_errato(void){
    struct turbina *puntatore_errato=NULL;
    int errore = 0;
    puntatore_errato = estrazione_dati_turbine(puntatore_errato,PERCORSO_TURBINE_DATA_ERRATO, &errore);
    TEST_ASSERT_EQUAL_INT(CSV_E_IO,errore);
}


int main()
{
    UNITY_BEGIN();
    RUN_TEST(verifica_presenza_file_csv_percorso_corretto);
    RUN_TEST(verifica_presenza_file_csv_percorso_errato);
   
    return UNITY_END();
}