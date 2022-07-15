#ifndef FORMULE_H
    #define FORMULE_H
    #include <math.h>
    
    //interpolazione lineare tra due punti
    float interpolazione_lineare(float x1, float y1, float x2, float y2, float x);

    float interpolazione_logaritmica(float x1, float y1, float x2, float y2, float x);

    float profilo_logaritmico(float x1, float y1, float z0, float hOstacolo, float x);

    float hellman(float x1, float y1, float z0,float x);

#endif
