
#include "parametri.h"
#include "formule.h"
#include "estrattore_csv.h"

/************************GESTIONE STRUTTURA PARAMETRI********************/

struct parametro *aggiungi_elemento(const char *orario, struct parametro *elemento_attuale, float val_vento, float val_densita)
{
    struct parametro *nuovo_elemento;

    nuovo_elemento = malloc(sizeof(struct parametro));
    if (nuovo_elemento == NULL) {
        printf("Error: malloc() failed in insert()\n");
		exit(EXIT_FAILURE);
    }

    //salvo i dati
	nuovo_elemento->orario = malloc(sizeof(char) * (strlen(orario) + 1));
	strcpy(nuovo_elemento->orario, orario);
    nuovo_elemento->vento = val_vento;
    nuovo_elemento->densita_aria = val_densita;

    //salvo posizione 
    nuovo_elemento->next = elemento_attuale; 

    return nuovo_elemento;
}

struct parametro *cerca_nodo_parametri(const char *const orario, const struct parametro *const head_parametro)
{
	const struct parametro *temporaneo_par = head_parametro;
        
	while((temporaneo_par != NULL) && (strcmp(temporaneo_par->orario, orario) != 0))
		temporaneo_par = temporaneo_par->next;

	return (struct parametro *) temporaneo_par;
}

struct parametro *svuota_parametri(struct parametro *head)
{
     struct parametro *temp = head;
	
	if (head == NULL)
		return NULL; 
	
    do {
        temp = head->next;
		free(head->orario);
		free(head);
        head = temp;
    } while (temp != NULL);

	return head;
}




/**************************GESTIONE DEI CALCOLI*****************/
float calcolo_vel_vento(tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo, float altezza_x)
{
    switch (metodo)
    {
    case INTERPOLAZIONE_LINEARE_V:
        return interpolazione_lineare(altezza1, velocita1, altezza2, velocita2, altezza_x);
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

float calcolo_temperatura_aria(tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x)
{
    switch (metodo)
    {
    case INTERPOLAZIONE_LINEARE_T:
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

float calcolo_densita_aria(tipo_calcolo_densita metodo, float altezza1, float pressione1,float temperatura_x,float altezza_x)
{
    switch (metodo)
    {
    case BAROMETRICO:
        return barometrico(altezza1, pressione1, temperatura_x, altezza_x);
        break;
    
    case GAS_IDEALE:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x);
        break;

    default:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x);
        break;
    }
}


/******************CALCOLO DEI PARAMETRI******************/
struct parametro *calcolo_parametri(const struct dati_weather *dati, const struct tipo_metodo *metodo, float altezza_ostacolo,float altezza_mozzo, struct parametro *head)
{
    float vento, temperatura, densita;
    struct parametro *out = head;

    //Calcolo tutti i parametri a partire dai dati weather
    for(struct weather *in = dati->head_weather; in != NULL; in = in->prev) {

        //calcolo i 3 parametri
        vento = calcolo_vel_vento(metodo->vento, dati->h_vel1, in->velocita_vento1, dati->h_vel2, in->velocita_vento2, in->rugosita, altezza_ostacolo,altezza_mozzo);
        temperatura = calcolo_temperatura_aria(metodo->temperatura, dati->h_t1, in->temperatura1, dati->h_t2, in->temperatura2, altezza_mozzo);
        densita = calcolo_densita_aria(metodo->densita, dati->h_pressione, in->pressione, temperatura, altezza_mozzo);  
    
        //salvo i 3 parametri calcolati nell'elemento corrente
        out = aggiungi_elemento(in->orario, out, vento, densita);
    }

    return out;
    
}
