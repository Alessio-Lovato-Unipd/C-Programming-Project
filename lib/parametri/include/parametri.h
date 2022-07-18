#ifndef PARAMETRI_H
    #define PARAMETRI_H

    typedef enum tipo_calcolo_vento {INTERPOLAZIONE_LINEARE, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN};
    typedef enum tipo_calcolo_temperatura {INTERPOLAZIONE_LINEARE, GRADIENTE_LINEARE};
    typedef enum tipo_calcolo_densita {BAROMETRICO, GAS_IDEALE};

    struct parametro{
        float vento_mozzo;
        float densita_aria_mozzo;
    };
    
    struct tipo_metodo{
        enum tipo_calcolo_vento vento;
        enum tipo_calcolo_temperatura temperatura;
        enum tipo_calcolo_densita densita;
    }

    float calcolo_vel_vento(enum tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo,float altezza_x);

    float calcolo_temperatura_aria(enum tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x);

    float calcolo_densita_aria(enum tipo_calcolo_densita metodo, float altezza1, float pressione1,float temperatura_x,float altezza_x);


    
#endif
