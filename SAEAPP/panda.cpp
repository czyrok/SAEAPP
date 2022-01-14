int deplacementPanda(jardins& jardin, int x) {
	jardin.panda.position = x;
}

int actualiserAffichagePanda(jardins& jardin) {

}

int pandaCoupeBambou(jardins& jardin) {
	jardin.bambous[jardin.panda.position].indDPousse = 1;
}