/*************************************************
Travail Pratique #2 ; Module t_terraon.cpp
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Module de fonction de base
#include <stdio.h>
#include <stdlib.h>

//Fonction qui genere des aleatoires
#include "mtwister.h"

//Module pour l'affichage graphique
#include "graph_io.h"
#include "WINBGIM.H"

//Module de constante utile
#include "constantes.h"

//Typedef t_terrain et fonction relie au type
#include "t_terrain.h"

//Module de fonction utile
#include "module_utilitaire.h"


//Affichage graphique de la carte et du terrain en associant la bonne couleur 
//aux cases du tableau. Utilisation d'un for pour scruter le tableau puisqu'on 
//connait le nombre de case.
void affichage_terrain(t_terrain terrain){
	int i = 0;				//compteur
	int j = 0;				//compteur
	double pourcentage;		//pourcentage pour les couleurs

	//boucle for pour scruter le tableau en entier. et 
	//puisqu'on connait le nombre exacte de case
	//Associe les couleurs aux cases
	for (i = 0; i < HAUTEUR_TERRAIN; i++){
		for (j = 0; j < LARGEUR_TERRAIN; j++){

			//pour le blanc
			if (!terrain[i][j]){

				//Encadre et dessine la case avec la même couleur
				encadrer_case(i, j, get_degrade_blanc_jaune(terrain[i][j]));
				dessiner_case(i, j, get_degrade_blanc_jaune(terrain[i][j]), 
					get_degrade_blanc_jaune(terrain[i][j]));
			}

			//pour le jaune 
			else  if (terrain[i][j] < (COUT_SONDAGE + COUT_FORAGE)){

				//calcule du pourcentage pour avoir la bonne couleur
				pourcentage = terrain[i][j] / (COUT_SONDAGE + COUT_FORAGE);

				//Encadre et dessine la case avec la même couleur
				encadrer_case(i, j, get_degrade_blanc_jaune(pourcentage));
				dessiner_case(i, j, 
					get_degrade_blanc_jaune(pourcentage), 
					get_degrade_blanc_jaune(pourcentage));
			}

			//pour le orange
			else if (terrain[i][j] > (COUT_SONDAGE + COUT_FORAGE)){

				//calcule du pourcentage pour avoir la bonne couleur
				pourcentage = terrain[i][j] / (COUT_SONDAGE + COUT_FORAGE);

				//Encadre et dessine la case avec la même couleur
				encadrer_case(i, j, get_degrade_orange_rouge(pourcentage));
				dessiner_case(i, j, get_degrade_orange_rouge(pourcentage), 
					get_degrade_orange_rouge(pourcentage));
			}
			//pour le rouge
			else if (terrain[i][j] > (3 * (COUT_SONDAGE + COUT_FORAGE))){

				//force le terrain à être en rouge
				terrain[i][j] = 1;

				//Encadre et dessine la case avec la même couleur
				encadrer_case(i, j, get_degrade_orange_rouge(terrain[i][j]));
				dessiner_case(i, j, get_degrade_orange_rouge(terrain[i][j]), 
					get_degrade_orange_rouge(terrain[i][j]));
			}
		}
	}
	//Pause le systeme
	system("pause");

	//Fermeture du mode graphique
	fermer_graph;
}

//Vide le terrain completement
//Utilisation d'un for pour scruter le tableau puisqu'on connait le nombre de
//case.
void vider_terrain(t_terrain terrain){

	int i = 0;		//compteur
	int j = 0;		//compteur

	//boucle for pour scruter le tableau en entier et 
	//puisqu'on connait le nombre exacte de case
	for (i = 0; i < HAUTEUR_TERRAIN; i++){

		for (j = 0; j < LARGEUR_TERRAIN; j++){
			terrain[i][j] = 0;
		}
	}
}

//Remplir le terrain aleatoirement dans une uniforme [MIN_ALEA,MAX_ALEA]
//Utilisation d'un for pour scruter le tableau puisqu'on connait le nombre 
//de case.
void remplir_terrain_aleatoire(t_terrain terrain){

	int i;			//compteur
	int j;			//compteur

	//LES COULEURS CHANGENT AVEC DES MIN ET MAX DIFFÉRENT
	for (i = 0; i < HAUTEUR_TERRAIN; i++) {
		for (j = 0; j < LARGEUR_TERRAIN; j++){

			//L'émission d'un nombre réel dans une uniforme [MIN_ALEA,MAX_ALEA]
			terrain[i][j] = mt_randf(MIN_ALEA, MAX_ALEA);
		}
	}
}

//Remplir un terrain avec une courbe normal. Les valeurs de chaque case vont
//graviter autour d'une moyenne ne dépassant pas les bornes d'un écart type 
//donné. Utilisation d'un for pour scruter le tableau puisqu'on connait le 
//nombre de case.
void remplir_terrain_normal(t_terrain terrain){

	int i;		//compteur
	int j;		//compteur

	//LES COULEURS CHANGE SI ONT CHANGE LES VALEURS MOYENNE ET ECART TYPE
	for (i = 0; i < HAUTEUR_TERRAIN; i++) {
		for (j = 0; j < LARGEUR_TERRAIN; j++){

			//L'émission d'un nombre réel dans une distribution normale 
            //de moyenne et d'écart-type donnés
			terrain[i][j] = mt_randnormal(MOYENNE, ECART);
		}
	}
}

//Remplir un terrain avec un ou plusieurs filons aléatoire entre NB_FILONS_MIN 
//et NB_FILONS_MAX. Utilisation d'une boucle for parce qu'on va connaitre le 
//nombre de veine.
void remplir_terrain_filons(t_terrain terrain){

	int veine = 0;		//Nombre de veine qui seront générée.
	int i = 0;			//Compteur.
	
	//Nombre de veine générée aléatoirement
	veine = alea(NB_FILONS_MIN, NB_FILONS_MAX);

	//scrute chaque veine
	for (i = 0; i < veine; i++) {
		//Appel d'un sous-programme qui cree un filon
		creer_filons(terrain);
	}
}

//Crée un ou plusieurs filon qui seront utilisées dans replir_terrain_filon.
void creer_filons(t_terrain terrain){

	//Valeur comparative qui doit être <= à la  
	//VALEUR_FILON pour arrêter l'incrémentaion.
	double distribue = 0;	
	
	//longueur ligne.
	int l;					 
	
	//longueur colonne.
	int c;					

	//Permet de garder en mémoire la valeur initiale de l.
	int i;					
	
	//Permet de garder en mémoire la valeur initiale de c.
	int j;
		
	//valeur à obtenir pour permettre un changement
	//de direction au filon.
	double probabilite;		

	//Fait bouger le carré de ligne en ligne.
	int case_bouger_ligne;	
	
	//Fait bouger le carré de colonne en colonne.
	int case_bouger_colone;	

	//Hauteur du terrain
	int c_hauteur;
	
	//Largeur du terrain
	int c_largeur;

	//Choisis aleatoirement une ligne ou une colonne dans les dimensions 
	//du terrain
	l = alea((MINIMUM_TERRAIN + 1), (MAXIMUM_TERRAIN - 2));
	c = alea((MINIMUM_TERRAIN + 1), (MAXIMUM_TERRAIN - 2));
	
	//Pour que le programme ce souvienne de la case de depart
	i = l;
	j = c;

	//Boucle qui rempli VALEUR FILON dans un terrain 
	//L'utilisation du while car on ne sait pas combien de tour de boucle
	//le programme va devoir faire avant de terminer
	while (distribue <= VALEUR_FILON){

		//Boucle qui s'arrete quand la valeur de la case devient superieur 
		//a la valeur du filon
		for(c_hauteur = 0; c_hauteur < TAILLE_CARRE_AJOUT; c_hauteur++)
			for(c_largeur = 0; c_largeur < TAILLE_CARRE_AJOUT; c_largeur++)
				//Incremente la case par la VAL_AJOUT
				terrain[l+c_largeur][c+c_hauteur] += VAL_AJOUT;

		//Valeur de sorti de la boucle while
		distribue += TAILLE_CARRE_AJOUT*TAILLE_CARRE_AJOUT * VAL_AJOUT;

		//Donne une probabilite enter 0 et 1
		probabilite = ((double) rand() / (RAND_MAX));

		//Condition de mouvement si elle est remplie, il y a mouvement
		if (probabilite <= PROBABILITE){

			//Bouge la ligne ou la colonne (avance, recule, ne bouge pas)
			//Choisis aleatoirement
			//Met la ligne ou la colonne a la nouvelle position
			case_bouger_ligne = alea(BORNE_MIN, BORNE_MAX);
			l += case_bouger_ligne;

			case_bouger_colone = alea(BORNE_MIN, BORNE_MAX);
			c += case_bouger_colone;

			//Condition de sorti de terrain, revien à la position de base
			if ((l == MINIMUM_TERRAIN + BORNE_MIN) || (l == MAXIMUM_TERRAIN)){
				l = i;
				c = j;
			}

			if ((c == MINIMUM_TERRAIN + BORNE_MIN) || (c == MAXIMUM_TERRAIN)){
				l = i;
				c = j;
			}
		}
	}
}
//Calculer le total de minerai se trouvant sur le terrain choisi en scrutant 
//le tableau. Utilisation d'un for pour scruter le tableau puisqu'on connait
//le nombre de case.
void total_minerai_terrain(const t_terrain terrain, double * total_terrain) {
	int i;		//compteur
	int j;		//compteur
	

	//LES COULEURS CHANGENT SI ON CHANGE LES VALEURS MOYENNE ET ECART TYPE
	for (i = 0; i < HAUTEUR_TERRAIN; i++) {
		for (j = 0; j < LARGEUR_TERRAIN; j++) {

			//incrémente le total de minerai
			*total_terrain += terrain[i][j];
		}
	}
}