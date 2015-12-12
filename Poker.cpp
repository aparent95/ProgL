#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;


struct T_compo_paquet
{
	string 	nom ;
	string 	sorte ;
	string 	valeur ;		//string parce que 10 n'est pas un caractère
	int 	valeur_num ; 	//valeur numérique des cartes : 2 pour un 2, 14 pour un as, 15 pour les Jokers
	bool 	garder ;
	bool 	owned	;  
};

void display(T_compo_paquet tab[], int c)		//Cette fonction est à enlever avant que le TP ne soit rendu
{											//Elle permet d'afficher toutes les cartes dans l'ordre, donc de vérifier nos fonctions de creation et brassage
	for ( int i=0 ; i < c ; i++ )	//Good thing to know : elle affiche aussi bien (cartes,52) que (main,5)
	{
		if ((tab[i].valeur == "JN") || (tab[i].valeur == "JR"))
		{
			cout << "(" << i+1 << ") " << tab[i].nom << " (valeur: "<< tab[i].valeur_num << ")" << endl ;
		}
		else
		{
			cout << "(" << i+1 << ") " << tab[i].nom << "  de  " << tab[i].sorte << " (valeur: "<< tab[i].valeur_num << ")" << endl;
		}
	}
}

void choisir_main(T_compo_paquet cartes[] , T_compo_paquet main[], int &nb_joker)
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
		while( (rep < 0) || (rep > 53) )
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

	system("cls");
	
	cout << endl << endl << "Voici votre main : " << endl << endl ;
	display(main,5);
	
}

