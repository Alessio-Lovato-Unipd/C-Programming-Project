#include "plot.h"

//gnuplot_plot genera un file coi dati numerici anche?
//altrimenti genero il file con gnuplot_write e poi lo plotto con gnuplot_atmpfile


void plot_curva_potenza(const struct turbina *turbina)
{
    gnuplot_ctrl *gp = NULL;  
    gp = gnuplot_init(); 
    gnuplot_setstyle(gp, "linespoints");
    gnuplot_set_xlabel(gp, "Velocità del vento [m/s]");
    gnuplot_set_ylabel(gp, "Potenza [kW]");
    //comandi diretti a gnuplot
    gnuplot_cmd(gp, "set grid back nopolar");
    gnuplot_cmd(gp, "set xrange[0:35]");
    gnuplot_cmd(gp, "set yrange[0:35]");
    gnuplot_cmd(gp, "set terminal png");
	gnuplot_cmd(gp, "set output \"curva_di_potenza.png\"");
    gnuplot_plot_xy(gp, turbina->wind_speed, turbina->power_curves, LUNGHEZZA_VETTORE_POWER_CURVES, "Curva di Potenza");

    gnuplot_close(gp);

}

void plot_curva_coefficienti(const struct turbina *turbina)
{
    gnuplot_ctrl *gp = NULL;  
    gp = gnuplot_init();
    gnuplot_cmd(gp, "set terminal png");
	gnuplot_cmd(gp, "set output \"curva_di_potenza.png\"");
    gnuplot_setstyle(gp, "linespoints");
    gnuplot_set_xlabel(gp, "Velocità del vento [m/s]");
    gnuplot_set_ylabel(gp, "Coefficienti di potenza");
    gnuplot_plot_xy(gp, turbina->wind_speed, turbina->power_coefficients, LUNGHEZZA_VETTORE_POWER_COEFFICIENT, "Curva coefficienti di potenza");

    gnuplot_close(gp);
}

/*
void plot_potenza(const struct turbina *turbina, const struct weather *meteo, int lunghezza_vettore)//scrivo anche un file csv coi dati calcolati
{
    gnuplot_ctrl *gp = NULL;  
    gp = gnuplot_init();

    gnuplot_setstyle(gp, "linespoints");
    gnuplot_write_xy_csv("potenza.csv", , turbina->potenza_nominale, lunghezza_vettore, "#Potenza elettrica generata dalla turbina nel tempo");

    gnuplot_close(gp);
}
*/
