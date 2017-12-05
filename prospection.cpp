/*************************************************
Travail Pratique #2 ; Module prospection.cpp
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Fonctions de base
#include <stdio.h>
#include <stdlib.h>

//constantes utiles
#include "constantes.h"

//typedef de t_terrain et fonctions utile sur le type
#include "t_terrain.h"

//prototypes
#include "prospection.h"

//affichage (ex: encadrer_case())
#include "graph_io.h"
#include "WINBGIM.h"

//Utile pour les stats
#include "extraction.h"


/*************************************************
On crée et on initialise un tableau dynamiquement à l'aide de malloc pour la
première ligne et par la suite initialise avec calloc toute les colonnes
du tableau
Utilisation du for puisqu'on connaît la hauteur de notre tableau
(HAUTEUR_TERRAIN)
**************************************************/
t_carte carte_neuve(){
	//carte de type t_carte
	t_carte carte;
	//compteur
	int i;

	//On assigne la valeur des constantes HAUTEUR_TERRAIN et LARGEUR_TERRAIN
	//à notre carte
	carte.nb_col = HAUTEUR_TERRAIN;
	carte.nb_lig = LARGEUR_TERRAIN;

	//Alloue l'espace mémoire pour la premiere ligne du tableau. Converti en
	//pointeur de type char**
	carte.tableau = (char**) malloc (carte.nb_col * sizeof(char*));

	//boucle for qui s'arrete lorsque le compteur i est egale ou plus grand que
	//le nombre de colonne de notre terrain.
	for(i = 0; i < carte.nb_col; i++)

		//Alloue l'espace mémoire pour toute les colonne du tableau. Initialise
		//toutes les cases du tableau à NULL. Converti en pointeur 
		//de type char**
		carte.tableau [i] = (char*) calloc (carte.nb_lig, 2 * sizeof(char));

	//retourne la carte qui a été créé
	return carte;
}


/*************************************************
Utilisation de while puisque les constantes LIGNE_DE_DEPART, COLONNE_DE_DEPART,
PAS_LIGNE et PAS_COLONNE sont des constantes modifiables dans constantes.h.
Donc, on ne peut savoir combien de fois il fera la boucle.
**************************************************/
void sonder_a_pas_fixe(t_carte carte){
	//compteurs
	int i=0;
	int j=0;

	//initialise la ligne et la colonne de départ à la valeur prédéfinie dans
	//le module constantes.h
	int ligne = LIGNE_DE_DEPART;
	int colonne = COLONNE_DE_DEPART;

	//encadre la premiere case du terrain
	encadrer_case(LIGNE_DE_DEPART, COLONNE_DE_DEPART, BLACK);

	//la boucle s'arrête si ligne est égale ou supérieur à la hauteur du 
	//terrain
	while(ligne < HAUTEUR_TERRAIN){
		
		//marque la case comme sondée
		carte.tableau [ligne][colonne] = SONDEE;
		//encadre la case en question
		encadrer_case(ligne, colonne, BLACK);

		//la boucle s'arrête si colonne est égale ou supérieur à la largeur
		//du terrain moins le PAS_COLONNE
		while(colonne < (LARGEUR_TERRAIN-PAS_COLONNE)){

			//incrémente la colonne d'un pas de colonne
			colonne += PAS_COLONNE;
			//marque la case comme sondée
			carte.tableau [ligne][colonne] = SONDEE;
			//encadre la case en question
			encadrer_case(ligne, colonne, BLACK);
		}
		//Initialise la colonne à COLONNE_DE_DEPART avant de reprendre la
		//boucle
		colonne = COLONNE_DE_DEPART;
		//incrémente la ligne d'un pas de ligne
		ligne += PAS_LIGNE;
	}
}


/*************************************************
Utilisation d'une boucle while puisque distance est variable (constantes.h).
**************************************************/
void sonder_case_voisine(t_carte carte, int ligne, int colonne,
	int perso_compagnie, int deuxieme_tour){

	//distance entre la case initiale et la case sondée la plus loin
	int distance;

	//Marque la case sondee et indique que ses voisins ont été sondées
	carte.tableau[ligne][colonne] = SONDEE_ET_VOISIN_SONDEE;

	//initialise distance selon celui qui l'appel (compagnie ou perso) et
	//selon le tour effectué
	distance = choisir_distance (perso_compagnie, deuxieme_tour);

	//positionne la première case à sondée dans le coin gauche
	int lig = ligne-distance;
	int col = colonne-distance;
	
	//boucle while qui se termine si lig est plus grand que ligne+distance
	//ou si il sort du tableau
	while(lig <= (ligne+distance) && lig < HAUTEUR_TERRAIN){

		//Si lig est à l'extérieur du tableau, on saute une ligne
		if(lig<MIN)

			//incrémente lig de distance
			lig += distance;
		else{

			//encadre la case en question
			encadrer_case(lig, col, BLACK);

			//marque la case comme étant sondee
			carte.tableau [lig][col] = SONDEE;

			//boucle while qui se termine si col est plus grand ou égale à 
			//que ligne+distance ou si il sort du tableau 
			while(col < (colonne+distance) && col < LARGEUR_TERRAIN){

				//incrémente col de distance
				col += distance;

				//encadre et marque la case comme sondée seulement si la case
				//est à l'intérieur du tableau et que la case n'est pas
				//déjà marqué comme sondée
				if(col>=MIN && !carte.tableau[lig][col]){
					encadrer_case(lig, col, BLACK);
					carte.tableau [lig][col] = SONDEE;
				}
			}
		}

		//Initialise la col à colonne-distance avant de reprendre la
		//boucle
		col = colonne-distance;

		//incrémente lig de distance
		lig += distance;
	}
}


