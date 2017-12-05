/******************************************************************************
	FICHIER : GRAPH_IO.C
	PAR     : Pierre Belisle (tout a ete refait)
	DATE    : 21/09/2010
	POUR    : INF145

	Implementation du module
******************************************************************************/
#include <stdlib.h>
#include "graph_io.h"
#include "winbgim.h"


//Calcul de la taille graphique d'une case 
//Elles sont initialisees dans demarrer_graph
static int dim_casex;
static int dim_casey;

//Retourne un entier qui represente une couleur entre blanche et jaune en RGB selon
//le pourcentage de jaune fourni (0 == WHITE)
int get_degrade_blanc_jaune(double pourcentage)
{
	//On utilise COLOR de winbgim qui retourne un entier representant la coouleur en RGB
	return COLOR(MAX_COULEUR, MAX_COULEUR, (1-pourcentage)* MAX_COULEUR);
}

//Retourne un entier qui represente une couleur entre orange et rouge en RGB 
//r,g et b doivent être entre 0 et MAX_COULEUR
int get_degrade_orange_rouge(double pourcentage)
{
	//On utilise COLOR de winbgim qui retourne un entier representant la coouleur en RGB
	return COLOR(MAX_COULEUR, (1-pourcentage)* MAX_COULEUR, 0);
}


//Met la console en mode graphique avec une fenêtre de la taille fournie en x et en y
void demarrer_graph( int HAUTEUR_TERRAIN, int LARGEUR_TERRAIN)
{
	int gdriver = DETECT, gmode;
	int maxx, maxy;

	//Plein ecran avec initwindow de winbgim
	initwindow(getmaxy(), getmaxx(), &gdriver, &gmode);

	//On calcule la taille d'une case après l'intialisation graphique
	//sinon getmaxx() et getmaxy retournent -1
	maxx = getmaxx();
	maxy = getmaxy();

	//Il est possible que la dimension en x et en y soit differentes.
	dim_casex = maxx / (LARGEUR_TERRAIN);
	dim_casey = maxy / (HAUTEUR_TERRAIN);
	
}

//Ferme le mode graphique
void fermer_graph(void)
{

   //winbgim
   closegraph();
}

//Dessiner une case à la position fournie de la couleur interieure avec un encadre de la couleur de contour,

//de la dimension fournie.

//La couleur est un entier representant une des couleurs en RGB creee par la fonction get_couleur(r,g,b).

void dessiner_case(int ligne, int colonne, int couleur_interieur, int couleur_contour)
{
	/*
	* Strategie : On utilise fillpoly pour remplir la case.  Il faut donc creer un tableau de points et lui passer.
	*                 On dessine de la taille des dimensions calcules dans demarrer_grapoh.
	*/
	//evite pls calculs redondants
	int haut = ligne * dim_casey ;
	int bas = haut +dim_casey;   
	int gauche = colonne*dim_casex;
	int droite = gauche + dim_casex;

	POINT haut_gauche = {gauche, haut};
	POINT haut_droite =  {droite, haut};
	POINT bas_gauche = {gauche, bas};
	POINT bas_droite = {droite, bas};

	POINT tab[] = {haut_gauche, bas_gauche,  bas_droite, haut_droite};

	//remplissage
    setfillstyle(SOLID_FILL,couleur_interieur);

	/*	On dessine la case. */
	fillpoly(4, (int*)tab);
}

//Affiche une croix noire.
void afficher_croix(int ligne, int colonne)
{

	/*
	* Strategie : On utilise line pour afficher la croix.  Il faut calculer les coordonnees.
	*                 On dessine de la taille des cases des dimensions calculees dans demarrer_graph.
	*/

	//evite pls calculs redondants
	int haut = ligne * dim_casey;
	int bas = haut +dim_casey;   
	int gauche = colonne*dim_casex;
	int droite = gauche + dim_casex;

	setcolor(BLACK);
	
	line(gauche, haut, droite, bas);
	line(droite, haut, gauche, bas);

}

//Dessine le contour d'une case sans en changer la coueleur interieur.

//La couleur est un entier representant une des couleurs en RGB creee par la fonction get_couleur(r,g,b).

void encadrer_case(int ligne, int colonne, int couleur_contour)
{

	/*
	* Strategie : On utilise rectangle pour afficher le contour.  Il faut donc calculer les coins haut gauche, bas droit.
	*                 On dessine de la taille des cases des dimensions calculees dans demarrer_graph.
	*/

	//evite pls calculs redondants
	int haut = ligne * dim_casey;
	int bas = haut +dim_casey;   
	int gauche = colonne*dim_casex;
	int droite = gauche + dim_casex;

	setcolor(couleur_contour);
	rectangle(gauche, haut, droite, bas);
}

//Affiche le message en (x,y)
void afficher_message(const char * message, int x, int y)
{
	int hauteur_texte;		/* La dimension du texte à afficher. */

	
	/*	On ajuste les caracteristiques du message à afficher. */
	setbkcolor(COULEUR_DE_FOND);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	/*	On affiche le message au milieu de la bordure du bas. */
	hauteur_texte = textheight(message);
	outtextxy(x, y,  message);
}


//Attend enter en mode graphique.
void effectuer_pause(void)
{
	(void) getch_graph();
}