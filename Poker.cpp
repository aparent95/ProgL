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

void display(T_compo_paquet tab[], int c)		//Cette fonction est à enlever avant que le TP ne soit rendu
{											//Elle permet d'afficher toutes les cartes dans l'ordre, donc de vérifier nos fonctions de creation et brassage
	for ( int i=0 ; i < c ; i++ )	//Good thing to know : elle affiche aussi bien (cartes,52) que (main,5)
	{
		cout << "(" << i+1 << ") " << tab[i].nom << "  de  " << tab[i].sorte << /*" (valeur: "<< main[i].valeur_num << ")" <<*/ endl;
	}
}

void choisir_main(T_compo_paquet cartes[] , T_compo_paquet main[])
{
	system("cls");
	int tabrep[5];
	int rep = 0 ;
	int count = 0 ;
	cout << endl << "Felicitation ! Vous trichez !" << endl << "Pour l'indice des cartes, merci de vous referer au document Cartes.pdf" << endl << endl ;
	cout << "Vous pouvez alors choisir les cartes qui seront dans votre main." << endl ;
	while (count < 5)
	{
		cout << "Veuillez entrer l'indice : ";
		cin >> rep ;
		cout << endl << endl ;
		while( (rep < 0) || (rep > 52) )
		{
			cout << endl << "Cette carte n'existe pas. Tricher, oui; mais trichez bien !" << endl ;
			cout << "Veuillez entrer l'indice : ";
			cin >> rep ;
			cout << endl << endl ;
		}
		tabrep[count] = rep ;
		count++;
	}
	
	for (int i=0 ; i < 5 ; i++)
	{
		main[i] = cartes[tabrep[i]];
	}
	
	cout << endl << endl << "Voici votre main : " << endl << endl ;
	display(main,5);
	
}

void creation_tas(T_compo_paquet cartes[])
{
	int 	count 				=	0 ;
	string 	tabsorte[4]			=	{"carreaux", "coeur", "pique", "trefle"} ;
	string	tabvaleur[13]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A"}	;
	string 	tabnom[13]			=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as"} ;
	int 	tabvaleur_num[13]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14} ;
	
	while ( count < 52 )
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
				count ++;									//owned = true quand il aura sa main
			}
		}
	}
	
		
}

void brasser(T_compo_paquet cartes[])
{
	srand (time(NULL)) ;					//initialisation de l'aléatoire
	T_compo_paquet temp ;
	int tabalea[6] = {0} ;
	
	for (int i=0 ; i < 100 ; i++)			//Brassage 100
	{
		for ( int j=0 ; j < 6 ; j++ )		//Le nombre aléatoire seront changé à chaque boucle
		{									//les positions seront interverti deux à deux
			tabalea[j] = rand() %52 ;		//On set un tableau de nombre aléatoire compris entre 0 et 52 exclu	(52 cartes, de 0 à 51)
		}
		for ( int j=0 ; j < 6 ; j++ )		//interpositionnage deux par deux des éléments de la structure
		{
			temp				=	cartes[tabalea[j]] ;		
			cartes[tabalea[j]]	=	cartes[tabalea[j+1]] ;
			cartes[tabalea[j+1]]=	temp ;
		}
	}
}

float demander_mise(float &x)
{
	cout << endl << "Veuillez indiquez votre mise : " ; cin >> x ; cout << endl ; // Confirmation à faire ? Utile ?
	
	while(x <= 0)
	{
		cout << "Saisie invalide." << endl << "Veuillez indiquez votre mise : ";
		cin >> x ;
	}
	
	return x ;
}

