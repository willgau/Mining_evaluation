/*************************************************
Travail Pratique #2 ; Module t_terrain.h
Vincent Cournoyer 
William Gauvin
Bastien Giroux
Olivier Pelletier
21 Octobre 2015
**************************************************/

//Fonction qui crée un tableau à deux dimensions, soit une hauteur 
//et une largeur
typedef double t_terrain [HAUTEUR_TERRAIN][LARGEUR_TERRAIN];

// Cette fonction permet au mode graphique de reconnaitre la valeur attribuée
// à une case du tableau et de lui assigner la coulleur correspondante 
//dépendant du cout de forage et de sondage.
void affichage_terrain (t_terrain terrain);

//Cette fonction réinitialise tout les cases du tableau à la valeur zéro.
void vider_terrain (t_terrain terrain);

//Cette fonction permet de remplir tout les cases du tableau de manière 
//uniforme. Les valeurs de chaque case devront graviter autour d'une moyenne
//ne dépassant pas les bornes d'un écart type donné.
void remplir_terrain_normal( t_terrain terrain);

//Cette fonction permet de remplir tout les cases du tableau avec des valeurs 
//aléatoire. Ces valeurs ne doivent pas dépasser MIN et MAX définies plus bas 
//dans le fichier.
void remplir_terrain_aleatoire ( t_terrain terrain);

//Cette fonction insère un ou plusieurs filon dans le tableau. Le nombre de 
//filon varie aléatoirement entre NB_FILONS_MIN et NB_FILONS_MAX
void remplir_terrain_filons(t_terrain terrain);

//Cette fonction sert à générer un filon, ça position d'origine, son déplacement
//et la valeur de son incrémentation.
void creer_filons(t_terrain terrain);

//Cette fonction sert à calculer le totals de minerais (en argent) se trouvant sur 
// le terrain choisis
void total_minerai_terrain(const t_terrain terrain, double *total_terrain);