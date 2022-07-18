#ifndef PARAMETRI_H
    #define PARAMETRI_H

    #include "formule.h"
    #include "estrattore_csv.h"

    typedef enum {INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN} tipo_calcolo_vento;
    typedef enum {INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE} tipo_calcolo_temperatura;
    typedef enum {BAROMETRICO, GAS_IDEALE} tipo_calcolo_densita;

    struct parametro{
        float vento;
        float densita_aria;
    };
    
    struct tipo_metodo{
        tipo_calcolo_vento vento;
        tipo_calcolo_temperatura temperatura;
        tipo_calcolo_densita densita;
    };

    float calcolo_vel_vento(tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo,float altezza_x);

    float calcolo_temperatura_aria(tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x);

    float calcolo_densita_aria(tipo_calcolo_densita metodo, float altezza1, float pressione1,float temperatura_x,float altezza_x);

    struct parametro calcolo_parametri(const struct weather *in, const struct altezze  *h, const struct tipo_metodo *metodo, float altezza_ostacolo,float altezza_mozzo);

#endif