/*************************************************
Reçoit en paramètre si c'est la compagnie ou le sondage perso qui l'appel.
Aussi, reçoit un booléen qui lui indique si c'est le 2e tour.
**************************************************/
int choisir_distance (int perso_compagnie, int deuxieme_tour){
	int distance;
	
	//Si c'est la compagnie qui sonde et que c'est le deuxième tour,
	//retourne DISTANCE_COMPAGNIE
	if(perso_compagnie && deuxieme_tour){
		distance = DISTANCE_COMPAGNIE;

		//Sinon retourne DISTANCE
	} else {
		distance = DISTANCE;
	}

	return distance;
}


/*************************************************
Reçoit en paramètre si c'est la compagnie ou le sondage perso qui l'appel.
**************************************************/
double choisir_seuil_rentabilite (int perso_compagnie){

	double seuil_rentabilite_case;

	//Si c'est la compagnie qui sonde retourne SEUIL_RENTABILITE_CASE_COMPAGNIE
	if(perso_compagnie){
		seuil_rentabilite_case = SEUIL_RENTABILITE_CASE_COMPAGNIE;
		//sinon retourne SEUIL_RENTABILITE_CASE
	} else {
		seuil_rentabilite_case = SEUIL_RENTABILITE_CASE;
		
	}

	return seuil_rentabilite_case;
}


/*************************************************
Utilisation de for puisqu'on connaît la hauteur et la largeur du terrain
**************************************************/
void sonder_cases_valent_moins_que_n(t_carte carte, const t_terrain terrain,
	int perso_compagnie){

	//compteurs
	int i;
	int j;

	//seuil de rentabilité variable selon perso_compagnie
	double seuil_rentabilite_case;

	//choisi le bon seuil de rentabilité selon perso_compagnie
	seuil_rentabilite_case = choisir_seuil_rentabilite (perso_compagnie);

	//boucles qui s'arrête lorsqu'on sort du tableau
	for(i = COLONNE_DE_DEPART; i < HAUTEUR_TERRAIN; i += PAS_COLONNE){
		for(j = LIGNE_DE_DEPART; j < LARGEUR_TERRAIN; j += PAS_LIGNE){

			//Si la case a été sondée et que la quantité de minerais est 
			//supérieur à seuil_rentabilite_case
			if (carte.tableau[i][j] && terrain[i][j] >= seuil_rentabilite_case)

				//sonde les cases voisines de la case en question
				sonder_case_voisine(carte, i, j, perso_compagnie, TRUE);
			
		}
		//remet j à la LIGNE_DE_DEPART avant de reprendre la premiere boucle
		j = LIGNE_DE_DEPART;
	}
}

/*************************************************
Utilisation de while puisqu'on ne sait pas combien de fois il va falloir
scruter le tableau avant qu'il n'y est plus de modification
**************************************************/
void troisieme_tour(t_carte carte, const t_terrain terrain,
	int perso_compagnie){

	//compteurs
	int i;
	int j;

	//Permet de nous dire s'il y a eu des cases modifiées dans le tableau
	int case_changee = TRUE;

	//seuil de rentabilité qui dépend de qui l'appel (perso ou compagnie)
	double seuil_rentabilite_case;

	//seuil_rentabilite_case prend la valeur désiré dépendemment de qui l'appel
	seuil_rentabilite_case = choisir_seuil_rentabilite (perso_compagnie);

	//tant qu'il y a une case changé
	while (case_changee) {

		//initialise à FALSE avant de commencer le tour
		case_changee = FALSE;

		//boucles qui s'arrête lorsqu'on sort du tableau
		for (i = 0; i < HAUTEUR_TERRAIN; i++) {
			for (j = 0; j < LARGEUR_TERRAIN; j++) {

				//Si la case est sondée et que les voisins n'ont pas été sondée
				//et que la valeur du minerai de la case est supérieur au
				//seuil_rentabilite_case
				if (carte.tableau[i][j] && carte.tableau[i][j] !=
					SONDEE_ET_VOISIN_SONDEE && terrain[i][j] >=
					seuil_rentabilite_case){
					
					//on sonde les cases voisines
					sonder_case_voisine(carte, i, j, perso_compagnie, FALSE);
				}
			}
		}
	}
}


