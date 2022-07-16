#ifndef PARAMETRI_H
    #define PARAMETRI_H
    struct parametro{
        float velocita_vento;
        float temperatura_aria;
        float densita_aria;
        struct parametro *prev;
    }

    void calcolo_parametri(const struct weather *in, float altezza_mozzo, struct parametro *out);
#endif