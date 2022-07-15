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
    float denominatore = log((y1 - d)/z0);
    return y1 * (numeratore / denominatore);
}

float hellman(float x1, float y1, float z0,float x)
{
    float alpha = 1 / (log(x / z0));
    return y1 * pow((x / x1), alpha);
}
