#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;


struct T_compo_paquet
{
	string 	sorte ;
	string 	valeur ;		//string parce que 10 n'est pas un caractère
	int 	valeur_num ; 	//valeur numérique des cartes : 2 pour un 2, 14 pour un as
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
	int 	tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14} ;								//Ou alors on fait une fonction qui paramètre ca ? TELLEMENT DE POSSIBILITÉ !!
	
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
				cartes[count].garder			= true	;	//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront changées
				cartes[count].owned				= false	;	//quand il faudra changer les cartes, ce sera le flag de "est-ce qu'il l'a déjà eu ?"
				count ++;									//owned = true quand il aura sa main
			}
		}
	}	
}

void brasser(T_compo_paquet cartes[])
{
	srand (time(NULL)) ;					//initialisation de l'aléatoire
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

void donne_main(T_compo_paquet cartes[], T_compo_paquet main[])		//servira aussi à redonner la main
{
	T_compo_paquet temp ;
	int c ;
	bool modif = true;
	
	for ( int i=0 ; i < 5 ; i++ )
	{
		c = i ;
		if (main[i].garder == false)
		{
			while (cartes[c].owned == true)
			{
				c++;
			}
		main[i] = cartes[c] ;
		main[i].owned = true ;
		cartes[c].owned = true ;
		}
	}
	
	while (modif==true)
	{
		modif = false ;
		for (int i=0 ; i < 5 ; i++)
		{
			if (main[i].valeur_num > main[i+1].valeur_num)
			{
				temp = main[i] ;
				main[i] = main[i+1] ;
				main[i+1]=temp ;
				modif = true ;
			}
		}
	}
	
	cout << endl << endl << "Voici votre main : " << endl << endl ;
	for ( int i=0 ; i < 5 ; i++ )
	{
		cout << "(" << i+1 << ") " << main[i].nom << "  de  " << main[i].sorte << /*" (valeur: "<< main[i].valeur_num << ")" <<*/ endl;
	}
}

void garde_main(T_compo_paquet cartes[] , T_compo_paquet main[])
{
	int tabgarde[5]={0};
	int indice;
	int count = 0;		//compteur pour le while
	char rep;			//confimation de l'échange
	
	for ( int i=0 ; i < 5 ; i++ )		//set tous les "garder" à vrai, en cas de non confirmation de l'échange
	{
		main[i].garder = true ;
	}
	
	cout << endl << endl << "Veuillez indiquer le numéro de la carte de votre main que vous voulez garder." << endl ;
	cout << "Pour terminer, entrez 0" << endl << "Indiquer l'indice : " ; cin >> indice ; cout << endl ;
	
	while (( indice != 0 )&&( count < 5 ))
	{
		while (( indice < 0 ) || ( indice > 5 ))		//vérification de la saisie
		{
			cout << endl << "Saisie invalide. Veuillez entrer un indice compris entre 1 et 5." << endl ;
			cout << "Indiquer l'indice : " ; cin >> indice ; cout << endl << endl ;
		}
		tabgarde[count] = indice ;
		cout << endl << "Indiquer l'indice : " ; cin >> indice ; cout << endl ;
		count++;
	}
	
	for ( int i=0 ; i < 5 ; i++ )		//set tous les garder à faux. Dans le cas où il n'en a gardé aucune, toutes les cartes sont changées
	{
		main[i].garder = false ;
	}
	
	for ( int i=0 ; i < 5 ; i++ )		//vérifie quelles cartes il a garder
	{
		if (tabgarde[i] != 0)
		{
			main[tabgarde[i]-1].garder = true ;		//tabgarde[i]-1 c'est parce que le tableau commence toujours à 0
		}
	}
	
	cout << endl << "Les cartes suivantes vont etre echangees :" << endl ;		//Confirmation
	
	for ( int i=0 ; i < 5 ; i++ )
	{
		if (main[i].garder == false)
		{
			cout << main[i].nom << " de " << main[i].sorte << endl ;
		}
	}
	
	cout << endl << "Confirmer l'echange ? (o/n) : "; cin >> rep ; cout << endl ;

	while ((toupper(rep) != 'O') && (toupper(rep) != 'N'))		//Vérification de la saisie
	{	
		cout << endl << "Saisie invalide." << endl;
		cout << endl << "Confirmer l'echange ? (o/n) : "; cin >> rep ; cout << endl ;
	}
	switch (toupper(rep))		//deux fins de la fonction possibles
	{
		case 'O' : donne_main(cartes,main);		//La fonction se termine et change les cartes avec "garde=faux"
		break;
		case 'N' : garde_main(cartes,main);		//La fonction se relance, elle réinitialise donc "garder"
		break;
	}
	
}

void display(T_compo_paquet cartes[])		//Cette fonction est à enlever avant que le TP ne soit rendu
{											//Elle permet d'afficher toutes les cartes dans l'ordre, donc de vérifier nos fonctions de creation et brassage
	for ( int i=0 ; i < 52 ; i++ )
	{
		cout << cartes[i].nom << "	de	" << cartes[i].sorte <<"(valeur: " << cartes[i].valeur_num << ") "<< endl ;	//en commentaire : poid de la carte
	}
}

int main ()
{	
	
	T_compo_paquet cartes[52] ;
	T_compo_paquet main[5] ;

	creation_tas(cartes) ;
	brasser(cartes);
	donne_main(cartes,main) ;
	garde_main(cartes,main) ;

	
	
}
