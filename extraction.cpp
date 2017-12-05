/*************************************************
Travail Pratique #2 ; Module extraction.cpp
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Fonction de base
#include <stdio.h>
#include <stdlib.h>

//Constante utile
#include "constantes.h"

//typedef de t_terrain et fonction utile sur le type
#include "t_terrain.h"

//typedef de t_carte et fonction utile lie sur le type
#include "prospection.h"

//Fonction utile lie a l'extraction (case marquer comme foree)
#include "extraction.h"


//Change la valeur des cases marquées à forer par un 3 qui est la valeur pour les cases forées.
//Utilisation d'un for pour scruter le tableau puisqu'on connait le nombre de case.
void forage_compagnie(t_carte carte,const t_terrain terrain){

	//Compteurs
	int i;
	int j;

	//boucle for pour scruter le tableau en entier,
	//puisqu'on connait le nombre exacte de case.
	for (i = 0; i < HAUTEUR_TERRAIN; i++) {

		for (j = 0; j < LARGEUR_TERRAIN; j++) {

			//associe forage aux cases marquées à forer
			if (carte.tableau[i][j] && terrain[i][j] >= SEUIL_RENTABILITE_CASE_COMPAGNIE)
				carte.tableau[i][j] = FORAGE;
		}
	}
}

//Retourne la somme du minerai dans les cases du terrain qui ont été forées en parcourant toutes les cases.
//Utilisation d'un for pour scruter le tableau puisqu'on connait le nombre de case.
double somme_minerai_extrait (const t_carte carte, const t_terrain terrain){

	//Compteurs
	int i;
	int j;

	//Variable temporaire pour contenir la somme du terrain
	double somme = 0;

	//boucle for pour scruter le tableau en entier,
	//puisqu'on connait le nombre exacte de case.
	for (i = 0; i < HAUTEUR_TERRAIN; i++) {

		for (j = 0; j < LARGEUR_TERRAIN; j++) {

			//on additionne la valeur du minerai pour chaque case forée
			if (carte.tableau[i][j] == FORAGE)
				somme = somme + terrain [i][j];
		}
	}

	return somme;
}
//Retourne le nombre de cases marquées comme forées en parcourant toutes les cases du terrain.
//Utilisation d'un for pour scruter le tableau puisqu'on connait le nombre de case.
int nombre_cases_forées(const t_carte carte, const t_terrain terrain){

	//Compteurs
	int i;
	int j;
	int compteur_case = 0;

	//boucle for pour scruter le tableau en entier,
	//puisqu'on connait le nombre exacte de case.
	for (i = 0; i < HAUTEUR_TERRAIN; i++) {

		for (j = 0; j < LARGEUR_TERRAIN; j++) {

			//on incrémente le compteur de cases marquées comme forées.
			if (carte.tableau[i][j] == FORAGE)
				//Incrementation du compteur
				compteur_case ++;

		}
	}

	//Retourne la valeur du compteur
	return compteur_case;
}