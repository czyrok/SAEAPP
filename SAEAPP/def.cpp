#pragma once
using namespace std;

#include "var.h"

#include <cstring>

void initJardin(
    jardins jardins[],
    int& jardinActuel,
    const char nomJardin[],
    bambous bambous[],
    int NBBambous,
    pandas pandas[],
    int NBPandas,
    int pandaDeplacementLimite,
    const char nomAlgo[],
    bool manuelActive,
    float paramPourReduceFastest)
{
    strcpy_s(jardins[jardinActuel].nom, nomJardin);

    for (int i = 0; i < NBBambous; i++) {
        jardins[jardinActuel].bambous[i] = bambous[i];
    }

    jardins[jardinActuel].NBBambous = NBBambous;

   jardins[jardinActuel].NBCoupesStat = 0;
   
   strcpy_s(jardins[jardinActuel].nomAlgo, nomAlgo);
   
   for (int i = 0; i < NBPandas; i++) {
       jardins[jardinActuel].pandas[i] = pandas[i];
   }

   jardins[jardinActuel].NBPandas = NBPandas;

   for (int i = 0; i < NBStats; i++) {
       jardins[jardinActuel].tailleMaxStat[i] = 0;
       jardins[jardinActuel].tailleMinStat[i] = 0;
       jardins[jardinActuel].tailleMoyStat[i] = 0;
   }

   jardins[jardinActuel].pandaDeplacementLimite = pandaDeplacementLimite;

   jardins[jardinActuel].manuelActive = manuelActive;

   jardins[jardinActuel].indStat = 0;
   jardins[jardinActuel].NBCoupesStat = 0;

   jardins[jardinActuel].paramPourReduceFastest = paramPourReduceFastest;
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

    NBPandas++;
}