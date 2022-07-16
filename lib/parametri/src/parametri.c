#include "../include/parametri.h"
#include "../../formule/include/formule.h"
#include "../../estrazione_csv/include/estrattore_csv.h"

float calcolo_vel_vento(enum tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float altezza_x)
{
    switch (metodo)
    {
    case INTERPOLAZIONE_LINEARE:
        return interpolazione_lineare(altezza1, velocita1, altezza2, velocita1, altezza_x);
        break;
    
    default:
        break;
    }
    
}

float calcolo_temperatura_aria(float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x)
{
    return interpolazione_lineare(altezza1, temperatura1, altezza2, temperatura2, altezza_x);
}

float calcolo_densita_aria(float altezza1, float pressione1, float altezza2, float pressione2, float altezza_x)
{
    return interpolazione_lineare(altezza1, pressione1, altezza2, pressione2, altezza_x);
}

void calcolo_parametri(const struct weather *in, const struct altezze  *h, float altezza_mozzo, struct parametro *out)
{
    out->velocita_vento = calcolo_vel_vento(h->h_vel1, in->velocità_vento1, h->h_vel2, in->velocità_vento2, in->rugosità, altezza_mozzo);
    out->temperatura_aria = calcolo_temperatura_aria(h->h_t1, in->temperatura1, h->h_t2, in->temperatura2, altezza_mozzo);
    out->densita_aria = calcolo_densita_aria();
}