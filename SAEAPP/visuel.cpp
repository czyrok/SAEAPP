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
	SDL_Rect carre = { TAILLEMENUX, TAILLEBARY, TAILLEFENX - TAILLEMENUX - tailleStatsX, tailleStatsY };

	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_Rect carre2 = { TAILLEFENX - tailleStatsX, TAILLEBARY, TAILLEFENX - tailleStatsX, tailleStatsY };

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
	int i;
	float taillemax = jardin.tailleMaxStat[jardin.indStat];
	float taillemin = jardin.tailleMinStat[jardin.indStat];
	float taillemoy = jardin.tailleMoyStat[jardin.indStat];
	
	if (jardin.indStat < 100) {
		for (i = 0; i < jardin.indStat; i++) {
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge

			SDL_Rect pointmax;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmax.y = TAILLEFENY - jardin.tailleMaxStat[i];
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmax);

			if (jardin.indStat > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMaxStat[i - 1], pointmax.x,pointmax.y);
			}

			SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255); //min vert
			SDL_Rect pointmin;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmax.y = TAILLEFENY - jardin.tailleMinStat[i];
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmin);

			if (jardin.indStat > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMinStat[i - 1], pointmax.x, pointmax.y);
			}
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
			SDL_Rect pointmoy;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmax.y = TAILLEFENY - jardin.tailleMoyStat[i];
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmoy);

			if (jardin.indStat > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMoyStat[i - 1], pointmax.x, pointmax.y);
			}
		}
	}
	else {
		for (i = jardin.indStat % 100; i < 100; i++) {
		}
		for (i = 0; i < jardin.indStat % 100; i++) {
		}
	}

	SDL_RenderPresent(rendu);
}