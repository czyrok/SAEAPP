#pragma once
using namespace std;

#include <iostream>

#include "var.h"

Uint32 actualiser(Uint32 interval, void* params) {
	paramsPourTimer* paramsTimer = (paramsPourTimer*)params;

	actualiser(paramsTimer->rendu, paramsTimer->police, paramsTimer->jardins, paramsTimer->jardinActuel, paramsTimer->texturePanda, false, false);

	return interval;
}

void lancer(SDL_TimerID& timer, paramsPourTimer& paramsTimer, jardins jardins[], int jardinActuel, int tempsTimer) {
	SDL_RemoveTimer(timer);
	jardins[jardinActuel].manuelActive = false;
	timer = SDL_AddTimer(tempsTimer, actualiser, &paramsTimer);
}

void pause(SDL_TimerID& timer) {
	SDL_RemoveTimer(timer);
}

void modeManuel(SDL_TimerID& timer, jardins jardins[], int jardinActuel) {
	jardins[jardinActuel].manuelActive = true;
	SDL_RemoveTimer(timer);
}

void augmenterTimer(int& valeur) {
	if (valeur >= 200) {
		valeur -= 100;
	}
}

void diminuerTimer(int& valeur) {
	valeur += 100;
}

void resetTimer(int& valeur) {
	valeur = 100;
}

void actualiser(SDL_Renderer* rendu, TTF_Font* police, jardins* jardins, int* jardinActuel, SDL_Texture* texturePanda, bool manuel, bool setup) {
	clock_t temps = clock();
	if (!setup) croissanceBambou(jardins[*jardinActuel]);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	if (!manuel) couperBambou(jardins[*jardinActuel]);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	afficherCarre(rendu);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	actualiserAffichageBambous(jardins[*jardinActuel], rendu);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	actualiserAffichagePandas(jardins[*jardinActuel], rendu, texturePanda);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	actualiserAffichageStatistiques(jardins[*jardinActuel], rendu);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	afficherLegende(rendu, police);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	temps = clock();
	afficherStatNBCoupes(rendu, jardins[*jardinActuel]);
	temps = clock() - temps;
	jardins[*jardinActuel].tailleTempsCalculStat[jardins[*jardinActuel].indTempsCalculStat++ % NBStats] = ((double)temps) / CLOCKS_PER_SEC;

	afficherTempsCalcul(rendu, jardins[*jardinActuel]);

	SDL_RenderPresent(rendu);
}