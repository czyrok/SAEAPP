#pragma once
using namespace std;

#include <iostream>
#include "var.h"

void afficherMenu(SDL_Renderer *rendu)
{
	SDL_Rect menu = {0, TAILLEBARY, TAILLEMENUX, TAILLEFENY};

	SDL_SetRenderDrawColor(rendu, 59, 93, 108, 255);
	SDL_RenderFillRect(rendu, &menu);
}

void afficherBar(SDL_Renderer *rendu)
{
	SDL_Rect bar = {0, 0, TAILLEFENX, TAILLEBARY};

	SDL_SetRenderDrawColor(rendu, 37, 60, 71, 255);
	SDL_RenderFillRect(rendu, &bar);
}

void afficherCarre(SDL_Renderer *rendu)
{
	SDL_Rect carre = {TAILLEMENUX, TAILLEBARY, TAILLEFENX - TAILLEMENUX - tailleStatsX, tailleStatsY};

	SDL_SetRenderDrawColor(rendu, 169, 169, 169, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_Rect carre2 = {TAILLEFENX - tailleStatsX - tailleEchelleStatsX - tailleNBCoupesStatX, TAILLEBARY, tailleStatsX, tailleStatsY};

	SDL_SetRenderDrawColor(rendu, 189, 189, 189, 255);
	SDL_RenderFillRect(rendu, &carre2);
	
}

void actualiserAffichagePandas(jardins &jardin, SDL_Renderer *rendu)
{
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);

	for (int i = 0; i < jardin.NBPandas; i++)
	{
		SDL_Rect rect = {TAILLEMENUX + taillePandaX * jardin.pandas[i].x, TAILLEFENY - taillePandaY, taillePandaX, taillePandaY};

		SDL_Texture *texture = loadImage(rendu, "img/panda.png");

		SDL_RenderCopy(rendu, texture, NULL, &rect);
	}
}

void actualiserAffichageBambous(jardins &jardin, SDL_Renderer *rendu)
{
	int tailleFosse = 4;

	SDL_SetRenderDrawColor(rendu, 68, 118, 54, 255);

	for (int i = 0; i < jardin.NBBambous; i++)
	{
		int sommeH = 0;

		for (int j = 0; j < jardin.bambous[i].taillePousse; j++)
		{
			SDL_Rect carre = {TAILLEMENUX + (tailleBambousX * i) + tailleFosse / 2, (TAILLEFENY - taillePandaY - ((float)jardin.bambous[i].vitessePousse * (float)10 * (j + 1))), tailleBambousX - tailleFosse, jardin.bambous[i].vitessePousse * 10};

			if (sommeH + carre.h > tailleMaxBambousY && sommeH - tailleMaxBambousY <= tailleMaxBambousY)
			{
				carre.h = sommeH - tailleMaxBambousY;
				break;
			}

			SDL_RenderDrawLine(rendu, carre.x - tailleFosse / 2, carre.y, carre.x + tailleFosse / 2 + carre.w, carre.y);

			SDL_RenderFillRect(rendu, &carre);

			sommeH += carre.h;
		}
	}
}

