#include <stdlib.h> //rand

//Genère un entier entre min et max
int alea(int min,int max)
{
	//Strategie, on utilise le generateur de C qui retourne une valeur en 1 et RANDMAX
	return rand() % (max - min + 1) + min;
}
