
#include "parametri.h"
#include "formule.h"
#include "estrattore_csv.h"




/****************** CALCOLO DEI PARAMETRI ******************/

struct parametro *calcolo_parametri(const struct dati_weather *const dati, const struct tipo_metodo *const metodo, float altezza_ostacolo,float altezza_mozzo, struct parametro *const head)
{
    float vento, temperatura, densita;
    struct parametro *out = head;
	int errore[NUMERO_ERRORI] = {0};

    //Calcolo tutti i parametri a partire dai dati weather
    for (struct weather *in = dati->head_weather; in != NULL; in = in->prev) {

        //calcolo i 3 parametri
        vento = calcolo_vel_vento(metodo->vento, dati->h_vel1, in->velocita_vento1, dati->h_vel2, in->velocita_vento2, in->rugosita, altezza_ostacolo, altezza_mozzo, errore);
        temperatura = calcolo_temperatura_aria(metodo->temperatura, dati->h_t1, in->temperatura1, dati->h_t2, in->temperatura2, altezza_mozzo, errore);
        densita = calcolo_densita_aria(metodo->densita, dati->h_pressione, in->pressione, temperatura, altezza_mozzo, errore);  
    
        //salvo i 3 parametri calcolati nell'elemento corrente
        out = aggiungi_elemento(in->orario, out, vento, densita);
        if (out == NULL)
            return NULL;
    }
	controllo_errori_parametri(errore);

    for (int i = 0; i < NUMERO_ERRORI; i++)
        if (errore[i] == 1)
            return NULL;

    return out;
    
}




/****************** GESTIONE STRUTTURA PARAMETRI ******************/

struct parametro *aggiungi_elemento(const char *const orario, struct parametro *const elemento_attuale, float val_vento, float val_densita)
{
    struct parametro *nuovo_elemento;

    nuovo_elemento = malloc(sizeof(struct parametro));
    if (nuovo_elemento == NULL) {
        printf("Errore: malloc() ha fallito nell'aggiunta di un parametro\n");
        svuota_parametri(elemento_attuale);
		return NULL;
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
        
	while ((temporaneo_par != NULL) && (strcmp(temporaneo_par->orario, orario) != 0))
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




/****************** GESTIONE DEI CALCOLI *****************/

float calcolo_vel_vento(tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo, float altezza_x, int *const errore)
{
    switch (metodo) {
    case INTERPOLAZIONE_LINEARE_V:
        return interpolazione_lineare(altezza1, velocita1, altezza2, velocita2, altezza_x);
        break;

    case INTERPOLAZIONE_LOGARITMICA:
        return interpolazione_logaritmica(altezza1, velocita1, altezza2, velocita2, altezza_x);
        break;

    case PROFILO_LOGARITMICO:
        return profilo_logaritmico(altezza1, velocita1, rugosita, h_ostacolo, altezza_x, errore);
        break;

    case HELLMAN: 
        return hellman(altezza1, velocita1, rugosita, altezza_x, errore);
        break;

    default:
        return interpolazione_lineare(altezza1, velocita1, altezza2, velocita1, altezza_x);
        break;
    }
    
}


float calcolo_temperatura_aria(tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x, int *const errore)
{
    switch (metodo) {
    case INTERPOLAZIONE_LINEARE_T:
        return interpolazione_lineare(altezza1, temperatura1, altezza2, temperatura2, altezza_x);
        break;
    
    case GRADIENTE_LINEARE:
        return gradiente_lineare(altezza1, temperatura1, altezza_x, errore);
        break;

    default:
        return interpolazione_lineare(altezza1, temperatura1, altezza2, temperatura2, altezza_x);
        break;
    }
    
}


float calcolo_densita_aria(tipo_calcolo_densita metodo, float altezza1, float pressione1, float temperatura_x, float altezza_x, int *const errore)
{
    switch (metodo) {
    case BAROMETRICO:
        return barometrico(altezza1, pressione1, temperatura_x, altezza_x, errore);
        break;
    
    case GAS_IDEALE:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x, errore);
        break;

    default:
        return gas_ideale(altezza1, pressione1, temperatura_x, altezza_x, errore);
        break;
    }
}


/****************** CONTROLLO ERRORI ******************/
void controllo_errori_parametri(const int *const errore){
	if(errore[ERR_OSTACOLO] == 1)
		printf("***ERRORE: Altezza ostacolo errata o troppo elevata per questa turbina***\n\n");
	if(errore[ERR_H_MOZZO] == 1)
		printf("***ERRORE: Altezza mozzo errata***\n\n");
	if(errore[ERR_H_DATI] == 1)
		printf("***ERRORE: Altezze dati misurati negative***\n\n");
	if(errore[ERR_RUGOSITA] == 1)
		printf("***ERRORE: Rugosità negativa***\n\n");
	if(errore[ERR_PRESS] == 1)
		printf("***ERRORE: Pressione negativa nei dati***\n\n");
	if(errore[ERR_TEMP] == 1)
		printf("***ERRORE: Temperatura errata nei dati***\n\n");
    if(errore[ERR_VENTO] == 1)
		printf("***ERRORE: Velocità del vento errata nei dati (negativa)***\n\n");    
}
