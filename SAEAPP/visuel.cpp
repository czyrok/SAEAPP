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

void actualiserAffichagePanda(jardins& jardin)
{

}