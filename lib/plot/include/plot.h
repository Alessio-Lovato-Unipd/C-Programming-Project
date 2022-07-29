#ifndef PLOT_H
#define PLOT_H

    #include <stdlib.h>
    #include <stdio.h> 
    #include "../../../external/gnuplot_i/src/gnuplot_i.h"
    #include "estrattore_csv.h"
    #include "calcolo_output.h"

    void plot_curva_potenza(const struct turbina *turbina);

    void plot_curva_coefficienti(const struct turbina *turbina);

    void gnuplot_write_xtime_y_csv(const char *file_name, const struct weather *time, const struct potenza_out *y, int n_dati, const char *title);

    void plot_potenza(const struct weather *tempo, const struct potenza_out *potenza, int giorni);
    
#endif
