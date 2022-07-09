#include "../include/main.h"


#define PERCORSO_TURBINE_DATA "../data/turbine_data.csv"


int main()
{
    struct turbina *head_turbina=NULL; //definisco lista per il salvataggio delle turbine
    char *turbine_data;
    struct turbina *temporaneo=NULL;
    bool penultimo=false;
    bool ultimo=false;
    turbine_data=PERCORSO_TURBINE_DATA;

    //generazione lista con lettura da file
    head_turbina = estrazione_dati_turbine(head_turbina, turbine_data);
    if (head_turbina==NULL)
    {
        printf("Errore nella lettura dei dati da file turbine_data.csv\n");
        return(EXIT_FAILURE);
    }

    //esempio stampa lista per verifica dturbine_data.csv
    temporaneo=head_turbina;
    while (!ultimo) {
        printf(" Modello turbina: %s\n", temporaneo->nome);
        printf(" Potenza nominale: %d\n", temporaneo->potenza_nominale);
        printf("----\n\n");

        temporaneo=temporaneo->next;

        if (temporaneo == NULL)
        {
            penultimo=true;
        }

        if (penultimo)
        {
            ultimo=true;
        }
    }
    //fine esempio di stampa

    //deallocazione memoria heap
    svuota_lista_turbine_data(head_turbina);

    return 0;
}