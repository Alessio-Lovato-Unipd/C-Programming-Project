#ifndef PLOT_H
#define PLOT_H

    #include <stdlib.h>
    #include <stdio.h>
    #include "estrattore_csv.h"
    #include "../../../external/gnuplot_i/src/gnuplot_i.h"

    void plot_curva_potenza(const struct turbina *turbina);

    void plot_curva_coefficienti(const struct turbina *turbina);
    
#endif
