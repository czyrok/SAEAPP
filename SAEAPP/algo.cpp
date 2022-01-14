#pragma once
#include "var.h"
#include "panda.cpp"
#include "stats.cpp"
using namespace std;

void couperBambou(jardins& jardin) {
	if (strcmp(jardin.nomAlgo, "ReduceMax") == 0) {
		int indMax = 0;

		for (int i = 0; i < jardin.NBBambous; i++) {
			if (jardin.bambous[i].taillePousse > jardin.bambous[indMax].taillePousse) {
				indMax = i;
			}
		}

		int statut = deplacementPanda(jardin, 0, indMax);

		if (statut == 1) {
			pandaCoupeBambou(jardin, 0);
		}
	}
	else if (strcmp(jardin.nomAlgo, "ReduceFastest") == 0) {

	}

	actualiserStats(jardin);
}

void croissanceBambou(jardins& jardin) {
	for (int i = 0; i < jardin.NBBambous; i++) {
		jardin.bambous[i].taillePousse += jardin.bambous[i].vitessePousse;
	}
}