void donne_main(T_compo_paquet cartes[], T_compo_paquet main[])		//sert à donner et à redonner la main
{
	T_compo_paquet temp ;
	int c = 0;
	bool modif = true;
	
	system("cls");		// possiblement, il y a autre part où il faudrait l'enlever.
	
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
	int tabgarde[5] = {0};
	int indice;
	int count = 0;		//compteur pour le while
	char rep;			//confimation de l'échange
	
	for (int i=0 ; i < 5 ; i++)
	{
		main[i].garder = false;
	}
	
	cout << endl << endl << "Veuillez indiquer le num" << char(130) << "ro de la carte de votre main que vous voulez garder." << endl ;
	cout << "Pour terminer, entrez 0" << endl << endl ;
	
	do
	{
		cout << endl << "Indiquez l'indice : " ; cin >> indice ; cout << endl ;
		while (( indice < 0 ) || ( indice > 5 ))		//vérification de la saisie
		{
			cout << endl << "Saisie invalide. Veuillez entrer un indice compris entre 1 et 5." << endl;
			cout << "Indiquez l'indice : " ; cin >> indice ; cout << endl << endl ;
		}
		tabgarde[count] = indice ;
		count++;
	}
	while (( indice != 0 )&&( count < 5 ));
	
	count = 0;		//En vue d'une réutilisation prochaine
	
	for ( int i=0 ; i < 5 ; i++ )		//vérifie quelles cartes il a gardées
	{
		if (tabgarde[i] != 0)
		{
			main[tabgarde[i]-1].garder = true ;		//tabgarde[i]-1 c'est parce que le tableau commence toujours à 0
			count++;		//réutilisation dde la variable pour compter le nombre de carte échangée.
		}
	}
	system("cls") ;		//Efface la console
	
	if (count !=0)
	{
		cout << endl << "Les cartes suivantes seront " << char(130) << "chang" << char(130) << "es :" << endl ;		//affichage des cartes ECHANGÉES
		
		for ( int i=0 ; i < 5 ; i++ )
		{
			if (main[i].garder == false)
			{
				cout << main[i].nom << " de " << main[i].sorte << endl ;
			}
		}
		
		cout << endl << "Les cartes suivantes seront gard" << char(130) << "es : " << endl ;	//affichage des cartes GARDÉES
		
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
		cout << endl << "Toutes les cartes seront " << char(130) << "chang" << char(130) << "es." << endl ;
	}
	
	
	cout << endl << "Confirmer l'" << char(130) << "change ? (o/n) : "; cin >> rep ; cout << endl ;	//Confirmation de l'échange

	while ((toupper(rep) != 'O') && (toupper(rep) != 'N'))		//Vérification de la saisie
	{	
		cout << endl << "Saisie invalide." << endl;
		cout << endl << "Confirmer l'" << char(130) << "change ? (o/n) : "; cin >> rep ; cout << endl ;
	}
	switch (toupper(rep))		//deux fins de la fonction possibles
	{
		case 'O' :	donne_main(cartes,main);		//La fonction se termine et change les cartes avec "garde=faux"
					for ( int i=0 ; i < 5 ; i++ )	
					{	//set main.garder à faux, pour que main[i] puisse être réutilisable sans probleme
						main[i].garder = false ;
					}
		break;
		
		case 'N' : 	system("cls");
					cout << endl << endl << "Voici votre main : " << endl << endl ; display(main,5) ;	//affichage avec fonction qui se trouve au début
					garde_main(cartes,main);		//La fonction se relance MAIS ELLE DEVRAIT ÊTRE EN DESSOUS DE LA REMISE À 0
//					for ( int i=0 ; i < 5 ; i++ )
//					{	//set main.garder à faux, pour que main[i] puisse être réutilisable sans probleme
//						main[i].garder = false ;
//					}
		break;
	}
	
}

void evaluer_main(T_compo_paquet main[] , float &gain , float mise)
{
	bool flag = true;
	int combinaison = 0 ;
	int compteur = 0 ;
	int c = 0 ;
		
	for ( int i=0 ; i < 4 ; i ++ )		// Vérification des sortes
	{
		if (main[i].sorte != main[i+1].sorte)
		{
			flag = false ;
		}
	}

	if (flag)		// SI toutes les cartes sont de la même sorte
	{
		for (int i=0 ; i < 4 ; i++ )
		{
			if (main[i].valeur_num != main[i+1].valeur_num - 1)
			{
				flag = false ;
			}
		}
		if (!flag)
		{
			combinaison = 5;		// 5 cartes de la même sorte
		}
		else
		{
			if (main[0].valeur_num == 10)
			{
				combinaison = 1 ;		// Suite royale (premiere carte = 10)
				
			}
			else
			{
				combinaison = 2 ;		// Suite
			}
		}	
	}
	
	else			// SINON (si pas toutes des la mêmes sortes)
	{
		flag = true ;
		for ( int i=0 ; i < 4 ; i++ )
		{
			if (main[i].valeur_num != main[i+1].valeur_num - 1)
			{
				flag = false ;
			}
		}
		if (flag)
		{
			combinaison = 4 ;		// Suite de 5 cartes (pas de la même sorte)
		}
		flag = true ;
		if (main[0].valeur_num != main[1].valeur_num)		// Si la premiere carte differente de la 2nd (test des 4 cartes pareilles)
		{
			for ( int i=1 ; i < 4 ; i++ )		// Vérification si les cartes restantes sont identiques entre elles
			{
				if (main[i].valeur_num != main[i+1].valeur_num)	// les cartes identiques sont à la fin
				{
					flag = false ;
				}
			}
			if (flag)
			{
				combinaison = 3 ;	// 4 cartes pareilles
			}
		}
		else		// Test dans le cas ou les 4 cartes identiques sont au début
		{
			flag = true ;
			for ( int i=0 ; i < 3 ; i++ )	// vérifie les 4 premieres cartes si elles sont IDENTIQUE
			{
				if (main[i].valeur_num != main[i+1].valeur_num)
				{
					flag = false ;	
				}
			}
			if ( (flag) && (main[3].valeur_num != main[4].valeur_num) )	// Si la dernière cartes est differente de l'avant derniere
			{
				combinaison = 3 ;
			}
		}
		compteur = 1 ;
		for (int i=0 ; i < 4 ; i++)		//Vérification de la 6e possibilié : FullHouse
		{
			if (main[i].valeur_num == main[i+1].valeur_num)	// Compteur ne peut valoir que 2 ou 3, puisque la paire ne peut être qu'au début et à la fin.
			{
				compteur++ ;
				if (compteur == 3)
				{
					flag = true ;
				}
				
			}
			else
			{
				compteur = 1 ;	
			}
		}
		if (flag)	// Si 3 cartes sont identiques d'AFFILÉ un fois dans la main
		{
			combinaison = 7 ;	// Il y a au mois 3 cartes IDENTIQUES
			if (compteur == 2)
			{
				combinaison = 6 ;		// Il y a FullHouse, 3 cartes identiques au début, 2 cartes identiques à la fin
			}
			else
			{
				if (main[3].valeur_num == main[4].valeur_num)
				{
					combinaison = 6;	//deux cartes identiques au début, 3 cartes identiques à la fin
				}
			}
		}
		for (int i=0 ; i < 4 ; i++)
		{
			if ( (main[i].valeur_num == main[i+1].valeur_num) && (i < 2) )		// si il y a une paire avant que le nombre de cartes permette d'avoir une autre paire
			{
				for ( int j=i+2 ; j < 4 ; j++ )		// vérification si, dans le reste des cartes, ya une autre paire
				{
					if (main[j].valeur_num == main[j+1].valeur_num)
					{
						combinaison = 8 ;
					}
				}
			}
		}
		
	}
	cout << endl << "combi : " << combinaison << endl ;
	// Mise à jour du gain
	switch (combinaison)
	{
		case 1 : gain = mise * 40;
		break;
		case 2 : gain = mise * 30;
		break;
		case 3 : gain = mise * 25;
		break;
		case 4 : gain = mise * 20;
		break;
		case 5 : gain = mise * 15;
		break;
		case 6 : gain = mise * 10;
		break;
		case 7 : gain = mise * 5;
		break;
		case 8 : gain = mise * 3;
		break;
		default : cout << endl << "Vous ne gagnez rien !" << endl;
	}
	
}

