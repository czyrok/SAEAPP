#pragma once
using namespace std;

#include <iostream>

#include "var.h"

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

	/* SDL_RenderDrawLine(rendu, carre.x - tailleFosse / 2, carre.y, carre.w + tailleFosse, 1); */

	jardins jardins[2];
	int NBJardins = 0;
	int jardinActuel = 0;

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

	afficherLegende(rendu, police);
	afficherStatNBCoupes(rendu, jardins[jardinActuel]);
	afficherEchelle(rendu);

	SDL_Rect rectBoutonsBar[10];
	char boutonsBar[10][NBMaxCaracBoutons] = { { "Lancer" }, { "Pause" }, { "Mode manuel" } };
	int NBBoutonsBar = 3;
	afficherBoutonsBar(rendu, police, rectBoutonsBar, boutonsBar, NBBoutonsBar);

	SDL_Rect rectBoutonsMenuHaut[10];
	char boutonsMenuHaut[10][NBMaxCaracBoutons] = { { "Mode ReduceMax" }, { "Mode ReduceFastest" } };
	int NBBoutonsMenuHaut = 2;
	SDL_Rect rectBoutonsBas[10];
	char boutonsMenuBas[10][NBMaxCaracBoutons] = { { "Exporter" }, { "Importer" } };
	int NBBoutonsMenu = 2;
	afficherBoutonsMenu(rendu, police, rectBoutonsMenuHaut, boutonsMenuHaut, NBBoutonsMenuHaut, rectBoutonsBas, boutonsMenuBas, NBBoutonsMenu);

	bool ouvert = true;
	SDL_Event event;

	paramsPourTimer paramsTimer;

	paramsTimer.rendu = rendu;
	paramsTimer.police = police;
	paramsTimer.jardins = jardins;
	paramsTimer.jardinActuel = &jardinActuel;

	SDL_TimerID timer = SDL_AddTimer(100, actualiser, &paramsTimer);
	SDL_RemoveTimer(timer);

	while (ouvert) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				for (int i = 0; i < NBBoutonsBar; i++) {
					if (
						event.button.x > rectBoutonsBar[i].x
						&& event.button.x < rectBoutonsBar[i].x + rectBoutonsBar[i].w
						&& event.button.y > rectBoutonsBar[i].y
						&& event.button.y < rectBoutonsBar[i].y + rectBoutonsBar[i].h
						) {
						
						if (strcmp(boutonsBar[i], "Lancer") == 0) {
							lancer(timer, paramsTimer, jardins, jardinActuel);
						}
						else if (strcmp(boutonsBar[i], "Pause") == 0) {
							pause(timer);
						}
						else if (strcmp(boutonsBar[i], "Mode manuel") == 0) {
							modeManuel(timer, jardins, jardinActuel);
						}

						break;
					}
				}

				for (int i = 0; i < NBBoutonsMenuHaut; i++) {
					if (
						event.button.x > rectBoutonsMenuHaut[i].x
						&& event.button.x < rectBoutonsMenuHaut[i].x + rectBoutonsMenuHaut[i].w
						&& event.button.y > rectBoutonsMenuHaut[i].y
						&& event.button.y < rectBoutonsMenuHaut[i].y + rectBoutonsMenuHaut[i].h
						) {

						if (strcmp(boutonsMenuHaut[i], "Mode ReduceFastest") == 0) {
							SDL_StartTextInput();
						}

						break;
					}
				}
			}
			break;
		case SDL_TEXTINPUT:
			cout << event.text.text << endl;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_l) {
				lancer(timer, paramsTimer, jardins, jardinActuel);
			}
			else if (event.key.keysym.sym == SDLK_p) {
				pause(timer);
			}
			else if (event.key.keysym.sym == SDLK_m) {
				modeManuel(timer, jardins, jardinActuel);
				/*if (strcmp(jardins[jardinActuel].nomAlgo, "ReduceMax") == 0) {
					strcpy_s(jardins[jardinActuel].nomAlgo, "ReduceFastest");
				}
				else if (strcmp(jardins[jardinActuel].nomAlgo, "ReduceFastest") == 0) {
					strcpy_s(jardins[jardinActuel].nomAlgo, "ReduceMax");
				}*/
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