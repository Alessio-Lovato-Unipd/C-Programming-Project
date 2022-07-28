#ifndef PLOT_H
#define PLOT_H

    #include <stdlib.h>
    #include <stdio.h> 
    #include "../../../external/gnuplot_i/src/gnuplot_i.h"
    #include "estrattore_csv.h"
    #include "calcolo_output.h"

    void plot_curva_potenza(const struct turbina *turbina);

    void plot_curva_coefficienti(const struct turbina *turbina);

    void plot_potenza(const struct turbina *turbina, const struct weather *meteo,int giorni);
    
#endif