bool rejouer(bool &play)		//Affiche/demande au joueur s'il veut rejouer
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
		case 'N' : play  = false; return play ;
		break;
	}
}

void demarrer(bool &jouer, bool &triche)		//premiere fonction appellée. Elle affiche le menu de démarrage, et demande au joueur de choisir entre jouer et arrêter le processus
{
	int rep ;
	cout << setfill('=') << setw(25) << ' ' << "Nom de code: Poker Machine " << setw(25) << '=' << setfill(' ') << endl ;
	cout << endl << endl << endl ;
	cout << "Que voulez vous faire ?" << endl ;
	cout << "1 - Jouer " << char(133) << " Ndc: Poker Machine." << endl ;
	cout << "2 - Tricher" << endl ;
	cout << "3 - Quitter" << endl ;
	cout << "Entrez votre choix : " ; cin >> rep ;
	while ((rep != 2) && (rep != 1))
	{
		cout << endl << "Saisie invalide. \nEntrez votre choix : " ; cin >> rep ;
	}
	
	switch (rep)
	{
		case 1 : jouer = true;
		break;
		case 2 : jouer  = true; triche = true ;
		break;
		case 3 : jouer  = false;
		break;
	}
}


int main ()
{	
	bool playagain = false;
	bool jouer = false;
	bool triche = false;
	float mise = 0 ;
	float gain = 0 ;
	
	demarrer(jouer, triche) ;
	while ((playagain) || (jouer))
	{
		system("cls") ;
		
		T_compo_paquet cartes[52] ;
		T_compo_paquet main[5] ;
		playagain = false ;
		jouer = false ;
		
		creation_tas(cartes) ;
		demander_mise(mise);
		
		if (triche)
		{
			choisir_main(cartes,main);
		}
		else
		{
			donne_main(cartes,main) ;
		}
		
		brasser(cartes);
		evaluer_main(main,gain,mise);
		garde_main(cartes,main) ;
		evaluer_main(main,gain,mise);
		cout << endl << "gain : " << gain << endl ;
		rejouer(playagain) ;
	}
	
	system("cls") ;
	cout << "Ce modeste jeu " << char(133) << ' ' << char(130) << 't' << char(130) << " d" << char(130) << "velopp" << char(130) << " par :" << endl;
	cout << "Aleck Parent" << endl << "Maxime Damour";
	cout << endl << endl << setfill('-') << setw(70) << '-' << setfill(' ') << endl << endl ;
	cout << setw(30) << "Merci d'avoir jou" << char(130) << " !" << endl ;
	cout << endl << setfill('-') << setw(70) << '-' << setfill(' ') << endl << endl ;

	system("Pause") ;
	
	return 0;
	
	

}