void actualiserAffichageStatistiques(jardins &jardin, SDL_Renderer *rendu)
{
	int hauteur = 50;

	if (jardin.indStat < 100)
	{
		for (int i = 0; i < jardin.indStat; i++)
		{
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge

			SDL_Rect pointmax;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmax.y = TAILLEFENY - jardin.tailleMaxStat[i] - 1 - hauteur;
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmax);

			if (i > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMaxStat[i - 1] - hauteur, pointmax.x + 1, pointmax.y + 1);
			}

			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255); //min marron
			SDL_Rect pointmin;
			pointmin.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmin.y = TAILLEFENY - jardin.tailleMinStat[i] - hauteur;
			pointmin.w = 3;
			pointmin.h = 3;
			SDL_RenderFillRect(rendu, &pointmin);

			if (i > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMinStat[i - 1] - hauteur, pointmin.x + 1, pointmin.y + 1);
			}
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
			SDL_Rect pointmoy;
			pointmoy.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmoy.y = TAILLEFENY - jardin.tailleMoyStat[i] - hauteur;
			pointmoy.w = 3;
			pointmoy.h = 3;
			SDL_RenderFillRect(rendu, &pointmoy);

			if (i > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMoyStat[i - 1] - hauteur, pointmoy.x + 1, pointmoy.y + 1);
			}
		}
	}
	else
	{
		int compteur = 0;

		for (int i = jardin.indStat % NBStats; i < NBStats; i++)
		{
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge

			SDL_Rect pointmax;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - (jardin.indStat % NBStats) * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmax.y = TAILLEFENY - jardin.tailleMaxStat[i] - 1 - hauteur;
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmax);

			if (compteur > 0 && jardin.indStat % NBStats > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX - (jardin.indStat % NBStats) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMaxStat[i - 1] - hauteur, pointmax.x + 1, pointmax.y + 1);
			}

			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255); //min marron
			SDL_Rect pointmin;
			pointmin.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - (jardin.indStat % NBStats) * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmin.y = TAILLEFENY - jardin.tailleMinStat[i] - hauteur;
			pointmin.w = 3;
			pointmin.h = 3;
			SDL_RenderFillRect(rendu, &pointmin);

			if (compteur > 0 && jardin.indStat % NBStats > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX - (jardin.indStat % NBStats) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMinStat[i - 1] - hauteur, pointmin.x + 1, pointmin.y + 1);
			}
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
			SDL_Rect pointmoy;
			pointmoy.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - (jardin.indStat % NBStats) * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmoy.y = TAILLEFENY - jardin.tailleMoyStat[i] - hauteur;
			pointmoy.w = 3;
			pointmoy.h = 3;
			SDL_RenderFillRect(rendu, &pointmoy);

			if (compteur > 0 && jardin.indStat % NBStats > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX - (jardin.indStat % NBStats) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMoyStat[i - 1] - hauteur, pointmoy.x + 1, pointmoy.y + 1);
			}
			compteur++;
		}
		for (int i = 0; i < jardin.indStat % NBStats; i++)
		{
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge

			SDL_Rect pointmax;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmax.y = TAILLEFENY - jardin.tailleMaxStat[i] - 1 - hauteur;
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmax);

			if (i == 0)
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMaxStat[99] - hauteur, pointmax.x + 1, pointmax.y + 1);

			if (compteur < NBStats && i > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMaxStat[i - 1] - hauteur, pointmax.x + 1, pointmax.y + 1);
			}

			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255); //min marron
			SDL_Rect pointmin;
			pointmin.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmin.y = TAILLEFENY - jardin.tailleMinStat[i] - hauteur;
			pointmin.w = 3;
			pointmin.h = 3;
			SDL_RenderFillRect(rendu, &pointmin);

			if (compteur < NBStats && i > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMinStat[i - 1] - hauteur, pointmin.x + 1, pointmin.y + 1);
			}

			if (i == 0)
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMinStat[99] - hauteur, pointmin.x + 1, pointmin.y + 1);

			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
			SDL_Rect pointmoy;
			pointmoy.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - 1 - tailleNBCoupesStatX - tailleEchelleStatsX;
			pointmoy.y = TAILLEFENY - jardin.tailleMoyStat[i] - hauteur;
			pointmoy.w = 3;
			pointmoy.h = 3;
			SDL_RenderFillRect(rendu, &pointmoy);

			if (compteur < NBStats && i > 0)
			{
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMoyStat[i - 1] - hauteur, pointmoy.x + 1, pointmoy.y + 1);
			}

			if (i == 0)
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX + (NBStats - (jardin.indStat % NBStats)) * tailleStatX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEFENY - jardin.tailleMoyStat[99] - hauteur, pointmoy.x + 1, pointmoy.y + 1);

			compteur++;
		}
	}
}

