#include "calcolo_output.h"

float calcolo_potenza_curve_di_potenza(const char *nome_turbina, const struct turbina *head, float vel_vento)
{
	struct turbina *temp = head;
	int vel_min = 0;
	int vel_max = 0;
	float potenza = 0;
	int indice = 0;
	while(strcmp(nome_turbina, temp->nome) != 0){
		temp = scorri_lista_turbina(temp);
		if(temp == NULL){
			printf("turbina non trovata, inserire nuovo nome\n");
			svuota_lista_turbine_data(head);
			exit(EXIT_FAILURE);
		}
	}
	indice = trova_vel_vento_per_interpolazione(&vel_min, &vel_max, vel_vento, temp);
	if(indice == LUNGHEZZA_VETTORE_CURVE)
		return temp->power_curves[indice];
	//richiamo funzioni interpolazione con ingresso le due potenze corrispondenti alle vel_max e vel_min
	return potenza;
}

float calcolo_potenza_curve_coefficienti(const char *nome_turbina, const struct turbina *head, float vel_vento)
{
	struct turbina *temp = head;
	int vel_min = 0;
	int vel_max = 0;
	int indice = 0;
	float potenza = 0;
	while(strcmp(nome_turbina, temp->nome) != 0){
		temp = scorri_lista_turbina(temp);
		if(temp == NULL){
			printf("turbina non trovata, inserire nuovo nome\n");
			svuota_lista_turbine_data(head);
			exit(EXIT_FAILURE);
		}
	}
	indice = trova_vel_vento_per_interpolazione(&vel_min, &vel_max, vel_vento, temp);
	if(indice == LUNGHEZZA_VETTORE_CURVE)
		return temp->power_coefficients[indice];
	//richiamo funzioni interpolazione con ingresso le due potenze corrispondenti alle vel_max e vel_min
	return potenza;
}

int trova_vel_vento_per_interpolazione(int *vel_min, int *vel_max, int vel_vento, const struct turbina *target) //ritorna il valore in cui vel_vento = vel_max
{
	int i = 0;
	for(i = 0; i <= LUNGHEZZA_VETTORE_CURVE; i++){
		if(target->wind_speed[i] > vel_vento){
			*vel_max = target->wind_speed[i];
			*vel_min = target->wind_speed[i - 1];
		}
	}
	return i;
}