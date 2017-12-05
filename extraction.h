/*************************************************
Travail Pratique #2 ; Module extraction.h
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Marque comme �tant for�es les cases sond�es qui sont marqu�es � forer d�une carte 
//de prospection re�ue.
void forage_compagnie(t_carte carte,const t_terrain terrain);

//Fonction qui re�oit une carte de prospection et un terrain et fait la somme du minerai 
//dans les cases du terrain qui ont �t� for�es.
double somme_minerai_extrait (const t_carte carte, const t_terrain terrain);

//Fonction qui re�oit une carte de prospection et g�n�re le nombre de cases marqu�es comme for�es
int nombre_cases_for�es(const t_carte carte, const t_terrain terrain);