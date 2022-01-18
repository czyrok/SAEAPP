#pragma once
using namespace std;

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

const int tailleMaxBambousY = 600;
const int maxNBBambous = 40;
const int tailleBambousX = 15;

const int taillePandaY = 20;
const int maxNBPandas = 10;
const int taillePandaX = tailleBambousX;

const int tailleStatsY = tailleMaxBambousY + taillePandaY;
const int NBStats = 100;
const int tailleStatX = 6;
const int tailleStatsX = NBStats * tailleStatX;

struct bambous {
	int taillePousse;
	float vitessePousse;
};

struct pandas {
	int x;
};

struct jardins {
	char nom[100];

	bambous bambous[maxNBBambous];
	int NBBambous;

	pandas pandas[maxNBPandas];
	int NBPandas;
	int pandaDeplacementLimite;

	int NBCoupesStat;

	float tailleMaxStat[NBStats];
	float tailleMinStat[NBStats];
	float tailleMoyStat[NBStats];

	int indStat = 0;

	char nomAlgo[30];

	bool manuelActive;

	float paramPourReduceFastest = 1.45;
};

const int TAILLEBARY = 50;
const int TAILLEMENUX = 300;

const int TAILLEFENX = (maxNBBambous * tailleBambousX) + TAILLEMENUX + tailleStatsX;
const int TAILLEFENY = tailleStatsY + TAILLEBARY;

const int NBMaxCaracBoutons = 50;

// prototype algo.cpp
void couperBambou(jardins&);
void croissanceBambou(jardins&);

// prototype stats.cpp
void actualiserStats(jardins&);
void actualiserAffichageStatistiques(jardins&, SDL_Renderer*);

// prototype panda.cpp
bool deplacementPanda(jardins&, int, int);
void actualiserAffichagePanda(jardins&);
void pandaCoupeBambou(jardins&, int);

void afficherMenu(SDL_Renderer*);
void afficherBar(SDL_Renderer*);
void afficherCarre(SDL_Renderer*);

void initJardin(
	jardins[],
	int&,
	const char[],
	bambous[],
	int,
	pandas[],
	int,
	int,
	const char[],
	bool
);

void initBambous(
	bambous[],
	int&,
	float
);

void initPandas(
	pandas[],
	int&,
	int
);

void actualiserAffichageBambous(jardins&, SDL_Renderer*);
void actualiserAffichagePandas(jardins&, SDL_Renderer*);

void afficherBoutonsBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int);
void afficherTexteBoutonBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int, int);
void afficherIMGBoutonBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int, int);

void afficherBoutonsMenu(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int);
void afficherBoutonsMenu(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int, int);

void importerConfig(jardins[], int&);

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
	SDL_SetSurfaceAlphaMod(loadedImage, 200);//transparence � 200
	if (loadedImage != NULL)
	{
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(rendu, loadedImage);
		// On se d�barrasse du pointeur vers une surface
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	return texture;
}