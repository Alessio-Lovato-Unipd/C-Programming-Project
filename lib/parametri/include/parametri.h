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

    /*****  GESTIONE LISTA PARAMETRI    *****/

    /*
     * Funzione che crea e calcola una lista di parametri (velocità vento
     * e densità aria) per il calcolo dell'output.
    */
    struct parametro *calcolo_parametri(const struct dati_weather *const dati, const struct tipo_metodo *const metodo, float altezza_ostacolo, float altezza_mozzo, struct parametro *const head);
    
    /*
     * Aggiunge parametro alla lista
     * NOTA: Funzione ad uso interno della libreria
    */
    struct parametro *aggiungi_elemento(const char *const orario, struct parametro *const elemento_attuale, float val_vento, float val_densita);
    
    /*
     * Funzione che svuota la lista parametri
    */
    struct parametro *svuota_parametri(struct parametro *head);
	
	/*
     * Funzione di ricerca parametri corrispondenti ad un orario specifico
	*/
    struct parametro *cerca_nodo_parametri(const char *const orario, const struct parametro *const head_parametro);

     /*
     * Funzione per il calcolo della velocità del vento all'altezza del
     * mozzo secondo la metodologia stabilita.
     * I metodi consentiti sono: INTERPOLAZIONE LINEARE, INTERPOLAZIONE LOGARITMICA,
     * PROFILO LOGARITMICO, HELLMAN.
     * Default: INTERPOLAZIONE LINEARE
    */
    float calcolo_vel_vento(tipo_calcolo_vento metodo, float altezza1, float velocita1, float altezza2, float velocita2, float rugosita, float h_ostacolo, float altezza_x, int *const errore);

    /*
     * Funzione per il calcolo della temperatura dell'aria all'altezza del
     * mozzo secondo la metodologia stabilita.
     * I metodi consentiti sono: INTERPOLAZIONE LINEARE, GRADIENTE LINEARE
     * Default: INTERPOLAZIONE LINEARE
    */
    float calcolo_temperatura_aria(tipo_calcolo_temperatura metodo, float altezza1, float temperatura1, float altezza2, float temperatura2, float altezza_x, int *const errore);

    /*
     * Funzione per il calcolo della temperatura dell'aria all'altezza del
     * mozzo secondo la metodologia stabilita.
     * I metodi consentiti sono: BAROMETRICO, GAS_IDEALE
     * Default: GAS_IDEALE
    */
    float calcolo_densita_aria(tipo_calcolo_densita metodo, float altezza1, float pressione1,float temperatura_x,float altezza_x, int *const errore);

   
	


	/*CONTROLLO ERRORI DI LIMITI NELLE FORMULE*/

    /*
     * Funzione che stampa il tipo di parametro errato inserito
     * nelle formule del calcolo dei parametri.
    */
	void controllo_errori_parametri(const int *const errore);

#endif
