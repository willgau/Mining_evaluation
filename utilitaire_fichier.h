#ifndef _utilitaire_fichier__
#define _utilitaire_fichier__

#include "t_stats.h"

//Ouvre le fichier d'ecriture de stats
//Doit être appelee une seule fois avant d'ecrire,
//suite à une fermeture.
//Le fichier est vide.  
//S'il n'existe pas, le fichier est cree.
void ouvrir_fichier(const char* nom_fic);

//À appeler à chaque fois qu'on veut ajouter une
//ligne de stats dans le fichier
void ecrire_stats(const t_stats* stats);

//Ferme le fichier d'ecriture de stats.
//Doit être appelee une seule fois à la fin,
//suite à une ouverture et des ecritures.
void fermer_fichier();

#endif