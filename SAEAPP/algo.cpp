#pragma once
#include <cstring>
using namespace std;

#include <iostream>

#include "var.h"

void couperBambou(jardins& jardin) {
	int indBambou = 0;
	int indBambousStockage[maxNBBambous];
	int NBIndBambous = 0;

	jardin.tailleNBDeplacementStat[jardin.indStat % NBStats] = 0;

	if (strcmp(jardin.nomAlgo, "ReduceMax") == 0) {
		for (int i = 0; i < jardin.NBBambous; i++) {
			indBambousStockage[NBIndBambous] = i;
			NBIndBambous++;
		}

		int indMax = 0;

		for (int i = 0; i < NBIndBambous; i++) {
			indMax = i;

			for (int j = i + 1; j < NBIndBambous; j++) {
				if (jardin.bambous[indBambousStockage[j]].taillePousse * jardin.bambous[indBambousStockage[j]].vitessePousse
				> jardin.bambous[indBambousStockage[indMax]].taillePousse * jardin.bambous[indBambousStockage[indMax]].vitessePousse) {
					indMax = j;
				}
			}

			int temp = indBambousStockage[indMax];
			indBambousStockage[indMax] = indBambousStockage[i];
			indBambousStockage[i] = temp;
		}
	}
	else if (strcmp(jardin.nomAlgo, "ReduceFastest") == 0) {
		int sommeVitessePousse = 0;

		for (int i = 0; i < jardin.NBBambous; i++) {
			sommeVitessePousse += jardin.bambous[i].vitessePousse;
		}

		indBambou = -1;

		for (int i = 0; i < jardin.NBBambous; i++) {
			if (jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse > sommeVitessePousse * jardin.paramPourReduceFastest) {
				indBambousStockage[NBIndBambous] = i;
				NBIndBambous++;
			}
		}

		if (NBIndBambous > 0) {
			int indMax = 0;

			for (int i = 0; i < NBIndBambous; i++) {
				indMax = i;

				for (int j = i + 1; j < NBIndBambous; j++) {
					if (jardin.bambous[indBambousStockage[j]].vitessePousse > jardin.bambous[indBambousStockage[indMax]].vitessePousse) {
						indMax = j;
					}
				}

				int temp = indBambousStockage[indMax];
				indBambousStockage[indMax] = indBambousStockage[i];
				indBambousStockage[i] = temp;
			}
		}
	}

	if (NBIndBambous > 0) {
		int pandasDeplaces[maxNBPandas] = { 0 };

		for (int i = 0; i < NBIndBambous && i < jardin.NBPandas; i++) {
			int indPandaPlusPret = -1;

			for (int j = 0; j < jardin.NBPandas; j++) {
				if (pandasDeplaces[j] == 0) indPandaPlusPret = j;
			}

			if (indPandaPlusPret == -1) break;

			for (int j = 0; j < jardin.NBPandas; j++) {
				if (pandasDeplaces[j] == 0 && abs(jardin.pandas[j].x - indBambousStockage[i]) < abs(jardin.pandas[indPandaPlusPret].x - indBambousStockage[i])) {
					indPandaPlusPret = j;
				}
			}

			pandasDeplaces[indPandaPlusPret] = -1;

			bool statut = deplacementPanda(jardin, indPandaPlusPret, indBambousStockage[i], false);

			if (statut == true) {
				pandaCoupeBambou(jardin, indPandaPlusPret);
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