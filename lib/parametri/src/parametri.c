
#include "parametri.h"
#include "formule.h"
#include "estrattore_csv.h"


/**************************GESTIONE DEI CALCOLI*****************/
float calcolo_vel_vento(tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo,float altezza_x)
{
    switch (metodo)
    {
    case INTERPOLAZIONE_LINEARE_V:
        return interpolazione_lineare(altezza1, velocita1, altezza2, velocita1, altezza_x);
        break;
    
    case INTERPOLAZIONE_LOGARITMICA:
        return interpolazione_logaritmica(altezza1, velocita1, altezza2, velocita2, altezza_x);
        break;

    case PROFILO_LOGARITMICO:
        return profilo_logaritmico(altezza1, velocita1, rugosita, h_ostacolo, altezza_x);
        break;

    case HELLMAN: 
        return hellman(altezza1, velocita1, rugosita, altezza_x);
        break;

    default:
        return interpolazione_lineare(altezza1, velocita1, altezza2, velocita1, altezza_x);
        break;
    }
    
}

float calcolo_temperatura_aria(tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x)
{
    switch (metodo)
    {
    case INTERPOLAZIONE_LINEARE_T:
        return interpolazione_lineare(altezza1, temperatura1, altezza2, temperatura2, altezza_x);
        break;
    
    case GRADIENTE_LINEARE:
        return gradiente_lineare(altezza1, temperatura1, altezza_x);
        break;

    default:
        return interpolazione_lineare(altezza1, temperatura1, altezza2, temperatura2, altezza_x);
        break;
    }
    
}

float calcolo_densita_aria(tipo_calcolo_densita metodo, float altezza1, float pressione1,float temperatura_x,float altezza_x)
{
    switch (metodo)
    {
    case BAROMETRICO:
        return barometrico(altezza1, pressione1, temperatura_x, altezza_x);
        break;
    
    case GAS_IDEALE:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x);
        break;

    default:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x);
        break;
    }
}


/******************CALCOLO DEI PARAMETRI******************/
struct parametro calcolo_parametri(const struct weather *in, const struct altezze  *h, const struct tipo_metodo *metodo, float altezza_ostacolo,float altezza_mozzo)
{
    struct parametro out;    
    float temperatura;

    //calcolo i 3 parametri
    out.vento = calcolo_vel_vento(metodo->vento, h->h_vel1, in->velocita_vento1, h->h_vel2, in->velocita_vento2, in->rugosita, altezza_ostacolo,altezza_mozzo);
    temperatura = calcolo_temperatura_aria(metodo->temperatura, h->h_t1, in->temperatura1, h->h_t2, in->temperatura2, altezza_mozzo);
    out.densita_aria = calcolo_densita_aria(metodo->densita, h->h_pressione, in->pressione, temperatura,altezza_mozzo);  
    
    return out;
}
