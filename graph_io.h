/******************************************************************************
	FICHIER : GRAPH_IO.H
	DATE    : 21/09/2010
	POUR    : INF145

	ADAPTe par Pierre Belisle : inspire d'un document de Frederick Henri
	
	Ce module definit l'ensemble des fonctions graphiques necessaires pour
	implementer le tp2 A15

	À NOTER : Pour pouvoir utiliser ce module, assurez-vous d'utiliser 
	          le jeu de caractères MBCS. //menu : projet/propriete de .../propriete de configuration/general/jeu de caractères
******************************************************************************/
#ifndef _GRAPH_IO__
#define  _GRAPH_IO__

/*	Les couleurs utilisees. */
/* Fond de l'ecran. */
#define COULEUR_DE_FOND			COLOR(80, 0, 0)	

//Plus grande valeur pour  une des couleurs RGB
#define MAX_COULEUR 255

//Met la console en mode graphique plein ecran avec un nombre de cases à afficher
//calcule à partir des dimensions du terrain.
void demarrer_graph(int hauteur_terrain, int largeur_terrain);

//Retourne un entier qui represente une couleur entre blanche et jaune en RGB selon
//le pourcentage de jaune fourni (0 == WHITE, 1 == YELLOW)
int get_degrade_blanc_jaune(double pourcentage);

//Retourne un entier qui represente une couleur entre orange et rouge en RGB selon
//le pourcentage de rouge fourni (0 == ORANGE, 1 == RED)
int get_degrade_orange_rouge(double pourcentage);

//Dessiner une case à la position fournie de la couleur interieure avec un encadre de la couleur de contour,
//de la dimension fourni.
//La couleur est un entier representant une des couleurs en RGB creee par une des fonctions get_degrade...
//Pour ne pas avoir d'encadre, il faut mettre la même couleur au deux.
void dessiner_case(int ligne, int colonne, int couleur_interieur, int couleur_contour);

//Dessine le contour d'une case sans en changer la couleur interieure.
//La couleur est un entier representant une des couleurs en RGB creee par  par une des fonctions get_degrade...
void encadrer_case(int ligne, int colonne, int couleur_contour);

//Affiche une croix de couleur noire à la position de la case fournie
void afficher_croix(int ligne, int colonne);

//Si on veut afficher des messages à une position x,y de l'ecran.
void afficher_message(const char * message, int x, int y);

//Ferme le mode graphique
void fermer_graph(void);

//Attend une touche en prevenance du clavier.
void effectuer_pause(void);

#endif /* defined(_graph_io__) */