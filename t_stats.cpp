#include "t_stats.h"
#include <string.h>

//Initialise toutes les stats à 0.
void init_stats(t_stats* stats, char* id, int type_terrain)
{
	strcpy(stats->id_algo, id);
	stats->nb_case_forees = 0;
	stats->nb_case_sondees = 0;
	stats->pourc_profit = 0;
	stats->profit_extraction = 0;
	stats->profit_possible = 0;
	stats->total_forees = 0;
	stats->total_sondees = 0;
	stats->total_terrain = 0;
	stats->type_terrain =  type_terrain;
}

char* terrain_to_string(int type_terrain)
{ 
    //Pour eviter d'utiliser malloc, on utilise 
	//exceptionnellement plusieurs return.
	switch(type_terrain)
	{
		case UNI : return "uniforme";
		case ALEA : return "aleatoire";
		case FILONS : return "en filons";
		default : return "erreur de type de terrain";
     }

}