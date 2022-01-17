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
        char params[4][50];
        int indCarac = 0;
        int NBVirgules = 0;

        for (int i = 2; i < tailleLigneJardin, i++) {
            params[NBVirgules][indCarac] = ligneJardin[i];
        }

        entree.close();
    }
}

//while (i <NBJardins ) {
//    char ligne[10];
//    entree.getline(ligne, 10, ',');
//    jardins[i].dpt = atoi(ligne);
//    entree.getline(jardins[i]., 100, ',');
//    entree.getline(jardins[i].indStat, 100, ',');
//    entree.getline(jardins[i].nomAlgo, 100,',');
//    entree.getline(jardins[i].manuelActive, 100,',');
//    i++;
//}
//  






if (NBVirgules == ',') {
    NBVirgules++;
else {
    indCarac++;
}
}