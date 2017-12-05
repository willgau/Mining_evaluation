/*************************************************
Travail Pratique #2 ; Constantes.h
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/
//Les booleenes en C
#define FALSE 0
#define TRUE 1

//Minimum 
#define MIN 0

//Dimensions du terrainutilis dans la simulation
#define HAUTEUR_TERRAIN 40
#define LARGEUR_TERRAIN 40

//Sert à clarifier le code du main pourl a generation des filons
#define NB_FILONS_MIN 1
#define NB_FILONS_MAX 6

//Sert à creer les filons en baionette
#define PROB_MOUVEMENT .05

// Constantes liees aux coûts d'exploitation et prospection.
#define COUT_SONDAGE  50

#define COUT_FORAGE 2000

#define SEUIL_RENTABILITE_CASE  (COUT_SONDAGE + COUT_FORAGE)

#define SEUIL_RENTABILITE_CASE_COMPAGNIE  (COUT_SONDAGE * 4 + COUT_FORAGE) / 2

// On considère qu'une case est "riche" lorsqu'elle contient au moins 3 fois
// le coût de forage et de sondage.
#define FACTEUR_RICHESSE 3
#define  VALEUR_CASE_RICHE  (FACTEUR_RICHESSE * SEUIL_RENTABILITE_CASE)

//**************************************
//      Pour le terrain UNIFORME
//**************************************
//La moyenne en minerai que tout les cases du tableau valent.
#define MOYENNE 20000

//L'ecart type de la moyenne de minerai par case.
#define ECART 50

//**************************************
//      Pour le terrain ALEATOIRE
//**************************************
//Valeur minimum de mnerai que peut contenir une case du tableau.
#define MIN_ALEA 1000

//Valeur maximum de mnerai que peut contenir une case du tableau.
#define MAX_ALEA 3000

//************************************************
//      Pour le terrain FILONS
//************************************************
//Carre qui utilisera 2 cases par 2 cases.
#define TAILLE_CARRE_AJOUT 2

//Quantite de minerai ajouter par incrementation.
#define VAL_AJOUT 10

//Valeur maximal qu'un filion vaut en minerai.
#define VALEUR_FILON 2000000
//************************************************
//Defini la valeur minimum que le terrain a en largeur et en hauteur.
#define MINIMUM_TERRAIN 0

//Defini la valeur maximum que le terrain a en largeur et en hauteur.
#define MAXIMUM_TERRAIN 40

//Point de depart pour le sondage fixe (Ligne et Colonne)
#define LIGNE_DE_DEPART 2
#define COLONNE_DE_DEPART 2

//Pas auquel il avance pour le sondage (Ligne et Colonne)
#define PAS_LIGNE 4
#define PAS_COLONNE 3

//Distance auquel il sonde les prochaines cases (Sondage perso et compagnie)
#define DISTANCE 1
#define DISTANCE_COMPAGNIE 2 * DISTANCE

//Pour la carte de prospection, marque les cases comme etant sondee, sondee et
//voison de sondee, comme etant foree puis que le forage a ete fait
#define SONDEE 1
#define SONDEE_ET_VOISIN_SONDEE 11
#define FOREE 2
#define FORAGE 3

//Structure tableau qui contient MAX_CARA comme nombre de case et de type char.
#define MAX_CARA 2

//Pour le choix du bon seuil de rentabilite soit si on est avec la compagnie
//ou si on est dans notre algorithme perso
#define COMPAGNIE 1
#define PERSO 0

//Constante de gestion du terrain pour avoir le bon chiffre associe
// au bon terrain
#define GESTION_MIN 1
#define GESTION_MAX 3

// Constante pour le nombre d'iteration dans la boucle principale dans le main
// il faut faire deux fois le nombre de terrain choisi pour avoir les resultats
//de la compagnie et ceux personelle
#define NB_DE_TERRAIN 1000
#define NB_DE_TERRAIN_CHOISIS NB_DE_TERRAIN* 2

//Multiplication pour avoir le bon pourcentage dans le fichier texte
#define POURCENTAGE 100
//Exception si le profit_possible est negatif, multiplie par -1 pour avoir
//un pourcentage reellement negatif et non pas avoir une division avec deux
//negatif qui s'annule 
#define POURCENTAGE_NEGATIF -100

//Probabilite de mouvement pour le filon
#define PROBABILITE 0.05

//Borne de mouvement si la case bouge vers le haut,bas ou ne bouge pas
#define BORNE_MIN -1
#define BORNE_MAX 1