#ifndef PLOT_H
#define PLOT_H

    #include <stdlib.h>
    #include <stdio.h> 
    #include "../../../external/gnuplot_i/src/gnuplot_i.h"
    #include "estrattore_csv.h"
    #include "calcolo_output.h"

    //genera grafico della curva di potenza
    void plot_curva_potenza(float *x, const struct turbina *turbina);

    //genera grafico curva coefficienti di potenza
    void plot_curva_coefficienti(float *x, const struct turbina *turbina);

    //genera file csv con tempo e potenza corrispondente
    void gnuplot_write_xtime_y_csv(const char *file_name, const struct weather *time, const struct potenza_out *y, int n_dati, const char *title);


    void plot_potenza(const struct weather *tempo, const struct potenza_out *potenza, int giorni);
    
#endif
