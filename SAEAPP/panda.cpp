#pragma once
using namespace std;

#include <iostream>

#include "var.h"

bool deplacementPanda(jardins &jardin, int indPanda, int x, bool gestionBatterie)
{
	int positionInitiale = jardin.pandas[indPanda].x;
	int distanceParcourue = 0;

	if (jardin.pandas[indPanda].x != x)
	{
		if (jardin.pandaDeplacementLimite == -1)
		{
			jardin.pandas[indPanda].x = x;

			distanceParcourue = abs(jardin.pandas[indPanda].x - x);
		}
		else
		{
			if (jardin.pandas[indPanda].x < x)
			{
				int NBDeplacementLimite = jardin.pandaDeplacementLimite;

				while (NBDeplacementLimite > 0 && jardin.pandas[indPanda].x != x)
				{
					jardin.pandas[indPanda].x++;
					NBDeplacementLimite--;
					distanceParcourue++;
				}
			}
			else
			{
				int NBDeplacementLimite = jardin.pandaDeplacementLimite;

				while (NBDeplacementLimite > 0 && jardin.pandas[indPanda].x != x)
				{
					jardin.pandas[indPanda].x--;
					NBDeplacementLimite--;
					distanceParcourue++;
				}
			}
		}
	}

	if (gestionBatterie) {
		if (strcmp(jardin.pandas[indPanda].gestionBatterie, "Distance") == 0) {
			jardin.pandas[indPanda].batterie -= distanceParcourue;
		}
		else if (strcmp(jardin.pandas[indPanda].gestionBatterie, "Jour") == 0) {
			jardin.pandas[indPanda].batterie -= 1;
		}

		if (jardin.pandas[indPanda].x == 0) jardin.pandas[indPanda].batterie = jardin.pandas[indPanda].limite;

		return false;
	}

	if (strcmp(jardin.pandas[indPanda].gestionBatterie, "Distance") == 0) {
		if (jardin.pandas[indPanda].x > jardin.pandas[indPanda].batterie - distanceParcourue) {

			jardin.pandas[indPanda].x = positionInitiale;

			return deplacementPanda(jardin, indPanda, 0, true);
		}
		else {
			jardin.pandas[indPanda].batterie -= distanceParcourue;

			if (jardin.pandas[indPanda].x != x)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	else if (strcmp(jardin.pandas[indPanda].gestionBatterie, "Jour") == 0) {
		if (jardin.pandas[indPanda].batterie - jardin.pandas[indPanda].x < 0) {

			jardin.pandas[indPanda].x = positionInitiale;

			return deplacementPanda(jardin, indPanda, 0, true);
		}
		else {
			jardin.pandas[indPanda].batterie -= 1;

			if (jardin.pandas[indPanda].x != x)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

void pandaCoupeBambou(jardins &jardin, int indPanda)
{
	jardin.bambous[jardin.pandas[indPanda].x].taillePousse = 0;
	jardin.NBCoupesStat++;
}

void pandaCoupeBambouManuel(jardins& jardin, int position)
{
	jardin.bambous[position].taillePousse = 0;
	jardin.NBCoupesStat++;
}