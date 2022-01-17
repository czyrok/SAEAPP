#pragma once
using namespace std;

#include <iostream>

#include "var.h"

bool deplacementPanda(jardins &jardin, int indPanda, int x)
{
	if (jardin.pandas[indPanda].x != x)
	{
		if (jardin.pandaDeplacementLimite == -1)
		{
			jardin.pandas[indPanda].x = x;
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
				}
			}
			else
			{
				int NBDeplacementLimite = jardin.pandaDeplacementLimite;

				while (NBDeplacementLimite > 0 && jardin.pandas[indPanda].x != x)
				{
					jardin.pandas[indPanda].x--;
					NBDeplacementLimite--;
				}
			}
		}
	}

	if (jardin.pandas[indPanda].x != x)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void pandaCoupeBambou(jardins &jardin, int indPanda)
{
	jardin.bambous[jardin.pandas[indPanda].x].taillePousse = 0;
}