#pragma once
using namespace std;

#include <iostream>

#include "var.h"

int main(int argc, char* argv[])
{
	jardins jardins[3];
	int jardinActuel = 0;
	int indBoutonMilieuActive = -1;

	importerConfig(jardins, jardinActuel);
	importerConfig(jardins, jardinActuel + 1);
	importerConfig(jardins, jardinActuel + 2);

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

	const int NBBoutonsBar = 9;
	SDL_Rect rectBoutonsBar[NBBoutonsBar];
	char boutonsBar[NBBoutonsBar][NBMaxCaracBoutons] = { { "Lancer" }, { "Pause" }, { "Plus vite" }, { "Moins vite" }, { "Vitesse par defaut" }, { "Mode manuel" }, { "Jardin 1" }, { "Jardin 2" }, { "Jardin 3" } };

	afficherBoutonsBar(rendu, police, rectBoutonsBar, boutonsBar, NBBoutonsBar);

	const int NBBoutonsMenuHaut = 2;
	SDL_Rect rectBoutonsMenuHaut[NBBoutonsMenuHaut];
	char boutonsMenuHaut[NBBoutonsMenuHaut][NBMaxCaracBoutons] = { { "Mode ReduceMax" }, { "Mode ReduceFastest" } };

	const int NBBoutonsMenuMilieu = 4;
	SDL_Rect rectBoutonsMenuMilieu[NBBoutonsMenuMilieu];
	char boutonsMenuMilieu[NBBoutonsMenuMilieu][NBMaxCaracBoutons] = { { "Valeur de X" }, { "Limite de deplacement" }, { "Bambou" }, { "Panda" } };

	champs champsMenuMilieu[NBBoutonsMenuMilieu];

	SDL_Rect rectImagesPlusMenuMilieu[NBBoutonsMenuMilieu];
	SDL_Rect rectImagesMoinsMenuMilieu[NBBoutonsMenuMilieu];

	const int NBBoutonsMenuBas = 2;
	SDL_Rect rectBoutonsMenuBas[NBBoutonsMenuBas];
	char boutonsMenuBas[NBBoutonsMenuBas][NBMaxCaracBoutons] = { { "Exporter" }, { "Importer" } };

	afficherBoutonsMenu(rendu,
		police,
		rectBoutonsMenuHaut,
		boutonsMenuHaut,
		NBBoutonsMenuHaut,
		rectBoutonsMenuBas,
		boutonsMenuBas,
		NBBoutonsMenuBas,
		rectBoutonsMenuMilieu,
		boutonsMenuMilieu,
		NBBoutonsMenuMilieu,
		rectImagesPlusMenuMilieu,
		rectImagesMoinsMenuMilieu
	);

	actualiser(rendu, police, jardins, &jardinActuel, texturePanda, true, true);

	SDL_RenderPresent(rendu);

	bool ouvert = true;
	SDL_Event event;

	paramsPourTimer paramsTimer = { rendu, police, jardins, &jardinActuel, texturePanda };
	int tempsTimer = 100;

	SDL_TimerID timer = SDL_AddTimer(tempsTimer, actualiser, &paramsTimer);
	SDL_RemoveTimer(timer);

	while (ouvert) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (
					event.button.x > 0
					&& event.button.x < TAILLEFENX
					&& event.button.y > 0
					&& event.button.y < TAILLEBARY
				) {
					for (int i = 0; i < NBBoutonsBar; i++) {
						if (
							event.button.x > rectBoutonsBar[i].x
							&& event.button.x < rectBoutonsBar[i].x + rectBoutonsBar[i].w
							&& event.button.y > rectBoutonsBar[i].y
							&& event.button.y < rectBoutonsBar[i].y + rectBoutonsBar[i].h
							) {
							if (strcmp(boutonsBar[i], "Lancer") == 0) {
								lancer(timer, paramsTimer, jardins, jardinActuel, tempsTimer);
							}
							else if (strcmp(boutonsBar[i], "Pause") == 0) {
								pause(timer);
							}
							else if (strcmp(boutonsBar[i], "Plus vite") == 0) {
								augmenterTimer(tempsTimer);
								lancer(timer, paramsTimer, jardins, jardinActuel, tempsTimer);
							}
							else if (strcmp(boutonsBar[i], "Moins vite") == 0) {
								diminuerTimer(tempsTimer);
								lancer(timer, paramsTimer, jardins, jardinActuel, tempsTimer);
							}
							else if (strcmp(boutonsBar[i], "Vitesse par defaut") == 0) {
								resetTimer(tempsTimer);
								lancer(timer, paramsTimer, jardins, jardinActuel, tempsTimer);
							}
							else if (strcmp(boutonsBar[i], "Mode manuel") == 0) {
								modeManuel(timer, jardins, jardinActuel);
							}
							else if (strcmp(boutonsBar[i], "Jardin 1") == 0) {
								jardinActuel = 0;
								actualiser(rendu, police, jardins, &jardinActuel, texturePanda, true, true);
							}
							else if (strcmp(boutonsBar[i], "Jardin 2") == 0) {
								jardinActuel = 1;
								actualiser(rendu, police, jardins, &jardinActuel, texturePanda, true, true);
							}
							else if (strcmp(boutonsBar[i], "Jardin 3") == 0) {
								jardinActuel = 2;
								actualiser(rendu, police, jardins, &jardinActuel, texturePanda, true, true);
							}

							break;
						}
					}
				}

				if (indBoutonMilieuActive != -1) {
					SDL_SetRenderDrawColor(rendu, 59, 93, 108, 255);
					SDL_Rect rect = { rectBoutonsMenuMilieu[indBoutonMilieuActive].x - 3, rectBoutonsMenuMilieu[indBoutonMilieuActive].y - 3, rectBoutonsMenuMilieu[indBoutonMilieuActive].w + 6, rectBoutonsMenuMilieu[indBoutonMilieuActive].h + 6 };
					SDL_RenderDrawRect(rendu, &rect);
					SDL_RenderPresent(rendu);


					indBoutonMilieuActive = -1;
				}

				if (
					event.button.x > 0
					&& event.button.x < TAILLEMENUX
					&& event.button.y > TAILLEBARY
					&& event.button.y < TAILLEFENY
				) {
					for (int i = 0; i < NBBoutonsMenuHaut; i++) {
						if (
							event.button.x > rectBoutonsMenuHaut[i].x
							&& event.button.x < rectBoutonsMenuHaut[i].x + rectBoutonsMenuHaut[i].w
							&& event.button.y > rectBoutonsMenuHaut[i].y
							&& event.button.y < rectBoutonsMenuHaut[i].y + rectBoutonsMenuHaut[i].h
							) {
							if (strcmp(boutonsMenuHaut[i], "Mode ReduceFastest") == 0) {
								strcpy_s(jardins[jardinActuel].nomAlgo, "ReduceFastest");
							}
							else if (strcmp(boutonsMenuHaut[i], "Mode ReduceMax") == 0) {
								strcpy_s(jardins[jardinActuel].nomAlgo, "ReduceMax");
							}

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
								actualiser(rendu, police, jardins, &jardinActuel, texturePanda, true, true);
							}
							else if (strcmp(boutonsMenuBas[i], "Exporter") == 0) {
								exporterConfig(jardins[jardinActuel]);
							}

							break;
						}
					}

					for (int i = 0; i < NBBoutonsMenuMilieu; i++) {
						if (
							event.button.x > rectImagesPlusMenuMilieu[i].x
							&& event.button.x < rectImagesPlusMenuMilieu[i].x + rectImagesPlusMenuMilieu[i].w
							&& event.button.y > rectImagesPlusMenuMilieu[i].y
							&& event.button.y < rectImagesPlusMenuMilieu[i].y + rectImagesPlusMenuMilieu[i].h
							) {
							if (strcmp(boutonsMenuMilieu[i], "Valeur de X") == 0) {
								if (atof(champsMenuMilieu[i].valeur) > 0) {
									jardins[jardinActuel].paramPourReduceFastest = atof(champsMenuMilieu[i].valeur);
								}
							}
							else if (strcmp(boutonsMenuMilieu[i], "Limite de deplacement") == 0) {
								if (atoi(champsMenuMilieu[i].valeur) > 0) {
									jardins[jardinActuel].pandaDeplacementLimite = atoi(champsMenuMilieu[i].valeur);
								}
							}
							else if (strcmp(boutonsMenuMilieu[i], "Bambou") == 0) {
								if (atof(champsMenuMilieu[i].valeur) > 0 && jardins[jardinActuel].NBBambous < maxNBBambous) {
									initBambous(jardins[jardinActuel].bambous, jardins[jardinActuel].NBBambous, atof(champsMenuMilieu[i].valeur));
								}
							}
							else if (strcmp(boutonsMenuMilieu[i], "Panda") == 0 && jardins[jardinActuel].NBPandas < maxNBPandas) {
								if (atof(champsMenuMilieu[i].valeur) > 0) {
									char algoBatterie[] = "Distance";

									initPandas(jardins[jardinActuel].pandas, jardins[jardinActuel].NBPandas, 0, atoi(champsMenuMilieu[i].valeur), atoi(champsMenuMilieu[i].valeur), algoBatterie);
								}
							}

							break;
						}

						if (
							event.button.x > rectImagesMoinsMenuMilieu[i].x
							&& event.button.x < rectImagesMoinsMenuMilieu[i].x + rectImagesMoinsMenuMilieu[i].w
							&& event.button.y > rectImagesMoinsMenuMilieu[i].y
							&& event.button.y < rectImagesMoinsMenuMilieu[i].y + rectImagesMoinsMenuMilieu[i].h
							) {

							if (strcmp(boutonsMenuMilieu[i], "Bambou") == 0) {
								if (jardins[jardinActuel].NBBambous > 0) {
									jardins[jardinActuel].NBBambous--;
								}
							}
							else if (strcmp(boutonsMenuMilieu[i], "Panda") == 0 && jardins[jardinActuel].NBPandas < maxNBPandas) {
								if (jardins[jardinActuel].NBPandas > 0) {
									jardins[jardinActuel].NBPandas--;
								}
							}

							break;
						}
					}

					for (int i = 0; i < NBBoutonsMenuMilieu; i++) {
						if (
							event.button.x > rectBoutonsMenuMilieu[i].x
							&& event.button.x < rectBoutonsMenuMilieu[i].x + rectBoutonsMenuMilieu[i].w
							&& event.button.y > rectBoutonsMenuMilieu[i].y
							&& event.button.y < rectBoutonsMenuMilieu[i].y + rectBoutonsMenuMilieu[i].h
							) {
							for (int i = 0; i < NBBoutonsMenuMilieu; i++) {
								strcpy_s(champsMenuMilieu[i].valeur, "");
								champsMenuMilieu[i].indValeur = 0;
							}

							SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
							SDL_Rect rect = { rectBoutonsMenuMilieu[i].x - 3, rectBoutonsMenuMilieu[i].y - 3, rectBoutonsMenuMilieu[i].w + 6, rectBoutonsMenuMilieu[i].h + 6 };
							SDL_RenderDrawRect(rendu, &rect);
							SDL_RenderPresent(rendu);

							indBoutonMilieuActive = i;

							break;
						}
					}
				}

				if (
					jardins[jardinActuel].manuelActive == true
					&& event.button.x > TAILLEMENUX
					&& event.button.x < TAILLEMENUX + maxNBBambous * tailleBambousX
					&& event.button.y > TAILLEBARY
					&& event.button.y < tailleMaxBambousY
				) {
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
								pandaCoupeBambouManuel(jardins[jardinActuel], i);

								actualiser(rendu, police, jardins, &jardinActuel, texturePanda, true, false);
							}
						}
					}
				}
			}
			break;
		case SDL_TEXTINPUT:
			if (indBoutonMilieuActive > -1) {
				if (champsMenuMilieu[indBoutonMilieuActive].indValeur >= 30) champsMenuMilieu[indBoutonMilieuActive].indValeur = 0;

				champsMenuMilieu[indBoutonMilieuActive].valeur[champsMenuMilieu[indBoutonMilieuActive].indValeur] = *event.text.text;
				champsMenuMilieu[indBoutonMilieuActive].valeur[champsMenuMilieu[indBoutonMilieuActive].indValeur + 1] = '\0';

				champsMenuMilieu[indBoutonMilieuActive].indValeur++;
			}

			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_l) {
				lancer(timer, paramsTimer, jardins, jardinActuel, tempsTimer);
			}
			else if (event.key.keysym.sym == SDLK_p) {
				pause(timer);
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