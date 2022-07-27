#include "plot.h"

//gnuplot_plot genera un file coi dati numerici anche?
//altrimenti genero il file con gnuplot_write e poi lo plotto con gnuplot_atmpfile





void plot_curva_potenza(const struct turbina *turbina)
{
    gnuplot_ctrl *gp = NULL;  
    gp = gnuplot_init(); 
    gnuplot_setstyle(gp, "linespoints");

    gnuplot_set_linecolor(gp, "green");
    //gnuplot_set_linestyle();
    //gnuplot_set_point();

    gnuplot_set_xlabel(gp, "Velocità del vento [m/s]");
    gnuplot_set_ylabel(gp, "Potenza [kW]");
    //comandi diretti a gnuplot
    //gnuplot_cmd(gp, "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 5 ps 1.5");

    gnuplot_cmd(gp, "set grid back nopolar");
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
    float tempo[lunghezza_vettore];
    gnuplot_ctrl *gp = NULL; 

    for(int i = 0; i < lunghezza_vettore; i++){
        tempo[i] = i;
    }

    gp = gnuplot_init();

    gnuplot_setstyle(gp, "linespoints");
    gnuplot_write_xy_csv("potenza.csv", tempo, turbina->potenza_nominale, lunghezza_vettore, "#Potenza elettrica generata dalla turbina nel tempo");
    gnuplot_plot_atmpfile(gp, "potenza.csv", "Potenza elettrica generata dalla turbina nel tempo");

    gnuplot_close(gp);
}
*/