void actualiserAffichageStatistiques2(jardins &jardin, SDL_Renderer *rendu)
{
	int hauteurX = taillePandaY,
		compteur = 0,
		taille = 3;

	int decalage = jardin.indStat < NBStats ? 0 : jardin.indStat % NBStats;
	int max = jardin.indStat < NBStats ? jardin.indStat : NBStats;

	for (int i = decalage; i < max; i++)
	{
		int pointX = tailleStatX * (i - decalage) + TAILLEFENX - tailleStatsX - tailleNBCoupesStatX - tailleEchelleStatsX - (int)(taille / 2);
		int pointY = TAILLEFENY - hauteurX - (int)(taille / 2);

		int ligneX = tailleStatX * ((i - 1) - decalage) + TAILLEFENX - tailleStatsX - tailleNBCoupesStatX - tailleEchelleStatsX;
		int ligneY = TAILLEFENY - hauteurX;

		SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
		int pointMaxY = pointY - jardin.tailleMaxStat[i] <= TAILLEBARY ? TAILLEBARY : pointY - jardin.tailleMaxStat[i];
		SDL_Rect pointMax = {pointX, pointMaxY, taille, taille};
		SDL_RenderFillRect(rendu, &pointMax);

		SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255);
		int pointMinY = pointY - jardin.tailleMinStat[i] <= TAILLEBARY ? TAILLEBARY : pointY - jardin.tailleMinStat[i];
		SDL_Rect pointMin = {pointX, pointMinY, taille, taille};
		SDL_RenderFillRect(rendu, &pointMin);

		SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
		int pointMoyY = pointY - jardin.tailleMoyStat[i] <= TAILLEBARY ? TAILLEBARY : pointY - jardin.tailleMoyStat[i];
		SDL_Rect pointMoy = {pointX, pointMoyY, taille, taille};
		SDL_RenderFillRect(rendu, &pointMoy);

		if (compteur > 0 && jardin.indStat % NBStats > 0)
		{
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
			int ligneMaxY = ligneY - jardin.tailleMaxStat[i - 1] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMaxStat[i - 1];
			SDL_RenderDrawLine(rendu, ligneX, ligneMaxY, pointMax.x + (int)(taille / 2), pointMax.y + (int)(taille / 2));
			
			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255);
			int ligneMinY = ligneY - jardin.tailleMinStat[i - 1] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMinStat[i - 1];
			SDL_RenderDrawLine(rendu, ligneX, ligneMinY, pointMin.x + (int)(taille / 2), pointMin.y + (int)(taille / 2));
			
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
			int ligneMoyY = ligneY - jardin.tailleMoyStat[i - 1] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMoyStat[i - 1];
			SDL_RenderDrawLine(rendu, ligneX, ligneMoyY, pointMoy.x + (int)(taille / 2), pointMoy.y + (int)(taille / 2));
		}

		compteur++;
	}

	for (int i = 0; i < decalage; i++)
	{
		int pointX = tailleStatX * (i + (NBStats - decalage)) + TAILLEFENX - tailleStatsX - tailleNBCoupesStatX - tailleEchelleStatsX - (int)(taille / 2);
		int pointY = TAILLEFENY - hauteurX - (int)(taille / 2);

		int ligneX = tailleStatX * ((i - 1) + (NBStats - decalage)) + TAILLEFENX - tailleStatsX - tailleNBCoupesStatX - tailleEchelleStatsX;
		int ligneY = TAILLEFENY - hauteurX;

		SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
		int pointMaxY = pointY - jardin.tailleMaxStat[i] <= TAILLEBARY ? TAILLEBARY : pointY - jardin.tailleMaxStat[i];
		SDL_Rect pointMax = {pointX, pointMaxY, taille, taille};
		SDL_RenderFillRect(rendu, &pointMax);

		SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255);
		int pointMinY = pointY - jardin.tailleMinStat[i] <= TAILLEBARY ? TAILLEBARY : pointY - jardin.tailleMinStat[i];
		SDL_Rect pointMin = {pointX, pointMinY, taille, taille};
		SDL_RenderFillRect(rendu, &pointMin);

		SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
		int pointMoyY = pointY - jardin.tailleMoyStat[i] <= TAILLEBARY ? TAILLEBARY : pointY - jardin.tailleMoyStat[i];
		SDL_Rect pointMoy = {pointX, pointMoyY, taille, taille};
		SDL_RenderFillRect(rendu, &pointMoy);

		if (i == 0)
		{
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
			int ligneMaxY = ligneY - jardin.tailleMaxStat[99] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMaxStat[99];
			SDL_RenderDrawLine(rendu, ligneX, ligneMaxY, pointMax.x + (int)(taille / 2), pointMax.y + (int)(taille / 2));
			
			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255);
			int ligneMinY = ligneY - jardin.tailleMinStat[99] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMinStat[99];
			SDL_RenderDrawLine(rendu, ligneX, ligneMinY, pointMin.x + (int)(taille / 2), pointMin.y + (int)(taille / 2));
			
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
			int ligneMoyY = ligneY - jardin.tailleMoyStat[99] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMoyStat[99];
			SDL_RenderDrawLine(rendu, ligneX, ligneMoyY, pointMoy.x + (int)(taille / 2), pointMoy.y + (int)(taille / 2));
		}
		else if (compteur < NBStats)
		{
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
			int ligneMaxY = ligneY - jardin.tailleMaxStat[i - 1] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMaxStat[i - 1];
			SDL_RenderDrawLine(rendu, ligneX, ligneMaxY, pointMax.x + (int)(taille / 2), pointMax.y + (int)(taille / 2));
			
			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255);
			int ligneMinY = ligneY - jardin.tailleMinStat[i - 1] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMinStat[i - 1];
			SDL_RenderDrawLine(rendu, ligneX, ligneMinY, pointMin.x + (int)(taille / 2), pointMin.y + (int)(taille / 2));
			
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
			int ligneMoyY = ligneY - jardin.tailleMoyStat[i - 1] <= TAILLEBARY ? TAILLEBARY + (int)(taille / 2) : ligneY - jardin.tailleMoyStat[i - 1];
			SDL_RenderDrawLine(rendu, ligneX, ligneMoyY, pointMoy.x + (int)(taille / 2), pointMoy.y + (int)(taille / 2));
		}

		compteur++;
	}
}

