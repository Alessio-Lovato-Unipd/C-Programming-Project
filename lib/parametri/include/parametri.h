#ifndef PARAMETRI_H
    #define PARAMETRI_H
    typedef enum tipo_calcolo_vento {INTERPOLAZIONE_LINEARE, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN};
    struct parametro{
        float velocita_vento;
        float temperatura_aria;
        float densita_aria;
        struct parametro *next;
    }

    void calcolo_parametri(const struct weather *in, const struct altezze  *h, float altezza_mozzo, struct parametro *out);
#endif