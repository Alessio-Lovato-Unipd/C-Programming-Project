#ifndef PARAMETRI_H
    #define PARAMETRI_H

    typedef enum tipo_calcolo_vento {INTERPOLAZIONE_LINEARE, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN};
    typedef enum tipo_calcolo_temperatura {INTERPOLAZIONE_LINEARE, GRADIENTE_LINEARE};
    typedef enum tipo_calcolo_densita {BAROMETRICO, GAS_IDEALE};

    struct parametro{
        float velocita_vento;
        float temperatura_aria;
        float densita_aria;
        struct parametro *next;
    };
    
    struct tipo_metodo{
        enum tipo_calcolo_vento vento;
        enum tipo_calcolo_temperatura temperatura;
        enum tipo_calcolo_densita densita;
    }

    
    
#endif
