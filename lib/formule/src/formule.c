#include "../include/formule.h"

float interpolazione_lineare(float x1, float y1, float x2, float y2, float x)
{
    return ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;
}

float interpolazione_logaritmica(float x1, float y1, float x2, float y2, float x)
{
    float numeratore = (log(x) * (y2 - y1)) - y2 * log(x1) + y1 * log(x2);
    return numeratore / (log(x2) - log(x1)); 
}

float profilo_logaritmico(float x1, float y1, float z0, float hOstacolo, float x)
{
    float d = 0.7 * hOstacolo;
    float numeratore =  log((x - d)/z0);
    float denominatore = log((x1 - d)/z0);
    return y1 * (numeratore / denominatore);
}

float hellman(float x1, float y1, float z0,float x)
{
    float alpha = 1 / (log(x / z0));
    return y1 * pow((x / x1), alpha);
}

//calcolo temperatura altezza mozzo
float gradiente_lineare(float x1, float y1, float x)
{
    return y1 - (GRADIENTE_TEMPERATURA * (x - x1));
}


float p_x(float p1, float h1, float h_x)//calcola la pressione a livello di x
{
    return 100 * ((p1 / 100) - (GRADIENTE_PRESSIONE * (h_x - h1)));
}

//calcolo densità dell'aria a livello del mozzo
float barometrico(float h1, float p1, float T_x, float h_x)//T_x (mozzo) la passo per paramtri perchè non posso sapere quale metodo di calcolo va usato
{
    return p_x(p1, h1, h_x) * ((DENSITA_AMBIENTE_STANDARD * TEMPERATURA_ABIENTE_STANDARD) / (PRESSIONE_AMBIENTE_STANDARD_PA * T_x)); 
}

float gas_ideale(float h1, float p1, float T_x, float h_x)
{
    return p_x(p1, h1, h_x) / (COSTANTE_GAS_IDEALE * T_x);
}
