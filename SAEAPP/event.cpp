#pragma once
using namespace std;

#include "var.h"

Uint32 actualiser(Uint32 interval, void* params) {
	paramsPourTimer* paramsTimer = (paramsPourTimer*)params;

	croissanceBambou(paramsTimer->jardins[*(paramsTimer->jardinActuel)]);
	couperBambou(paramsTimer->jardins[*(paramsTimer->jardinActuel)]);

	afficherCarre(paramsTimer->rendu);

	actualiserAffichageBambous(paramsTimer->jardins[*(paramsTimer->jardinActuel)], paramsTimer->rendu);
	actualiserAffichagePandas(paramsTimer->jardins[*(paramsTimer->jardinActuel)], paramsTimer->rendu);
	actualiserAffichageStatistiques(paramsTimer->jardins[*(paramsTimer->jardinActuel)], paramsTimer->rendu);

	afficherLegende(paramsTimer->rendu, paramsTimer->police);
	afficherStatNBCoupes(paramsTimer->rendu, paramsTimer->jardins[*(paramsTimer->jardinActuel)]);

	return interval;
}

void lancer(SDL_TimerID& timer, paramsPourTimer& paramsTimer, jardins jardins[], int jardinActuel) {
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