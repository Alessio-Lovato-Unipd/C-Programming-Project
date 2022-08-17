#include "potenze.h"

int main(int argc, char *argv[])
{
    struct turbina *head_turbina=NULL;
    struct turbina *turbina_cercata=NULL;
    struct dati_weather *dati = NULL;
    int errore=0;
    float array_vento_power_coefficient[LUNGHEZZA_VETTORE_POWER_COEFFICIENT + 1] = {0};
    float array_vento_power_curves[LUNGHEZZA_VETTORE_POWER_CURVES + 1] = {0};

    if (argc != VALORE_ARGOMENTI_INSERIBILI) {
        printf("\nErrore nell'inserimento degli argomenti. La sintassi corretta è:\n");
        printf("\t- argv[1] ---> nomi turbine desiderate, da inserire tra virgolette e divise da ',' senza spazi\n");
        printf("\t- argv[2] ---> {INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN}, per il calcolo della velocità del vento\n");
        printf("\t- argv[3] ---> {INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE}, per il calcolo della temperatura\n");
        printf("\t- argv[4] ---> {BAROMETRICO, GAS_IDEALE}, per il calcolo della densità dell'aria\n");
        printf("\t- argv[5] ---> {CURVE_DI_POTENZA, CURVE_DI_COEFFICIENTI_POTENZA}, per la scelta se usare le curve di coefficienti di potenza oppure le curve di potenza\n");
        printf("\t- argv[6] ---> {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O}, per la scelta del tipo di interpolazione da utilizzare per il calcolo dell'output\n");
        printf("\t- argv[7] ---> valore di altezza_ostacolo (in metri), mettere 0 se si pensa di non utilizzare PROFILO_LOGARITMICO in argv[2]\n");
        printf("\t- argv[8] ---> altezza del mozzo considerata, inserire 0 per selezione automatica\n");
        printf("\t- argv[9] ---> data e orario di inizio analisi dati, inserire tra gli apici \n\n");
        
        return(EXIT_FAILURE);
    }   

    //stampa a schermo degli argomenti inseriti dall'utente
    printf("\n\nTurbine scelte: %s\n\n", argv[1]);
    printf("Output di potenza ottenuto come: %s\n\n", argv[5]);
    printf("Metodo per il calcolo del vento impostato su %s\n", argv[2]);
    printf("Metodo per il calcolo della temperatura impostato su %s\n", argv[3]);
    printf("Metodo per il calcolo della densità dell'aria impostato su %s\n", argv[4]);
    printf("Metodo di interpolazione per il calcolo dell'output: %s\n", argv[6]);
    printf("Altezza ostacolo impostata a: %s metri\n", argv[7]);
    printf("Altezza del mozzo: %s\n", argv[8]);
    printf("Orario di partenza scelto: %s\n\n", argv[9]);

    //estrazione dei nomi delle turbine da argomento
    int conteggio = conteggio_turbine(argv[1]);

    char *array_turbine[conteggio];

    estrazione_nome_turbine(argv[1], array_turbine);
    if((conteggio == 0)) {
        printf("Errore: numero turbine insufficiente per la creazione di un parco.\n\n");
        return(EXIT_FAILURE);
    }
    //fine estrazione nomi

    //inizio generazione lista turbine tramite la lettura da file
    head_turbina = estrazione_dati_turbine(head_turbina, PERCORSO_TURBINE_DATA, &errore);
    if (errore != CSV_END)
        return(EXIT_FAILURE);

    lettura_file_power_coefficient(head_turbina, PERCORSO_POWER_COEFFICIENT, &errore, array_vento_power_coefficient);
    lettura_file_power_curves(head_turbina, PERCORSO_POWER_CURVES, &errore, array_vento_power_curves);
    //fine generazione lista

    //inizio generazione lista dati meteorologici tramite la lettura da file
    dati = estrazione_dati_weather(dati, PERCORSO_WEATHER, &errore);
    if (errore != CSV_END) {
        svuota_lista_turbine_data(head_turbina);
        return(EXIT_FAILURE);
    }
    //fine generazione lista

    //salvataggio degli argomenti necessari alla determinazione del metodo per calcolare la velocità del vento, la temperatura e la densità dell'aria
    struct tipo_metodo *metodo_calcolo_parametri = NULL;

    metodo_calcolo_parametri = malloc(sizeof(struct tipo_metodo));
    if (metodo_calcolo_parametri == NULL) {
        printf("Errore: malloc() ha fallito in metodo calcolo parametri\n");
        svuota_dati_weather(dati);
        svuota_lista_turbine_data(head_turbina);
        exit(EXIT_FAILURE);
    }

    //inizializzazione struttura metodo_calcolo_parametri
    metodo_calcolo_parametri->vento = INTERPOLAZIONE_LINEARE_V;
    metodo_calcolo_parametri->temperatura = INTERPOLAZIONE_LINEARE_T;
    metodo_calcolo_parametri->densita = BAROMETRICO;

    //salvataggio di argv[2] nella variabile vento 
    if (strcmp("INTERPOLAZIONE_LINEARE_V", argv[2]) == 0)
        metodo_calcolo_parametri->vento = INTERPOLAZIONE_LINEARE_V;
    else if (strcmp("INTERPOLAZIONE_LOGARITMICA", argv[2]) == 0)
        metodo_calcolo_parametri->vento = INTERPOLAZIONE_LOGARITMICA;
    else if (strcmp("PROFILO_LOGARITMICO", argv[2]) == 0)
        metodo_calcolo_parametri->vento = PROFILO_LOGARITMICO;
    else if (strcmp("HELLMAN", argv[2]) == 0)
        metodo_calcolo_parametri->vento = HELLMAN;
    else {
        printf("\nL'argomento inserito in argv[2] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN\n\n");
        free(metodo_calcolo_parametri);
        svuota_dati_weather(dati);
        svuota_lista_turbine_data(head_turbina);
        exit(EXIT_FAILURE);
    }
    
    //salvataggio di argv[3] nella variabile temperatura
    if (strcmp("INTERPOLAZIONE_LINEARE_T", argv[3]) == 0)
        metodo_calcolo_parametri->temperatura = INTERPOLAZIONE_LINEARE_T;
    else if (strcmp("GRADIENTE_LINEARE", argv[3]) == 0)
        metodo_calcolo_parametri->temperatura = GRADIENTE_LINEARE;
    else {
        printf("\nL'argomento inserito in argv[3] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE\n\n");
        free(metodo_calcolo_parametri);
        svuota_dati_weather(dati);
        svuota_lista_turbine_data(head_turbina);
        exit(EXIT_FAILURE);
    }

    //salvataggio di argv[4] nella variabile densita 
    if (strcmp("BAROMETRICO", argv[4]) == 0)
        metodo_calcolo_parametri->densita = BAROMETRICO;
    else if (strcmp("GAS_IDEALE", argv[4]) == 0)
        metodo_calcolo_parametri->densita = GAS_IDEALE;
    else {
        printf("\nL'argomento inserito in argv[4] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: BAROMETRICO, GAS_IDEALE\n\n");
        free(metodo_calcolo_parametri);
        svuota_dati_weather(dati);
        svuota_lista_turbine_data(head_turbina);
        exit(EXIT_FAILURE);
    }
    
    //ricerca della turbina richiesta
    struct parametro *temp_parametri = NULL;
    struct parametro *head_parametri = NULL;
    float array_potenza_istantanea_totale[NUMERO_ORE_IN_UN_GIORNO] = {0};
    int count_turbine = 1;
    char str[20];

    //salvataggio di argv[6]
    tipo_calcolo_output var_argv6=INTERPOLAZIONE_LINEARE_O;
    if (strcmp("INTERPOLAZIONE_LINEARE_O", argv[6]) == 0)
        var_argv6=INTERPOLAZIONE_LINEARE_O;
    else if (strcmp("INTERPOLAZIONE_LOGARITMICA_O", argv[6]) == 0)
        var_argv6=INTERPOLAZIONE_LOGARITMICA_O;
    else {
        printf("\nL'argomento inserito in argv[6] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O\n\n");
        svuota_parametri(head_parametri);
        free(metodo_calcolo_parametri);
        svuota_dati_weather(dati);
        svuota_lista_turbine_data(head_turbina);
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<conteggio;i++) { //ciclo for, scorre tutte le turbine del parco eolico
        //char str[20];
        
        strcpy(str, array_turbine[i]);

        if (isanumber(argv[8]) && (atof(argv[8]) >= 0)) {
            float altezza_mozzo = atof(argv[8]);
            turbina_cercata = cerca_dati_turbina(array_turbine[i], altezza_mozzo, head_turbina);
        } else {
            printf("\nL'argomento inserito in argv[8] non è corretto.\nInserire un valore numerico >= 0\n");
            svuota_dati_weather(dati);
            svuota_lista_turbine_data(head_turbina);
            free(metodo_calcolo_parametri);
            exit(EXIT_FAILURE);
        }
    
        printf("%d° turbina cercata: %s\n", count_turbine, turbina_cercata->nome);
        if (turbina_cercata == NULL) {
            printf("ESITO RICERCA TURBINA: Modello turbina non trovato!\n\n");
        } else {
            printf("ESITO RICERCA TURBINA: Modello turbina trovato!\n\n");

            //calcolo dei parametri a partire dai dati meteorologici
            if (isanumber(argv[7]) && (atof(argv[7]) >= 0)) {
                float altezza_ostacolo = atof(argv[7]);
                head_parametri = calcolo_parametri(dati, metodo_calcolo_parametri, altezza_ostacolo, turbina_cercata->altezza_mozzo, head_parametri);
                if (head_parametri == NULL) {
                    svuota_dati_weather(dati);
                    svuota_lista_turbine_data(head_turbina);
                    free(metodo_calcolo_parametri);
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("\nL'argomento in argv[7] non è corretto.\n Bisogna inserire un numero dell'altezza dell'ostacolo >= 0\n");
                svuota_dati_weather(dati);
                svuota_lista_turbine_data(head_turbina);
                free(metodo_calcolo_parametri);
                exit(EXIT_FAILURE);
            }
            //fine calcolo parametri

            float potenza_istantanea_singola=0;
            float *potenza = NULL;

            temp_parametri = cerca_nodo_parametri(argv[9], head_parametri);
            if (temp_parametri == NULL) {
                printf("Data e orario inseriti errati, fare riferimento al file weather.csv o verificare di aver utilizzato gli apici come nell'esempio sottostante:\n");
                printf("\'2010-06-05 06:00:00+01:00\'\n\n");
                free(potenza);
                svuota_parametri(head_parametri);
                free(metodo_calcolo_parametri);
                svuota_dati_weather(dati);
                svuota_lista_turbine_data(head_turbina);
                exit(EXIT_FAILURE);
            }
            printf("RISULTATI:\n");
            printf("Potenze o velocità del vento pari a -1 indicano un errore in fase di interpolazione\n\n");
        
            if (strcmp(argv[5], "CURVE_DI_POTENZA")==0 && turbina_cercata->bool_p_curves) {
                potenza = calcolo_potenza(CURVA_POTENZA, var_argv6, str, turbina_cercata, turbina_cercata->altezza_mozzo, array_vento_power_curves, head_parametri);
                if (potenza == NULL) {
                    svuota_parametri(head_parametri);
                    free(metodo_calcolo_parametri);
                    svuota_dati_weather(dati);
                    svuota_lista_turbine_data(head_turbina);
                    exit(EXIT_FAILURE);
                }

                for (int i = 0; (i < NUMERO_ORE_IN_UN_GIORNO && temp_parametri != NULL); i++) {
                    potenza_istantanea_singola=calcolo_potenza_curve_di_potenza(var_argv6, str, turbina_cercata, turbina_cercata->altezza_mozzo, temp_parametri->vento, array_vento_power_curves);
                    printf("\tOrario misure: %s\n", temp_parametri->orario);
                    printf("\tPotenza in uscita: %f\n", potenza_istantanea_singola);
                    printf("\tVelocità del vento: %f\n", temp_parametri->vento);
                    printf("\tDensità dell'aria: %f\n\n", temp_parametri->densita_aria);
                    array_potenza_istantanea_totale[i] = array_potenza_istantanea_totale[i] + potenza_istantanea_singola;
                    temp_parametri = temp_parametri->next;
                }
                if (plot_curva_potenza(array_vento_power_curves, turbina_cercata, count_turbine) == EXIT_FAILURE) {
                    printf("\nNon è stato possibile stampare la curva dei coefficienti\n");
                    free(potenza);
                    svuota_parametri(head_parametri);
                    free(metodo_calcolo_parametri);
                    svuota_dati_weather(dati);
                    svuota_lista_turbine_data(head_turbina);
                    exit(EXIT_FAILURE);
                } else if (plot_potenza(dati->head_weather, turbina_cercata->nome, potenza, 1, count_turbine) == EXIT_FAILURE) {
                    printf("\nNon è stato possibile stampare il grafico della potenza\n");
                    free(potenza);
                    svuota_parametri(head_parametri);
                    free(metodo_calcolo_parametri);
                    svuota_dati_weather(dati);
                    svuota_lista_turbine_data(head_turbina);
                    exit(EXIT_FAILURE);
                } else {
                    printf("\nNOTA: curva_di_potenza_%d.png disponibile in build/app\n", count_turbine);
                    printf("NOTA: potenza_%d.png disponibile in build/app\n\n\n", count_turbine);
                    free(potenza);
                }
            } else if (strcmp(argv[5], "CURVE_DI_COEFFICIENTI_POTENZA")==0 && turbina_cercata->bool_p_coefficient) {
                potenza= calcolo_potenza(CURVA_COEFFICIENTI_POTENZA, var_argv6, str, turbina_cercata, turbina_cercata->altezza_mozzo, array_vento_power_coefficient, head_parametri);
                if (potenza == NULL) {
                    svuota_parametri(head_parametri);
                    free(metodo_calcolo_parametri);
                    svuota_dati_weather(dati);
                    svuota_lista_turbine_data(head_turbina);
                    exit(EXIT_FAILURE);
                }

                for( int i = 0; (i < NUMERO_ORE_IN_UN_GIORNO && temp_parametri != NULL); i++) {
                    potenza_istantanea_singola=calcolo_potenza_curve_coefficienti(var_argv6, str, turbina_cercata, turbina_cercata->altezza_mozzo, temp_parametri->vento, temp_parametri->densita_aria, array_vento_power_coefficient);
                    printf("\tOrario misure: %s\n", temp_parametri->orario);
                    printf("\tPotenza in uscita: %f\n", potenza_istantanea_singola);
                    printf("\tVelocità del vento: %f\n", temp_parametri->vento);
                    printf("\tDensità dell'aria: %f\n\n", temp_parametri->densita_aria); 
                    array_potenza_istantanea_totale[i] = array_potenza_istantanea_totale[i] + potenza_istantanea_singola;
                    temp_parametri = temp_parametri->next;
                }
                if (plot_curva_coefficienti(array_vento_power_coefficient, turbina_cercata, count_turbine) == EXIT_FAILURE) {
                    printf("\nNon è stato possibile stampare la curva dei coefficienti\n");
                    free(potenza);
                    svuota_parametri(head_parametri);
                    free(metodo_calcolo_parametri);
                    svuota_dati_weather(dati);
                    svuota_lista_turbine_data(head_turbina);
                    exit(EXIT_FAILURE);
                } else if (plot_potenza(dati->head_weather, turbina_cercata->nome, potenza, 1, count_turbine) == EXIT_FAILURE) {
                    printf("\nNon è stato possibile stampare il grafico della potenza\n");
                    free(potenza);
                    svuota_parametri(head_parametri);
                    free(metodo_calcolo_parametri);
                    svuota_dati_weather(dati);
                    svuota_lista_turbine_data(head_turbina);
                    exit(EXIT_FAILURE);
                } else {
                    printf("\nNOTA: curva_coefficienti_di_potenza_%d.png disponibile in build/app\n", count_turbine);
                    printf("NOTA: potenza_%d.png disponibile in build/app\n\n\n", count_turbine);
                    free(potenza);
                    svuota_parametri(head_parametri);
                }
            } else {
                printf("\nL'argomento inserito in argv[5] non è corretto.\nIn questo campo è possibile inserire una delle seguenti voci: CURVE_DI_POTENZA, CURVE_DI_COEFFICIENTI_POTENZA\n");
                printf("Se l'errore persiste, controllare se la turbina cercata possiede le informazioni relative al tipo di curva voluta.\n");
                free(potenza);
                svuota_parametri(head_parametri);
                free(metodo_calcolo_parametri);
                svuota_dati_weather(dati);
                svuota_lista_turbine_data(head_turbina);
                exit(EXIT_FAILURE);
            }
            
            count_turbine++;
        }
    } //fine del ciclo for

    //ciclo for necessario a stampare a schermo la potenza totale del parco eolico
    printf("POTENZA ISTANTANEA TOTALE DEL PARCO EOLICO PER OGNI ORA DEL GIORNO:\n\n");
    for (int i = 0; (i < NUMERO_ORE_IN_UN_GIORNO && temp_parametri != NULL); i++) {
        printf("\tOrario misure: %s\n", temp_parametri->orario);
        printf("\tPotenza in uscita: %f\n\n", array_potenza_istantanea_totale[i]);
        temp_parametri = temp_parametri->next;
    }

    if(plot_potenza_parco_eolico(dati->head_weather, array_potenza_istantanea_totale, 1) == EXIT_FAILURE) {
        printf("Non è stato possibile stampare il grafico della potenza per il parco eolico.\n");
    }
    else{
        printf("NOTA: potenza.png relativa al parco eolico disponibile in build/app\n\n\n");
    }

    svuota_lista_turbine_data(head_turbina);
    svuota_dati_weather(dati);
    free(metodo_calcolo_parametri);
    svuota_parametri(head_parametri);

    return 0;
}



bool isanumber(const char *str)
{
    for (int i = 0; str[i]!= '\0'; i++)
    {
        if (isdigit(str[i]) == 0)
              return false;
    }
    return true;
}