/*************************************************
Utilisation de for puisqu'on connaît la hauteur et la largeur du terrain
**************************************************/
void nb_cases_sondees_rentables(t_carte carte,const t_terrain terrain,
	int **nb_cases_sondees, double **total_sondees){

	//compteurs
	int i;
	int j;

	//initialise le nombre de cases sondées et le total de minerai sondée à 0
	int cases_sondees = 0;
	double total_minerai_sondee = 0;

	//boucles qui s'arrête lorsqu'on sort du tableau
	for(i = 0;  i < HAUTEUR_TERRAIN; i++){
		for(j = 0;  j < LARGEUR_TERRAIN; j++){

			//si la case a été sondée
			if(carte.tableau[i][j]){

				//incrémentation du nombre de cases sondées
				cases_sondees++;
				
				//on augmente total_minerai_sondee par le nombre de minerai
				//dans la case
				total_minerai_sondee += terrain[i][j];
			}
		}
	}

	//modifie la valeur des variables pointées en paramètre
	**nb_cases_sondees = cases_sondees;
	**total_sondees = total_minerai_sondee;
}


/*************************************************
Utilisation de for puisqu'on connaît la hauteur et la largeur du terrain
**************************************************/
void case_marquer_forer(t_carte carte, const  t_terrain terrain,
	int perso_compagnie, int **nb_cases_forees, double **total_forees) {

	//compteurs
	int i;
	int j;

	//seuil de rentabilité qui dépend de qui l'appel (perso ou compagnie)
	double seuil_rentabilite_case;
	
	//seuil_rentabilite_case prend la valeur désiré dépendemment de qui l'appel
	seuil_rentabilite_case = choisir_seuil_rentabilite (perso_compagnie);
	
	//boucles qui s'arrête lorsqu'on sort du tableau
	for (i = 0; i < HAUTEUR_TERRAIN; i++) {
		for (j = 0; j < LARGEUR_TERRAIN; j++) {

			//Si la case est sondée
			if (carte.tableau[i][j] && terrain[i][j] >= seuil_rentabilite_case) 
				afficher_croix(i, j);
		}
	}
	//Marque les cases qui ont été forer
	forage_compagnie(carte, terrain);

	//modifie la valeur des variables pointées en paramètre
	**nb_cases_forees = nombre_cases_forées(carte, terrain);
	**total_forees = somme_minerai_extrait(carte, terrain);
	
}


void sondage_perso(const t_terrain terrain, int *nb_cases_sondees,
	double *total_sondees, int *nb_cases_forees, double *total_forees){
	
	//carte de prospection de type t_carte
	t_carte carte_prospection;
	
	//crée une carte neuve initialisé à 0
	carte_prospection = carte_neuve();

	//première passe
	//sonde à partir d'une case (LIGNE_DE_DEPART, COLONNE_DE_DEPART) à
	//pas fixe PAS_LIGNE et PAS_COLONNE
	sonder_a_pas_fixe(carte_prospection);

	//deuxieme passe
	//sonde les cases voisines des cases déjà sondés
	sonder_cases_valent_moins_que_n(carte_prospection, terrain, PERSO);

	//troisième passe
	//si une case est rentable, sonde les cases voisines et s'arrete seulement
	//si aucune modification a été apporté au tableau lors d'un tour
	troisieme_tour(carte_prospection, terrain, PERSO);

	//marque les cases comme comme étant forer
	case_marquer_forer(carte_prospection, terrain,PERSO, &nb_cases_forees,
		&total_forees);

	//compte le nombre de case sondée et rentable
	nb_cases_sondees_rentables(carte_prospection, terrain, &nb_cases_sondees,
		&total_sondees);

	//libère l'espace mémoire du tableau dynamique et met le pointeur à NULL
	free(carte_prospection.tableau);
	carte_prospection.tableau = NULL;
}


void sondage_compagnie(const t_terrain terrain,int *nb_cases_sondees,
	double *total_sondees, int *nb_cases_forees, double * total_forees){
	
	//carte de prospection de type t_carte
	t_carte carte_prospection;

	//crée une carte neuve initialisé à 0
	carte_prospection = carte_neuve();
	
	//première passe
	//sonde à partir d'une case (LIGNE_DE_DEPART, COLONNE_DE_DEPART) à
	//pas fixe PAS_LIGNE et PAS_COLONNE
	sonder_a_pas_fixe(carte_prospection);

	//deuxieme passe
	//sonde les cases voisines des cases déjà sondés
	sonder_cases_valent_moins_que_n(carte_prospection, terrain, COMPAGNIE);

	//troisième passe
	//si une case est rentable, sonde les cases voisines et s'arrete seulement
	//si aucune modification a été apporté au tableau lors d'un tour
	troisieme_tour(carte_prospection, terrain, COMPAGNIE);
	nb_cases_sondees_rentables(carte_prospection, terrain, &nb_cases_sondees,
		&total_sondees);

	//marque les cases comme comme étant forer
	case_marquer_forer(carte_prospection, terrain, COMPAGNIE, &nb_cases_forees,
		&total_forees);
	
	//libère l'espace mémoire du tableau dynamique et met le pointeur à NULL
	free(carte_prospection.tableau);
	carte_prospection.tableau = NULL;
}
