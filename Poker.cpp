#include <iostream>
#include <iomanip>

using namespace std;


struct T_carte
{
	string sorte ;
	string valeur ;	//string parce que 10 n'est pas un caract�re
	int valeur_num ; //valeur num�rique des cartes : 2 pour un 2, 13 pour un as
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
				tabpaquet[i].garder		= false		//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront chang�es
				tabpaquet[i].jeter		= false		//quand il d�cidera de ne pas garder, jeter prendra true
			}
		}
	}
}

/*
!!!!!!!!!!!!! Il faudra penser � changer les noms, en mettre peut �tre pas des plus simples, mais des plus pr�cis.
*/

main ()
{
	string tabsorte[4]		=	{"carreaux", "coeur", "pique", "trefle"} ;
	string tabvaleur[13]	=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A"}	;		//Je me questionne sur l'utilit� de �a, vu qu'on a la table des valeurs num�riques.
	string tabnom[13]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as"} ;
	int tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13} ;					//Ou alors on fait une fonction qui param�tre ca ? TELLEMENT DE POSSIBILIT� !!
	
	T_carte tabpaquet [52] ;
	
	C_carte(tabpaquet) ;
	
	
	
	
}
