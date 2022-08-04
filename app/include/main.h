#ifndef MAIN_H

    #define MAIN_H
    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "../../lib/estrazione_csv/include/estrattore_csv.h"
    #include "../../lib/formule/include/formule.h"
    #include "../../lib/parametri/include/parametri.h"
    #include "../../lib/calcolo_output/include/calcolo_output.h"

    #define PERCORSO_TURBINE_DATA "../../data/turbine_data.csv"
    #define PERCORSO_WEATHER "../../data/weather.csv"
    #define PERCORSO_POWER_COEFFICIENT "../../data/power_coefficient_curves.csv"
	#define PERCORSO_POWER_CURVES "../../data/power_curves.csv"
    #define VALORE_ARGOMENTI_INSERIBILI 8

    //typedef enum {CURVE_DI_POTENZA, CURVE_DI_COEFFICIENTI_POTENZA} tipo_output_uscente;

    /*
    -----ARGOMENTI DA PASSARE AL PROGRAMMA MAIN-----
    Il programma main richiede 7 argomenti:
        - argv[0] ---> nome programma
        - argv[1] ---> nome turbina desiderata
        - argv[2] ---> {INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN}, per il calcolo della velocità del vento
        - argv[3] ---> {INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE}, per il calcolo della temperatura
        - argv[4] ---> {BAROMETRICO, GAS_IDEALE}, per il calcolo della densità dell'aria
        - argv[5] ---> {CURVE_DI_POTENZA, CURVE_DI_COEFFICIENTI_POTENZA}, per la scelta se usare le curve di coefficienti di potenza oppure le curve di potenza
        - argv[6] ---> {INTERPOLAZIONE_LINEARE_O, INTERPOLAZIONE_LOGARITMICA_O}, per la scelta del tipo di interpolazione da utilizzare per il calcolo dell'output
        - argv[7] ---> valore di altezza_ostacolo
        - argv[8] ---> NULL
    */

#endif
