#pragma once
using namespace std;

#include <iostream>

#include "var.h"

void afficherMenu(SDL_Renderer* rendu) {
	SDL_Rect menu = { 0, TAILLEBARY, TAILLEMENUX, TAILLEFENY };

	SDL_SetRenderDrawColor(rendu, 59, 93, 108, 255);
	SDL_RenderFillRect(rendu, &menu);

	SDL_RenderPresent(rendu);
}

void afficherBar(SDL_Renderer* rendu) {
	SDL_Rect bar = { 0, 0, TAILLEFENX, TAILLEBARY };

	SDL_SetRenderDrawColor(rendu, 37, 60, 71, 255);
	SDL_RenderFillRect(rendu, &bar);

	SDL_RenderPresent(rendu);
}

void afficherCarre(SDL_Renderer* rendu) {
	SDL_Rect carre = { TAILLEMENUX, TAILLEBARY, TAILLEFENX - TAILLEMENUX - (NBStats * 3), TAILLEFENY - TAILLEBARY };

	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_Rect carre2 = { TAILLEFENX - (NBStats * 3), TAILLEBARY, TAILLEFENX - (NBStats * 3), TAILLEFENY - TAILLEBARY };

	SDL_SetRenderDrawColor(rendu, 189, 189, 189, 255);
	SDL_RenderFillRect(rendu, &carre2);

	SDL_RenderPresent(rendu);
}

void actualiserAffichagePandas(jardins& jardin, SDL_Renderer* rendu)
{
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);

	for (int i = 0; i < jardin.NBPandas; i++) {
		SDL_Rect rect;
		rect.x = TAILLEMENUX + taillePandaX * jardin.pandas[i].x;
		rect.y = TAILLEFENY - taillePandaY;
		rect.w = taillePandaX;
		rect.h = taillePandaY;

		SDL_RenderFillRect(rendu, &rect);
	}

	SDL_RenderPresent(rendu);
}

void actualiserAffichageBambous(jardins& jardin, SDL_Renderer* rendu)
{
	SDL_SetRenderDrawColor(rendu, 68, 118, 54, 255);

	for (int i = 0; i < jardin.NBBambous; i++) {
		for (int j = 0; j < jardin.bambous[i].taillePousse; j++) {
			SDL_Rect carre = { TAILLEMENUX + (tailleBambousX * i) + 2, (TAILLEFENY - taillePandaY - ((float)jardin.bambous[i].vitessePousse * (float)7 * (j + 1))), tailleBambousX - 4, jardin.bambous[i].vitessePousse * 7 };

			SDL_RenderFillRect(rendu, &carre);
		}
	}

	SDL_RenderPresent(rendu);
}

void actualiserAffichageStatistiques(jardins& jardin, SDL_Renderer* rendu)
{
	int x = jardin.indStat;
	float taillemax = jardin.tailleMaxStat[jardin.indStat];
	float taillemin = jardin.tailleMinStat[jardin.indStat];
	float taillemoy = jardin.tailleMoyStat[jardin.indStat];
	actualiserStats(jardin);
	SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge
	SDL_RenderDrawLine(rendu, x, taillemax, jardin.indStat, jardin.tailleMaxStat[jardin.indStat]);
	SDL_Rect pointmax;
	pointmax.x = 0 + x;
	pointmax.y = TAILLEFENY - taillemax;
	pointmax.w = 0 + jardin.indStat;
	pointmax.h = TAILLEFENY - jardin.tailleMaxStat[jardin.indStat];
	SDL_RenderFillRect(rendu, &pointmax);
	SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255); //min vert
	SDL_Rect pointmin;
	pointmin.x = 0 + x;
	pointmin.y = TAILLEFENY - taillemin;
	pointmin.w = 0 + jardin.indStat;
	pointmin.h = TAILLEFENY - jardin.tailleMinStat[jardin.indStat];
	SDL_RenderDrawLine(rendu, x, taillemin, jardin.indStat, jardin.tailleMinStat[jardin.indStat]);
	SDL_RenderFillRect(rendu, &pointmin);
	SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
	SDL_RenderDrawLine(rendu, x, taillemoy, jardin.indStat, jardin.tailleMoyStat[jardin.indStat]);
	SDL_Rect pointmoyenne;
	pointmoyenne.x = 0 + x;
	pointmoyenne.y = TAILLEFENY - taillemoy;
	pointmoyenne.w = 0 + jardin.indStat;
	pointmoyenne.h = TAILLEFENY - jardin.tailleMoyStat[jardin.indStat];
	SDL_RenderFillRect(rendu, &pointmoyenne);
}