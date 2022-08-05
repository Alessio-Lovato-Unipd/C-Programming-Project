#include "../include/main.h"

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
        printf("Errore nell'inserimento degli argomenti. La sintassi corretta è riportata nel file app/include/main.h\n");
        return(EXIT_FAILURE);
    }   

    //inizio generazione lista turbine tramite la lettura da file
    printf("Codice partito.\n");
    head_turbina=estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore!=CSV_END)
    {
        return(EXIT_FAILURE);
    }
    printf("fine estrazione.\n");

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

    printf("Lettura power_curves iniziata.\n");
    lettura_file_power_coefficient(head_turbina, PERCORSO_POWER_COEFFICIENT, &errore, array_vento_power_coefficient);
    lettura_file_power_curves(head_turbina, PERCORSO_POWER_CURVES, &errore, array_vento_power_curves);
    //fine generazione lista

    //inizio generazione lista dati meteorologici tramite la lettura da file
    printf("Inizio salvataggio weather.\n");
    struct csv file;
    char** fields=NULL;

    dati = apertura_file_weather(&file, fields, dati, PERCORSO_WEATHER, &errore);
    dati=estrazione_dati_weather(dati, PERCORSO_WEATHER, &errore);
    if (errore!=CSV_END)
    {
        return(EXIT_FAILURE);
    }

    printf("Fine salvataggio weather.\n");
    //fine generazione lista


    //salvataggio degli argomenti necessari alla determinazione del metodo per calcolare la velocità del vento, la temperatura e la densità dell'aria
    printf("salvataggio argomenti per tipo calcolo.\n");
    struct tipo_metodo *metodo_calcolo_parametri=NULL;

    metodo_calcolo_parametri = malloc(sizeof(struct tipo_metodo));
    if (metodo_calcolo_parametri == NULL) {
        printf("Error: malloc() failed in insert()\n");
        exit(EXIT_FAILURE);
    }

    //inizializzazione struttura metodo_calcolo_parametri
    metodo_calcolo_parametri->vento=INTERPOLAZIONE_LINEARE_V;
    metodo_calcolo_parametri->temperatura=INTERPOLAZIONE_LINEARE_T;
    metodo_calcolo_parametri->densita=BAROMETRICO;

    printf("Valore argv[2]:%s\n", argv[2]);
    printf("Valore argv[3]:%s\n", argv[3]);
    printf("Valore argv[4]:%s\n", argv[4]);

    //salvataggio di argv[2] nella variabile vento 
    if(strcmp("INTERPOLAZIONE_LINEARE_V", argv[2])==0)
        metodo_calcolo_parametri->vento=INTERPOLAZIONE_LINEARE_V;
    else if(strcmp("INTERPOLAZIONE_LOGARITMICA", argv[2])==0)
        metodo_calcolo_parametri->vento=INTERPOLAZIONE_LOGARITMICA;
    else if(strcmp("PROFILO_LOGARITMICO", argv[2])==0)
        metodo_calcolo_parametri->vento=PROFILO_LOGARITMICO;
    else if(strcmp("HELLMAN", argv[2])==0)
        metodo_calcolo_parametri->vento=HELLMAN;
    else
    {
        printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
        exit(EXIT_FAILURE);
    }
    
    //salvataggio di argv[3] nella variabile temperatura
    if(strcmp("INTERPOLAZIONE_LINEARE_T", argv[3])==0)
        metodo_calcolo_parametri->temperatura=INTERPOLAZIONE_LINEARE_T;
    else if(strcmp("GRADIENTE_LINEARE", argv[3])==0)
        metodo_calcolo_parametri->temperatura=GRADIENTE_LINEARE;
    else
    {
        printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
        exit(EXIT_FAILURE);
    }

    //salvataggio di argv[4] nella variabile densita 
    if(strcmp("BAROMETRICO", argv[4])==0)
        metodo_calcolo_parametri->densita=BAROMETRICO;
    else if(strcmp("GAS_IDEALE", argv[4])==0)
        metodo_calcolo_parametri->densita=GAS_IDEALE;
    else
    {
        printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
        exit(EXIT_FAILURE);
    } 

    printf("Valore vento :%u\n", metodo_calcolo_parametri->vento);
    printf("Valore temperatura:%u\n", metodo_calcolo_parametri->temperatura);
    printf("Valore densita :%u\n", metodo_calcolo_parametri->densita);
    printf("fine salvataggio argomenti.\n");
    

    //ricerca della turbina richiesta
    printf("ricerca turbina.\n");
    turbina_cercata = cerca_dati_turbina(argv[1], 0.0, head_turbina); 
    if (turbina_cercata == NULL)
    {
        printf("Modello turbina non trovato!\n\n\n");
    }else
    {
        //cose da fare se la turbina esiste
        printf("Modello turbina trovato!\n\n\n");

        
        //calcolo dei parametri a partire dai dati meteorologici
        struct parametro *parametri=NULL;
        struct parametro *head_parametri=NULL;
        float altezza_ostacolo=0;

        parametri = malloc(sizeof(struct parametro));
        if (parametri == NULL) {
            printf("Error: malloc() failed in insert()\n");
            exit(EXIT_FAILURE);
        }
    
        altezza_ostacolo=atof(argv[7]);
        parametri=calcolo_parametri(dati, metodo_calcolo_parametri, altezza_ostacolo, turbina_cercata->altezza_mozzo, head_parametri);
        printf("Altezza ostacolo: %f\n", altezza_ostacolo);
        printf("Vento parametri: %f\n", parametri->vento);
        printf("Densità aria parametri: %f\n", parametri->densita_aria);
        //fine calcolo parametri

        //salvataggio di argv[6]
        printf("argv[6]: %s\n", argv[6]);
        tipo_calcolo_output var_argv6=INTERPOLAZIONE_LINEARE_O;
        if(strcmp("INTERPOLAZIONE_LINEARE_O", argv[6])==0)
            var_argv6=INTERPOLAZIONE_LINEARE_O;
        else if(strcmp("INTERPOLAZIONE_LOGARITMICA_O", argv[6])==0)
            var_argv6=INTERPOLAZIONE_LOGARITMICA_O;
        else
        {
            printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
            exit(EXIT_FAILURE);
        }
        printf("var_argv6: %u\n", var_argv6);


        float potenza_in_uscita=0;

        if(strcmp(argv[5], "CURVE_DI_POTENZA")==0 && turbina_cercata->bool_p_curves)
        {
            potenza_in_uscita=calcolo_potenza_curve_di_potenza(var_argv6, argv[1], turbina_cercata, turbina_cercata->altezza_mozzo, parametri->vento, array_vento_power_curves);
        }
        else if(strcmp(argv[5], "CURVE_DI_COEFFICIENTI_POTENZA")==0 && turbina_cercata->bool_p_coefficient)
        {
            potenza_in_uscita=calcolo_potenza_curve_coefficienti(var_argv6, argv[1], turbina_cercata, turbina_cercata->altezza_mozzo, parametri->vento, parametri->densita_aria, array_vento_power_coefficient);
        }
        else
        {
            printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
            exit(EXIT_FAILURE);
        }

        printf("Otteniamo: %f\n", potenza_in_uscita); 
    }

    svuota_lista_turbine_data(head_turbina);
    svuota_dati_weather(dati);

    return 0;
}

//RICODATI DI DEALLOCARE LA MEMORIA!!!!!!
