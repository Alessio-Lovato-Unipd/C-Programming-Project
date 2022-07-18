#include "../include/main.h"
#define tipo_dati_stampa 1 //serve per eseguire solo il codice relativo alla turbina oopure quello relativo al meteo, se pari a 0 esegue le turbine, se pari a 1 esegue il meteo


int main()
{
    #if(tipo_dati_stampa==0)

    struct turbina *head_turbina=NULL; //definisco lista per il salvataggio delle turbine
    struct turbina *temporaneo=NULL; //variabile temporanea per dimostrazione stampa <-------------------- DA ELIMINARE
    bool penultimo=false; //variabile temporanea per dimostrazione stampa <------------------------------- DA ELIMINARE
    bool ultimo=false; //variabile temporanea per dimostrazione stampa <---------------------------------- DA ELIMINARE
    int errore=0;

    //generazione lista con lettura da file
    head_turbina=estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore==CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }
    // fine generazione lista

    //stampa un elemento della lista            <------------------------------------------------------INIZIO CODICE DA ELIMINARE (ESEMPIO)
    temporaneo = cerca_dati_turbina("DUMMY 2", head_turbina);
    if (temporaneo == NULL)
    {
        printf("Modello turbina non trovato!\n\n\n");
    }else{
        printf("Ricerca modello: %s\n", temporaneo->nome);
        printf("Potenza nominale: %d\n\n\n", temporaneo->potenza_nominale);
    }
    //fine stampa elemento lista

    //esempio stampa lista per verifica turbine_data.csv         
    temporaneo=head_turbina;
    printf("*****   Stampa elementi lista   *****\n\n");
    while (!ultimo) {
        printf(" Modello turbina: %s\n", temporaneo->nome);
        printf(" Potenza nominale: %d\n", temporaneo->potenza_nominale);
        printf("----\n\n");

        temporaneo=temporaneo->prev;

        if (temporaneo == NULL)
        {
            penultimo=true;
        }

        if (penultimo)
        {
            ultimo=true;
        }
    }
    //fine esempio di stampa                <------------------------------------------------------------ FINE CODICE DA ELIMINARE


    svuota_lista_turbine_data(head_turbina); //deallocazione memoria heap

    return 0;

    #endif

    
    
    #if(tipo_dati_stampa==1)

    //variabile temporanea per dimostrazione stampa <-------------------- DA ELIMINARE
	struct csv file;
    struct dati_weather *dati = NULL;
    int errore=0;

    dati = apertura_file_weather(&file, dati, PERCORSO_WEATHER, &errore);
    if (errore==CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }
	controllo_csv(&errore);
    //lettura weather in una funzione secondaria
	
	//lettura struttura altezze
	printf("%f\t", dati->h_pressione);
    printf("%f\t", dati->h_t1);
	printf("%f\t", dati->h_vel1);
	printf("%f\t", dati->h_rugosita);
	printf("%f\t", dati->h_t2);
	printf("%f\n", dati->h_vel2);
	
	chiusura_file_weather(&file, dati);
	
    return 0;

    #endif
}
