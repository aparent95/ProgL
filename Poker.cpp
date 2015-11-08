#include <iostream>
#include <iomanip>

using namespace std;


struct T_compo_paquet
{
	string 	sorte ;
	string 	valeur ;		//string parce que 10 n'est pas un caractère
	int 	valeur_num ; 	//valeur numérique des cartes : 2 pour un 2, 13 pour un as
	string 	nom ;
	bool 	garder ;
	bool 	owned	;  
};

void creation_tas(T_compo_paquet carte[])
{
	int 	count 				=	0 ;
	string 	tabsorte[4]			=	{"carreaux", "coeur", "pique", "trefle"} ;
	string	tabvaleur[13]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A"}	;		//Je me questionne sur l'utilité de ça, vu qu'on a la table des valeurs numériques.
	string 	tabnom[13]			=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as"} ;
	int 	tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14} ;					//Ou alors on fait une fonction qui paramètre ca ? TELLEMENT DE POSSIBILITÉ !!
	
	while ( count < 51 )
	{
		for ( int i=0 ; i < 4 ; i++ )
		{
			for ( int j=0 ; j < 13 ; j++ )
			{
				carte[count].sorte			= tabsorte[i] ;
				carte[count].valeur			= tabvaleur[j] ;
				carte[count].valeur_num		= tabvaleur_num[j] ;
				carte[count].nom			= tabnom[j] ;
				carte[count].garder			= false	;	//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront changées
				carte[count].owned			= false	;	//quand il faudra changer les cartes, ce sera le flag de "est-ce qu'il l'a déjà eu ?"
				count ++;								//owned = true quand il aura sa main
			}
		}
	}	
}


/*
!!!!!!!!!!!!! Il faudra penser à changer les noms, en mettre peut être pas des plus simples, mais des plus précis.
*/


int main ()
{	
	T_compo_paquet carte[52] ;

	creation_tas(carte) ;
	
//	for ( int i=0 ; i < 52 ; i++ )			//Vérification du tas de carte
//	{
//		cout << carte[i].nom << " de " << carte[i].sorte << " (" << carte[i].valeur_num << ") " << i+1 << "e carte" << endl ;
//	}
	
	
	
}
