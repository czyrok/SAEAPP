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

	SDL_RenderPresent(rendu);
}

void afficherTexteBoutonBar(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsBar[], char boutonsBar[][NBMaxCaracBoutons], int indBouton, int departX) {
	SDL_Texture* texture = loadText(rendu, boutonsBar[indBouton], { 255, 255, 255 }, police);

	int positionTexteW, positionTexteH;
	SDL_QueryTexture(texture, NULL, NULL, &positionTexteW, &positionTexteH);

	SDL_Rect positionTexte = { departX + (TAILLEBARY - positionTexteH) / 2, (TAILLEBARY - positionTexteH) / 2, positionTexteW, positionTexteH };
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	rectBoutonsBar[indBouton] = positionTexte;
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
}

void afficherBoutonsMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsMenu[], char boutonsMenu[][NBMaxCaracBoutons], int NBBoutonsMenu) {
	int positionY = 0;

	for (int i = 0; i < NBBoutonsMenu; i++) {
		if (i == 0) {
			afficherBoutonsMenu(rendu, police, rectBoutonsMenu, boutonsMenu, i, TAILLEBARY);
		}
		else {
			afficherBoutonsMenu(rendu, police, rectBoutonsMenu, boutonsMenu, i, rectBoutonsMenu[i - 1].y + rectBoutonsMenu[i - 1].h);
		}
	}

	SDL_RenderPresent(rendu);
}

void afficherBoutonsMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsMenu[], char boutonsMenu[][NBMaxCaracBoutons], int indBouton, int departY) {
	SDL_Texture* texture = loadText(rendu, boutonsMenu[indBouton], { 255, 255, 255 }, police);

	int positionTexteW, positionTexteH;
	SDL_QueryTexture(texture, NULL, NULL, &positionTexteW, &positionTexteH);

	SDL_Rect positionTexte = { TAILLEMENUX / 2 - positionTexteW / 2, departY + 10, positionTexteW, positionTexteH };
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	rectBoutonsMenu[indBouton] = positionTexte;
}