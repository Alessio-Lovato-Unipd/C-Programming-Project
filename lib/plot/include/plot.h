#ifndef PLOT_H
#define PLOT_H

    #include <stdlib.h>
    #include <stdio.h> 
    #include "../../../external/gnuplot_i/src/gnuplot_i.h"
    #include "estrattore_csv.h"
    #include "calcolo_output.h"

    /*
    * Genera il grafico della curva di potenza della turbina data
    * e lo alva in .png 
    */
    void plot_curva_potenza(float *array_vento, const struct turbina *turbina);

    /*
    * Genera grafico della curva coefficienti di potenza 
    * della turbina data e lo salva in .png
    */
    void plot_curva_coefficienti(float *array_vento, const struct turbina *turbina);

    /*
    * Genera file csv a due colonne con tempo e potenza istantanea corrispondente
    */
    void gnuplot_write_xtime_y_csv(const char *file_name, const struct weather *time, const float *y, int n_dati, const char *title);

    /*
    * Genera grafico e file csv dell'andamento di potenza in un arco temporale di giorni impostati
    * con i valori temporali plottati nell'asse x
    * 
    * NON FUNZIONA ANCORA
    */
    void plot_time_potenza(const struct weather *tempo, const float *potenza, int giorni);

    /*
    * Crea il titolo del grafico inserendo l'orario e data di partenza dell'arco temporale
    * considerato e dicendo il numero di giorni visualizzato
    */
    void gnuplot_set_title(gnuplot_ctrl * h, const struct weather *head_tempo, int giorni);

    /*
    * Genera grafico e file csv dell'andamento di potenza generata nell'arco temporale
    * di giorni impostati.
    * Nell'asse x sono riportate il numero di ore considerate a partire dall'inizio 
    */
    void plot_potenza(const struct weather *head_tempo,const char *nome_turbina, float *potenza, int giorni);
    
#endif


