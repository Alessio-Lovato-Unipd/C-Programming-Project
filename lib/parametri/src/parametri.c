#include "../include/parametri.h"
#include "../../formule/include/formule.h"
#include "../../estrazione_csv/include/estrattore_csv.h"

float calcolo_vel_vento(float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float altezza_x)
{
    return interpolazione_lineare(altezza1, velocita1, altezza2, velocita1, altezza_x);
}

float calcolo_temperatura_aria(float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x)
{
    return interpolazione_lineare(altezza1, temperatura1, altezza2, temperatura2, altezza_x);
}

float calcolo_densita_aria(float altezza1, float pressione1, float altezza2, float pressione2, float altezza_x)
{
    return interpolazione_lineare(altezza1, pressione1, altezza2, pressione2, altezza_x);
}

void calcolo_parametri(const struct weather *p, float altezza_mozzo)
{
    calcolo_vel_vento(, p->velocità_vento1, , p->velocità_vento2, p->rugosità, altezza_mozzo);
    calcolo_temperatura_aria();
    calcolo_densita_aria();
}