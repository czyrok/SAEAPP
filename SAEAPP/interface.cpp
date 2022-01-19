#pragma once
using namespace std;

#include <cstring>

#include "var.h"

void afficherBoutonsBar(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsBar[], char boutonsBar[][NBMaxCaracBoutons], int NBBoutonsBar) {
	for (int i = 0; i < NBBoutonsBar; i++) {
		if (i == 0) {
			afficherIMGBoutonBar(rendu, police, rectBoutonsBar, boutonsBar, i, 0);
		}
		else {
			afficherIMGBoutonBar(rendu, police, rectBoutonsBar, boutonsBar, i, rectBoutonsBar[i - 1].x + rectBoutonsBar[i - 1].w);
		}
	}
}

void afficherTexteBoutonBar(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsBar[], char boutonsBar[][NBMaxCaracBoutons], int indBouton, int departX) {
	SDL_Texture* texture = loadText(rendu, boutonsBar[indBouton], { 255, 255, 255 }, police);

	int positionTexteW, positionTexteH;
	SDL_QueryTexture(texture, NULL, NULL, &positionTexteW, &positionTexteH);

	SDL_Rect positionTexte = { departX + (TAILLEBARY - positionTexteH) / 2, (TAILLEBARY - positionTexteH) / 2, positionTexteW, positionTexteH };
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	rectBoutonsBar[indBouton] = positionTexte;
	SDL_DestroyTexture(texture);
}

void afficherIMGBoutonBar(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsBar[], char boutonsBar[][NBMaxCaracBoutons], int indBouton, int departX) {
	char texteBouton[NBMaxCaracBoutons + 8] = "img/";

	strcat_s(texteBouton, boutonsBar[indBouton]);
	strcat_s(texteBouton, ".png");

	SDL_Texture* texture = loadImage(rendu, texteBouton);

	int positionIMGW = 20, positionIMGH = 20;

	SDL_Rect positionIMG = { departX + ((TAILLEBARY - positionIMGH) / 2), (TAILLEBARY - positionIMGH) / 2, positionIMGW, positionIMGH };
	SDL_RenderCopy(rendu, texture, NULL, &positionIMG);

	rectBoutonsBar[indBouton] = positionIMG;

	afficherTexteBoutonBar(rendu, police, rectBoutonsBar, boutonsBar, indBouton, departX + 30);
	SDL_DestroyTexture(texture);
}