void afficherLegende(SDL_Renderer *rendu, TTF_Font *font)
{
	SDL_Rect positionTexte;
	positionTexte.x = TAILLEFENX - tailleStatsX - tailleEchelleStatsX - tailleNBCoupesStatX + (tailleStatsX) / 2 - ((tailleStatsX) / 4);
	positionTexte.y = 50;
	SDL_Texture *texture = loadText(rendu, "Max", { 255, 0, 0 }, font);
	SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
	positionTexte.x -= positionTexte.w / 2;
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	positionTexte.y = 100;
	texture = loadText(rendu, "Min", { 111, 45, 0 }, font);
	positionTexte.x += positionTexte.w / 2;
	SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
	positionTexte.x -= positionTexte.w / 2;
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	positionTexte.x = TAILLEFENX - tailleStatsX - tailleEchelleStatsX - tailleNBCoupesStatX + (tailleStatsX) / 2 + ((tailleStatsX) / 4);
	texture = loadText(rendu, "Nb de bambous coupes", { 0, 255, 0 }, font);
	SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
	positionTexte.x -= positionTexte.w / 2;
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);

	positionTexte.y = 50;
	texture = loadText(rendu, "Moyenne", { 0, 0, 255 }, font);
	positionTexte.x += positionTexte.w / 2;
	SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
	positionTexte.x -= positionTexte.w / 2;
	SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
	SDL_DestroyTexture(texture);
	

	/*SDL_Rect positionTextemarron;
	positionTextemarron.x = TAILLEFENX - tailleStatsX - tailleEchelleStatsX - tailleNBCoupesStatX + (tailleStatsX) / 2 - ((tailleStatsX) / 4);
	positionTextemarron.y = 100;
	SDL_Texture *texture2 = loadText(rendu, "Min", marron, font);
	SDL_QueryTexture(texture2, NULL, NULL, &positionTextemarron.w, &positionTextemarron.h);
	positionTextemarron.x -= positionTextemarron.w / 2;
	SDL_RenderCopy(rendu, texture2, NULL, &positionTextemarron);
	SDL_DestroyTexture(texture2);

	SDL_Rect positionTextebleu;
	positionTextebleu.x = TAILLEFENX - tailleStatsX - tailleEchelleStatsX - tailleNBCoupesStatX + (tailleStatsX) / 2 + ((tailleStatsX) / 4);
	positionTextebleu.y = 50;
	SDL_Texture *texture3 = loadText(rendu, "Moyenne", bleu, font);
	SDL_QueryTexture(texture3, NULL, NULL, &positionTextebleu.w, &positionTextebleu.h);
	positionTextebleu.x -= positionTextebleu.w / 2;
	SDL_RenderCopy(rendu, texture3, NULL, &positionTextebleu);
	SDL_DestroyTexture(texture3);

	SDL_Rect positionTexteVert;
	positionTexteVert.x = TAILLEFENX - tailleStatsX - tailleEchelleStatsX - tailleNBCoupesStatX + (tailleStatsX) / 2 + ((tailleStatsX) / 4);
	positionTexteVert.y = 100;
	SDL_Texture *texture4 = loadText(rendu, "Nb de bambous coupes", vert, font);
	SDL_QueryTexture(texture4, NULL, NULL, &positionTexteVert.w, &positionTexteVert.h);
	positionTexteVert.x -= positionTexteVert.w / 2;
	SDL_RenderCopy(rendu, texture4, NULL, &positionTexteVert);
	SDL_DestroyTexture(texture4);*/
}

