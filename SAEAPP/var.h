#pragma once
using namespace std;

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

const int tailleMaxBambous = 480;
const int maxNBBambous = 100;

const int taillePanda = 20;
const int maxNBPandas = 10;

const int NBStats = 100;

struct bambous {
	float taillePousse;
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

const int TAILLEFENX = (maxNBBambous * 6) + TAILLEMENUX + (NBStats * 6);
const int TAILLEFENY = tailleMaxBambous + taillePanda + TAILLEBARY;

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