#include "../include/main.h"

int main(int argc, char *argv[])
{
    struct turbina *head_turbina=NULL;
    struct turbina *turbina_cercata=NULL;
    struct dati_weather *dati = NULL;
    int errore=0;
    float array_vento_power_coefficient=0;
    float array_vento_power_curves=0;

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
    lettura_file_power_coefficient(head_turbina, PERCORSO_POWER_COEFFICIENT, &errore, &array_vento_power_coefficient);
    lettura_file_power_curves(head_turbina, PERCORSO_POWER_CURVES, &errore, &array_vento_power_curves);
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
    
    metodo_calcolo_parametri->vento=argv[2]; //CONTROLLO PER VERIFICARE SE ESISTONO QUESTE STRINGHE?
    metodo_calcolo_parametri->temperatura=argv[3];
    metodo_calcolo_parametri->densita=argv[4];

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
        struct parametro *head_parametri;
        float altezza_ostacolo=0;

        parametri = malloc(sizeof(struct parametro));
        if (parametri == NULL) {
            printf("Error: malloc() failed in insert()\n");
            exit(EXIT_FAILURE);
        }
    
        altezza_ostacolo=atof(argv[7]);
        parametri=calcolo_parametri(dati, metodo_calcolo_parametri, altezza_ostacolo, turbina_cercata->altezza_mozzo, head_parametri);
        //fine calcolo parametri

        float potenza_in_uscita=0;

        if(strcmp(argv[5], "CURVE_DI_POTENZA")==0)
        {
            potenza_in_uscita=calcolo_potenza_curve_di_potenza(argv[6], argv[1], turbina_cercata, turbina_cercata->altezza_mozzo, parametri->vento, array_vento_power_curves);
        }
        if(strcmp(argv[5], "CURVE_DI_COEFFICIENTI_POTENZA")==0)
        {
            potenza_in_uscita=calcolo_potenza_curve_coefficienti(argv[6], argv[1], turbina_cercata, turbina_cercata->altezza_mozzo, parametri->vento, parametri->densita, array_vento_power_coefficient);
        }
        else
        {
            printf("L'argomento inserito non è corretto. La sintassi corretta è riportata nel file app/include/main.h");
            exit(EXIT_FAILURE);
        }
    }

    svuota_lista_turbine_data(head_turbina);
    svuota_dati_weather(dati);

    return 0;
}

//RICODATI DI DEALLOCARE LA MEMORIA!!!!!!
