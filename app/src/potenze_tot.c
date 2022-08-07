#include "potenze_tot.h"

int main(int argc, char *argv[])
{
    struct turbina *head_turbina=NULL;
    //struct turbina *temporaneo=NULL; //<----da eliminare
    struct turbina *turbina_cercata=NULL;
    struct dati_weather *dati = NULL;
    int errore=0;
    float array_vento_power_coefficient[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1]={0};
    float array_vento_power_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1]={0};
    //bool penultimo=false; //<---da eliminare
    //bool ultimo=false; //<---da eliminare

    if(argc != VALORE_ARGOMENTI_INSERIBILI)
    {
        printf("\nErrore nell'inserimento degli argomenti. La sintassi corretta è:\n");
        printf("\t- argv[1] ---> nome turbina desiderata\n");
        printf("\t- argv[2] ---> {INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN}, per il calcolo della velocità del vento\n");
        printf("\t- argv[3] ---> {INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE}, per il calcolo della temperatura\n");
        printf("\t- argv[4] ---> {BAROMETRICO, GAS_IDEALE}, per il calcolo della densità dell'aria\n");
        printf("\t- argv[5] ---> {CURVE_DI_POTENZA, CURVE_DI_COEFFICIENTI_POTENZA}, per la scelta se usare le curve di coefficienti di potenza oppure le curve di potenza\n");
        printf("\t- argv[6] ---> {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O}, per la scelta del tipo di interpolazione da utilizzare per il calcolo dell'output\n");
        printf("\t- argv[7] ---> valore di altezza_ostacolo (in metri), mettere 0 se si pensa di non utilizzare PROFILO_LOGARITMICO in argv[2]\n");
		printf("\t- argv[8] ---> altezza del mozzo considerata, inserire 0 per selezione automatica\n\n");
		//printf("\t- argv[9] ---> stringa di data e ora di partenza per l'analisi dei dati considerati\n");
		
        return(EXIT_FAILURE);
    }   

    //stampa a schermo degli argomenti inseriti dall'utente
    printf("\n\nTurbina scelta: %s\n\n", argv[1]);
    printf("Output di potenza ottenuto come: %s\n\n", argv[5]);
    printf("Metodo per il calcolo del vento impostato su %s\n", argv[2]);
    printf("Metodo per il calcolo della temperatura impostato su %s\n", argv[3]);
    printf("Metodo per il calcolo della densità dell'aria impostato su %s\n", argv[4]);
    printf("Metodo di interpolazione per il calcolo dell'output: %s\n", argv[6]);
    printf("Altezza ostacolo impostata a: %s metri\n", argv[7]);
	printf("Altezza del mozzo: %s\n", argv[8]);
	//printf("Orario di partenza scelto: %s\n", argv[9]);
	

    //inizio generazione lista turbine tramite la lettura da file
    head_turbina = estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore != CSV_END)
    {
        return(EXIT_FAILURE);
    }

    /*temporaneo=head_turbina; <-----------------------------------per verificare il corretto salvataggio di tutte le turbine, OK
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
        for(int i = 0; i < (NUMERO_COLONNE_POWER_COEFFICIENT_CURVES- 1); i++)
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
    }*/
    //fine esempio di stampa

    lettura_file_power_coefficient(head_turbina, PERCORSO_POWER_COEFFICIENT, &errore, array_vento_power_coefficient);
    lettura_file_power_curves(head_turbina, PERCORSO_POWER_CURVES, &errore, array_vento_power_curves);
    //fine generazione lista

    //inizio generazione lista dati meteorologici tramite la lettura da file
    dati = estrazione_dati_weather(dati, PERCORSO_WEATHER, &errore);
    if (errore != CSV_END)
    {
        svuota_lista_turbine_data(head_turbina);
        return(EXIT_FAILURE);
    }
    //fine generazione lista

    //salvataggio degli argomenti necessari alla determinazione del metodo per calcolare la velocità del vento, la temperatura e la densità dell'aria
    struct tipo_metodo *metodo_calcolo_parametri = NULL;

    metodo_calcolo_parametri = malloc(sizeof(struct tipo_metodo));
    if (metodo_calcolo_parametri == NULL) {
        printf("Error: malloc() failed in insert()\n");
		svuota_dati_weather(dati);
		svuota_lista_turbine_data(head_turbina);
        exit(EXIT_FAILURE);
    }

    //inizializzazione struttura metodo_calcolo_parametri
    metodo_calcolo_parametri->vento = INTERPOLAZIONE_LINEARE_V;
    metodo_calcolo_parametri->temperatura = INTERPOLAZIONE_LINEARE_T;
    metodo_calcolo_parametri->densita = BAROMETRICO;

    //salvataggio di argv[2] nella variabile vento 
    if(strcmp("INTERPOLAZIONE_LINEARE_V", argv[2]) == 0)
        metodo_calcolo_parametri->vento = INTERPOLAZIONE_LINEARE_V;
    else if(strcmp("INTERPOLAZIONE_LOGARITMICA", argv[2]) == 0)
        metodo_calcolo_parametri->vento = INTERPOLAZIONE_LOGARITMICA;
    else if(strcmp("PROFILO_LOGARITMICO", argv[2]) == 0)
        metodo_calcolo_parametri->vento = PROFILO_LOGARITMICO;
    else if(strcmp("HELLMAN", argv[2]) == 0)
        metodo_calcolo_parametri->vento = HELLMAN;
    else
    {
        printf("\nL'argomento inserito in argv[2] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN\n\n");
        svuota_dati_weather(dati);
		svuota_lista_turbine_data(head_turbina);
		free(metodo_calcolo_parametri);
		exit(EXIT_FAILURE);
    }
    
    //salvataggio di argv[3] nella variabile temperatura
    if(strcmp("INTERPOLAZIONE_LINEARE_T", argv[3]) == 0)
        metodo_calcolo_parametri->temperatura = INTERPOLAZIONE_LINEARE_T;
    else if(strcmp("GRADIENTE_LINEARE", argv[3]) == 0)
        metodo_calcolo_parametri->temperatura = GRADIENTE_LINEARE;
    else
    {
        printf("\nL'argomento inserito in argv[3] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE\n\n");
		svuota_dati_weather(dati);
		svuota_lista_turbine_data(head_turbina);
		free(metodo_calcolo_parametri);
        exit(EXIT_FAILURE);
    }

    //salvataggio di argv[4] nella variabile densita 
    if(strcmp("BAROMETRICO", argv[4]) == 0)
        metodo_calcolo_parametri->densita = BAROMETRICO;
    else if(strcmp("GAS_IDEALE", argv[4]) == 0)
        metodo_calcolo_parametri->densita = GAS_IDEALE;
    else
    {
        printf("\nL'argomento inserito in argv[4] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: BAROMETRICO, GAS_IDEALE\n\n");
		svuota_dati_weather(dati);
		svuota_lista_turbine_data(head_turbina);
		free(metodo_calcolo_parametri);
        exit(EXIT_FAILURE);
    } 

    //per stampare a schermo gli interi, è una verifica del corretto salvataggio degli argomenti
    /*
    printf("Valore vento :%u\n", metodo_calcolo_parametri->vento);
    printf("Valore temperatura:%u\n", metodo_calcolo_parametri->temperatura);
    printf("Valore densita :%u\n", metodo_calcolo_parametri->densita);
    printf("fine salvataggio argomenti.\n");
    */
    
    //ricerca della turbina richiesta
	float altezza_mozzo = atof(argv[8]);
    turbina_cercata = cerca_dati_turbina(argv[1], altezza_mozzo, head_turbina);
	struct parametro *temp_parametri = NULL;
    struct parametro *head_parametri = NULL;
	
    if (turbina_cercata == NULL)
    {
        printf("\nESITO RICERCA TURBINA: Modello turbina non trovato!\n\n");
    }else
    {
        //cose da fare se la turbina esiste
        printf("\nESITO RICERCA TURBINA: Modello turbina trovato!\n\n");

        //calcolo dei parametri a partire dai dati meteorologici
        float altezza_ostacolo=0;

        altezza_ostacolo=atof(argv[7]);
        head_parametri = calcolo_parametri(dati, metodo_calcolo_parametri, altezza_ostacolo, turbina_cercata->altezza_mozzo, head_parametri);
        if (head_parametri == NULL) {
            svuota_dati_weather(dati);
            svuota_lista_turbine_data(head_turbina);
            exit(EXIT_FAILURE);
        }
        //fine calcolo parametri

        //salvataggio di argv[6]
        tipo_calcolo_output var_argv6=INTERPOLAZIONE_LINEARE_O;
        if(strcmp("INTERPOLAZIONE_LINEARE_O", argv[6]) == 0)
            var_argv6=INTERPOLAZIONE_LINEARE_O;
        else if(strcmp("INTERPOLAZIONE_LOGARITMICA_O", argv[6]) == 0)
            var_argv6=INTERPOLAZIONE_LOGARITMICA_O;
        else
        {
            printf("\nL'argomento inserito in argv[6] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O\n\n");
			svuota_dati_weather(dati);
			svuota_lista_turbine_data(head_turbina);
			free(metodo_calcolo_parametri);
			svuota_parametri(head_parametri);
            exit(EXIT_FAILURE);
        }

        //per verificare il corretto salvataggio 
        /*
        printf("var_argv6: %u\n", var_argv6);
        */

        float potenza_in_uscita=0;
		temp_parametri = head_parametri;
		printf("RISULTATI:\n");
		printf("Potenze o velocità del vento pari a -1 indicano un errore in fase di interpolazione\n");
		
        if(strcmp(argv[5], "CURVE_DI_POTENZA")==0 && turbina_cercata->bool_p_curves)
        {
			while(temp_parametri != NULL){
				potenza_in_uscita=calcolo_potenza_curve_di_potenza(var_argv6, argv[1], turbina_cercata, turbina_cercata->altezza_mozzo, temp_parametri->vento, array_vento_power_curves);
				printf("\tPotenza in uscita: %f\n", potenza_in_uscita);
				printf("\tVelocità del vento: %f\n", temp_parametri->vento);
				printf("\tDensità dell'aria: %f\n\n\n", temp_parametri->densita_aria); 
				temp_parametri = temp_parametri->next;
			}
		}
        else if(strcmp(argv[5], "CURVE_DI_COEFFICIENTI_POTENZA")==0 && turbina_cercata->bool_p_coefficient)
        {
			while(temp_parametri != NULL){
				potenza_in_uscita=calcolo_potenza_curve_coefficienti(var_argv6, argv[1], turbina_cercata, turbina_cercata->altezza_mozzo, temp_parametri->vento, temp_parametri->densita_aria, array_vento_power_coefficient);
				printf("\tPotenza in uscita: %f\n", potenza_in_uscita);
				printf("\tVelocità del vento: %f\n", temp_parametri->vento);
				printf("\tDensità dell'aria: %f\n\n\n", temp_parametri->densita_aria); 
				temp_parametri = temp_parametri->next;
			}
		}
        else
        {
            printf("\nL'argomento inserito in argv[5] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: CURVE_DI_POTENZA, CURVE_DI_COEFFICIENTI_POTENZA\n");
            printf("Se l'errore persiste, controllare se la turbina cercata possiede le informazioni relative al tipo di curva voluta.\n");
			svuota_dati_weather(dati);
			svuota_lista_turbine_data(head_turbina);
			free(metodo_calcolo_parametri);
			svuota_parametri(head_parametri);
            exit(EXIT_FAILURE);
        }
    }

    svuota_lista_turbine_data(head_turbina);
    svuota_dati_weather(dati);
	free(metodo_calcolo_parametri);
	svuota_parametri(head_parametri);

    return 0;
}

//RICODATI DI DEALLOCARE LA MEMORIA!!!!!!
