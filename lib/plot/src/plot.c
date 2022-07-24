#include "plot.h"

void plot_curva_potenza(const struct turbina *turbina)
{
    gnuplot_ctrl *gp = NULL;  
    gp = gnuplot_init();

    gnuplot_setstyle(gp, "linespoints");
    gnuplot_set_xlabel(gp, "Velocità del vento [m/s]");
    gnuplot_set_ylabel(gp, "Potenza [kW]");
    gnuplot_cmd(gp, "set grid back nopolar");
    gnuplot_cmd(gp, "xtics nomxtics ytics nomytics noztics nomztics nortics nomrtics nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics");
    gnuplot_plot_xy(gp, turbina->wind_speed, turbina->power_curves, LUNGHEZZA_VETTORE_POWER_CURVES, "Curva di Potenza");

    gnuplot_close(gp);

}

void plot_curva_coefficienti(const struct turbina *turbina)
{
    gnuplot_ctrl *gp = NULL;  
    gp = gnuplot_init();

    gnuplot_setstyle(gp, "linespoints");

    gnuplot_close(gp);
}

void plot_potenza(const struct turbina *turbina)//scrivo anche un file csv coi dati calcolati
{
    gnuplot_ctrl *gp = NULL;  
    gp = gnuplot_init();

    gnuplot_setstyle(gp, "linespoints");
    gnuplot_write_xy_csv(, turbina->wind_speed, turbina->potenza_nominale, , );

    gnuplot_close(gp);
}
