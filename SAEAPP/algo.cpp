#pragma once
#include <cstring>
using namespace std;

#include "var.h"

void couperBambou(jardins& jardin) {
	if (strcmp(jardin.nomAlgo, "ReduceMax") == 0) {
		int indMax = 0;

		for (int i = 0; i < jardin.NBBambous; i++) {
			if (jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse > jardin.bambous[indMax].taillePousse * jardin.bambous[indMax].vitessePousse) {
				indMax = i;
			}
		}

		bool statut = deplacementPanda(jardin, 0, indMax);

		if (statut == true) {
			pandaCoupeBambou(jardin, 0);
		}
	}
	else if (strcmp(jardin.nomAlgo, "ReduceFastest") == 0) {
		int sommeVitessePousse = 0;

		for (int i = 0; i < jardin.NBBambous; i++) {
			sommeVitessePousse += jardin.bambous[i].vitessePousse;
		}

		int indBambou = -1;

		for (int i = 0; i < jardin.NBBambous; i++) {
			if (jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse > sommeVitessePousse * jardin.paramPourReduceFastest && indBambou == -1) {
				indBambou = i;
			}
			else if(jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse > sommeVitessePousse){
				if (jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse > jardin.bambous[indBambou].taillePousse * jardin.bambous[indBambou].vitessePousse) {
					indBambou = i;
				}
			}
		}

		if (indBambou != -1) {
			bool statut = deplacementPanda(jardin, 0, indBambou);

			if (statut == true) {
				pandaCoupeBambou(jardin, 0);
			}
		}
	}

	actualiserStats(jardin);
}

void croissanceBambou(jardins& jardin) {
	for (int i = 0; i < jardin.NBBambous; i++) {
		jardin.bambous[i].taillePousse += 1;
	}
}