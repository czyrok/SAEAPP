#pragma once
using namespace std;

#include "var.h"

#include <cstring>

void initJardin(
    jardins jardins[],
    int& NBJardins,
    char nomJardin[],
    bambous bambous[],
    int NBBambous,
    pandas pandas[],
    int NBPandas,
    int pandaDeplacementLimite,
    char nomAlgo[],
    bool manuelActive)
{
    strcpy_s(jardins[NBJardins].nom, nomJardin);

    for (int i = 0; i < NBBambous; i++) {
        jardins[NBJardins].bambous[i] = bambous[i];
    }

   jardins[NBJardins].NBCoupesStat = 0;
   
   strcpy_s(jardins[NBJardins].nomAlgo, nomAlgo);
   
   for (int i = 0; i < NBPandas; i++) {
       jardins[NBJardins].pandas[i] = pandas[i];
   }

   for (int i = 0; i < NBStats; i++) {
       jardins[NBJardins].tailleMaxStat[i] = 0;
       jardins[NBJardins].tailleMinStat[i] = 0;
       jardins[NBJardins].tailleMoyStat[i] = 0;
   }

   jardins[NBJardins].pandaDeplacementLimite = pandaDeplacementLimite;

   jardins[NBJardins].manuelActive = manuelActive;

   NBJardins++;
}

void initBambous(
    bambous bambous[],
    int& NBBambous,
    float vitessePousse)
{
    bambous[NBBambous].taillePousse = 0;
    bambous[NBBambous].vitessePousse = vitessePousse;

    NBBambous++;
}

void initPandas(
    pandas pandas[],
    int& NBPandas,
    int x)
{
    
    pandas[NBPandas].x = x;


}