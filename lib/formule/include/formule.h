#ifndef FORMULE_H
    #define FORMULE_H
    #include <math.h>
    
    #define GRADIENTE_TEMPERATURA 0.0065
    #define GRADIENTE_PRESSIONE 0.125
    #define PRESSIONE_AMBIENTE_STANDARD_PA 101325 
    #define DENSITA_AMBIENTE_STANDARD 1.292
    #define TEMPERATURA_ABIENTE_STANDARD 273.15
    #define COSTANTE_GAS_IDEALE 287.058

    //interpolazione lineare tra due punti
    float interpolazione_lineare(float x1, float y1, float x2, float y2, float x);

    float interpolazione_logaritmica(float x1, float y1, float x2, float y2, float x);

    float profilo_logaritmico(float x1, float y1, float z0, float hOstacolo, float x);

    float hellman(float x1, float y1, float z0,float x);

    float gradiente_lineare(float x1, float y1, float x);

    float p_x(float p1, float h1, float h_x);

    float barometrico(float h1, float p1, float T_x, float h_x);

    float gas_ideale(float h1, float p1, float T_x, float h_x);

#endif
