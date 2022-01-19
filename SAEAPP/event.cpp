#pragma once
using namespace std;

#include <iostream>

#include "var.h"

Uint32 actualiser(Uint32 interval, void* params) {
	paramsPourTimer* paramsTimer = (paramsPourTimer*)params;

	clock_t temps = clock();
	croissanceBambou(paramsTimer->jardins[*(paramsTimer->jardinActuel)]);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[0] = ((double)temps) / CLOCKS_PER_SEC;
	temps = clock();
	couperBambou(paramsTimer->jardins[*(paramsTimer->jardinActuel)]);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[1] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	afficherCarre(paramsTimer->rendu);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[2] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	actualiserAffichageBambous(paramsTimer->jardins[*(paramsTimer->jardinActuel)], paramsTimer->rendu);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[3] = ((double)temps) / CLOCKS_PER_SEC;
	temps = clock();
	actualiserAffichagePandas(paramsTimer->jardins[*(paramsTimer->jardinActuel)], paramsTimer->rendu, paramsTimer->texturePanda);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[4] = ((double)temps) / CLOCKS_PER_SEC;
	temps = clock();
	actualiserAffichageStatistiques(paramsTimer->jardins[*(paramsTimer->jardinActuel)], paramsTimer->rendu);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[5] = ((double)temps) / CLOCKS_PER_SEC;
	temps = clock();

	afficherLegende(paramsTimer->rendu, paramsTimer->police);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[6] = ((double)temps) / CLOCKS_PER_SEC;
	temps = clock();
	afficherStatNBCoupes(paramsTimer->rendu, paramsTimer->jardins[*(paramsTimer->jardinActuel)]);
	temps = clock() - temps;
	paramsTimer->tempsCalcul[7] = ((double)temps) / CLOCKS_PER_SEC;
	
	afficheTempsCalcul(paramsTimer->rendu, paramsTimer->tempsCalcul);

	SDL_RenderPresent(paramsTimer->rendu);

	return interval;
}

void lancer(SDL_TimerID& timer, paramsPourTimer& paramsTimer, jardins jardins[], int jardinActuel) {
	SDL_RemoveTimer(timer);
	jardins[jardinActuel].manuelActive = false;
	timer = SDL_AddTimer(100, actualiser, &paramsTimer);
}

void pause(SDL_TimerID& timer) {
	SDL_RemoveTimer(timer);
}

void modeManuel(SDL_TimerID& timer, jardins jardins[], int jardinActuel) {
	jardins[jardinActuel].manuelActive = true;
	SDL_RemoveTimer(timer);
}

void diminimuerTimer(int& valeur) {
	if (valeur >= 200) {
		valeur -= 100;
	}
}

void augmanterTimer(int& valeur) {
	valeur += 100;
}

void resetTimer(int& valeur) {
	valeur = 100;
}