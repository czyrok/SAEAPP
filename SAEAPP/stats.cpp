#pragma once
using namespace std;

#include "var.h"

void actualiserStats(jardins& jardin)
{
	float max = 0;
	float min = jardin.bambous[0].taillePousse * jardin.bambous[0].vitessePousse;
	float sommePousseBambous = 0;

	for (int i = 0; i < jardin.NBBambous; i++)
	{
		if (jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse > max)
		{
			max = jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse;
		}

		if (jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse < min)
		{
			min = jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse;
		}

		sommePousseBambous += jardin.bambous[i].taillePousse * jardin.bambous[i].vitessePousse;
	}

	jardin.tailleMaxStat[jardin.indStat % NBStats] = max;
	jardin.tailleMinStat[jardin.indStat % NBStats] = min;
	jardin.tailleMoyStat[jardin.indStat % NBStats] = sommePousseBambous / jardin.NBBambous;

	jardin.indStat++;
}