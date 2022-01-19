#pragma once
using namespace std;

#include <iostream>

#include "var.h"

int main(int argc, char* argv[])
{
	jardins jardins[1];
	int jardinActuel = 0;
	double tempsCalcul[8];

	importerConfig(jardins, jardinActuel);

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

	SDL_Texture* texturePanda = loadImage(rendu, "img/panda.png");

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
	SDL_Rect rectBoutonsMenuBas[10];
	char boutonsMenuBas[10][NBMaxCaracBoutons] = { { "Exporter" }, { "Importer" } };
	int NBBoutonsMenuBas = 2;
	afficherBoutonsMenu(rendu, police, rectBoutonsMenuHaut, boutonsMenuHaut, NBBoutonsMenuHaut, rectBoutonsMenuBas, boutonsMenuBas, NBBoutonsMenuBas);

	SDL_RenderPresent(rendu);

	bool ouvert = true;
	SDL_Event event;

	paramsPourTimer paramsTimer = { rendu, police, jardins, &jardinActuel, texturePanda, tempsCalcul };

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
							strcpy_s(jardins[jardinActuel].nomAlgo, "ReduceMax");
						}
						else if (strcmp(boutonsMenuHaut[i], "Mode ReduceMax") == 0) {
							strcpy_s(jardins[jardinActuel].nomAlgo, "ReduceFastest");
						}

						/*if (strcmp(boutonsMenuHaut[i], "Mode ReduceFastest") == 0) {
							SDL_StartTextInput();
						}*/

						break;
					}
				}

				for (int i = 0; i < NBBoutonsMenuBas; i++) {
					if (
						event.button.x > rectBoutonsMenuBas[i].x
						&& event.button.x < rectBoutonsMenuBas[i].x + rectBoutonsMenuBas[i].w
						&& event.button.y > rectBoutonsMenuBas[i].y
						&& event.button.y < rectBoutonsMenuBas[i].y + rectBoutonsMenuBas[i].h
						) {

						if (strcmp(boutonsMenuBas[i], "Importer") == 0) {
							pause(timer);
							importerConfig(jardins, jardinActuel);
						}
						else if (strcmp(boutonsMenuBas[i], "Exporter") == 0) {
							exporterConfig(jardins[jardinActuel]);
						}

						break;
					}
				}

				if (jardins[jardinActuel].manuelActive == true) {
					for (int i = 0; i < jardins[jardinActuel].NBBambous; i++) {
						int sommeH = 0;

						for (int j = 0; j < jardins[jardinActuel].bambous[i].taillePousse; j++) {
							SDL_Rect carre = { TAILLEMENUX + (tailleBambousX * i) + 2, (TAILLEFENY - taillePandaY - ((float)jardins[0].bambous[i].vitessePousse * (float)10 * (j + 1))), tailleBambousX - 4, jardins[0].bambous[i].vitessePousse * 10 };
							
							if (sommeH + carre.h > tailleMaxBambousY && sommeH - tailleMaxBambousY <= tailleMaxBambousY)
							{
								carre.h = sommeH - tailleMaxBambousY;
								break;
							}
							else {
								sommeH += carre.h;
							}

							if (event.button.x > carre.x
								&& event.button.x < carre.x + carre.w
								&& event.button.y > carre.y
								&& event.button.y < carre.y + carre.h
								) {
								croissanceBambou(jardins[jardinActuel]);

								pandaCoupeBambouManuel(jardins[jardinActuel], i);

								actualiserStats(jardins[jardinActuel]);

								afficherCarre(rendu);

								actualiserAffichageBambous(jardins[jardinActuel], rendu);
								actualiserAffichageStatistiques(jardins[jardinActuel], rendu);

								afficherLegende(rendu, police);
								afficherStatNBCoupes(rendu, jardins[jardinActuel]);

								SDL_RenderPresent(rendu);
							}
						}
					}
				}
			}
			break;
		case SDL_TEXTINPUT:
			//cout << event.text.text << endl;
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
			}
			break;
		case SDL_QUIT:
			ouvert = false;
			break;
		}
	}

	SDL_DestroyTexture(texturePanda);

	TTF_CloseFont(police);
	TTF_Quit();

	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(fen);
	SDL_Quit();
	return 0;
}