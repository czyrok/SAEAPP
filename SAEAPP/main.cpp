#pragma once
using namespace std;

#include <iostream>

#include "var.h"

int main(int argc, char* argv[])
{
    jardins jardins[2];
    int NBJardins = 0;

	bambous bambous[15];
	int NBBambous = 0;

	for (int i = 0; i < 10; i++) {
		initBambous(
			bambous,
			NBBambous,
			i + 1
		);

		bambous[NBBambous].taillePousse = 10;
	}

	pandas pandas[1];
	int NBPandas = 0;

	initPandas(pandas, NBPandas, 0);

	initJardin(
		jardins,
		NBJardins,
		"cc",
		bambous,
		NBBambous,
		pandas,
		NBPandas,
		-1,
		"ReduceMax",
		false
	);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;

	SDL_Window* fen = SDL_CreateWindow("SAPP",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		TAILLEFENX,
		TAILLEFENY,
		SDL_WINDOW_SHOWN
	);

	if (fen == NULL) return 2;

	SDL_Renderer* rendu = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED);

	afficherMenu(rendu);
	afficherBar(rendu);
	afficherCarre(rendu);

	bool ouvert = true;
	SDL_Event event;

	while (ouvert) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				cout << "salut" << endl;
				actualiserAffichageBambous(jardins[0], rendu);

				/*if (event.button.x > TAILLEX - TAILLE_PA) {
					for (int i = 0; i < NB_COULEURS_PA; i++) {
						if (
							event.button.x > positionRectPalette[i].x
							&& event.button.x < positionRectPalette[i].x + positionRectPalette[i].w
							&& event.button.y > positionRectPalette[i].y
							&& event.button.y < positionRectPalette[i].y + positionRectPalette[i].h
							) {
							SDL_SetRenderDrawColor(rendu, CODE_COULEURS_PA[i].r, CODE_COULEURS_PA[i].g, CODE_COULEURS_PA[i].b, 255);
							break;
						}
					}

					if (event.button.x < TAILLEX - TAILLE_PA + TAILLE_BOUTON[0] && event.button.y > TAILLEY - TAILLE_BOUTON[1]) {
						sauvegarder_dessin(rendu);
					}
				}
				else {
					dessiner_pixel(event.button.y / CARRE, event.button.x / CARRE, rendu, tabCouleur);

					SDL_RenderPresent(rendu);
				}*/
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_n) {
				//negatif(tabCouleur, rendu);
			}
			break;
		case SDL_QUIT:
			ouvert = false;
			break;
		}
	}

	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(fen);
	SDL_Quit();
	return 0;
}