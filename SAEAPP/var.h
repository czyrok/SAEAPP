#pragma once
using namespace std;

const int tailleMaxBambous = 30;
const int maxNBBambous = 100;

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

	float tailleMaxStat[NBStats];
	float tailleMinStat[NBStats];
	float tailleMoyStat[NBStats];

	int indStat = 0;

	char nomAlgo[30];
};

// prototype algo.cpp
void couperBambou(jardins&);
void croissanceBambou(jardins&);

// prototype stats.cpp
void actualiserStats(jardins&);

// prototype panda.cpp
bool deplacementPanda(jardins&, int, int);
void actualiserAffichagePanda(jardins&);
void pandaCoupeBambou(jardins&, int);