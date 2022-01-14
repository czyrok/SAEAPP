#pragma once
#include "var.h"
#include <cstring>
using namespace std;

int deplacementPanda(jardins& jardin, int indPanda, int x) {
	jardin.pandas[indPanda].x = x;

	return 1;
}

void actualiserAffichagePanda(jardins& jardin) {

}

void pandaCoupeBambou(jardins& jardin, int indPanda) {
	jardin.bambous[jardin.pandas[indPanda].x].taillePousse = 0;
}

int main() {
	return 0;
}