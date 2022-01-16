#pragma once
using namespace std;

const int NBStats = 100;
const int tailleMaxBambous = 30;
const int NBDeplacementLimite = -1;

struct bambous {
	float taillePousse;
	float vitessePousse;
};

struct pandas {
	int x;
};

struct jardins {
	bambous bambous[100];
	int NBBambous;

	pandas pandas[10];
	int NBPandas;

	float stats[3][NBStats];
	char nomAlgo[10];
};


// prototype algo.cpp
void couperBambou(jardins&);
void croissanceBambou(jardins&);

// prototype stats.cpp
void actualiserStats(jardins&);

// prototype panda.cpp
int deplacementPanda(jardins&, int, int);
void actualiserAffichagePanda(jardins&);
void pandaCoupeBambou(jardins&, int);