#pragma once
using namespace std;

#include <iostream>

#include "var.h"

int main(int argc, char* argv[])
{
	jardins jardins[1];
	int jardinActuel = 0;
	double tempsCalcul[8];
	int indBoutonMilieuActive = -1;

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

	const int NBBoutonsBar = 5;
	SDL_Rect rectBoutonsBar[NBBoutonsBar];
	char boutonsBar[NBBoutonsBar][NBMaxCaracBoutons] = { { "Lancer" }, { "Pause" }, { "Mode manuel" }, { "Jardin 1" }, { "Jardin 2" } };

	afficherBoutonsBar(rendu, police, rectBoutonsBar, boutonsBar, NBBoutonsBar);

	const int NBBoutonsMenuHaut = 2;
	SDL_Rect rectBoutonsMenuHaut[NBBoutonsMenuHaut];
	char boutonsMenuHaut[NBBoutonsMenuHaut][NBMaxCaracBoutons] = { { "Mode ReduceMax" }, { "Mode ReduceFastest" } };

	const int NBBoutonsMenuMilieu = 3;
	SDL_Rect rectBoutonsMenuMilieu[NBBoutonsMenuMilieu];
	char boutonsMenuMilieu[NBBoutonsMenuMilieu][NBMaxCaracBoutons] = { { "Valeur de X" }, { "Bambou" }, { "Panda" } };

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
						}
						else if (strcmp(boutonsMenuBas[i], "Exporter") == 0) {
							exporterConfig(jardins[jardinActuel]);
						}

						break;
					}
				}

				for (int i = 1; i < NBBoutonsMenuMilieu; i++) {
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
						else if (strcmp(boutonsMenuMilieu[i], "Bambou") == 0) {
							if (atof(champsMenuMilieu[i].valeur) > 0) {
								initBambous(jardins[jardinActuel].bambous, jardins[jardinActuel].NBBambous, atof(champsMenuMilieu[i].valeur));
							}
						}
						else if (strcmp(boutonsMenuMilieu[i], "Panda") == 0) {
							if (atof(champsMenuMilieu[i].valeur) > 0) {
								char algoBatterie[] = "Distance";

								initPandas(jardins[jardinActuel].pandas, jardins[jardinActuel].NBPandas, 0, atoi(champsMenuMilieu[i].valeur), atoi(champsMenuMilieu[i].valeur), algoBatterie);
							}
						}

						break;
					}
				}

				indBoutonMilieuActive = -1;

				for (int i = 0; i < NBBoutonsMenuMilieu; i++) {
					if (
						event.button.x > rectBoutonsMenuMilieu[i].x
						&& event.button.x < rectBoutonsMenuMilieu[i].x + rectBoutonsMenuMilieu[i].w
						&& event.button.y > rectBoutonsMenuMilieu[i].y
						&& event.button.y < rectBoutonsMenuMilieu[i].y + rectBoutonsMenuMilieu[i].h
					) {
						indBoutonMilieuActive = i;

						for (int i = 0; i < NBBoutonsMenuMilieu; i++) {
							strcpy_s(champsMenuMilieu[i].valeur, "");
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
			if (indBoutonMilieuActive > -1) {
				champsMenuMilieu[indBoutonMilieuActive].valeur[champsMenuMilieu[indBoutonMilieuActive].indValeur] = *event.text.text;
				champsMenuMilieu[indBoutonMilieuActive].valeur[champsMenuMilieu[indBoutonMilieuActive].indValeur + 1] = '\0';

				cout << champsMenuMilieu[indBoutonMilieuActive].valeur << endl;

				champsMenuMilieu[indBoutonMilieuActive].indValeur++;
			}

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