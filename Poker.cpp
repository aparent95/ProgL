#include <iostream>
#include <iomanip>

using namespace std;


struct T_carte
{
	string sorte ;
	string valeur ;	//string parce que 10 n'est pas un caractère
	int valeur_num ; //valeur numérique des cartes : 2 pour un 2, 13 pour un as
	string nom ;
	bool garder ;
	bool jeter	;  
};

T_carte C_carte(T_carte tabpaquet)
{
	for ( int i=0; i < 51 ; i++ )
	{
		for ( int j=0 ; j < 3 ; j++ )
		{
			for ( int k=0 ; k < 12 ; k++ )
			{
				tabpaquet[i].valeur		= tabvaleur[k] ;
				tabpaquet[i].valeur_num	= tabvaleur_num[k] ;
				tabpaquet[i].nom		= tabnom[k] ;
				tabpaquet[i].garder		= false		//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront changées
				tabpaquet[i].jeter		= false		//quand il décidera de ne pas garder, jeter prendra true
			}
		}
	}
}

/*
!!!!!!!!!!!!! Il faudra penser à changer les noms, en mettre peut être pas des plus simples, mais des plus précis.
*/

main ()
{
	string tabsorte[4]		=	{"carreaux", "coeur", "pique", "trefle"} ;
	string tabvaleur[13]	=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A"}	;		//Je me questionne sur l'utilité de ça, vu qu'on a la table des valeurs numériques.
	string tabnom[13]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as"} ;
	int tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13} ;					//Ou alors on fait une fonction qui paramètre ca ? TELLEMENT DE POSSIBILITÉ !!
	
	T_carte tabpaquet [52] ;
	
	C_carte(tabpaquet) ;
	
	
	
	
}
