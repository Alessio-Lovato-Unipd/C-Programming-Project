#include "calcolo_output.h"

float calcolo_potenza_curve_di_potenza(tipo_calcolo_output metodo, const char *nome_turbina, const struct turbina *head, float vel_vento)
{
	const struct turbina *temp = head;
	float vel_min = 0;
	float vel_max = 0;
	int indice = 0;
	while(strcmp(nome_turbina, temp->nome) != 0){
		temp = scorri_lista_turbina(temp);
		if(temp == NULL){
			printf("turbina non trovata, inserire nuovo nome\n");
			exit(EXIT_FAILURE);
		}
	}
	indice = trova_vel_vento_per_interpolazione(&vel_min, &vel_max, vel_vento, temp, LUNGHEZZA_VETTORE_POWER_CURVES);
	
	if(indice == LUNGHEZZA_VETTORE_POWER_CURVES){
		if(temp->power_curves[indice] == -1)
			return temp->power_curves[indice - 1]; //se manca l'ultimo valore, diamo il penultimo
		return temp->power_curves[indice];
	}
	if(temp->power_curves[indice] == -1)
		temp->power_curves[indice] = interpolazione_potenza_per_valori_mancanti(metodo, temp, indice);
	if(temp->power_curves[indice - 1] == -1)
		temp->power_curves[indice - 1] = interpolazione_potenza_per_valori_mancanti(metodo, temp, (indice - 1));
	
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

float calcolo_potenza_curve_coefficienti(tipo_calcolo_output metodo, const char *nome_turbina, const struct turbina *head, float vel_vento, float densita_aria)
{
	const struct turbina *temp = head;
	float vel_min = 0;
	float vel_max = 0;
	int indice = 0;
	float pot_min = 0;
	float pot_max = 0;
	while(strcmp(nome_turbina, temp->nome) != 0){
		temp = scorri_lista_turbina(temp);
		if(temp == NULL){
			printf("turbina non trovata, inserire nuovo nome\n");
			exit(EXIT_FAILURE);
		}
	}
	indice = trova_vel_vento_per_interpolazione(&vel_min, &vel_max, vel_vento, temp, LUNGHEZZA_VETTORE_POWER_COEFFICIENT);
	
	if(indice == LUNGHEZZA_VETTORE_POWER_COEFFICIENT){
		if(temp->power_coefficients[indice] == -1)
			return calcolo_potenza_da_coefficienti(densita_aria, temp->diametro_rotore, vel_vento, temp->power_coefficients[indice - 1]);; //se manca l'ultimo valore, diamo il penultimo
		return calcolo_potenza_da_coefficienti(densita_aria, temp->diametro_rotore, vel_vento, temp->power_coefficients[indice]);
	}
	if(temp->power_coefficients[indice] == -1)
		temp->power_coefficients[indice] = interpolazione_coefficienti_per_valori_mancanti(metodo, temp, indice);
	if(temp->power_coefficients[indice - 1] == -1)
		temp->power_coefficients[indice - 1] = interpolazione_coefficienti_per_valori_mancanti(metodo, temp, (indice - 1));
	
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

//nel caso di valori mancanti nella curva di potenza faccio interpolazione
float interpolazione_potenza_per_valori_mancanti(tipo_calcolo_output metodo, const struct turbina *puntatore, int i)
{
	switch(metodo){
	case INTERPOLAZIONE_LINEARE_O:
		return interpolazione_lineare(puntatore->wind_speed[i - 1], puntatore->power_curves[i - 1], puntatore->wind_speed[i + 1], puntatore->power_curves[i + 1], puntatore->wind_speed[i]);
	case INTERPOLAZIONE_LOGARITMICA_O:
		return interpolazione_logaritmica(puntatore->wind_speed[i - 1], puntatore->power_curves[i - 1], puntatore->wind_speed[i + 1], puntatore->power_curves[i + 1], puntatore->wind_speed[i]);
	default:
		return interpolazione_lineare(puntatore->wind_speed[i - 1], puntatore->power_curves[i - 1], puntatore->wind_speed[i + 1], puntatore->power_curves[i + 1], puntatore->wind_speed[i]);
	}
}

float interpolazione_coefficienti_per_valori_mancanti(tipo_calcolo_output metodo, const struct turbina *puntatore, int i)
{
	switch(metodo){
	case INTERPOLAZIONE_LINEARE_O:
		return interpolazione_lineare(puntatore->wind_speed[i - 1], puntatore->power_coefficients[i - 1], puntatore->wind_speed[i + 1], puntatore->power_coefficients[i + 1], puntatore->wind_speed[i]);
	case INTERPOLAZIONE_LOGARITMICA_O:
		return interpolazione_logaritmica(puntatore->wind_speed[i - 1], puntatore->power_coefficients[i - 1], puntatore->wind_speed[i + 1], puntatore->power_coefficients[i + 1], puntatore->wind_speed[i]);
	default:
		return interpolazione_lineare(puntatore->wind_speed[i - 1], puntatore->power_coefficients[i - 1], puntatore->wind_speed[i + 1], puntatore->power_coefficients[i + 1], puntatore->wind_speed[i]);
	}
}
