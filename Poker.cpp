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

void display(T_compo_paquet tab[], int c)		//Cette fonction est � enlever avant que le TP ne soit rendu
{											//Elle permet d'afficher toutes les cartes dans l'ordre, donc de v�rifier nos fonctions de creation et brassage
	for ( int i=0 ; i < c ; i++ )	//Good thing to know : elle affiche aussi bien (cartes,52) que (main,5)
	{
		cout << "(" << i+1 << ") " << tab[i].nom << "  de  " << tab[i].sorte << /*" (valeur: "<< main[i].valeur_num << ")" <<*/ endl;
	}
}

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
				cartes[count].garder			= false	;	//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront chang�es
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
	int c = 0;
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
	int indice = 0;
	int count = 0;		//compteur pour le while
	char rep;			//confimation de l'�change
	
	for ( int i=0 ; i < 5 ; i++ )		//set tous les "garder" � vrai, en cas de non confirmation de l'�change
	{
		main[i].garder = true ;
	}
	
	cout << endl << endl << "Veuillez indiquer le num�ro de la carte de votre main que vous voulez garder." << endl ;
	cout << "Pour terminer, entrez 0" << endl << endl << "Indiquer l'indice : " ; cin >> indice ; cout << endl ;
	
	while (( indice != 0 )&&( count < 4 ))
	{
		while (( indice < 0 ) || ( indice > 5 ))		//v�rification de la saisie
		{
			cout << endl << "Saisie invalide. Veuillez entrer un indice compris entre 1 et 5." << endl;
			cout << "Indiquer l'indice : " ; cin >> indice ; cout << endl << endl ;
		}
		tabgarde[count] = indice ;
		cout << endl << "Indiquer l'indice : " ; cin >> indice ; cout << endl ;
		count++;
	}
	count = 0;		//En vue d'une r�utilisation prochaine
	
	for ( int i=0 ; i < 5 ; i++ )		//set tous les garder � faux. Dans le cas o� il n'en a gard� aucune, toutes les cartes sont chang�es
	{
		main[i].garder = false ;
	}
	
	for ( int i=0 ; i < 5 ; i++ )		//v�rifie quelles cartes il a gard�
	{
		if (tabgarde[i] != 0)
		{
			main[tabgarde[i]-1].garder = true ;		//tabgarde[i]-1 c'est parce que le tableau commence toujours � 0
			count++;		//r�utilisation dde la variable pour compter le nombre de carte �chang�e.
		}
	}
	
	system("cls") ;		//Efface la console
	
	if (count !=0)
	{
		cout << endl << "Les cartes suivantes vont etre echangees :" << endl ;		//affichage des cartes ECHANG�ES
		
		for ( int i=0 ; i < 5 ; i++ )
		{
			if (main[i].garder == false)
			{
				cout << main[i].nom << " de " << main[i].sorte << endl ;
			}
		}
		
		cout << endl << "Les cartes suivantes vont etre gardees : " << endl ;	//affichage des cartes GARD�ES
		
		for ( int i=0 ; i < 5 ; i++ )
		{		
			if (main[i].garder == true)
			{
				cout << main[i].nom << " de " << main[i].sorte << endl;
			}
		}
	}
	else
	{
		cout << endl << "Toutes les cartes seront echangees." << endl ;
	}
	
	cout << endl << "Confirmer l'echange ? (o/n) : "; cin >> rep ; cout << endl ;	//Confirmation de l'�change

	while ((toupper(rep) != 'O') && (toupper(rep) != 'N'))		//V�rification de la saisie
	{	
		cout << endl << "Saisie invalide." << endl;
		cout << endl << "Confirmer l'echange ? (o/n) : "; cin >> rep ; cout << endl ;
	}
	switch (toupper(rep))		//deux fins de la fonction possibles
	{
		case 'O' : donne_main(cartes,main);		//La fonction se termine et change les cartes avec "garde=faux"
		break;
		case 'N' : 	system("cls");
					cout << endl << endl << "Voici votre main : " << endl << endl ; display(main,5) ;	//affichage avec fonction qui se trouve au d�but
					garde_main(cartes,main);		//La fonction se relance, elle r�initialise donc "garder"
		break;
	}
	
}

bool rejouer(bool &play)
{
	char rep ;
	cout << endl << endl ;
	cout << setfill('-') << setw(70) << '-' << setfill(' ') << endl << endl ;
	cout << "Voulez-vous rejouer ? (o/n) : " ; cin >> rep ; cout << endl ;
	while ((toupper(rep) != 'O') && (toupper(rep) != 'N'))
	{
		cout << endl << "Saisie invalide. \nVoulez-vous rejouer ? (o/n) : " ; cin >> rep ; cout << endl ;
	}
	switch (toupper(rep))
	{
		case 'O' : play = true; return play ;
		break;
		case 'N' : play  = false ; return play ;
		break;
	}
}


int main ()
{	
	bool playagain;
	
	do
	{
		system("cls") ;
		
		T_compo_paquet cartes[52] ;
		T_compo_paquet main[5] ;
		playagain = false ;
		
		creation_tas(cartes) ;
	//	brasser(cartes);
		donne_main(cartes,main) ;
		garde_main(cartes,main) ;
		rejouer(playagain) ;
	}
	while (playagain) ;
	
	system("cls") ;
	cout << endl << endl << setfill('-') << setw(70) << '-' << setfill(' ') << endl << endl ;
	cout << "Merci d'avoir jouer !" << endl ;
	system("Pause") ;
	
	return 0;
}
