#include <plot.h>

void plot_curva_potenza(const struct turbina *turbina)
{
    FILE *file_curva_potenza;
    FILE *comandi_gnuplot;

    file_curva_potenza = fopen("curva_potenza.txt", "w");

    for (int i = 0; turbina->wind_speed != NULL; i++)
    {
       fprintf(file_curva_potenza, "%f %f\n", turbina->wind_speed[i], turbina->power_curves[i]);
    }
    
    fclose(file_curva_potenza);
    
    comandi_gnuplot = fopen("gnuplot.txt", "w+");
    fprintf(comandi_gnuplot, "");
    fclose(comandi_gnuplot);

    system("gnuplot comando.txt");
}

void plot_curva_coefficienti()
{

}

void plot_potenza()
{

}
