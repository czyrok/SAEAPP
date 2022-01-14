#include <iostream>


const int NBstats = 100;
struct bambous {

	float indDPousse;
	float vitesse_pousse;
};
const bambous NBbambous[100];

struct panda {
	int x;
};


struct jardin {
	bambous bambou;
	panda  pandas;
	int NBbambous;
	float stat[3][NBstats];
	char nomAlgo[0];
};

const int TailleMaxBambous;
const int NBDeplacementLimite = -1;