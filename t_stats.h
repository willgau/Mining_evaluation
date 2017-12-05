#ifndef _t_stats__
#define _t_stats__


//Nombre de caractères max pour un 
//identificateur d'algorithmes
#define MAX_CAR 250

//Differents types de terrain
#define UNI 1
#define ALEA 2
#define FILONS 3

typedef struct
{

    //Identificateur de l'algotihme
	char id_algo[MAX_CAR];

    //type de terrain  (UNI, ALEA ou FILONS)
    int type_terrain;

	//Nombre total de cases sondees
	int nb_case_sondees;

	//Total de minerai aux endroits sondees (fore ou non)
	double total_sondees;

	//Nombre total de cases forees
	int nb_case_forees;

	//Total de minerai aux endroits fores
    double total_forees;

	//Minerai reellement extrait moins les coûts pour l'extraire
	double profit_extraction;

	//(Pour la suite, c'est de la triche car en realite on n'a pas cette information).
	//Total de minerai sur le terrain 	
    double total_terrain;

	//Minerai total moins les coûts pour l'extraire
	double profit_possible;

	//Ratio entre le profit reel et le profit maximum possible.
	double pourc_profit;

}t_stats;

//Initialise toutes les stats à 0.  Reçoit un identificateur pour la 
//stats et  le type de terrain.
void init_stats(t_stats* stats, char* id, int type_terrain);

//Retourne une chaîne correspondant au type de terrain
//"uniforme", "aleatoire", "en filons" ou "erreur_type"
char* terrain_to_string(int type_terrain);

#endif