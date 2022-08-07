#ifndef FORMULE_H
    #define FORMULE_H
    #include <math.h>
    #include <stdio.h>
    
    #define GRADIENTE_TEMPERATURA 0.0065
    #define GRADIENTE_PRESSIONE 0.125
    #define PRESSIONE_AMBIENTE_STANDARD_PA 101325 
    #define DENSITA_AMBIENTE_STANDARD 1.292
    #define TEMPERATURA_ABIENTE_STANDARD 273.15
    #define COSTANTE_GAS_IDEALE 287.058

	//Posizioni vettore errore nei calcoli
    #define NUMERO_ERRORI 7
	#define ERR_OSTACOLO 0
	#define ERR_H_MOZZO 1
	#define ERR_H_DATI 2
	#define ERR_RUGOSITA 3
	#define ERR_PRESS 4
	#define ERR_TEMP 5
    #define ERR_VENTO 6




    /*
     * Funzione che esegue un'interpolazione lineare tra due punti [1] e [2]
    */
    float interpolazione_lineare(float x1, float y1, float x2, float y2, float x);

    /*
     * Funzione che esegue un'interpolazione logaritmica tra due punti [1] e [2]
    */
    float interpolazione_logaritmica(float x1, float y1, float x2, float y2, float x);





    /****** FORMULE CALCOLO VELOCITÁ VENTO *****/

    /*
     *
    */
    float profilo_logaritmico(float h_dati, float vel_vento, float z0, float h_ostacolo, float h_mozzo, int *const errore);

    /*
     * Calcolo velocità vento
    */
    float hellman(float h_dati, float vel_vento, float z0,float h_mozzo, int *const errore);

    /*
     * Calcolo temperatura all'altezza mozzo
    */
    float gradiente_lineare(float h_dati, float T_aria, float h_mozzo, int *const errore);





    /****   FORMULE PER CALCOLO DENSITÁ ARIA AD ALTEZZA MOZZO  ******/

    /*
     * Calcolo della pressione atmosferica all'altezza mozzo
    */
    float p_x(float p1, float h_dati, float h_mozzo);

    /*
     * Calcolo densità con metodo barometrico
    */
    float barometrico(float h_dati, float p1, float T_mozzo, float h_mozzo, int *const errore);

    /*
     *Calcolo densità con metodo del gas ideale
    */
    float gas_ideale(float h_dati, float p1, float T_mozzo, float h_mozzo, int *const errore);
	




    /*****  CALCOLO POTENZA *****/
 
	float calcolo_potenza_da_coefficienti(float densita_aria, float diametro, float vel_vento, float coefficiente);

#endif
