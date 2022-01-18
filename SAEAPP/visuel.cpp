#pragma once
using namespace std;

#include <iostream>
#include "var.h"

void afficherMenu(SDL_Renderer* rendu) {
	SDL_Rect menu = { 0, TAILLEBARY, TAILLEMENUX, TAILLEFENY };

	SDL_SetRenderDrawColor(rendu, 59, 93, 108, 255);
	SDL_RenderFillRect(rendu, &menu);

	SDL_RenderPresent(rendu);
}

void afficherBar(SDL_Renderer* rendu) {
	SDL_Rect bar = { 0, 0, TAILLEFENX, TAILLEBARY };

	SDL_SetRenderDrawColor(rendu, 37, 60, 71, 255);
	SDL_RenderFillRect(rendu, &bar);

	SDL_RenderPresent(rendu);
}

void afficherCarre(SDL_Renderer* rendu) {
	SDL_Rect carre = { TAILLEMENUX, TAILLEBARY, TAILLEFENX - TAILLEMENUX - tailleStatsX, tailleStatsY };

	SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
	SDL_RenderFillRect(rendu, &carre);

	SDL_Rect carre2 = { TAILLEFENX - tailleStatsX, TAILLEBARY, TAILLEFENX - tailleStatsX, tailleStatsY };

	SDL_SetRenderDrawColor(rendu, 189, 189, 189, 255);
	SDL_RenderFillRect(rendu, &carre2);

	SDL_RenderPresent(rendu);
}

void actualiserAffichagePandas(jardins& jardin, SDL_Renderer* rendu)
{
	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);

	for (int i = 0; i < jardin.NBPandas; i++) {
		SDL_Rect rect;
		rect.x = TAILLEMENUX + taillePandaX * jardin.pandas[i].x;
		rect.y = TAILLEFENY - taillePandaY;
		rect.w = taillePandaX;
		rect.h = taillePandaY;

		SDL_RenderFillRect(rendu, &rect);
	}

	SDL_RenderPresent(rendu);
}

void actualiserAffichageBambous(jardins& jardin, SDL_Renderer* rendu)
{
	SDL_SetRenderDrawColor(rendu, 68, 118, 54, 255);

	for (int i = 0; i < jardin.NBBambous; i++) {
		for (int j = 0; j < jardin.bambous[i].taillePousse; j++) {
			SDL_Rect carre = { TAILLEMENUX + (tailleBambousX * i) + 2, (TAILLEFENY - taillePandaY - ((float)jardin.bambous[i].vitessePousse * (float)10 * (j + 1))), tailleBambousX - 4, jardin.bambous[i].vitessePousse * 10 };

			SDL_RenderFillRect(rendu, &carre);
		}
	}

	SDL_RenderPresent(rendu);
}

