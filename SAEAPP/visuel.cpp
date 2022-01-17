#pragma once
using namespace std;

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
	SDL_Rect carre = { TAILLEMENUX, TAILLEBARY, TAILLEFENX - TAILLEMENUX, TAILLEFENY - TAILLEBARY };

	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_RenderPresent(rendu);
}

void actualiserAffichagePandas(jardins& jardin, SDL_Renderer* rendu)
{
	int i, nouveau;
	jardin.pandas[i]->x = 0;
	for (i = 0; i < jardin.NBPandas; i++) {
		jardin.pandas[i]->x = 6 + x;
		nouveau = jardin.pandas[i]->x;
		SDL_Rect rect;
		rect.x = TAILLEMENUX + nouveau;
		rect.y = TAILLEFENY - 6;
		rect.w = 20;
		rect.h = 6;
		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		SDL_RenderFillRect(rendu, &rect);
	}
	SDL_RenderPresent(rendu);
}