/*************************************************
Travail Pratique #2 ; Module t_terrain.h
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Fonction qui cr�e un tableau � deux dimensions, soit une hauteur 
//et une largeur
typedef double t_terrain [HAUTEUR_TERRAIN][LARGEUR_TERRAIN];

// Cette fonction permet au mode graphique de reconnaitre la valeur attribu�e
// � une case du tableau et de lui assigner la coulleur correspondante 
//d�pendant du cout de forage et de sondage.
void affichage_terrain (t_terrain terrain);

//Cette fonction r�initialise tout les cases du tableau � la valeur z�ro.
void vider_terrain (t_terrain terrain);

//Cette fonction permet de remplir tout les cases du tableau de mani�re 
//uniforme. Les valeurs de chaque case devront graviter autour d'une moyenne
//ne d�passant pas les bornes d'un �cart type donn�.
void remplir_terrain_normal( t_terrain terrain);

//Cette fonction permet de remplir tout les cases du tableau avec des valeurs 
//al�atoire. Ces valeurs ne doivent pas d�passer MIN et MAX d�finies plus bas 
//dans le fichier.
void remplir_terrain_aleatoire ( t_terrain terrain);

//Cette fonction ins�re un ou plusieurs filon dans le tableau. Le nombre de 
//filon varie al�atoirement entre NB_FILONS_MIN et NB_FILONS_MAX
void remplir_terrain_filons(t_terrain terrain);

//Cette fonction sert � g�n�rer un filon, �a position d'origine, son d�placement
//et la valeur de son incr�mentation.
void creer_filons(t_terrain terrain);

//Cette fonction sert � calculer le totals de minerais (en argent) se trouvant sur 
// le terrain choisis
void total_minerai_terrain(const t_terrain terrain, double *total_terrain);