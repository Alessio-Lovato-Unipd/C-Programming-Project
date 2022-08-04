#include "../include/main.h"

int main(int argc, char *argv[])
{
    struct turbina *head_turbina=NULL;
    struct turbina *turbina_cercata=NULL;
    struct dati_weather *dati = NULL;
    int errore=0;
    float array_vento_power_coefficient[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1]={0};
    float array_vento_power_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1]={0};

    if(argc != VALORE_ARGOMENTI_INSERIBILI)
    {
        printf("Errore nell'inserimento degli argomenti. La sintassi corretta è riportata nel file app/include/main.h\n");
        return(EXIT_FAILURE);
    }   

    //inizio generazione lista turbine tramite la lettura da file
    head_turbina=estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore!=CSV_OK)
    {
        return(EXIT_FAILURE);
    }
    controllo_csv(&errore);
    lettura_file_power_coefficient(head_turbina, PERCORSO_POWER_COEFFICIENT, &errore, array_vento_power_coefficient);
    lettura_file_power_curves(head_turbina, PERCORSO_POWER_CURVES, &errore, array_vento_power_curves);
    //fine generazione lista

    //inizio generazione lista dati meteorologici tramite la lettura da file
    struct csv file;
    char** fields=NULL;

    dati = apertura_file_weather(&file, fields, dati, PERCORSO_WEATHER, &errore);
    dati=estrazione_dati_weather(dati, PERCORSO_WEATHER, &errore);
    if (errore!=CSV_OK)
    {
        return(EXIT_FAILURE);
    }
    controllo_csv(&errore);
    //fine generazione lista

    //salvataggio degli argomenti necessari alla determinazione del metodo per calcolare la velocità del vento, la temperatura e la densità dell'aria
    struct tipo_metodo *metodo_calcolo_parametri=NULL;

    metodo_calcolo_parametri = malloc(sizeof(struct tipo_metodo));
    if (metodo_calcolo_parametri == NULL) {
        printf("Error: malloc() failed in insert()\n");
        exit(EXIT_FAILURE);
    }
    //salvataggio di argv[2] nella variabile vento 
    if(strcmp("INTERPOLAZIONE_LINEARE_V", argv[2])==0)
        metodo_calcolo_parametri->vento=INTERPOLAZIONE_LINEARE_V;
    if(strcmp("INTERPOLAZIONE_LOGARITMICA", argv[2])==0)
        metodo_calcolo_parametri->vento=INTERPOLAZIONE_LOGARITMICA;
    if(strcmp("PROFILO_LOGARITMICO", argv[2])==0)
        metodo_calcolo_parametri->vento=PROFILO_LOGARITMICO;
    if(strcmp("HELLMAN", argv[2])==0)
        metodo_calcolo_parametri->vento=HELLMAN;
    else
    {
        printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
        exit(EXIT_FAILURE);
    }

    //salvataggio di argv[3] nella variabile temperatura
    if(strcmp("INTERPOLAZIONE_LINEARE_T", argv[3])==0)
        metodo_calcolo_parametri->temperatura=INTERPOLAZIONE_LINEARE_T;
    if(strcmp("GRADIENTE_LINEARE", argv[3])==0)
        metodo_calcolo_parametri->temperatura=GRADIENTE_LINEARE;
    else
    {
        printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
        exit(EXIT_FAILURE);
    }

    //salvataggio di argv[4] nella variabile densita 
    if(strcmp("BAROMETRICO", argv[4])==0)
        metodo_calcolo_parametri->densita=BAROMETRICO;
    if(strcmp("GAS_IDEALE", argv[4])==0)
        metodo_calcolo_parametri->densita=GAS_IDEALE;
    else
    {
        printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
        exit(EXIT_FAILURE);
    }

    //ricerca della turbina richiesta
    turbina_cercata = cerca_dati_turbina("argv[1]", 0.0, head_turbina); 
    if (turbina_cercata == NULL)
    {
        printf("Modello turbina non trovato!\n\n\n");
    }else
    {
        //cose da fare se la turbina esiste

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
        //fine calcolo parametri

        //salvataggio di argv[6]
        tipo_calcolo_output var_argv6;
        if(strcmp("INTERPOLAZIONE_LINEARE_O", argv[6])==0)
            var_argv6=INTERPOLAZIONE_LINEARE_O;
        if(strcmp("INTERPOLAZIONE_LOGARITMICA_O", argv[6])==0)
            var_argv6=INTERPOLAZIONE_LOGARITMICA_O;
        else
        {
            printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
            exit(EXIT_FAILURE);
        }

        float potenza_in_uscita=0;

        if(strcmp(argv[5], "CURVE_DI_POTENZA")==0)
        {
            potenza_in_uscita=calcolo_potenza_curve_di_potenza(var_argv6, argv[1], turbina_cercata, turbina_cercata->altezza_mozzo, parametri->vento, array_vento_power_curves);
        }
        if(strcmp(argv[5], "CURVE_DI_COEFFICIENTI_POTENZA")==0)
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
