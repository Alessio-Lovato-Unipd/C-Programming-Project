
#include "parametri.h"
#include "formule.h"
#include "estrattore_csv.h"

/************************GESTIONE STRUTTURA PARAMETRI********************/

struct parametro *aggiungi_elemento(const struct parametro *elemento_attuale, float val_vento, float val_temperatura, float val_densita)
{
    struct parametro *nuovo_elemento;

    nuovo_elemento = malloc(sizeof(struct parametro));
    if (nuovo_elemento == NULL) {
        printf("Error: malloc() failed in insert()\n");
		exit(EXIT_FAILURE);
    }

    //salvo i dati
    nuovo_elemento->velocita_vento = val_vento;
    nuovo_elemento->temperatura_aria = val_temperatura;
    nuovo_elemento->densita_aria = val_densita;
    //salvo posizione 
    nuovo_elemento->next = elemento_attuale; 

    return nuovo_elemento;
}

/**************************GESTIONE DEI CALCOLI*****************/
float calcolo_vel_vento(enum tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo,float altezza_x)
{
    switch (metodo)
    {
    case INTERPOLAZIONE_LINEARE:
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

float calcolo_temperatura_aria(enum tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x)
{
    switch (metodo)
    {
    case INTERPOLAZIONE_LINEARE:
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

float calcolo_densita_aria(enum tipo_calcolo_densita metodo, float altezza1, float pressione1, float temperatura_ambiente,float temperatura_x,float altezza_x)
{
    switch (metodo)
    {
    case BAROMETRICO:
        return barometrico(altezza1, pressione1, temperatura_ambiente, temperatura_x, altezza_x);
        break;
    
    case GAS_IDEALE:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x);
        break;

    default:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x);
        break;
    }
}


/********************INTERROGAZIONE DELL'UTENTE***********************/
void interroga_utente(struct tipo_metodo *m, float *ostacolo)
{

}


/******************CALCOLO DEI PARAMETRI******************/
void calcolo_parametri(const struct weather *in, const struct altezze  *h, float altezza_mozzo, struct parametro *out)
{
    struct weather *p;    
    struct tipo_metodo metodo;
    float vento, temperatura, pressione, densita;
    float altezza_ostacolo;

    //Chiedo quali metodi di calcolo vuole utilizzare per ognuno dei 3 valori da calcolare
    interroga_utente(&metodo, &altezza_ostacolo);

    //Calcolo tutti i parametri a partire dai dati weather
    for(p = in; p != NULL; p = p->prev) {

        //calcolo i 3 parametri
        vento = calcolo_vel_vento(metodo.vento, h->h_vel1, in->velocita_vento1, h->h_vel2, in->velocita_vento2, in->rugosita, altezza_ostacolo,altezza_mozzo);
        temperatura = calcolo_temperatura_aria(metodo.temperatura, h->h_t1, in->temperatura1, h->h_t2, in->temperatura2, altezza_mozzo);
        densita = calcolo_densita_aria(metodo.densita, h->h_pressione, in->pressione, , temperatura,altezza_mozzo);  
        
        //salvo i 3 parametri calcolati nell'elemento corrente
        out = aggiungi_elemento(out, vento, temperatura, densita);
    }
    
}
