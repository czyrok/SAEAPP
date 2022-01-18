#pragma once
using namespace std;

#include "var.h"

SDL_Texture* loadText(SDL_Renderer* rendu, const char* text, SDL_Color coul, TTF_Font* font) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, coul);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* loadImage(SDL_Renderer* rendu, const char* name)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Texture* texture = NULL;

	loadedImage = IMG_Load(name);

	SDL_SetSurfaceAlphaMod(loadedImage, 200);

	if (loadedImage != NULL)
	{
		texture = SDL_CreateTextureFromSurface(rendu, loadedImage);

		SDL_FreeSurface(loadedImage);

		loadedImage = NULL;
	}

	return texture;
}