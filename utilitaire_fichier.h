#ifndef _utilitaire_fichier__
#define _utilitaire_fichier__

#include "t_stats.h"

//Ouvre le fichier d'ecriture de stats
//Doit �tre appelee une seule fois avant d'ecrire,
//suite � une fermeture.
//Le fichier est vide.  
//S'il n'existe pas, le fichier est cree.
void ouvrir_fichier(const char* nom_fic);

//� appeler � chaque fois qu'on veut ajouter une
//ligne de stats dans le fichier
void ecrire_stats(const t_stats* stats);

//Ferme le fichier d'ecriture de stats.
//Doit �tre appelee une seule fois � la fin,
//suite � une ouverture et des ecritures.
void fermer_fichier();

#endif