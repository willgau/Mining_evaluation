/*************************************************
Travail Pratique #2 ; MAIN (Devoir 2)
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Fonction utilitaire de base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Genere des aleatoire
#include "mtwister.h"
#include "module_utilitaire.h"

//Module d'afficahge graphique
#include "graph_io.h"
#include "WINBGIM.H"

//Constantes utile
#include "constantes.h"

//Typedef t_terrain et fonction relie au type
#include "t_terrain.h"

//typedef t_carte et fonction relie au type
#include "prospection.h"

//Module d'extraction relie au case etant foree
#include "extraction.h"

//Module d'ecriture en fichier texte
#include "utilitaire_fichier.h"

//Typedef t_stats et fonction relie au type
#include "t_stats.h"

//prototype de la gestion des terrains 
int gestion_terrain(t_terrain terrain);
//Prototype de l'affichage du message de fin
void affichage_de_fin (double moyenne_perso,double moyenne_compa);
//Affichange pour le fichier texte
double affichage_fichier_texte (int *nb_cases_sondees, double *total_sondees,
	int *nb_cases_forees, double *total_forees, const t_terrain terrain, 
	const int x, const int choix_terrain);
//Affichage graphique de la carte si l'utilisateur le veut
void affichage_graphique_carte(t_terrain terrain);

int main(void) {

		//Fait en sorte que l'aleatoire se base sur le temps reel 
		srand(time(NULL));

		//Enregistrement t_terrain qui provient du module t_terrain
		t_terrain terrain;
		
		//Compteur pour la boucle principale en plus d'etre la ligne
		//associe au bon sondage dans le fichier texte
		int x =1;

		//Variable pour les donnees du fichier texte	
		int nb_cases_sondees = 0; //Nombre de case sondees
		double total_sondees = 0; //Minerai total dans les cases sondees
		int nb_cases_forees = 0; //Nombre de cases forees
		double total_forees = 0; //Minerai total dans les cases forees
		int choix_terrain; //Variable qui indique le choix du terrain
		
		//Variable utiliser pour le calcule de moyenne personnelle et celui
		// de la compagnie
		double moyenne_perso = 0;
		double moyenne_compa = 0;
		double moyenne = 0;

		//Ouverture du fichier texte
		ouvrir_fichier("INF145-02_RESULTAT");
		
		//Besoin du double d'iteration vu que j'incremente une deuxieme fois
		//pour afficher sur la deuxième ligne le resultat de la compagnie
		//Utilisation d'un FOR car on sait le nombre exact d'iteration
		for (int x = 1; x < NB_DE_TERRAIN_CHOISIS; x++) {
			
			//Met la console en mode graphique.
			demarrer_graph(HAUTEUR_TERRAIN, LARGEUR_TERRAIN);
			
			//Choix du terrain (UNI, ALEA, FILON)
			choix_terrain = gestion_terrain(terrain);

			//Affichage graphique de la carte si l'utilisateur le veut
			affichage_graphique_carte(terrain);

			//Sondage personnelle pour compare avec celui de la compagnie 
			//Les chiffres IMPAIRS dans le fichier texte sont les lignes
			//de resultats du sondage personnelle
			sondage_perso(terrain, &nb_cases_sondees, &total_sondees, 
				&nb_cases_forees, &total_forees);

			
			//Affichange des donnees dans le fichier texte pour le sondage 
			//perso
			moyenne = affichage_fichier_texte(&nb_cases_sondees, &total_sondees,
				&nb_cases_forees, &total_forees, terrain, x, choix_terrain);

			//MSomme des pourcentages de rentabilite
			//pour le sondage perso
			moyenne_perso = moyenne_perso + moyenne;
		
			//Sondage de la compagnie pour compare avec le sondage personnelle
			//Les chiffres PAIRES dans le fichier texte sont les lignes
			//de resultats du sondage de la compagnie
			sondage_compagnie(terrain, &nb_cases_sondees, &total_sondees,
				&nb_cases_forees, &total_forees);
			
			//incrementation du compteur pour change de ligne pour afficher les 
			//donnees pour une meilleur comparaison
			x++;
			
			//Affiche dans le fichier texte les donnees de la compagnie
			moyenne = affichage_fichier_texte(&nb_cases_sondees, 
				&total_sondees, &nb_cases_forees, &total_forees, terrain, x,
					choix_terrain);

			//Somme des pourcentages de rentabilite pour le sondage de la
			//compagnie
			moyenne_compa = moyenne_compa + moyenne;

			//Fermeture du mode graphique
			fermer_graph();
		}

		//Fermeture du fichier texte
		fermer_fichier();

		//Calcul des moyennes 
		moyenne_perso = moyenne_perso / NB_DE_TERRAIN; //Moyenne perso 
		moyenne_compa = moyenne_compa / NB_DE_TERRAIN;//Moyenne de la compagnie
		
		//Affichage d'un message de fin de fichier
		affichage_de_fin(moyenne_perso,moyenne_compa);

		//Pause du systeme
		system("pause");

		//Fin du programme
		return EXIT_SUCCESS;
}


int gestion_terrain (t_terrain terrain){
	
	//variable retourne pour l'affichage du nom du terrain dans le fichier
	//En plus d'être utilise pour le switch case avec l'aleatoire
	int choix_terrain;
	
	//Vide le terrain pour en faire un nouveau vide (chaque case à 0)
	vider_terrain(terrain);

	//Chiffre aleatoire pour le choix du terrain  
	//De plus le chiffre est utilise pour identifier les terrains
	// 1 pour UNI, 2 pour ALEA et 3 pour FILONS
	choix_terrain = alea(GESTION_MIN, GESTION_MAX);

	//Switch case utiliser pour remplir le bon terrain qui est choisi 
	//aleatoirement
	switch(choix_terrain){
		case 1 : remplir_terrain_normal(terrain); break;
		case 2 : remplir_terrain_aleatoire (terrain); break;
		case 3 : remplir_terrain_filons(terrain); break;
	}
	//Retour de la variable choix terrain 
	return choix_terrain ; 
}
//Sous-programme qui affiche simplement un message de fin
void affichage_de_fin (double moyenne_perso, double moyenne_compa) {
	
	//Affichage des moyennes perso et compagnie
	printf("\n\n Voici la moyenne personnelle = %.2lf",moyenne_perso);
	printf("\n\n Voici la moyenne de la compagnie %.2lf \n",moyenne_compa);
		
	//Affichage d'un message de fin de programme
	printf("\nVous pouvez maintenant voir les resultats de la simulation");
	printf("dans le fichier xls!\n Merci!\n");
}


double affichage_fichier_texte(int *nb_cases_sondees, double *total_sondees,
	int *nb_cases_forees, double *total_forees, const t_terrain terrain,
	const int x, const int choix_terrain) {
	
	//Enregistrement t_stats pour pouvoir garder les resultats et les 
	//ecrire dans un fichier texte
	t_stats stats;

	//Variable pour l'affichage des donnees dans le fichier
	double total_terrain = 0; //Minerai total dans le terrain
	char numero_ligne[5] = { 0 }; //Pour affichier le compteur dans le fichier
	double moyenne = 0;

	//Fonction qui change l'entier (int) du compteur x pour un char
	sprintf(numero_ligne, "%d", x);
	
	//Initialisation à 0 des donnees pour commencer l'ecriture dans le fichier
	init_stats(&stats, numero_ligne,choix_terrain );
	
	//Avoir le total de minerai dans le terrain 
	total_minerai_terrain(terrain, &total_terrain);

	//Avoir le total de minerai dans t_stats
	stats.total_terrain = total_terrain;

	//Avoir le nombre de cases sondees dans t_stats
	stats.nb_case_sondees = *nb_cases_sondees;

	//Avoir le total minerais dans les cases sondees dans t_stats
	stats.total_sondees = *total_sondees;

	//Avoir le nombre de cases forees dans t_stats
	stats.nb_case_forees = *nb_cases_forees;

	//Avoir le total de minerai de cases forees dans t_stats
	stats.total_forees = *total_forees;

	//Avoir le profit maximal possible dans t_stats
	stats.profit_possible = total_terrain - (*nb_cases_forees * COUT_FORAGE)
		- (*nb_cases_sondees * COUT_SONDAGE);
	
	//Avoir le profit d'extraction dans t_stats
	stats.profit_extraction = *total_forees - (*nb_cases_forees * COUT_FORAGE)
		- (*nb_cases_sondees * COUT_SONDAGE);

	//Avoir le pourcentage de profit realiser sur le profit total dans t_stats
	//Le code dans t_stats.h le int de stats.pourc_profit 
	//à ete change pour un double pour permettre un affichage dans le fichier
	stats.pourc_profit = (stats.profit_extraction / stats.profit_possible) * POURCENTAGE;
	
	//Condition particuliere si le pourcentage de profit est negatif
	if (stats.profit_possible < NULL)
		stats.pourc_profit = (stats.profit_extraction / stats.profit_possible) * POURCENTAGE_NEGATIF;
	
	//Ecriture des donnees dans le fichier texte
	ecrire_stats(&stats);

	//Retourne le pourcentage de profit pour calcule la somme
	//des pourcentages puis calculer la moyenne
	return moyenne = stats.pourc_profit;
}
//Affichage graphique de la carte si l'utilisateur le veut
void affichage_graphique_carte(t_terrain terrain) {

	//Variable pour le choix de l'utilisateur s'il affiche ou non la carte
	char reponse = NULL;
	
	//Verification et demande pour l'affichage du terrain
	//Utilisation d'un while car on ne sait pas quand l'utilisateur 
	//va entrer le bon caractere
	while (reponse != 'o' && reponse != 'O' && reponse != 'n' 
		&& reponse != 'N'){

			//********************************************************
			//Demande de validation à l'ecran pour une reponse correct
			//********************************************************
			printf("\n Voulez-vous afficher la carte?"); 
			printf("\nPour Oui, cliquer 'O' ou 'o'");
			printf("\n Pour Non, cliquer 'N' ou 'n' \n");
			
			//Prise de la reponse au clavier
			scanf("%c", &reponse);

			//Vide le tampon du clavier
			fflush(stdin);
	}

	//Affichage graphique du terrain si la reponse est oui
	if (reponse != 'n' && reponse != 'N')
		affichage_terrain(terrain);
}