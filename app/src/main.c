#include "../include/main.h"
#define tipo_dati_stampa 0 //serve per eseguire solo il codice relativo alla turbina oopure quello relativo al meteo, se pari a 0 esegue le turbine, se pari a 1 esegue il meteo

int main()
{
    struct turbina *head_turbina=NULL;
    struct weather *meteo=NULL; 
    struct dati_weather *dati = NULL;
    struct csv file_coefficient;
    struct csv file_power;
    int errore=0;

    //inizio generazione lista turbine tramite la lettura da file
    head_turbina=estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore==CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }
    controllo_csv(&errore);
    lettura_file_power_coefficient(&file_coefficient, head_turbina, PERCORSO_POWER_COEFFICIENT, &errore);
    lettura_file_power_curves(&file_power, head_turbina, PERCORSO_POWER_CURVES, &errore);
    //fine generazione lista

    //inizio generazione lista dati meteorologici tramite la lettura da file
    dati = apertura_file_weather(&file, dati, PERCORSO_WEATHER, &errore);
    dati=estrazione_dati_weather(dati, PERCORSO_WEATHER, &errore);
    if (errore!=CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }
    controllo_csv(&errore);
    //fine generazione lista
}

//RICODATI DI DEALLOCARE LA MEMORIA!!!!!!

--------------------------------------------------
/*
int main()
{
    #if(tipo_dati_stampa==0)

    struct turbina *head_turbina=NULL; //definisco lista per il salvataggio delle turbine
    struct turbina *temporaneo=NULL; //variabile temporanea per dimostrazione stampa <-------------------- DA ELIMINARE
	//struct csv file_coefficient;
	//struct csv file_power;
    bool penultimo=false; //variabile temporanea per dimostrazione stampa <------------------------------- DA ELIMINARE
    bool ultimo=false; //variabile temporanea per dimostrazione stampa <---------------------------------- DA ELIMINARE
    int errore=0;
	
    //generazione lista con lettura da file
    head_turbina=estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore==CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }
	//reading_file_power_coefficient(&file_coefficient, head_turbina, PERCORSO_POWER_COEFFICIENT, &errore);
	//reading_file_power_curves(&file_power, head_turbina, PERCORSO_POWER_CURVES, &errore);
    // fine generazione lista

    //stampa un elemento della lista            <------------------------------------------------------INIZIO CODICE DA ELIMINARE (ESEMPIO)
    temporaneo = cerca_dati_turbina("AD116/5000", 0.0, head_turbina);
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
        head_turbina=conversione_dati_in_booleano(temporaneo);
        printf(" Modello turbina: %s\n", temporaneo->nome);
        printf(" ID: %s\n", temporaneo->id);
        printf(" Potenza nominale: %d\n", temporaneo->potenza_nominale);
        printf(" Diametro del rotore: %d\n", temporaneo->diametro_rotore);
        printf(" Altezza del mozzo: %f\n", temporaneo->altezza_mozzo);
        printf(" Char power_coefficient: %s\n", temporaneo->char_p_coefficient);
        printf(" Bool power_coefficient: %d\n", temporaneo->bool_p_coefficient);
        printf(" Char power_curves: %s\n", temporaneo->char_p_curves);
        printf(" Bool power_curves: %d\n", temporaneo->bool_p_curves);
		printf(" Velocità vento: \n\n\n");
/*	for(int i = 0; i < (NUMERO_COLONNE_POWER_COEFFICIENT_CURVES- 1); i++)
			printf("%f\t", temporaneo->wind_speed[i]);
		printf("\n");
		printf("Coefficienti di potenza: \n");
		if(temporaneo->power_coefficients != NULL){
			for(int i = 0; i < (NUMERO_COLONNE_POWER_COEFFICIENT_CURVES - 1); i++)
				printf("%f\t", temporaneo->power_coefficients[i]);
		}
		printf("\n");
		printf("Curva di potenza: \n");
		if(temporaneo->power_curves != NULL){
			for(int i = 0; i < (NUMERO_COLONNE_POWER_CURVES - 1); i++)
				printf("%d\t", temporaneo->power_curves[i]);
		}
		printf("\n");
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

    struct weather *temporaneo=NULL; //variabile temporanea per dimostrazione stampa <-------------------- DA ELIMINARE
    struct dati_weather *dati = NULL;
    int errore=0;

    dati = apertura_file_weather(&file, dati, PERCORSO_WEATHER, &errore);
	
	bool penultimo=false; //variabile temporanea per dimostrazione stampa <------------------------------- DA ELIMINARE
    bool ultimo=false; //variabile temporanea per dimostrazione stampa <---------------------------------- DA ELIMINARE

    dati=estrazione_dati_weather(dati, PERCORSO_WEATHER, &errore);
    if (errore!=CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }
	controllo_csv(&errore);

    //stampa un elemento della lista            <------------------------------------------------------INIZIO CODICE DA ELIMINARE (ESEMPIO)
    temporaneo = cerca_dati_weather("2010-01-01 09:00:00+01:00",dati->head_weather);
    if (temporaneo == NULL)
    {
        printf("Giorno e ora non trovati!\n\n\n");
    }else{
        printf("Ordine temporale del dato: %s\n", temporaneo->orario);
        printf("Pressione: %f\n", temporaneo->pressione);
        printf("Temperatura ad altezza1: %f\n", temporaneo->temperatura1);
        printf("Velocita' del vento ad altezza1: %f\n", temporaneo->velocita_vento1);
        printf("Rugosita': %f\n", temporaneo->rugosita);
        printf("Temperatura ad altezza2: %f\n", temporaneo->temperatura2);
        printf("Velocita' del vento ad altezza2: %f\n", temporaneo->velocita_vento2);
    }
    //fine stampa elemento lista

    //esempio stampa lista per verifica turbine_data.csv         
    temporaneo=dati->head_weather;
    printf("*****   Stampa elementi lista   *****\n\n");
    while (!ultimo) {
        printf("Ordine temporale del dato: %s\n", temporaneo->orario);
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

    svuota_dati_weather(dati); //deallocazione memoria heap

    return 0;

    #endif

}*/
