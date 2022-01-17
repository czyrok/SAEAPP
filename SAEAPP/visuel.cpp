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
	SDL_Rect carre = { TAILLEMENUX, TAILLEBARY, TAILLEFENX - TAILLEMENUX, TAILLEFENY - TAILLEBARY };

	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_RenderPresent(rendu);
}

void actualiserAffichagePanda(jardins& jardin)
{

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