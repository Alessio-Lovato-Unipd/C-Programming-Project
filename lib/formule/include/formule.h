#ifndef FORMULE_H
    #define FORMULE_H
    #include <math.h>
    #include<stdio.h>
    
    #define GRADIENTE_TEMPERATURA 0.0065
    #define GRADIENTE_PRESSIONE 0.125
    #define PRESSIONE_AMBIENTE_STANDARD_PA 101325 
    #define DENSITA_AMBIENTE_STANDARD 1.292
    #define TEMPERATURA_ABIENTE_STANDARD 273.15
    #define COSTANTE_GAS_IDEALE 287.058

    //interpolazione lineare tra due punti
    float interpolazione_lineare(float x1, float y1, float x2, float y2, float x);

    float interpolazione_logaritmica(float x1, float y1, float x2, float y2, float x);
    
    /***FORMULE  VELOCITÁ VENTO***/
    float profilo_logaritmico(float h_dati, float vel_vento, float z0, float h_ostacolo, float h_mozzo);

    //Calcolo velocità vento
    float hellman(float h_dati, float vel_vento, float z0,float h_mozzo);

    //Calcolo temperatura all'altezza mozzo
    float gradiente_lineare(float h_dati, float T_aria, float h_mozzo);


    /*FORMULE PER CALCOLO DENSITÁ ARIA altezza mozzo*/

    //Calcolo della pressione all'altezza mozzo
    float p_x(float p1, float h_dati, float h_mozzo);

    //Calcolo densità con barometrico
    float barometrico(float h_dati, float p1, float T_mozzo, float h_mozzo);

    //Calcolo densità aria all'altezza mozzo con gas ideale
    float gas_ideale(float h_dati, float p1, float T_mozzo, float h_mozzo);
	

    //Calcolo della potenza
	float calcolo_potenza_da_coefficienti(float densita_aria, float diametro, float vel_vento, float coefficiente);

#endif
