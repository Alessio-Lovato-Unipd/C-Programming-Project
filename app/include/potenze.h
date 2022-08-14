#ifndef POTENZE_H

    #define POTENZE_H
    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <ctype.h>
    #include "estrattore_csv.h"
    #include "formule.h"
    #include "parametri.h"
    #include "calcolo_output.h"
    #include "plot.h"

    #define PERCORSO_TURBINE_DATA "../../data/turbine_data.csv"
    #define PERCORSO_WEATHER "../../data/weather.csv"
    #define PERCORSO_POWER_COEFFICIENT "../../data/power_coefficient_curves.csv"
	#define PERCORSO_POWER_CURVES "../../data/power_curves.csv"
    #define VALORE_ARGOMENTI_INSERIBILI 10
    #define NUMERO_ORE_IN_UN_GIORNO 24

    #define LUNGHEZZA_MASSIMA 12

    /*
    -----ARGOMENTI DA PASSARE AL PROGRAMMA MAIN-----
    Il programma main richiede 9 argomenti:
        - argv[0] ---> nome programma
        - argv[1] ---> nome turbina desiderata
        - argv[2] ---> {INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN}, per il calcolo della velocità del vento
        - argv[3] ---> {INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE}, per il calcolo della temperatura
        - argv[4] ---> {BAROMETRICO, GAS_IDEALE}, per il calcolo della densità dell'aria
        - argv[5] ---> {CURVE_DI_POTENZA, CURVE_DI_COEFFICIENTI_POTENZA}, per la scelta se usare le curve di coefficienti di potenza oppure le curve di potenza
        - argv[6] ---> {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O}, per la scelta del tipo di interpolazione da utilizzare per il calcolo dell'output
        - argv[7] ---> valore di altezza_ostacolo, mettere 0 se si pensa di non utilizzare PROFILO_LOGARITMICO in argv[2]
        - argv[8] ---> altezza del mozzo considerata

        Se eseguibile potenza_tot:
		    - argv[9] ---> numero giorni da visualizzare nel grafico di potenza generata

        Se eseguibile potenza_giorno:
		    - argv[9] ---> data e orario di inizio analisi dati, inserire tra le gli apici


        -----ESEMPI-----
        
        potenza_tot: ./potenza_tot E-126/7500 INTERPOLAZIONE_LINEARE_V INTERPOLAZIONE_LINEARE_T BAROMETRICO CURVE_DI_POTENZA INTERPOLAZIONE_LINEARE_O 1 0 10
        
        potenza_giorno: ./potenza_tot E-126/7500 INTERPOLAZIONE_LINEARE_V INTERPOLAZIONE_LINEARE_T BAROMETRICO CURVE_DI_POTENZA INTERPOLAZIONE_LINEARE_O 1 0 '2010-01-01 22:00:00+01:00' 

    */




    /*************  FUNZIONI  *************/

    /*
     * Funzione per verificare se un argomento passato è numerico
    */
    bool isanumber(const char *str);

#endif