void creation_tas(T_compo_paquet cartes[])
{
	int 	count 				=	0 ;
	string 	tabsorte[4]			=	{"carreaux", "coeur", "pique", "trefle"} ;
	string	tabvaleur[15]		=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "R", "A", "JR" , "JN"}	;
	string 	tabnom[15]			=	{"2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi", "as" , "Joker rouge" , "Joker noir"} ;
	int 	tabvaleur_num[15]	=	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15} ;
	
	while ( count < 52 )
	{
		for ( int i=0 ; i < 4 ; i++ )
		{
			for ( int j=0 ; j < 13 ; j++ )
			{
				cartes[count].sorte			= tabsorte[i] ;
				cartes[count].valeur		= tabvaleur[j] ;
				cartes[count].valeur_num	= tabvaleur_num[j] ;
				cartes[count].nom			= tabnom[j] ;
				cartes[count].garder		= false	;	//quand il choisira quoi garder, s'il n'entre rien, toutes les cartes seront changées
				cartes[count].owned			= false	;	//quand il faudra changer les cartes, ce sera le flag de "est-ce qu'il l'a déjà eu ?"
				count ++;									//owned = true quand il aura sa main
			}
		}
	}
	
	for ( int i=0 ; i < 2 ; i++ )
	{
		cartes[count].nom			= tabnom[i+13] ;
		cartes[count].valeur		= tabvaleur[i+13] ;
		cartes[count].valeur_num	= tabvaleur_num[i+13] ;
		cartes[count].garder		= false	;
		cartes[count].owned			= false	;
		count++ ;
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
			tabalea[j] = rand() %54 ;		//On set un tableau de nombre aléatoire compris entre 0 et 54 exclu	(54 cartes, de 0 à 53)
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

void donne_main(T_compo_paquet cartes[], T_compo_paquet main[], int &nb_joker)		//sert à donner et à redonner la main et détermine le nombre de joker
{
	T_compo_paquet temp ;
	int c = 0;
	bool modif = true;
	
	system("cls");		// possiblement, il y a autre part où il faudrait l'enlever.
	
	if (main[0].nom == "")		// Vérifie si la main est vide (si c'est la premiere fois que la fonction est appelée)
	{
		for (int i=0 ; i < 5 ; i++)
		{
			main[i].garder = false ;
		}
	}
	
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
		for (int i=0 ; i < 4 ; i++)
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
	
	for (int i=0 ; i < 5 ; i++)	//vérifie le nombre de joker dans la main et change j
	{
		if (main[i].valeur_num == 15)
		{
			nb_joker++;
		}
	}
	
	cout << endl << endl << "Voici votre main : " << endl << endl ;
	display(main,5);
}

void garde_main(T_compo_paquet cartes[] , T_compo_paquet main[])
{	
	int tabgarde[5] = {0};
	int indice ;
	int count = 0;		//compteur pour le while
	char rep;			//confirmation de l'échange
	int nb_joker ;
	
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
		case 'O' :	donne_main(cartes,main,nb_joker);		//La fonction se termine et change les cartes avec "garde=faux"
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

void trier_main(T_compo_paquet main[])
{
	T_compo_paquet temp ;
	bool modif = true ;
	
	while (modif==true)
	{
		modif = false ;
		for (int i=0 ; i < 4 ; i++)
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
}

void evaluer_main(T_compo_paquet main[] , float &gain , float mise)
{
	T_compo_paquet temp ;
	bool flag = true;
	int combinaison = 0 ;
	int compteur = 0 ;
	int c = 0 ;
	
	while(flag)
	{
		flag = false;
		for (int i=0 ; i < 4 ; i++)
		{
			if (main[i].valeur_num > main[i+1].valeur_num)
			{
				temp = main[i];
				main[i] = main[i+1];
				main[i+1] = temp;
				flag = true ;
			}
		}
	}
	
	flag = true;
	
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
		for ( int i=0 ; i < 4 ; i++ )	//Vérifie si les cartes se suivent
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
			for ( int i=0 ; i < 3 ; i++ )	// vérifie les 4 premieres cartes si elles sont IDENTIQUES
			{
				if (main[i].valeur_num != main[i+1].valeur_num)
				{
					flag = false ;	
				}
			}
			if  (flag) /*&& (main[3].valeur_num != main[4].valeur_num) )*/	// Si la dernière cartes est differente de l'avant derniere
			{
				combinaison = 3 ; //4 cartes identiques
			}
		}
		compteur = 1 ;
		for (int i=0 ; i < 4 ; i++)		//Vérification de la 6e possibilié : FullHouse
		{
			if ( (main[i].valeur_num == main[i+1].valeur_num) )	// Compteur ne peut valoir que 2 ou 3, puisque la paire ne peut être qu'au début et à la fin.
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
		if ((flag) && (combinaison == 0))	// Si 3 cartes sont identiques d'AFFILÉ un fois dans la main
		{
			combinaison = 7 ;	// Il y a au mois 3 cartes IDENTIQUES
			if ( (compteur == 2) && (combinaison == 7) )	// combinaison = 7 pour éviter des problemes de gain plus faibles qu'ils ne devraient être
			{
				combinaison = 6 ;		// Il y a FullHouse, 3 cartes identiques au début, 2 cartes identiques à la fin
			}
			else
			{
				if ( (main[0].valeur_num == main[1].valeur_num) && (combinaison == 7) && (compteur == 3) )
				{
					combinaison = 6;	//deux cartes identiques au début, 3 cartes identiques à la fin
				}
			}
		}
		for (int i=0 ; i < 4 ; i++)
		{
			if ( (main[i].valeur_num == main[i+1].valeur_num) && (i < 2) && (combinaison == 0) )		// si il y a une paire avant que le nombre de cartes permette d'avoir une autre paire
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
	}
	
}

void evaluer_joker(T_compo_paquet main[] , float &gain , float mise , int nb_joker)
{
	T_compo_paquet tabJoker[54];	//jeu de cartes de test
	T_compo_paquet temp_main[5];		//main originale
	T_compo_paquet temp_joker[5] ;		// Main dans laquelle le joker est à la meilleure place
	T_compo_paquet temp ;
	bool flag=true;
	int temp_gain = 0 ;
	
	creation_tas(tabJoker);		//jeu de cartes de test
		
	for (int i=0 ; i < 5 ; i++)	//variable temp_main est la variable temp que l'on peut modifier
	{
		temp_main[i] = main[i];
	}
	
	switch (nb_joker)
	{
		case 0 :	evaluer_main(main, gain, mise) ;
		break;
		
		case 1 :	for (int i=0 ; i < 52 ; i++)
					{
						for(int j=0 ; j < 5 ; j++) //trouver le JK dans la main, et le changer de valeur
						{
							if ((temp_main[j].valeur == "JR") || (temp_main[j].valeur == "JN"))
							{
								temp_main[j].valeur_num	= tabJoker[i].valeur_num;
								temp_main[j].sorte		= tabJoker[i].sorte;
							}
						}
						evaluer_main(temp_main,gain,mise);
						if (gain > temp_gain)
						{
							for (int j=0 ; j < 5 ; j++)
							{
								temp_joker[j] = temp_main[j];
							}
							temp_gain = gain;
						}
						for (int j=0 ; j < 5 ; j++)
						{
							temp_main[j] = main[j];
						}
					}
					gain = temp_gain;
					if (gain != 0)
					{
						cout << endl << endl << "Main apres calcul de la meilleure place :" << endl << endl
						 ;
						display(temp_joker,5);
					}
					else
					{
						cout << endl << endl << "Meilleur placement impossible. Votre main :" << endl << endl ;
						trier_main(main);	//dans le cas où elle ne serait pas triée (quand on utilise triche par example)
						display(main,5);
					}
					
		break;
		
		case 2 : 	for (int i=0 ; i < 52 ; i++)
					{
						for(int j=0 ; j < 52 ; j++)
						{
							for(int jk1=0 ; jk1 < 5 ; jk1++) //trouver les JK dans la main
							{
								if (temp_main[jk1].valeur == "JR")	//first JK
								{
									for (int jk2=0 ; jk2 < 5 ; jk2++)
									{
										if (temp_main[jk2].valeur == "JN")	// second JK
										{
											temp_main[jk1].valeur_num	= tabJoker[i].valeur_num;
											temp_main[jk1].sorte		= tabJoker[i].sorte;
											temp_main[jk2].valeur_num	= tabJoker[j].valeur_num;
											temp_main[jk2].sorte		= tabJoker[j].sorte;
										}
									}
								}
							}
							evaluer_main(temp_main,gain,mise);
							if (gain > temp_gain)
							{
								for (int k=0 ; k < 5 ; k++)
								{
									temp_joker[k] = temp_main[k];
								}
								temp_gain = gain;
							}
							for (int k=0 ; k < 5 ; k++)
							{
								temp_main[k] = main[k];
							}
						}
					}
					evaluer_main(temp_joker,gain,mise);
					gain = temp_gain ;
					if (temp_gain != 0)
					{
						cout << endl << endl << "Main apres calcul de la meilleure place :" << endl << endl ;
						display(temp_joker,5);
					}
					else
					{
						cout << endl << endl << "Meilleur placement impossible. Votre main :" << endl << endl ;
						trier_main(main);	//dans le cas où elle ne serait pas triée (quand on utilise triche par example)
						display(main,5);
					}
		break;
	}
	cout << endl << endl << "Gain : " << gain << " $." << endl ;
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

void information(bool &info, bool &jouer)
{
	system("cls");
	char rep;
	
	cout << "Informations compl" << char(130) << "mentaires :" << endl;
	cout << "Le mode 'Jouer' permet de demarrer le jeu normalement. Les cartes seront brassees, distribuées et pourront etre echangees." << endl;
	cout << "Le mode 'Tricher' permet de lancer le jeu en mode de triche, dans lequel vous pouvez choisir vos cartes selon leur indice dans le paquet." << endl;
	cout << "Le mode 'Tester' fonctionne comme 'Jouer', a ceci pres qu'il parametre la mise a 1, et ne demande pas le changement de cartes. Il affiche votre main, vos gains avec la main presente, pause le ";
	cout << "systeme, puis, en appuyant sur une touche, vous recommencez le meme processus. C'est un outil de test rapide. ";
	cout << "A noter toutefois qu'il n'est pas possible d'echanger les cartes dans ce mode, vos cartes seront donc juste triees" << endl << endl;
	cout << "N.B : Vous ne pouvez changer de mode de jeu uniquement au menu du jeu. Celui-ci ne s'affichera qu'a l'ouverture du programme." << endl;
	cout << "Ainsi, nous vous invitons a relancer le programme pour changer de mode. Notez aussi qu'en mode triche, la mise est demandee et les gains sont calcules." << endl << endl;
	
	system("Pause");
	
}

void demarrer(bool &jouer, bool &triche, bool &info, bool &test)		//premiere fonction appellée. Elle affiche le menu de démarrage, et demande au joueur de choisir entre jouer et arrêter le processus
{
	int rep ;
	
	do
	{
		system("cls");
			
		cout << setfill('=') << setw(25) << ' ' << "Nom de code: Poker Machine " << setw(25) << '=' << setfill(' ') << endl ;
		cout << endl << endl << endl ;
		cout << "Que voulez vous faire ?" << endl ;
		cout << "1 - Jouer " << char(133) << " Ndc: Poker Machine." << endl ;
		cout << "2 - Tricher" << endl ;
		cout << "3 - Informations" << endl ;
		cout << "4 - Tester" << endl ;
		cout << "5 - Quitter" << endl ;
		cout << "Entrez votre choix : " ; cin >> rep ;
		
			
		while ((rep < 1) || (rep > 5))
		{
			cout << endl << "Saisie invalide. \nEntrez votre choix : " ; cin >> rep ;
		}
		
		switch (rep)
		{
			case 1 : jouer	= true 	; 	info 	= false ;
			break;
			case 2 : jouer 	= true 	; 	triche 	= true 	; info = false ;
			break;
			case 3 : info  	= true 	;	information(info, jouer);
			break;
			case 4 : jouer 	= true	;	test	= true	; info 	= false ;
			break;
			case 5 : jouer 	= false ; 	info 	= false ;
			break;
		}
	}while((jouer==false)&&(rep!=5));
}


int main ()
{	
	T_compo_paquet cartes[54] ;
	T_compo_paquet main[5]	;
	int partie		= 0		;
	bool playagain 	= false ;
	bool jouer 		= false ;
	bool triche 	= false ;
	bool test		= false ;
	bool info ;
	
	do
	{
		demarrer(jouer, triche, info, test) ;
	}while(info);
	
	while ((playagain) || (jouer))
	{
		float mise 		= 0 ;
		float gain 		= 0 ;
		int nb_joker 	= 0 ;
		
		system("cls") ;
		
		playagain = false ;
		jouer = false ;
		creation_tas(cartes) ;
		
		if (test==false)
		{
			demander_mise(mise);
			if (triche)
			{
				choisir_main(cartes,main, nb_joker);
				evaluer_joker(main,gain,mise,nb_joker);
			}
			else
			{
				brasser(cartes);
				donne_main(cartes,main,nb_joker) ;
				evaluer_joker(main,gain,mise,nb_joker);
				garde_main(cartes,main) ;
				evaluer_joker(main,gain,mise,nb_joker);
			}
		}
		else
		{
			mise = 1 ;
			brasser(cartes) ;
			donne_main(cartes,main,nb_joker) ;
			evaluer_joker(main,gain,mise,nb_joker);
			cout << endl << "Test n_" << partie+1 << endl << endl;
		}
		partie++;
		rejouer(playagain) ;
	}
	system("cls") ;
	cout << "Nombre de partie(s) jou" << char(130) << "e(s) : " << partie << '.' << endl;
	cout << "Ce modeste jeu " << char(133) << ' ' << char(130) << 't' << char(130) << " d" << char(130) << "velopp" << char(130) << " par :" << endl;
	cout << "Aleck Parent" << endl << "Maxime Damour";
	cout << endl << endl << setfill('-') << setw(70) << '-' << setfill(' ') << endl << endl ;
	cout << setw(30) << "Merci d'avoir jou" << char(130) << " !" << endl ;
	cout << endl << setfill('-') << setw(70) << '-' << setfill(' ') << endl << endl ;

	system("Pause") ;
	
	return 0;
	
	

}
