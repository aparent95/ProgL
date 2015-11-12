#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;


struct T_compo_paquet
{
	string 	sorte ;
	string 	valeur ;		//string parce que 10 n'est pas un caract�re
	int 	valeur_num ; 	//valeur num�rique des cartes : 2 pour un 2, 14 pour un as
	string 	nom ;
	bool 	garder ;
	bool 	owned	;  
};

void creation_tas(T_compo_paquet cartes[])
{
	int 	count 				=	0 ;
	string 	tabsorte[4]			=	{"carreaux", "coeur", "pique", "trefle"} ;
	string	tabvaleur[13]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A"}	;		//Je me questionne sur l'utilit� de �a, vu qu'on a la table des valeurs num�riques.
	string 	tabnom[13]			=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as"} ;
	int 	tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14} ;								//Ou alors on fait une fonction qui param�tre ca ? TELLEMENT DE POSSIBILIT� !!
	
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
				cartes[count].garder			= true	;	//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront chang�es
				cartes[count].owned				= false	;	//quand il faudra changer les cartes, ce sera le flag de "est-ce qu'il l'a d�j� eu ?"
				count ++;									//owned = true quand il aura sa main
			}
		}
	}	
}

void brasser(T_compo_paquet cartes[])
{
	srand (time(NULL)) ;					//initialisation de l'al�atoire
	T_compo_paquet temp ;
	int tabalea[6] ;
	
	for (int i=0 ; i < 100 ; i++)			//Brassage 100
	{
		for ( int j=0 ; j < 6 ; j++ )		//Le nombre al�atoire seront chang� � chaque boucle
		{									//les positions seront interverti deux � deux
			tabalea[j] = rand() %52 ;		//On set un tableau de nombre al�atoire compris entre 0 et 52 exclu	(52 cartes, de 0 � 51)
		}
		for ( int j=0 ; j < 6 ; j++ )		//interpositionnage deux par deux des �l�ments de la structure
		{
			temp				=	cartes[tabalea[j]] ;		//faudrait peut �tre faire une sous fonction pour cette partie ?
			cartes[tabalea[j]]	=	cartes[tabalea[j+1]] ;
			cartes[tabalea[j+1]]=	temp ;
		}
	}
}

void donne_main(T_compo_paquet cartes[], T_compo_paquet main[])		//servira aussi � redonner la main
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
	char rep;			//confimation de l'�change
	
	for ( int i=0 ; i < 5 ; i++ )		//set tous les "garder" � vrai, en cas de non confirmation de l'�change
	{
		main[i].garder = true ;
	}
	
	cout << endl << endl << "Veuillez indiquer le num�ro de la carte de votre main que vous voulez garder." << endl ;
	cout << "Pour terminer, entrez 0" << endl << "Indiquer l'indice : " ; cin >> indice ; cout << endl ;
	
	while (( indice != 0 )&&( count < 5 ))
	{
		while (( indice < 0 ) || ( indice > 5 ))		//v�rification de la saisie
		{
			cout << endl << "Saisie invalide. Veuillez entrer un indice compris entre 1 et 5." << endl ;
			cout << "Indiquer l'indice : " ; cin >> indice ; cout << endl << endl ;
		}
		tabgarde[count] = indice ;
		cout << endl << "Indiquer l'indice : " ; cin >> indice ; cout << endl ;
		count++;
	}
	
	for ( int i=0 ; i < 5 ; i++ )		//set tous les garder � faux. Dans le cas o� il n'en a gard� aucune, toutes les cartes sont chang�es
	{
		main[i].garder = false ;
	}
	
	for ( int i=0 ; i < 5 ; i++ )		//v�rifie quelles cartes il a garder
	{
		if (tabgarde[i] != 0)
		{
			main[tabgarde[i]-1].garder = true ;		//tabgarde[i]-1 c'est parce que le tableau commence toujours � 0
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

	while ((toupper(rep) != 'O') && (toupper(rep) != 'N'))		//V�rification de la saisie
	{	
		cout << endl << "Saisie invalide." << endl;
		cout << endl << "Confirmer l'echange ? (o/n) : "; cin >> rep ; cout << endl ;
	}
	switch (toupper(rep))		//deux fins de la fonction possibles
	{
		case 'O' : donne_main(cartes,main);		//La fonction se termine et change les cartes avec "garde=faux"
		break;
		case 'N' : garde_main(cartes,main);		//La fonction se relance, elle r�initialise donc "garder"
		break;
	}
	
}

void display(T_compo_paquet cartes[])		//Cette fonction est � enlever avant que le TP ne soit rendu
{											//Elle permet d'afficher toutes les cartes dans l'ordre, donc de v�rifier nos fonctions de creation et brassage
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