void afficherBoutonsMenu(
	SDL_Renderer* rendu,
	TTF_Font* police,
	SDL_Rect rectBoutonsMenuHaut[],
	char boutonsMenuHaut[][NBMaxCaracBoutons],
	int NBBoutonsMenuHaut,
	SDL_Rect rectBoutonsMenuBas[],
	char boutonsMenuBas[][NBMaxCaracBoutons],
	int NBBoutonsMenuBas,
	SDL_Rect rectBoutonsMenuMilieu[],
	char boutonsMenuMilieu[][NBMaxCaracBoutons],
	int NBBoutonsMenuMilieu,
	SDL_Rect rectImagesPlusMenuMilieu[],
	SDL_Rect rectImagesMoinsMenuMilieu[]
) {
	int hauteur = 0;

	for (int i = 0; i < NBBoutonsMenuHaut; i++) {
		if (i == 0) {
			afficherBoutonsMenuHaut(rendu, police, rectBoutonsMenuHaut, boutonsMenuHaut, i, TAILLEBARY, 0);
		}
		else {
			afficherBoutonsMenuHaut(rendu, police, rectBoutonsMenuHaut, boutonsMenuHaut, i, rectBoutonsMenuHaut[i - 1].y + rectBoutonsMenuHaut[i - 1].h, 0);
		}

		hauteur = rectBoutonsMenuHaut[i].y + rectBoutonsMenuHaut[i].h;
	}

	SDL_Texture* textureImagePlus = loadImage(rendu, "img/plus.png");
	SDL_Texture* textureImageMoins = loadImage(rendu, "img/moins.png");
	SDL_Texture* textureImageMaj = loadImage(rendu, "img/maj.png");

	for (int i = 0; i < NBBoutonsMenuMilieu; i++) {
		int ind = 1;

		if (i > 0) {
			hauteur = rectBoutonsMenuMilieu[i - 1].y + rectBoutonsMenuMilieu[i - 1].h;
			ind = 0;
		}
		else {
			hauteur += 10;
		}

		if (strcmp(boutonsMenuMilieu[i], "Valeur de X") == 0 || strcmp(boutonsMenuMilieu[i], "Limite de deplacement") == 0) {
			afficherBoutonsMenuHaut(rendu, police, rectBoutonsMenuMilieu, boutonsMenuMilieu, i, hauteur, 20);

			afficherImagesMenuMilieu(rendu, rectImagesPlusMenuMilieu, i, rectBoutonsMenuMilieu[i].x + rectBoutonsMenuMilieu[i].w + 20, rectBoutonsMenuMilieu[i].y, textureImageMaj);
		} else {
			afficherBoutonsMenuHaut(rendu, police, rectBoutonsMenuMilieu, boutonsMenuMilieu, i, hauteur, 50);

			afficherImagesMenuMilieu(rendu, rectImagesPlusMenuMilieu, i, rectBoutonsMenuMilieu[i].x + rectBoutonsMenuMilieu[i].w + 20, rectBoutonsMenuMilieu[i].y, textureImagePlus);
			afficherImagesMenuMilieu(rendu, rectImagesMoinsMenuMilieu, i, rectBoutonsMenuMilieu[i].x + rectBoutonsMenuMilieu[i].w + 60, rectBoutonsMenuMilieu[i].y, textureImageMoins);
		}
	}

	SDL_DestroyTexture(textureImagePlus);
	SDL_DestroyTexture(textureImageMoins);
	SDL_DestroyTexture(textureImageMaj);

	for (int i = 0; i < NBBoutonsMenuBas; i++) {
		if (i == 0) {
			afficherBoutonsMenuBas(rendu, police, rectBoutonsMenuBas, boutonsMenuBas, i, 10);
		}
		else {
			afficherBoutonsMenuBas(rendu, police, rectBoutonsMenuBas, boutonsMenuBas, i, rectBoutonsMenuBas[i - 1].h + 10 * (i + 1));
		}
	}
}

void afficherBoutonsMenuHaut(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsMenu[], char boutonsMenu[][NBMaxCaracBoutons], int indBouton, int departY, int decalage) {
	SDL_Texture* texture = loadText(rendu, boutonsMenu[indBouton], { 255, 255, 255 }, police);

	int positionTexteW, positionTexteH;
	SDL_QueryTexture(texture, NULL, NULL, &positionTexteW, &positionTexteH);

	SDL_Rect positionTexte = { TAILLEMENUX / 2 - positionTexteW / 2 - decalage, departY + 10, positionTexteW, positionTexteH };
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	rectBoutonsMenu[indBouton] = positionTexte;
	SDL_DestroyTexture(texture);
}

void afficherImagesMenuMilieu(SDL_Renderer* rendu, SDL_Rect rectImagesMenu[], int indBouton, int departX, int departY, SDL_Texture* textureImage) {
	int positionIMGW = 20, positionIMGH = 20;

	SDL_Rect positionIMG = { departX, departY, positionIMGW, positionIMGH };
	SDL_RenderCopy(rendu, textureImage, NULL, &positionIMG);

	rectImagesMenu[indBouton] = positionIMG;
}

void afficherBoutonsMenuBas(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsMenu[], char boutonsMenu[][NBMaxCaracBoutons], int indBouton, int departY) {
	SDL_Texture* texture = loadText(rendu, boutonsMenu[indBouton], { 255, 255, 255 }, police);

	int positionTexteW, positionTexteH;
	SDL_QueryTexture(texture, NULL, NULL, &positionTexteW, &positionTexteH);

	SDL_Rect positionTexte = { TAILLEMENUX / 2 - positionTexteW / 2, TAILLEFENY - positionTexteH - departY, positionTexteW, positionTexteH };
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	rectBoutonsMenu[indBouton] = positionTexte;
	SDL_DestroyTexture(texture);
}