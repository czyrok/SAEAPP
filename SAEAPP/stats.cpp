#pragma once
using namespace std;

#include "var.h"

void actualiserStats(jardins &jardin)
{
	float max = 0;
	float min = jardin.bambous[0].taillePousse;
	float sommePousseBambous = 0;

	for (int i = 0; i < jardin.NBBambous; i++)
	{
		if (jardin.bambous[i].taillePousse > max)
		{
			max = jardin.bambous[i].taillePousse;
		}

		if (jardin.bambous[i].taillePousse < min)
		{
			min = jardin.bambous[i].taillePousse;
		}

		sommePousseBambous += jardin.bambous[i].taillePousse;
	}

	if (jardin.indStat < NBStats)
	{
		jardin.tailleMaxStat[jardin.indStat] = max;
		jardin.tailleMinStat[jardin.indStat] = min;
		jardin.tailleMoyStat[jardin.indStat] = sommePousseBambous / jardin.NBBambous;
	}
	else
	{
		jardin.tailleMaxStat[jardin.indStat % NBStats] = max;
		jardin.tailleMinStat[jardin.indStat % NBStats] = min;
		jardin.tailleMoyStat[jardin.indStat % NBStats] = sommePousseBambous / jardin.NBBambous;
	}

	jardin.indStat++;
}