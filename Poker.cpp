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
	bool owned	;  
};

T_carte C_carte(T_carte paquet)
{
	string tabsorte[4]		=	{"carreaux", "coeur", "pique", "trefle"} ;
	string tabvaleur[13]	=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A"}	;		//Je me questionne sur l'utilit� de �a, vu qu'on a la table des valeurs num�riques.
	string tabnom[13]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as"} ;
	int tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14} ;					//Ou alors on fait une fonction qui param�tre ca ? TELLEMENT DE POSSIBILIT� !!
	
	for ( int i=0; i < 51 ; i++ )
	{
		//for ( int j=0 ; j < 3 ; j++ )
		//{
			//for ( int k=0 ; k < 12 ; k++ )
			//{
				paquet.valeur			= tabvaleur[k] ;
				//paquet.valeur_num		= tabvaleur_num[k] ;
				//paquet.nom			= tabnom[k] ;
				//paquet.garder			= false	;	//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront chang�es
				//paquet.owned			= false	;	//quand il faudra changer les cartes, ce sera le flag de "est-ce qu'il l'a d�j� eu ?"
													//owned = true quand il aura sa main
		//	}
		//}
	}
	return paquet ;
}


/*
!!!!!!!!!!!!! Il faudra penser � changer les noms, en mettre peut �tre pas des plus simples, mais des plus pr�cis.
*/


main ()
{
	/*string tabsorte[4]		=	{"carreaux", "coeur", "pique", "trefle"} ;
	string tabvaleur[13]	=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A"}	;		//Je me questionne sur l'utilit� de �a, vu qu'on a la table des valeurs num�riques.
	string tabnom[13]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as"} ;
	int tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13} ;					//Ou alors on fait une fonction qui param�tre ca ? TELLEMENT DE POSSIBILIT� !!
	*/
	T_carte paquet[52] ;

	

	
	
	
	
}
