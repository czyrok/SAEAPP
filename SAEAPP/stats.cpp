#pragma once
using namespace std;

#include "var.h"

void actualiserStats(jardins& jardin) {
	int max = 0;
	int min = jardin.bambous[0].taillePousse;
	int sommePousseBambous = 0;

	for (int i = 0; i < jardin.NBBambous; i++) {
		if (jardin.bambous[i].taillePousse > max) {
			max = jardin.bambous[i].taillePousse;
		}

		if (jardin.bambous[i].taillePousse < min) {
			min = jardin.bambous[i].taillePousse;
		}

		sommePousseBambous += jardin.bambous[i].taillePousse;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < NBStats - 1; j++) {
			jardin.stats[i][j] = jardin.stats[i + 1][j + 1];
		}
	}

	jardin.stats[0][NBStats - 1] = max;
	jardin.stats[1][NBStats - 1] = min;
	jardin.stats[2][NBStats - 1] = sommePousseBambous / jardin.NBBambous;
}