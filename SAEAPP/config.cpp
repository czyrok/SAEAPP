#pragma once
using namespace std;

#include<fstream>

#include "var.h"

void importerConfig(jardins jardins[], int& NBJardins) {
    ifstream config("config.txt", ios::in);

    char ligne[1000];

    if (config) {
        char ligneJardin[1000];

        bambous bambous[maxNBBambous];
        int NBBambous = 0;

        pandas pandas[maxNBPandas];
        int NBPandas = 0;

        while (!config.eof()) {
            config.getline(ligne, 1000);

            int ligneTaille = strlen(ligne);

            char selection = ligne[0];

            if (selection == 'b') {
                char ligneBambou[1000];
                int indCarac = 0;

                for (int i = 2; i < ligneTaille; i++)
                {
                    ligneBambou[indCarac] = ligne[i];
                    indCarac++;
                }

                float vitessePousse = atof(ligneBambou);
                initBambous(bambous, NBBambous, vitessePousse);
            }
            else if (selection == 'p') {
                initPandas(pandas, NBPandas, 0);
            }
            else if (selection == 'j') {
                strcpy_s(ligneJardin, ligne);
            }
        }

        int tailleLigneJardin = strlen(ligneJardin);
        char paramsJardin[4][50];
        int indCaracLigneJardin = 0;
        int NBVirgulesLigneJardin = 0;

        for (int i = 2; i < tailleLigneJardin; i++) {
            if (ligneJardin[i] == ',') {
                paramsJardin[NBVirgulesLigneJardin][indCaracLigneJardin] = '\0';

                NBVirgulesLigneJardin++;
                indCaracLigneJardin = 0;
            }
            else {
                paramsJardin[NBVirgulesLigneJardin][indCaracLigneJardin] = ligneJardin[i];

                indCaracLigneJardin++;
            }
        }

        initJardin(jardins, NBJardins, paramsJardin[0], bambous, NBBambous, pandas, NBPandas, atoi(paramsJardin[1]), paramsJardin[2], atoi(paramsJardin[3]));
        
        config.close();
    }
}

void exporterConfig(jardins jardin) {
    ofstream config("config.txt", ios::out);

    config << "j," << jardin.pandaDeplacementLimite << ',' << jardin.nomAlgo << ',' << jardin.manuelActive << endl;

    for (int i = 0; i < jardin.NBPandas; i++) {
        if (i == jardin.NBPandas - 1 && i != 0) {
            config << "p";
        }
        else {
            config << "p" << endl;
        }
    }

    for (int i = 0; i < jardin.NBBambous; i++) {
        if (i == jardin.NBBambous - 1 && i != 0) {
            config << "b," << jardin.bambous[i].vitessePousse;
        }
        else {
            config << "b," << jardin.bambous[i].vitessePousse << endl;
        }
    }

    config.close();
}