void afficherStatNBCoupes(SDL_Renderer *rendu, jardins &jardin)
{
	SDL_Rect carre = {TAILLEFENX - tailleNBCoupesStatX, TAILLEBARY, tailleNBCoupesStatX, TAILLEFENY - TAILLEBARY};

	SDL_SetRenderDrawColor(rendu, 189, 189, 189, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
	SDL_Rect barre = {TAILLEFENX - tailleNBCoupesStatX, TAILLEFENY - jardin.NBCoupesStat * 10, tailleNBCoupesStatX, jardin.NBCoupesStat * 10};

	if (barre.h > tailleStatsY)
	{
		barre.y = TAILLEBARY;
		barre.h = tailleStatsY;
	}

	SDL_RenderFillRect(rendu, &barre);
}

void afficherEchelle(SDL_Renderer *rendu)
{
	SDL_Rect carre = {TAILLEFENX - tailleNBCoupesStatX - tailleEchelleStatsX, TAILLEBARY, tailleEchelleStatsX, TAILLEFENY - TAILLEBARY};

	SDL_SetRenderDrawColor(rendu, 189, 189, 189, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_SetRenderDrawColor(rendu, 0, 59, 6, 255);
	SDL_Rect echelle = {TAILLEFENX - tailleNBCoupesStatX - tailleEchelleStatsX + tailleEchelleStatsX / 4, TAILLEBARY, tailleEchelleStatsX / 2, tailleEchelleStatsY};

	SDL_RenderFillRect(rendu, &echelle);

	for (int i = 10; i < tailleEchelleStatsY; i += 10)
	{
		SDL_RenderDrawLine(rendu, echelle.x - tailleEchelleStatsX / 4, TAILLEFENY - i, echelle.x + echelle.w + tailleEchelleStatsX / 4, TAILLEFENY - i);
	}
}