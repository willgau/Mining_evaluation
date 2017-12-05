#include <stdio.h>

#include "t_stats.h"
#include "constantes.h"

  /*
	* Strategie : On utilise une variable locale static pour retenir le 
	*                 lien logique vers le fichier qui sera ouvert par ouvrir_fichier.
	*
	*                 On utilise le booleen première_fois pour afficher une en-tête dans le fichier
	*                 juste une fois.  
	*
	*                 On utilise que des fprintf pour afficher.
	*
	*                  Des tabulateurs sont mis entre chaque colonne.
	*/

//Fichier de stats
static FILE* f;

//Sert à afficher une entête dans le fichier
static int premiere_fois =  FALSE;

#define TAB '\t'

/*
* Affiche une entête dans le fichier ouvert par ouvrir_fichier()
*/
static void afficher_entete()
{
  
	fprintf(f,"Identificateur d'algorithme");
	fprintf(f,"%c",TAB);

	fprintf(f,"Type de terrain");
	fprintf(f,"%c",TAB);

	fprintf(f,"Total de minerai sur le terrain");
	fprintf(f,"%.2c",TAB);

	fprintf(f,"Profit maximal possible");
	fprintf(f,"%.2c",TAB);

	fprintf(f,"Nombre de cases sondees");
	fprintf(f,"%c",TAB);

	fprintf(f,"Total de minerai des cases sondees");
	fprintf(f,"%.2c",TAB);

	fprintf(f,"Nombre de cases forees");
	fprintf(f,"%c",TAB);

	fprintf(f,"Total de minerai des cases forees");
	fprintf(f,"%.2c",TAB);

	fprintf(f,"Ratio de profit par rapport au maximum possible");
	fprintf(f,"%.2c",TAB);

	//On saute des lignes aprèes l'entête
	fprintf(f, "\n\n");

}

/*
* Affiche elcontenu de l'enregistrements stats dans le fichier 
* ouvert par ouvrir_fichier().
*/
static void afficher_stats(const t_stats* stats)
{
	fprintf(f, stats->id_algo);
	fprintf(f,"%c",TAB);

	fprintf(f,"%s", terrain_to_string(stats->type_terrain));
	fprintf(f,"%c",TAB);

	//Total de minerai sur le terrain
	fprintf(f,"%lf", stats->total_terrain);
	fprintf(f,"%c",TAB);

	//Profit maximal possible
	fprintf(f,"%lf", stats->profit_possible);
	fprintf(f,"%c",TAB);

	//Nombre de cases sondees
	fprintf(f,"%d", stats->nb_case_sondees);
	fprintf(f,"%c",TAB);

	//Total de minerai des cases sondees;
	fprintf(f,"%lf", stats->total_sondees);
	fprintf(f,"%c",TAB);

	//Nombre de cases forees
	fprintf(f,"%d", stats->nb_case_forees);
	fprintf(f,"%c",TAB);

	//Total de minerai des cases forees
	fprintf(f,"%lf", stats->total_forees);
	fprintf(f,"%c",TAB);

	//Ratio de profit par rapport au maximum possible
	fprintf(f,"%lf", stats->pourc_profit);
	fprintf(f,"%c",TAB);

	//On passe à la ligne suivante
	fprintf(f, "\n");

}


//Ouvre le fichier d'ecriture de stats
void ouvrir_fichier(const char* nom_fic)
{
	 f = fopen(nom_fic,"wt");

	 premiere_fois = TRUE;
}

//À appeler à chaque fois qu'on veut ajouter une ligne de stats dans le fichier
void ecrire_stats(const t_stats* stats)
{
	//Le booleen est mis à FALSE alors ne sera plus affiche 
	//à moins de fermer et reouvrir
	if(premiere_fois)
	{
	    afficher_entete();
		premiere_fois = FALSE;
    }

	afficher_stats(stats);
}

////Ferme le fichier d'ecriture de stats
void fermer_fichier()
{
	fclose(f);
}