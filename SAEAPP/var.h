#pragma once
using namespace std;

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

const int NBMaxJardins = 3;

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

const int tailleEchelleStatsX = 10;
const int tailleEchelleStatsY = tailleStatsY;

const int tailleNBCoupesStatX = 10;
const int tailleNBCoupesStatY = tailleStatsY;

struct bambous {
	int taillePousse;
	float vitessePousse;
};

struct pandas {
	int x;
	int batterie;
	int limite;
	char gestionBatterie[30];
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

	float paramPourReduceFastest;
};

struct paramsPourTimer {
	SDL_Renderer* rendu;
	TTF_Font* police;
	jardins* jardins;
	int* jardinActuel;
	SDL_Texture* texturePanda;
	double* tempsCalcul;
};

struct champs {
	int indValeur = 0;
	char valeur[30] = "";
};

const int TAILLEBARY = 50;
const int TAILLEMENUX = 300;

const int TAILLEFENX = (maxNBBambous * tailleBambousX) + TAILLEMENUX + tailleStatsX + tailleEchelleStatsX + tailleNBCoupesStatX;
const int TAILLEFENY = tailleStatsY + TAILLEBARY;

const int NBMaxCaracBoutons = 50;

void couperBambou(jardins&);
void croissanceBambou(jardins&);

void actualiserStats(jardins&);

bool deplacementPanda(jardins&, int, int, bool);
void pandaCoupeBambou(jardins&, int);
void pandaCoupeBambouManuel(jardins&, int);

void afficherMenu(SDL_Renderer*);
void afficherBar(SDL_Renderer*);
void afficherCarre(SDL_Renderer*);
void afficherLegende(SDL_Renderer*, TTF_Font*);
void afficherStatNBCoupes(SDL_Renderer*, jardins&);
void afficherEchelle(SDL_Renderer*);

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
	bool,
	float
);

void initBambous(
	bambous[],
	int&,
	float
);

void initPandas(
	pandas[],
	int&,
	int,
	int,
	int,
	char[]
);

void actualiserAffichageBambous(jardins&, SDL_Renderer*);
void actualiserAffichagePandas(jardins&, SDL_Renderer*, SDL_Texture*);
void actualiserAffichageStatistiques(jardins&, SDL_Renderer*);

void afficherBoutonsBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int);
void afficherTexteBoutonBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int, int);
void afficherIMGBoutonBar(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int, int);

void afficherBoutonsMenu(
	SDL_Renderer*,
	TTF_Font*,
	SDL_Rect[],
	char[][NBMaxCaracBoutons],
	int,
	SDL_Rect[],
	char[][NBMaxCaracBoutons],
	int,
	SDL_Rect[],
	char[][NBMaxCaracBoutons],
	int,
	SDL_Rect[],
	SDL_Rect[]
);
void afficherBoutonsMenuHaut(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int, int, int);
void afficherBoutonsMenuBas(SDL_Renderer*, TTF_Font*, SDL_Rect[], char[][NBMaxCaracBoutons], int, int);
void afficherImagesMenuMilieu(SDL_Renderer*, SDL_Rect[], int, int, int, SDL_Texture*);

void importerConfig(jardins[], int&);
void exporterConfig(jardins);

Uint32 actualiser(Uint32, void*);
void lancer(SDL_TimerID&, paramsPourTimer&, jardins[], int);
void pause(SDL_TimerID&);
void modeManuel(SDL_TimerID&, jardins[], int);

SDL_Texture* loadText(SDL_Renderer*, const char*, SDL_Color, TTF_Font*);
SDL_Texture* loadImage(SDL_Renderer*, const char*);