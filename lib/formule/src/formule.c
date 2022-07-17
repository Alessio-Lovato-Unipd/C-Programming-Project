#include "../include/formule.h"

float interpolazione_lineare(float x1, float y1, float x2, float y2, float x)
{
    return ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;
}

float interpolazione_logaritmica(float x1, float y1, float x2, float y2, float x)
{
    float numeratore = (log(x) * (y2 - y1)) - y2 * log(x1) + y1 * log(x2);
    return numeratore / (log(x2) * log(x1)); 
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

//calcolo densità arialivello mozzo
float barometrico(float h1, float p1, float T0, float T_x, float h_x)//T_x (mozzo) la passo per paramtri perchè non posso sapere quale metodo di calcolo va usato
{
    return ((p1 / 100) - (GRADIENTE_PRESSIONE * (h_x - h1))) * ((T0 * 100)/ T_x); //T0 quale è??
}

float gas_ideale(float h1, float p1, float T_x, float h_x)
{
    float p_x = 100 * ((p1 / 100) - (GRADIENTE_PRESSIONE * (h_x - h1)));
    return p_x / (COSTANTE_GAS_IDEALE * T_x);
}
