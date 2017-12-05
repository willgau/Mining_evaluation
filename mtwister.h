/*==========================================================*/

/*
	le module offrant un mersenne twister, un generateur de nombres 
	pseudo-aleatoires considere comme le meilleur pour la simulation numerique

	Une courte presentation francaise suit l'introduction en anglais des auteurs japonais
	et donnera le caract�re general de chaque  fonction offerte

   Les 2 auteurs n'offraient originallement que des mtwister uniformes 
   qui peuvaient parfois paraitre redondantes. Pour un professionnel qui sait
   construire des mtwister differentes de l'uniforme, �a va
   mais j'ai choisi d'ajouter pour les etudiants quelques fonctions standardisees 
   permettant d'obtenir des ev�nements dans une distribution :

		uniforme generale , sans ou avec des bornes, enti�re ou reelle
		normale centree reduite Z(0,1) ou normale � moyenne et ecart-type definis
*/

/*==========================================================*/
/* Le module offre donc sept fonctions :

	deux fonctions capables d'initialiser le generateur 
	1 - void mt_srand(unsigned long s);
	2 - unsigned long mt_srandSys(void);

	deux fonctions pour emettre un nombre reel dans une uniforme
	double mt_rand(void);
	double mt_randf(double b1, double b2);

	une fonction pour emettre un nombre entier dans une uniforme
	int mt_randi(int borne);

	deux fonctions pour emettre un reel dans une distribution normale
	double mt_randz(void);
	double mt_randnormal(double mu, double sigma);

*/
/*==========================================================*/


/*==========================================================*/

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Remtwister of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Remtwister in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

/*==========================================================*/

#ifndef _MT19937AR_H_
#define _MT19937AR_H_
/*==========================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


/*==========================================================*/

/* UNE INTERFACE MODULAIRE STANDARD POUR MES eTUDIANTS */

/*==========================================================*/

/*  Voici deux fonctions d'initialisation du
     generateur. Un generateur non-initialise s'initialise 
     en fait � 0 et emet la m�me sequence ce qui fait douter
	 du caract�re aleatoire.... C'est au client de l'initialiser
	 MAIS JUSTE UNE FOIS dans tout le programme de simulation.
*/

/*==========================================================*/
/* La fonction mt_srand 
 la forme d'initialisation la plus classique d'un generateur  
 � partir d'un entier quelconque, la sequence pseudo aleatoire 
 � venir est totalement determinee par la valeur re�ue 

PARAMETRE(s): s, un entier quelconque

SORTIE: aucune

SPECS: aucune
*/
void mt_srand(unsigned long s);

/*==========================================================*/


/*==========================================================*/
/* la fonction mt_srandSys 
 une forme alternative d'initialisation du generateur � partir 
 de l'horloge interne de la machine,  l'horloge donne un entier
 qui sert de param�tre � la fonction precedente. 
 Cette valeur est retournee 

PARAMETRE(s): Aucun

SORTIE: l'entier qui a veritablement initialise le generateur

SPECS: aucune
*/
unsigned long mt_srandSys(void);
/*==========================================================*/

/* LES CINQ FONCTIONS D'eMISSION DANS LES mtwister SPeCIFIeES */

/*==========================================================*/
/* La fonction mt_rand   
L'emission d'un nombre reel dans la distribution uniforme 0,1 

PARAMETRE(s): Aucun

SORTIE : la valeur emise par le generateur

SPECS : aucune
*/
double mt_rand(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randf

L'emission d'un nombre reel dans une  uniforme [b1, b2] 

PARAMETRE(s): deux valeurs reelles quelconques qui serviront 
               de bornes � l'intervalle

SORTIE : la valeur emise par le generateur

SPECS : l'ordre des param�tres n'a aucune importance
*/
double mt_randf(double b1, double b2);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randi

L'emission d'un nombre entier positif dans une uniforme [1, borne]

PARAMETRE(s): une valeur enti�re quelconque

SORTIE : la valeur enti�re emise par le generateur

SPECS :  si le param�tre effectif < 0 , c'est la valeur absolue 
			du param�tre  qui sera consideree
         recevant 0 elle retourne automatiquement 0 et 
			c'est le seul 0 possible
*/
int mt_randi(int borne);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randz

L'emission d'un nombre reel dans la distribution normale Z, 
la plus classique  de moyenne 0 et d'ecart type 1

PARAMETRE(s) : Aucun

SORTIE : la valeur reelle emise par le generateur

SPECS : aucune
*/
double mt_randz(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randnormal

L'emission d'un nombre reel dans une distribution normale quelconque, 
  de moyenne mu  et d'ecart-type sigma donnes

PARAMETRE(s) : mu definit la moyenne voulue et sigma l'ecart-type

SORTIE : la valeur reelle emise par le generateur

SPECS : le signe de sigma n'aura pas d'importance.
*/
double mt_randnormal(double mu, double sigma);

/*==========================================================*/
/*==========================================================*/

/* L'INTERFACE ORIGINALE DES DEUX CReATEURS SERA DANS LE .C 	*/

/*==========================================================*/
#endif	
/*==========================================================*/

