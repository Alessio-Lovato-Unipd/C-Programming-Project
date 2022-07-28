#include "calcolo_output.h"

float calcolo_potenza_curve_di_potenza(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float vel_vento)
{
	struct turbina *temp = head;
	float vel_min = 0;
	float vel_max = 0;
	int indice = 0;
	while(strcmp(nome_turbina, temp->nome) != 0){
		temp = scorri_lista_turbina(temp);
		if(temp == NULL){
			printf("turbina non trovata, inserire nuovo nome\n");
			svuota_lista_turbine_data((struct turbina *) head);
			exit(EXIT_FAILURE);
		}
	}
	
	//interpolazione della curva
	interpolazione_potenza_per_valori_mancanti(metodo, temp);
	
	indice = trova_vel_vento_per_interpolazione(&vel_min, &vel_max, vel_vento, temp, LUNGHEZZA_VETTORE_POWER_CURVES);
	if(indice == LUNGHEZZA_VETTORE_POWER_CURVES){
		return temp->power_curves[indice];
	}
	
	//richiamo funzioni interpolazione con ingresso le due potenze corrispondenti alle vel_max e vel_min
	switch(metodo){
	case INTERPOLAZIONE_LINEARE_O:
		return interpolazione_lineare(vel_min, temp->power_curves[indice - 1], vel_max, temp->power_curves[indice], vel_vento);
	case INTERPOLAZIONE_LOGARITMICA_O:
		return interpolazione_logaritmica(vel_min, temp->power_curves[indice - 1], vel_max, temp->power_curves[indice], vel_vento);
	default:
		return interpolazione_lineare(vel_min, temp->power_curves[indice - 1], vel_max, temp->power_curves[indice], vel_vento);
	}
}

float calcolo_potenza_curve_coefficienti(tipo_calcolo_output metodo, const char *nome_turbina, struct turbina *head, float vel_vento, float densita_aria)
{
	struct turbina *temp = head;
	float vel_min = 0;
	float vel_max = 0;
	int indice = 0;
	float pot_min = 0;
	float pot_max = 0;
	while(strcmp(nome_turbina, temp->nome) != 0){
		temp = scorri_lista_turbina(temp);
		if(temp == NULL){
			printf("turbina non trovata, inserire nuovo nome\n");
			svuota_lista_turbine_data((struct turbina *) head);
			exit(EXIT_FAILURE);
		}
	}
	
	//interpolazione della curva
	interpolazione_coefficienti_per_valori_mancanti(metodo, temp);
	
	indice = trova_vel_vento_per_interpolazione(&vel_min, &vel_max, vel_vento, temp, LUNGHEZZA_VETTORE_POWER_COEFFICIENT);
	if(indice == LUNGHEZZA_VETTORE_POWER_COEFFICIENT){
		return calcolo_potenza_da_coefficienti(densita_aria, temp->diametro_rotore, vel_vento, temp->power_coefficients[indice]);
	}
	
	//calcolo le potenze corrispondenti ai coefficienti
	pot_min = calcolo_potenza_da_coefficienti(densita_aria, temp->diametro_rotore, vel_min, temp->power_coefficients[indice - 1]);
	pot_max = calcolo_potenza_da_coefficienti(densita_aria, temp->diametro_rotore, vel_max, temp->power_coefficients[indice]);
	//richiamo funzioni interpolazione con ingresso le due potenze corrispondenti alle vel_max e vel_min
	switch(metodo){
	case INTERPOLAZIONE_LINEARE_O:
		return interpolazione_lineare(vel_min, pot_min, vel_max, pot_max, vel_vento);
	case INTERPOLAZIONE_LOGARITMICA_O:
		return interpolazione_logaritmica(vel_min, pot_min, vel_max, pot_max, vel_vento);
	default:
		return interpolazione_lineare(vel_min, pot_min, vel_max, pot_max, vel_vento);
	}
}

int trova_vel_vento_per_interpolazione(float *vel_min, float *vel_max, float vel_vento, const struct turbina *target, int lunghezza_vettore) //ritorna il valore in cui vel_vento = vel_max
{
	int i;
	for(i = 1; i <= lunghezza_vettore; i++){
		if(target->wind_speed[i] >= vel_vento){
			*vel_max = target->wind_speed[i];
			*vel_min = target->wind_speed[i - 1];
			return i;
		}
	}
	return i;
}

//per ogni curva di interesse svolgerò un controllo dei valori mancanti e farò interpolazione
void interpolazione_potenza_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt)
{
	int i, j;
	punt->power_curves[0] = 0.0;
	for(i = 1; i <= LUNGHEZZA_VETTORE_POWER_CURVES; i++){
		if(punt->power_curves[i] == -1){ //devo fare interpolazione tra il valore precedente e il successivo non nullo
			for(j = i; j <= LUNGHEZZA_VETTORE_POWER_CURVES; j++){
				if(punt->power_curves[j] != -1)
					break;
			}
			switch(metodo){
			case INTERPOLAZIONE_LINEARE_O:
				punt->power_curves[i] = (int) interpolazione_lineare(punt->wind_speed[i - 1], punt->power_curves[i - 1], punt->wind_speed[j], punt->power_curves[j], punt->wind_speed[i]);
				break;
			case INTERPOLAZIONE_LOGARITMICA_O:
				punt->power_curves[i] = (int) interpolazione_logaritmica(punt->wind_speed[i - 1], punt->power_curves[i - 1], punt->wind_speed[j], punt->power_curves[j], punt->wind_speed[i]);
				break;
			default:
				punt->power_curves[i] = (int) interpolazione_lineare(punt->wind_speed[i - 1], punt->power_curves[i - 1], punt->wind_speed[j], punt->power_curves[j], punt->wind_speed[i]);
				break;
			}
		}
	}

}

void interpolazione_coefficienti_per_valori_mancanti(tipo_calcolo_output metodo, struct turbina *punt)
{
	int i, j;
	punt->power_coefficients[0] = 0.0;
	for(i = 1; i <= LUNGHEZZA_VETTORE_POWER_COEFFICIENT; i++){
		if(punt->power_coefficients[i] == -1){ //devo fare interpolazione tra il valore precedente e il successivo non nullo
			for(j = i; j <= LUNGHEZZA_VETTORE_POWER_COEFFICIENT; j++){
				if(punt->power_coefficients[j] != -1)
					break;
			}
			switch(metodo){
			case INTERPOLAZIONE_LINEARE_O:
				punt->power_coefficients[i] = interpolazione_lineare(punt->wind_speed[i - 1], punt->power_coefficients[i - 1], punt->wind_speed[j], punt->power_coefficients[j], punt->wind_speed[i]);
				break;
			case INTERPOLAZIONE_LOGARITMICA_O:
				punt->power_coefficients[i] = interpolazione_logaritmica(punt->wind_speed[i - 1], punt->power_coefficients[i - 1], punt->wind_speed[j], punt->power_coefficients[j], punt->wind_speed[i]);
				break;
			default:
				punt->power_coefficients[i] = interpolazione_lineare(punt->wind_speed[i - 1], punt->power_coefficients[i - 1], punt->wind_speed[j], punt->power_coefficients[j], punt->wind_speed[i]);
				break;
			}
		}
	}
}