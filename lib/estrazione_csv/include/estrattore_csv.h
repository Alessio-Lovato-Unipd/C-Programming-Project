#ifndef CSV_EXTRACTOR_H

    #define CSV_EXTRACTOR_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include "csv.h"
	#define NUMERO_COLONNE_TURBINA 19
	#define NUMERO_COLONNE_WEATHER 7 
    #define NUMERO_COLONNE_POWER_COEFFICIENT_CURVES 60
	#define NUMERO_COLONNE_POWER_CURVES 79
    #define LUNGHEZZA_VETTORE_POWER_COEFFICIENT 58
    #define LUNGHEZZA_VETTORE_POWER_CURVES 77
	#define SEPARATORE ','
    #define ERRORE_MALLOC 20 //numero casuale
    #define COLONNA_ALTEZZA_MOZZO 8

    /* 
     * Struttura per la creazione di nodi in una lista concatenata.
     * Ogni nodo contiene tutte le variabili che necessitiamo per salvare i dati ogni turbina.
    */
    struct turbina {
        char *nome, *id;
        int potenza_nominale;
        int diametro_rotore;
        float altezza_mozzo;
        float *power_coefficients;
        float *power_curves;
        char *char_p_coefficient;
        char *char_p_curves;
        bool bool_p_coefficient;
        bool bool_p_curves;
        struct turbina *prev;
    };

    /* 
     * Struttura per il salvataggio dei dati meteo ad ogni ora.
     * Corrisponde ad un nodo della lista concatenata.
    */ 
    struct weather {
        char *orario;
        float pressione;
        float temperatura1; //ad altezza = 2m
        float velocita_vento1; //ad altezza = 10m
        float rugosita;
        float temperatura2; //ad altezza = 10m
        float velocita_vento2; //ad altezza = 80m
        struct weather *next;
    };

    /* 
      * Struttura per il salvataggio delle altezze dei dati del meteo.
     * Contiene anche un puntatore ad una struttura che serve per salvare una lista
     * con tutti i dati meteo ora per ora.
     */
    struct dati_weather {
        float h_pressione;
        float h_t1;
        float h_vel1;
        float h_rugosita;
        float h_t2;
        float h_vel2;
        struct weather *head_weather;
    };

    /***********************   GESTIONE DATI TURBINA   ***********************/

    
    /*
     * Funzione per il salvataggio dei dati dal file turbine_data.csv tramite lista concatenata.
     * Restituisce il puntatore alla testa della lista (lo stesso puntatore va 
     * passato come primo argomento).
     * Il puntatore a errore serve per la gestione degli errori secondo la libreria csv.
     * Se la funzione non riesce a creare almeno un nodo o incontra errori, restituisce 
     * NULL e salva l'errore nel puntatore designato. 
    */
    struct turbina *estrazione_dati_turbine(struct turbina *puntatore, const char *const percorso_file_turbine_data, int *const errore);

    /*
     * Funzione per la creazione di nuovo elemento della lista turbina.
     * Se si hanno altezze del mozzo diverse per un unico modello vengono
     * create più copie della stessa turbina con id differenti come segue:
     * <id>_<altezza-mozzo.parte-decimale-se-presente>
    */
    struct turbina *nuovo_elemento_turbina(struct turbina *elemento_attuale_turbina, char **fields, char *punto_virgola);

    /*
     * Funzione per deallocare tutta la memoria utilizzata dalla lista turbina.
    */
    struct turbina *svuota_lista_turbine_data(struct turbina *head_turbina);

    /*
     * Funzione che elimina un singolo nodo della lista.
    */
    void elimina_nodo_turbina(struct turbina *nodo);

    /*
     * Funzione per ricercare i dati di una turbina.
     * Se non si vuole trovare un modello con un'altezza specifica,
     * inserire come altezza mozzo il valore 0.
     * Se il modello non viene trovato restituisce NULL.
    */
    struct turbina *cerca_dati_turbina(const char *const nome_modello_turbina, const float altezza_mozzo, const struct turbina *const head_turbina);
	
    /*
     * Funzione che serve per scorrere gli elementi della lista delle turbine.
     * Restituisce l'elemento successivo.
    */
	struct turbina *scorri_lista_turbina(const struct turbina *const puntatore);
    
    /*
     * Funzione per la conversione dei valori da char a bool per la verifica
     * delle curve.
    */
    struct turbina *conversione_dati_in_booleano(struct turbina *const elemento_attuale_turbina);

    /*
     * Funzione per stampare tutta la lista delle turbine.
     * Comincia a stampare dal puntatore dato per argomento
     * fino all'inizio della lista (a ritroso).
    */
    void stampa_lista_turbine(struct turbina *head_turbina);





    /***********************   GESTIONE DATI WEATHER   ***********************/


    /*
     * Funzione per l'apertura del file csv e l'inizializzazione dei dati della
     * struttura dati_weather. Puntatore_dati_weather è il puntatore alla lista
     * dei dati di ogni ora.
     * Nel caso di errori restituisce NULL e l'errore è salvato nell'apposito
     * puntatore.
     * Gli argomenti file e fields sono spiegati nella libreria csv. Sono passati
     * dalla funzione estrazione_dati_weather.
     * NOTA: Funzione pensata per non essere utilizzata esternamente.
    */
    struct dati_weather *apertura_file_weather(struct csv *const file, char **fields, struct dati_weather *puntatore_dati_weather, const char *const percorso_file_weather, int *const errore);

    /*
     * Funzione per il salvataggio dei dati dal file weather.csv tramite lista concatenata.
     * Restituisce il puntatore alla testa della lista (lo stesso puntatore va 
     * passato come primo argomento).
     * Il puntatore a errore serve per la gestione degli errori secondo la libreria csv.
     * Se la funzione non riesce a creare almeno un nodo o incontra errori, restituisce 
     * NULL e salva l'errore nel puntatore designato. 
    */
    struct dati_weather *estrazione_dati_weather(struct dati_weather * puntatore_dati_weather, const char *const percorso_file_weather, int *const errore);

    /*
     * Funzione per la creazione di nuovo elemento della lista head_weather.
    */
    struct weather *nuovo_elemento_weather(char **fields, struct weather *const elemento_attuale);

     /*
     * Funzione per ricercare i dati di un orario nella lista weather.
     * Il puntatore orario corrisponde alla stringa da cercare.
     * Se il modello non viene trovato restituisce NULL.
    */
    struct weather *cerca_dati_weather(const char *const orario, const struct weather *const head_weather);
	
    /*
     * Funzione per deallocare tutta la memoria utilizzata dalla struttura dati_weather.
     * Anche la lista con i dati del meteo viene deallocata.
    */
	struct dati_weather *svuota_dati_weather(struct dati_weather *puntatore_dati_weather);


    /*
     * Funzione per stampare tutta la lista degli orari weather.
     * Comincia a stampare dal puntatore dato per argomento
     * fino alla fine della lista.
    */
    void stampa_lista_weather(struct weather *head_weather);





    /***********************   GESTIONE CURVE POTENZA E CURVE COEFFICIENTI DI POTENZA   ***********************/


	/*
     * Funzione per la lettura delle curve dei coefficienti di potenza.
     * Array_vento sarà l'array corrispondente ai coefficienti.
     * Puntatore è la testa della lista.
    */
    void lettura_file_power_coefficient(struct turbina *const puntatore, const char *const percorso_file_power_coefficient_curves, int *const errore, float *const array_vento);
	
	/*
     * Funzione chiamata dalla precedente per l'effettivo inserimento dei valori.
    */
	void inserimento_power_coefficients(float *const array_dati, char **fields);
	
	/*
     * Funzione per la lettura delle curve di potenza.
     * Array_vento sarà l'array corrispondente alle curve di potenza.
     * Puntatore è la testa della lista.
    */
    void lettura_file_power_curves(struct turbina *const puntatore, const char *const percorso_file_power_curves, int *const errore, float *const array_vento);
	
	/*
     * Funzione chiamata dalla precedente per l'effettivo inserimento dei valori.
    */
	void inserimento_power_curves(float *const array_dati, char **fields);






    /***********************   GESTIONE ERRORI NEI FILE CSV   ***********************/
    

    /*
     * Funzione per la stampa degli errori che occorrono nella lettura dei file csv.
     * NOTA: per non creare un file .c in più, è stata inserita in estrattore_csv_weather.c.
    */
    void controllo_csv(const int *const errore);



#endif