void actualiserAffichageStatistiques(jardins& jardin, SDL_Renderer* rendu)
{
	int hauteur = 50;
	
	if (jardin.indStat < 100) {
		for (int i = 0; i < jardin.indStat; i++) {
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge

			SDL_Rect pointmax;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - 1;
			pointmax.y = TAILLEFENY - jardin.tailleMaxStat[i] - 1 - hauteur;
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmax);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMaxStat[i - 1] - hauteur, pointmax.x + 1,pointmax.y + 1);
			}

			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255); //min marron
			SDL_Rect pointmin;
			pointmin.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmin.y = TAILLEFENY - jardin.tailleMinStat[i] - hauteur;
			pointmin.w = 3;
			pointmin.h = 3;
			SDL_RenderFillRect(rendu, &pointmin);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMinStat[i - 1] - hauteur, pointmin.x + 1, pointmin.y + 1);
			}
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
			SDL_Rect pointmoy;
			pointmoy.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmoy.y = TAILLEFENY - jardin.tailleMoyStat[i] - hauteur;
			pointmoy.w = 3;
			pointmoy.h = 3;
			SDL_RenderFillRect(rendu, &pointmoy);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMoyStat[i - 1] - hauteur, pointmoy.x + 1, pointmoy.y + 1);
			}
		}
	}
	else {
		for (int i = jardin.indStat % NBStats; i < NBStats; i++) {
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge

			SDL_Rect pointmax;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - 1;
			pointmax.y = TAILLEFENY - jardin.tailleMaxStat[i] - 1 - hauteur;
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmax);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMaxStat[i - 1] - hauteur, pointmax.x + 1, pointmax.y + 1);
			}

			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255); //min marron
			SDL_Rect pointmin;
			pointmin.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmin.y = TAILLEFENY - jardin.tailleMinStat[i] - hauteur;
			pointmin.w = 3;
			pointmin.h = 3;
			SDL_RenderFillRect(rendu, &pointmin);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMinStat[i - 1] - hauteur, pointmin.x + 1, pointmin.y + 1);
			}
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
			SDL_Rect pointmoy;
			pointmoy.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmoy.y = TAILLEFENY - jardin.tailleMoyStat[i] - hauteur;
			pointmoy.w = 3;
			pointmoy.h = 3;
			SDL_RenderFillRect(rendu, &pointmoy);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMoyStat[i - 1] - hauteur, pointmoy.x + 1, pointmoy.y + 1);
			}
		}
		for (int i = 0; i < jardin.indStat % NBStats; i++) {
			SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //max rouge

			SDL_Rect pointmax;
			pointmax.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX - 1;
			pointmax.y = TAILLEFENY - jardin.tailleMaxStat[i] - 1 - hauteur;
			pointmax.w = 3;
			pointmax.h = 3;
			SDL_RenderFillRect(rendu, &pointmax);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMaxStat[i - 1] - hauteur, pointmax.x + 1, pointmax.y + 1);
			}

			SDL_SetRenderDrawColor(rendu, 111, 45, 0, 255); //min marron
			SDL_Rect pointmin;
			pointmin.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmin.y = TAILLEFENY - jardin.tailleMinStat[i] - hauteur;
			pointmin.w = 3;
			pointmin.h = 3;
			SDL_RenderFillRect(rendu, &pointmin);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMinStat[i - 1] - hauteur, pointmin.x + 1, pointmin.y + 1);
			}
			SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255); //moyenne bleu
			SDL_Rect pointmoy;
			pointmoy.x = (TAILLEFENX - tailleStatsX) + i * tailleStatX;
			pointmoy.y = TAILLEFENY - jardin.tailleMoyStat[i] - hauteur;
			pointmoy.w = 3;
			pointmoy.h = 3;
			SDL_RenderFillRect(rendu, &pointmoy);

			if (i > 0) {
				SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (i - 1) * tailleStatX, TAILLEFENY - jardin.tailleMoyStat[i - 1] - hauteur, pointmoy.x + 1, pointmoy.y + 1);
			}
		}
	}

	SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);

	SDL_RenderDrawLine(rendu, (TAILLEFENX - tailleStatsX) + (jardin.indStat % NBStats) * tailleStatX, TAILLEBARY, (TAILLEFENX - tailleStatsX) + (jardin.indStat % NBStats) * tailleStatX, TAILLEFENY);

	SDL_RenderPresent(rendu);
}

void afficherLegende(SDL_Renderer* rendu, TTF_Font* font) {
	SDL_Color rouge = { 255,0,0 };
	SDL_Color marron = { 111,45,0 };
	SDL_Color bleu = { 0,0,255 };

	SDL_Rect positionTexterouge;
	positionTexterouge.x = TAILLEFENX - tailleStatsX + (tailleStatsX) / 2 - ((tailleStatsX) / 2)/2;
	positionTexterouge.y = 50;
	SDL_Texture* texture1 = loadText(rendu, "Max", rouge, font);
	SDL_QueryTexture(texture1, NULL, NULL, &positionTexterouge.w, &positionTexterouge.h);
	positionTexterouge.x -= positionTexterouge.w / 2;
	SDL_RenderCopy(rendu, texture1, NULL, &positionTexterouge);
	SDL_RenderPresent(rendu);
	SDL_DestroyTexture(texture1);



	SDL_Rect positionTextemarron;
	positionTextemarron.x = TAILLEFENX - tailleStatsX + (tailleStatsX)/2;
	positionTextemarron.y = 50;
	SDL_Texture* texture2 = loadText(rendu, "Min", marron, font);
	SDL_QueryTexture(texture2, NULL, NULL, &positionTextemarron.w, &positionTextemarron.h);
	positionTextemarron.x -= positionTextemarron.w / 2;
	SDL_RenderCopy(rendu, texture2, NULL, &positionTextemarron);
	SDL_RenderPresent(rendu);
	SDL_DestroyTexture(texture2);


	SDL_Rect positionTextebleu;
	positionTextebleu.x = TAILLEFENX - tailleStatsX + (tailleStatsX) / 2 + ((tailleStatsX) / 2) / 2;
	positionTextebleu.y = 50;
	SDL_Texture* texture3 = loadText(rendu, "Moyenne", bleu, font);
	SDL_QueryTexture(texture3, NULL, NULL, &positionTextebleu.w, &positionTextebleu.h);
	positionTextebleu.x -= positionTextebleu.w / 2;
	SDL_RenderCopy(rendu, texture3, NULL, &positionTextebleu);
	SDL_RenderPresent(rendu);
	SDL_DestroyTexture(texture3);
}