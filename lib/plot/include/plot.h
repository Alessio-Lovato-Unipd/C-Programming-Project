#ifndef PLOT_H
#define PLOT_H

    #include <stdlib.h>
    #include <stdio.h> 
    #include "../../../external/gnuplot_i/src/gnuplot_i.h"
    #include "estrattore_csv.h"
    #include "calcolo_output.h"

    //genera grafico della curva di potenza
    void plot_curva_potenza(float *array_vento, const struct turbina *turbina);

    //genera grafico curva coefficienti di potenza x
    void plot_curva_coefficienti(float *array_vento, const struct turbina *turbina);

    //genera file csv con tempo e potenza corrispondente
    void gnuplot_write_xtime_y_csv(const char *file_name, const struct weather *time, const float *y, int n_dati, const char *title);

    //genera grafico e csv dell'andamento di potenza in un arco temporale di giorni impostati
    void plot_time_potenza(const struct weather *tempo, const float *potenza, int giorni);

    void gnuplot_set_title(gnuplot_ctrl * h, const struct weather *head_tempo, int giorni);

    //genera grafico potenza con x = array di numeri naturali
    void plot_potenza(const struct weather *head_tempo,const char *nome_turbina, const float *potenza, int giorni);
    
#endif


