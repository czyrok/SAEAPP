#include<fstream>
#include<iostream>
#include"var.h"
using namespace std; 

void importer(jardins jardins[], int& NBJardins) {
    ifstream entree("config.txt", ios::in);

    char ligne[1000];

    if (!entree)
        cout << "Probleme d'ouverture \n";
    else {
        char ligneJardin[1000];

        bambous bambous[maxNBBambous];
        int NBBambous = 0;

        pandas pandas[maxNBPandas];
        int NBPandas = 0;

        while (!entree.eof()) {
            entree.getline(ligne, 1000);

            int ligneTaille = strlen(ligne);

            char selection = ligne[0];


            if (selection == 'b') {
                float vitessePousse = 0;

                char ligneBambou[1000];
                int indCarac = 0;

                for (int i = 2; i < ligneTaille; i++)
                {
                    ligneBambou[indCarac] = ligne[i];
                    indCarac++;
                }
            }
            else if (selection == 'p') {
                initPandas(pandas, NBPandas, 0);
            }
            else if (selection == 'j') {
                strcpy_s(ligneJardin, ligne);
            }
        }
        entree.close();
    }
}