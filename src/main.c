#include "../include/main.h"


#define PERCORSO_TURBINE_DATA "../data/turbine_data.csv"


int main()
{
    struct turbina *head_turbina=NULL; //definisco lista per il salvataggio delle turbine
    char *turbine_data;
    bool penultimo=false;
    bool ultimo=false;

    turbine_data=PERCORSO_TURBINE_DATA;

    //generazione lista con lettura da file
    head_turbina = estrazione_dati_turbine(head_turbina, turbine_data);

    //stampa lista per verifica dturbine_data.csv
    while (!ultimo) {
        printf(" Modello turbina: %s\n", head_turbina->nome);
        printf(" Potenza nominale: %d\n", head_turbina->potenza_nominale);
        printf("----\n\n");
        head_turbina = head_turbina->next;
        
        if (head_turbina == NULL)
        {
            penultimo=true;
        }

        if (penultimo)
        {
            ultimo=true;
        }
        
    }

    
    return 0;
}