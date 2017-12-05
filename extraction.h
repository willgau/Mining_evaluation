/*************************************************
Travail Pratique #2 ; Module extraction.h
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Marque comme étant forées les cases sondées qui sont marquées à forer d’une carte 
//de prospection reçue.
void forage_compagnie(t_carte carte,const t_terrain terrain);

//Fonction qui reçoit une carte de prospection et un terrain et fait la somme du minerai 
//dans les cases du terrain qui ont été forées.
double somme_minerai_extrait (const t_carte carte, const t_terrain terrain);

//Fonction qui reçoit une carte de prospection et génère le nombre de cases marquées comme forées
int nombre_cases_forées(const t_carte carte, const t_terrain terrain);