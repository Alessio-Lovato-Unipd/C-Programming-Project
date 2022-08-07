#ifndef PARAMETRI_H
    #define PARAMETRI_H

    #include "formule.h"
    #include "estrattore_csv.h"

    typedef enum {INTERPOLAZIONE_LINEARE_V, INTERPOLAZIONE_LOGARITMICA, PROFILO_LOGARITMICO, HELLMAN} tipo_calcolo_vento;
    typedef enum {INTERPOLAZIONE_LINEARE_T, GRADIENTE_LINEARE} tipo_calcolo_temperatura;
    typedef enum {BAROMETRICO, GAS_IDEALE} tipo_calcolo_densita;

    struct parametro{
		char *orario;
        float vento;
        float densita_aria;
        struct parametro *next;
    };
    
    struct tipo_metodo{
        tipo_calcolo_vento vento;
        tipo_calcolo_temperatura temperatura;
        tipo_calcolo_densita densita;
    };

    /****GESTIONE LISTA PARAMETRI*****/
    //Aggiunge parametro alla lista
    struct parametro *aggiungi_elemento(const char *orario, struct parametro *elemento_attuale, float val_vento, float val_densita);
    
    //svuota lista parametri
    struct parametro *svuota_parametri(struct parametro *head);
	
	//ricerca orario corrispondente ai parametri
	struct parametro *cerca_nodo_parametri(const char *const orario, const struct parametro *const head_parametro);

    //Funzioni di calcolo dei vari parametri
    float calcolo_vel_vento(tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo,float altezza_x);

    float calcolo_temperatura_aria(tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x);

    float calcolo_densita_aria(tipo_calcolo_densita metodo, float altezza1, float pressione1,float temperatura_x,float altezza_x);

    /*CREA E CALCOLA LISTA DI PARAMETRI (vento e densità aria) per calcolo output */
    struct parametro *calcolo_parametri(const struct dati_weather *dati, const struct tipo_metodo *metodo, float altezza_ostacolo, float altezza_mozzo, struct parametro *head);

#endif
