#pragma once
using namespace std;

#include <iostream>

#include "var.h"

jardins jardins[2];
int NBJardins = 0;

Uint32 actualiser(Uint32 interval, void* rendu) {
	croissanceBambou(jardins[0]);
	couperBambou(jardins[0]);

	afficherCarre((SDL_Renderer*)rendu);

	actualiserAffichageBambous(jardins[0], (SDL_Renderer*)rendu);
	actualiserAffichagePandas(jardins[0], (SDL_Renderer*)rendu);

	return interval;
}

int main(int argc, char* argv[])
{
	/*bambous bambous[15];
	int NBBambous = 0;

	for (int i = 0; i < 10; i++) {
		initBambous(
			bambous,
			NBBambous,
			i + 1
		);
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
		"ReduceFastest",
		false
	);*/

	importerConfig(jardins, NBJardins);

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

	TTF_Init();
	TTF_Font* police = TTF_OpenFont("C:\\Windows\\Fonts\\calibri.ttf", 25);

	afficherMenu(rendu);
	afficherBar(rendu);
	afficherCarre(rendu);

	SDL_Rect rectBoutonsBar[10];
	char boutonsBar[10][NBMaxCaracBoutons] = { { "Mode" }, { "Lancer" }, { "Pause" } };
	int NBButonsBar = 3;

	afficherBoutonsBar(rendu, police, rectBoutonsBar, boutonsBar, NBButonsBar);

	bool ouvert = true;
	SDL_Event event;

	SDL_TimerID timer;

	while (ouvert) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
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
			if (event.key.keysym.sym == SDLK_l) {
				timer = SDL_AddTimer(250, actualiser, rendu);
			}
			else if (event.key.keysym.sym == SDLK_p) {
				SDL_RemoveTimer(timer);
			}
			break;
		case SDL_QUIT:
			ouvert = false;
			break;
		}
	}

	TTF_CloseFont(police);
	TTF_Quit();

	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(fen);
	SDL_Quit();
	return 0;
}