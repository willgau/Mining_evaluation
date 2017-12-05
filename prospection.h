/*************************************************
Travail Pratique #2 ; Module prospection.h
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

/*************************************************
Structure tableau qui contient MAX_CARA comme nombre de case et de type char.
**************************************************/
typedef char tableau[MAX_CARA];

/*************************************************
Structure t_carte qui contient un tableau dynamique 2D et deux int pour
indiquer le nombre de ligne et de colonne du tableau dynamique.
**************************************************/
typedef struct{
	char** tableau;   //Tableau dynamique
	int nb_lig;
	int nb_col;
} t_carte;

/*************************************************
La fonction cr�e une carte de prospection neuve (tableau dynamique) de largeur
LARGEUR_TERRAIN et de hauteur HAUTEUR_TERRAIN dynamiquement et retourne
l'adresse de la carte de prospection en question
**************************************************/
t_carte carte_neuve();

/*************************************************
Fonction qui marque comme sond�e la case (LIGNE_DE_DEPART, COLONNE_DE_DEPART)
et ensuite sonde les cases se trouvant � un pas de PAS_LIGNE et PAS_COLONNE.
**************************************************/
void sonder_a_pas_fixe(t_carte carte);

/*************************************************
Fonction qui sonde les cases voisine d'une case qu'on passe en param�tre
� distance DISTANCE (exemple 8 cases si DISTANCE = 1) et ne ressonde pas la
case envoy� en param�tre.
**************************************************/
void sonder_case_voisine(t_carte carte, int ligne, int colonne,
	int perso_compagnie, int deuxieme_tour);

/*************************************************
Fonction qui sonde les cases voisines des cases d�j� sond�e de la carte de
prospection seulement si la valeur de la case du terrain est sup�rieur au
seuil de rentabilit� pr�d�fini.
**************************************************/
void sonder_cases_valent_moins_que_n(const t_carte carte,
	const t_terrain terrain);

/*************************************************
Fonction qui sonde la carte de prospection en entier. Si une case est au
dessus du seuil de rentabilit� et que ses voisins n'ont pas d�j� �t� sond�e,
alors on sonde les cases voisines de celle ci. La carte est scrut�e jusqu'�
se qu'aucune modification est �t� apport� � la carte de prospection lors
d'un tour complet.
**************************************************/
void troisieme_tour(t_carte carte, const t_terrain terrain,
	int perso_compagnie);

/*************************************************
Notre sondage personnalis� qui se sert des fonctions pr�c�dentes pour
faire une sondage du terrain le plus rentable possible
**************************************************/
void sondage_perso(const t_terrain terrain, int *nb_cases_sondees,
	double *total_sondees, int *nb_cases_forees, double *total_forees);

/*************************************************
Fonction qui calcul le nombre de cases sondees et le total de minerai se
trouvant dans les cases sondees. Stock ensuite ses valeurs � l'adresse qu'on
lui passe en param�tres.
**************************************************/
void nb_cases_sondees_rentables(t_carte carte, const t_terrain terrain,
	int **nb_cases_sondees, double **total_sondees);

/*************************************************
Fonction qui marque les cases � forer en pla�ant un X sur les cases cibl�es,
calcul le nombre de case forer, calcul le total de minerais dans les cases
marqu� � forer et stock les deux valeurs calcul�es � l'adresse qu'il a re�u
en param�tre.
**************************************************/
void case_marquer_forer(t_carte carte, const  t_terrain terrain,
	int perso_compagnie, int **nb_cases_forees, double **total_forees);

/*************************************************
Algorithme de sondage de la compagnie. C'est l'algorithme de d�part que nous
allons optimiser dans la fonction sondage_perso.
**************************************************/
void sondage_compagnie(const t_terrain terrain, int *nb_cases_sondees,
	double *total_sondees, int *nb_cases_forees, double *total_forees);

/*************************************************
Fonction qui retourne le bon seuil de rentabilit� d�pendemment de si
c'est la compagnie qui sonde ou c'est notre sondage perso.
**************************************************/
double choisir_seuil_rentabilite (int perso_compagnie);

/*************************************************
Fonction qui retourne la distance appropri�e d�pendemment de celui qui l'appel
(compagnie ou perso) et du tour qu'il est en train d'effectuer
**************************************************/
int choisir_distance (int perso_compagnie, int deuxieme_tour);