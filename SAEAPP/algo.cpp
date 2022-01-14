void couperBambou(jardins& jardin) {
	if (strcmp(jardin.algo, "ReduceMax") == 0) {
		int indMax = 0;

		for (int i = 0; i < jardin.NBBambous; i++) {
			if (jardin.bambous[i].taillePousse > jardin.bambous[indMax].taillePousse) {
				indMax = i;
			}
		}

		int statut = deplacementPanda(jardin, indMax);

		if (statut == 1) {
			pandaCoupeBambou(jardin);
		}
	}
	else if (strcmp(jardin.algo, "ReduceFastest") == 0) {

	}

	actualiserStats(jardin);
}

void croissanceBambou(jardins& jardin) {
	for (int i = 0; i < jardin.NBBambous; i++) {
		jardin.bambous[i].taillePousse += jardin.bambous[i].vitessePousse;
	}
}