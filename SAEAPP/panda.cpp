#include <cstring>
using namespace std;

int deplacementPanda(jardins& jardin, int x) {
	jardin.panda.position = x;

	return 1;
}

void actualiserAffichagePanda(jardins& jardin) {

}

void pandaCoupeBambou(jardins& jardin) {
	jardin.bambous[jardin.panda.position].indDPousse = 0;
}