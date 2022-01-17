#pragma once
using namespace std;

#include <cstring>

#include "var.h"

SDL_Texture* loadText(SDL_Renderer* rendu, const char* text, SDL_Color coul, TTF_Font* font) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, coul);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* loadImage(SDL_Renderer* rendu, const char* name)
{
	/* Charge les images avec SDL Image dans une SDL_Surface */
	SDL_Surface* loadedImage = NULL;
	SDL_Texture* texture = NULL;
	loadedImage = IMG_Load(name);
	SDL_SetSurfaceAlphaMod(loadedImage, 200);//transparence à 200
	if (loadedImage != NULL)
	{
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(rendu, loadedImage);
		// On se débarrasse du pointeur vers une surface
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	return texture;
}

void afficherBoutonsBar(SDL_Renderer* rendu, TTF_Font* police, SDL_Rect rectBoutonsBar[], char boutonsBar[][NBMaxCaracBoutons], int NBButonsBar) {
	for (int i = 0; i < NBButonsBar; i++) {
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
	SDL_Texture* texture = loadText(rendu, boutonsBar[indBouton], { 0, 0, 0 }, police);

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