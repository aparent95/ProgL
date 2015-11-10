#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

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

void creation_tas(T_compo_paquet cartes[])
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
				cartes[count].sorte				= tabsorte[i] ;
				cartes[count].valeur			= tabvaleur[j] ;
				cartes[count].valeur_num		= tabvaleur_num[j] ;
				cartes[count].nom				= tabnom[j] ;
				cartes[count].garder			= false	;	//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront changées
				cartes[count].owned				= false	;	//quand il faudra changer les cartes, ce sera le flag de "est-ce qu'il l'a déjà eu ?"
				count ++;								//owned = true quand il aura sa main
			}
		}
	}	
}



void brasser(T_compo_paquet cartes[])
{
	srand (time(NULL)) ;				//initialisation de l'aléatoire
	T_compo_paquet temp ;
	int tabalea[6] ;
	
	for (int i=0 ; i < 100 ; i++)			//Brassage 100
	{
		for ( int j=0 ; j < 6 ; j++ )		//Le nombre aléatoire seront changé à chaque boucle
		{									//les positions seront interverti deux à deux
			tabalea[j] = rand() %52 ;		//On set un tableau de nombre aléatoire compris entre 0 et 52 exclu	(52 cartes, de 0 à 51)
		}
		for ( int j=0 ; j < 6 ; j++ )		//interpositionnage deux par deux des éléments de la structure
		{
			temp				=	cartes[tabalea[j]] ;		//faudrait peut être faire une sous fonction pour cette partie ?
			cartes[tabalea[j]]	=	cartes[tabalea[j+1]] ;
			cartes[tabalea[j+1]]=	temp ;
		}
	}
}

void display(T_compo_paquet cartes[])		//Cette fonction est à enlever avant que le TP ne soit rendu
{											//Elle permet d'afficher toutes les cartes dans, donc de vérifier nos fonctions de creation et brassage
	for ( int i=0 ; i < 52 ; i++ )
	{
		cout << cartes[i].nom << "	de	" << cartes[i].sorte /*<<"(poids: " << cartes[i].valeur_num << ") "*/<< endl ;	//en commentaire : poid de la carte
	}
}

/*
!!!!!!!!!!!!! Il faudra penser à changer les noms, en mettre peut être pas des plus simples, mais des plus précis.
*/


int main ()
{	
	
	T_compo_paquet cartes[52] ;

	creation_tas(cartes) ;
	
	brasser(cartes) ;
	
	display(cartes) ;

}
