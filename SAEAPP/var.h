#pragma once
using namespace std;

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

const int tailleMaxBambousY = 480;
const int maxNBBambous = 40;
const int tailleBambousX = 15;

const int taillePandaY = 20;
const int maxNBPandas = 10;
const int taillePandaX = tailleBambousX;

const int tailleStatsY = tailleMaxBambousY + taillePandaY;
const int NBStats = 100;
const int tailleStatsX = NBStats * 3;

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

void afficherBoutonsBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][50], int&);
void afficherBoutonBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][50], int);