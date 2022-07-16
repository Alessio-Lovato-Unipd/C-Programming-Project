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

    struct weather *head_weather=NULL; //definisco lista per il salvataggio dei dati meteo
    struct weather *temporaneo=NULL; //variabile temporanea per dimostrazione stampa <-------------------- DA ELIMINARE
    bool penultimo=false; //variabile temporanea per dimostrazione stampa <------------------------------- DA ELIMINARE
    bool ultimo=false; //variabile temporanea per dimostrazione stampa <---------------------------------- DA ELIMINARE
    int errore=0;

    head_weather=estrazione_dati_weather(head_weather, PERCORSO_WEATHER, &errore);
    if (errore==CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }

    //stampa un elemento della lista            <------------------------------------------------------INIZIO CODICE DA ELIMINARE (ESEMPIO)
    temporaneo = cerca_dati_weather("2010-01-01 06:00:00+01:00", head_weather);
    if (temporaneo == NULL)
    {
        printf("Giorno e ora non trovati!\n\n\n");
    }else{
        printf("Giorno e ora: %s\n", temporaneo->nome);
        printf("Pressione: %f\n", temporaneo->pressione);
        printf("Temperatura ad altezza1: %f\n", temporaneo->temperatura1);
        printf("Velocita' del vento ad altezza1: %f\n", temporaneo->velocita_vento1);
        printf("Rugosita': %f\n", temporaneo->rugosita);
        printf("Temperatura ad altezza2: %f\n", temporaneo->temperatura2);
        printf("Velocita' del vento ad altezza2: %f\n", temporaneo->velocita_vento2);
    }
    //fine stampa elemento lista

    //esempio stampa lista per verifica turbine_data.csv         
    temporaneo=head_weather;
    printf("*****   Stampa elementi lista   *****\n\n");
    while (!ultimo) {
        printf("Giorno e ora: %s\n", temporaneo->nome);
        printf("Pressione: %f\n", temporaneo->pressione);
        printf("Temperatura ad altezza1: %f\n", temporaneo->temperatura1);
        printf("Velocita' del vento ad altezza1: %f\n", temporaneo->velocita_vento1);
        printf("Rugosita': %f\n", temporaneo->rugosita);
        printf("Temperatura ad altezza2: %f\n", temporaneo->temperatura2);
        printf("Velocita' del vento ad altezza2: %f\n", temporaneo->velocita_vento2);
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

    svuota_lista_weather(head_weather); //deallocazione memoria heap

    return 0;

    #endif
}