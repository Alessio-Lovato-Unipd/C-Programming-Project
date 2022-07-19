#include "../include/main.h"
#define tipo_dati_stampa 0 //serve per eseguire solo il codice relativo alla turbina oopure quello relativo al meteo, se pari a 0 esegue le turbine, se pari a 1 esegue il meteo


int main()
{
    #if(tipo_dati_stampa==0)

    struct turbina *head_turbina=NULL; //definisco lista per il salvataggio delle turbine
    struct turbina *temporaneo=NULL; //variabile temporanea per dimostrazione stampa <-------------------- DA ELIMINARE
	struct csv file_coefficient;
	struct csv file_power;
    bool penultimo=false; //variabile temporanea per dimostrazione stampa <------------------------------- DA ELIMINARE
    bool ultimo=false; //variabile temporanea per dimostrazione stampa <---------------------------------- DA ELIMINARE
    int errore=0;
	
	apertura_file_power_coefficient(&file_coefficient, PERCORSO_POWER_COEFFICIENT, &errore);
	apertura_file_power_curves(&file_coefficient, PERCORSO_POWER_CURVES, &errore);
    //generazione lista con lettura da file
    head_turbina=estrazione_dati_turbine(&file_coefficient, &file_power, head_turbina, PERCORSO_TURBINE_DATA, &errore);
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
		for(int i = 0; i < (NUMERO_COLONNE_POWER_COEFFICIENT - 1); i++)
			printf(" Velocità vento: %f\t", temporaneo->wind_speed[i]);
		printf("\n");
		if(temporaneo->power_coefficients != NULL){
			for(int i = 0; i < (NUMERO_COLONNE_POWER_COEFFICIENT - 1); i++)
				printf(" Coefficienti di potenza: %f\t", temporaneo->power_coefficients[i]);
		}
		printf("\n");
		if(temporaneo->power_curves != NULL){
			for(int i = 0; i < (NUMERO_COLONNE_POWER_COEFFICIENT - 1); i++)
				printf(" Potenze: %d\t", temporaneo->power_curves[i]);
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
	
	//lettura struttura altezzehead_turbina=estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore==CSV_E_IO)
    {
        return(EXIT_FAILURE);
    }
    // fine generazione lista

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
