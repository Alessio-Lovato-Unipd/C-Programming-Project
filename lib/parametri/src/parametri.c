#include "../include/parametri.h"
#include "../../formule/include/formule.h"
#include "../../estrazione_csv/include/estrattore_csv.h"

/************************GESTIONE STRUTTURA PARAMETRI********************/

struct parametro *aggiungi_elemento(const struct parametro *elemento_attuale, float val_vento, float val_temperatura, float val_densita)
{
    struct parametro *nuovo_elemento;

    nuovo_elemento = malloc(sizeof(struct parametro));
    if (nuovo_elemento == NULL) {
        printf("Error: malloc() failed in insert()\n");
		exit(EXIT_FAILURE);
    }

    nuovo_elemento->velocita_vento = val_vento;
    nuovo_elemento->temperatura_aria = val_temperatura;
    nuovo_elemento->densita_aria = val_densita;
    nuovo_elemento->next = elemento_attuale; 
}

/**************************GESTIONE DEI CALCOLI********/
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





/******************CALCOLO DEI PARAMETRI******************/
void calcolo_parametri(const struct weather *in, const struct altezze  *h, float altezza_mozzo, struct parametro *out)
{

    float vento, temperatura, pressione, densita;
    //Chiudo quali metodi di calcolo vuole utilizzare per ognuno dei 3 valori da calcolare

    //Calcolo tutti i parametri a partire dai dati weather
    while(in != NULL){
        //calcolo i 3 parametri
        vento = calcolo_vel_vento(0, h->h_vel1, in->velocità_vento1, h->h_vel2, in->velocità_vento2, in->rugosità, altezza_mozzo);
        temperatura = calcolo_temperatura_aria(h->h_t1, in->temperatura1, h->h_t2, in->temperatura2, altezza_mozzo);
        densita = calcolo_densita_aria();  
        
        //salvo i 3 parametri calcolati nell'elemento corrente
        aggiungi_elemento(out, vento, temperatura, densita);

        //aggiorno i punattori all'elemento successivo
        in = in->prev;
        out = out->next;
    }
    
}