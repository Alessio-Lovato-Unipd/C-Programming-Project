#include "formule.h"

float interpolazione_lineare(float x1, float y1, float x2, float y2, float x)
{
	if( x1 == x2)
		return y1;
    return ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;
}


float interpolazione_logaritmica(float x1, float y1, float x2, float y2, float x)
{
    if (x <= 0) {
        printf("X=%f <= 0, non valido per interpolazione logaritmica\n", x);
        return -1;
    } else if (x1 <= 0) {
        return y1;
    } else if (x2 <= 0) {
        printf("X2=%f <= 0, non valido per interpolazione logaritmica\n", x2);
        return -1;
    }
	if (x1 == x2)
		return y1;
    float numeratore = (log(x) * (y2 - y1)) - y2 * log(x1) + y1 * log(x2);
    return numeratore / (log(x2) - log(x1)); 
}


float profilo_logaritmico(float h_dati, float vel_vento, float z0, float h_ostacolo, float h_mozzo, int *const errore)
{
    float d = 0.7 * h_ostacolo; 

    if (d < 0) {
        errore[ERR_OSTACOLO] = 1;
        return -1;
    }
    if (h_dati < 0) {
        errore[ERR_H_DATI] = 1;
        return -1;
    } else if (h_mozzo < 0) {
        errore[ERR_H_MOZZO] = 1;
        return -1;
    } else if ( z0 < 0) {
        errore[ERR_RUGOSITA] = 1;
        return -1;
    } else if (vel_vento < 0) {
        errore[ERR_VENTO] = 1;
        return -1;
    } else if ((h_dati <= d) || (h_mozzo <= d)) {
        errore[ERR_OSTACOLO] = 1;
        return -1;
    } else {
        float numeratore =  log((h_mozzo - d) / z0);
        float denominatore = log((h_dati - d) / z0);
        return vel_vento * (numeratore / denominatore); 
    }
    
}


float hellman(float h_dati, float vel_vento, float z0, float h_mozzo, int *const errore)
{
    if (h_dati < 0) {
        errore[ERR_H_DATI] = 1;
        return -1;
    } else if (h_mozzo < 0) {
        errore[ERR_H_MOZZO] = 1;
        return -1;
    } else if ( z0 < 0) {
        errore[ERR_RUGOSITA] = 1;
        return -1;
    } else if (vel_vento < 0) {
        errore[ERR_VENTO] = 1;
        return -1;
    } else {
        float alpha = 1 / (log(h_mozzo / z0));
        return vel_vento * pow((h_mozzo / h_dati), alpha);
    }
    
}



float gradiente_lineare(float h_dati, float T_aria, float h_mozzo, int *const errore)
{
    if (h_dati < 0) {
        errore[ERR_H_DATI] = 1;
        return -1;
    } else if (h_mozzo < 0) {
        errore[ERR_H_MOZZO] = 1;
        return -1;
    } else if (T_aria <= 0) {
        errore[ERR_TEMP] = 1;
        return -1;
    }
    return T_aria - (GRADIENTE_TEMPERATURA * (h_mozzo - h_dati));
}


float p_x(float p1, float h_dati, float h_mozzo)
{
    return 100 * ((p1 / 100) - (GRADIENTE_PRESSIONE * (h_mozzo - h_dati)));
}


float barometrico(float h_dati, float p1, float T_mozzo, float h_mozzo, int *const errore)
{
    if (h_dati < 0) {
        errore[ERR_H_DATI] = 1;
        return -1;
    } else if (h_mozzo < 0) {
        errore[ERR_H_MOZZO] = 1;
        return -1;
    } else if (p1 <= 0) {
        errore[ERR_PRESS] = 1;
        return -1;
    } else if (T_mozzo <= 0) {
        errore[ERR_TEMP] = 1;
        return -1;
    }
    return p_x(p1, h_dati, h_mozzo) * ((DENSITA_AMBIENTE_STANDARD * TEMPERATURA_ABIENTE_STANDARD) / (PRESSIONE_AMBIENTE_STANDARD_PA * T_mozzo)); 
}


float gas_ideale(float h_dati, float p1, float T_mozzo, float h_mozzo, int *const errore)
{
    if (h_dati < 0) {
        errore[ERR_H_DATI] = 1;
        return -1;
    } else if (h_mozzo < 0) {
        errore[ERR_H_MOZZO] = 1;
        return -1;
    } else if (p1 <= 0) {
        errore[ERR_PRESS] = 1;
        return -1;
    } else if (T_mozzo <= 0) {
        errore[ERR_TEMP] = 1;
        return -1;
    }
    return p_x(p1, h_dati, h_mozzo) / (COSTANTE_GAS_IDEALE * T_mozzo);
}


float calcolo_potenza_da_coefficienti(float densita_aria, float diametro, float vel_vento, float coefficiente)
{
	double pi = atan(1) * 4;
	return (densita_aria * (pow(diametro, 2)) * pi * (pow(vel_vento, 3)) * coefficiente / 8);
}
