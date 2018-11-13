#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * 
 * 
 * 
 * 
 * 
 */


//////////////// Déclaration des Types ///////////////////////
typedef struct TCarte{
	char nom[17];	        //Nom de la carte
        int  id;		//Type de carte
        int  position;
        struct TCarte * Suivant;
} TCarte;

//Création de la structure Joueurs et Plateau
TCarte * Joueur1;
TCarte * Joueur2;
TCarte * Joueur3;
TCarte * Plateau;

///// Procédures générales
void InsertionTete(TCarte*,TCarte*);
void InsertionQueue(TCarte*,TCarte*);
void InsertionTrie(TCarte*,TCarte*);
int  NombreDeJoueur();
void InitsCartes();             //Création et Initialisations des 32 cartes
int  Bornes(int,int);           //Borne pour le random
void DistributionCarte(int);    //Distribution des cartes selon nombre de joueur
void AfficherCarte(TCarte*);    // Affichage de la main du joueur ou du plateau
void ChoisirCarte(TCarte*,int,int,int);     //La/les cartes jouées par un joueur lors d'un tour
void Menteur(int,int,int);      //Un des joueurs dit menteur?
void RamasserCarte(TCarte*,TCarte*,TCarte*,int,int,int); //Si un joueur dit menteur, il ramasse toutes les cartes du plateau


// *******************************************
//                  Main
// ********************************************

int main()
{
        //LEXIQUE
        int nb;
	int position = 1;
	int tour = 0;
	int joueur;
	int choix = 0;
	int carte1 = 0;
	int carte2 = 0;
	
	printf("/////////////////BIENVENUE DANS LE JEU DU MENTEUR////////////////// \n\n");

	printf("/////////////////REGLE DU JEU////////////////// \n\n");
	
	printf("Composition du jeu : 28 cartes famille ( 4 pépés / 4 mémés / 4 papa/maman / 4 frérots / 4 soeurettes / 4 bébés ) \n");
	printf("Composition du jeu : 4 cartes Tante Carabosse \n");
	printf("Composition du jeu : Une planche de jeu avec une case pour chaque carte famille différente \n\n");
	
	printf("But du jeu : être le premier à poser toutes ses cartes \n\n");

	printf("Déroulement d'une partie  : à tour de rôle, les joueurs posent des cartes (1 ou 2) face cachée sur une case du plateau\n");
	printf("Déroulement d'une partie  : Vous annoncez ce que vous posez (sans montrer la carte), il faut normalement poser la carte correspondant à la case (carte frérot sur case frérot.. Il faut donc réussir à bluffer !)\n");
        printf("Déroulement d'une partie  : Le premier joueur joue sur la case Pépé, le deuxieme joueur sur la case Mémé, le troisième joueur sur la case Papa, et ainsi de suite\n");
	printf("Déroulement d'une partie  : Si un joueur ne vous croit pas, il peut dire menteur \n");
	printf("Déroulement d'une partie  : Si vous n'avez pas menti, montrez vos cartes, et le joueur récupère toutes les cartes sur la planche sauf les cartes précédentes de la case \n");
	printf("Déroulement d'une partie  : Si vous avez pas menti, c'est vous qui récupérez les cartes ! \n");
	printf("Déroulement d'une partie  : Il n'y a pas de case tante Carabosse, il faudra alors absolument bluffer pour s'en débarasser. \n\n");

	printf("/////////////////REGLE DU JEU////////////////// \n\n");
        
        
        // **** Début **** //
        
        //INITS
        nb=NombreDeJoueur();
        printf("DEBUG 1");
        InitsCartes();
        printf("DEBUG 2");
        DistributionCarte(nb);
        printf("DEBUG 3");
 	printf("////////////////Début de la partie/////////////// \n\n");
	
	while(Joueur1 != NULL && Joueur2 != NULL && Joueur3 != NULL)
	{
        if(position == 7)
		{
			position = 1; //remise à 0 du plateau (je sais pas comment faire autrement)
		}	
		while(position<=7)
		{
			tour = tour + 1;
			joueur = tour%nb;
			printf("///////////////Tour du joueur %d//////////////// \n\n",joueur);
			
			switch(joueur)
			{
				case 1 :
					AfficherCarte(Joueur1);
					ChoisirCarte(Joueur1,position,carte1,carte2);
					Menteur(choix,1,2); //fait le tour de la table pour savoir qui veut dire menteur
                                        
					if(choix==0)
					{
						Menteur(choix,1,3);
						if(choix==1)
						{ 
                                                        RamasserCarte(Joueur1,Joueur3,Plateau,position,carte1,carte2);
						}
					}
					else
					{
                                                RamasserCarte(Joueur1,Joueur2,Plateau,position,carte1,carte2);
					}
                                        
                                        break;
				
				case 2 :
					AfficherCarte(Joueur2);
					ChoisirCarte(Joueur2,position,carte1,carte2);
					Menteur(choix,2,3);
                                        
					if(choix==0)
					{
						Menteur(choix,2,1);
						if(choix==1)
						{
                                                        RamasserCarte(Joueur2,Joueur3,Plateau,position,carte1,carte2);
						}
					}
					else
					{
                                                RamasserCarte(Joueur2,Joueur1,Plateau,position,carte1,carte2);
					}
					
                                        break;
				
				case 3 :
					AfficherCarte(Joueur3);
					ChoisirCarte(Joueur3,position,carte1,carte2);
					Menteur(choix,3,1);
                                        
					if(choix==0)
					{
						Menteur(choix,3,2);
						if(choix==1)
						{
                                                        RamasserCarte(Joueur3,Joueur2,Plateau,position,carte1,carte2);
						}
					}
					else
					{
                                                RamasserCarte(Joueur3,Joueur2,Plateau,position,carte1,carte2);
					}
                                        break;
                        }
                        
                        position = position +1;
		}
	}
	printf("///////////////FIN DE PARTIE////////////////\n");
	printf("C'est le joueur %d qui a gagné !\n",joueur);
        
        return (0);
}



// ********************************************
//               Les procédures
// ********************************************


///////Les 3 types d'insertions////////////

//Insertion d'une nouvelle Cellule en tête de Liste (Joueur ou Plateau)
void InsertionTete (TCarte * Liste, TCarte * New)
{		
		New->Suivant = Liste; 
		Liste = New;
}

//Insertion d'une nouvelle Cellule en bout de Liste (Joueur ou Plateau)
void InsertionQueue (TCarte * Liste, TCarte * New)
{
	TCarte * aux;
        
	if (Liste != NULL)
	{
		*aux = *Liste;
		while (aux->Suivant != NULL) 
		{
			*aux = *aux->Suivant;
		}
		*aux->Suivant = *New;
	}
	else
	{
		*Liste = *New;
	}
}

//Insertion d'une nouvelle Cellule triée dans la liste (Joueur ou Plateau)
void InsertionTrie (TCarte * Liste, TCarte * New) 
{
	TCarte * aux;
	TCarte * prec;
	int trouve = 0;

	aux=Liste; 
	prec=aux;
	if(Liste == NULL)
	{
		InsertionTete(Liste,New);
	}
	else
	{
		while ((aux!=NULL) && (trouve == 0)) //insertin trié et queue
		{
			if(aux->id < New->id)
			{
				prec = aux;
				aux = aux->Suivant;
			}
			else 
			{	
				trouve = 1;
			}	
		}
		prec->Suivant = New;
		New->Suivant = aux;
	}


}

///////Autres Fonctions & Procédures////////////

//Fonction qui retourne le nombre de joueur dans la partie
int NombreDeJoueur()
{
        int nb;
        
        do
	{
                printf("Combien de joueurs êtes vous ? (de 2 à 3) \n");
                scanf("%d", &nb);
	}
	while(nb<2 || nb>3 );

        return nb;
}

//Insertion des différentes cartes dans la liste Plateau pour le début du jeu
void InitsCartes() 
{
	int i;
	int j;
        TCarte * New;

	for (i=0;i<=3;i++) // boucle for pour faire 4 cartes de chaque
	{
		for (j=0;j<=7;j++) // boucle for pour faire toutes les sortes de cartes
		{  
                        New = NULL;
                        switch(j)
                        {
                                case 0 :
					strcpy(New->nom , "Tante CARABOSSE");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;
				
				case 1 :
					strcpy(New->nom , "Pépé");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;
				
				case 2 :
					strcpy(New->nom , "Mémé");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;
				
				case 3 :
					strcpy(New->nom , "Papa");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;	
						
				case 4 :
					strcpy(New->nom , "Maman");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;	
						
				case 5 :
					strcpy(New->nom , "Frérot");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;	
						
				case 6 :
					strcpy(New->nom , "Soeurette");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;		
					
				case 7 :
					strcpy(New->nom , "Bébé");
					New->id = j;
                                        New->position=0;
					InsertionTete(Plateau,New);
				break;								
		    }
	    }
    }
}

//Définition des bornes nécessaires au random
int Bornes(int Min , int Max)
{
	static int rand_is_seeded = 0;
        
	if(!rand_is_seeded)
	{
                srand(time(NULL));
                rand_is_seeded = 1;
        }
        
        return rand()%(Max-Min+1) + Min;
}

//Distribution des Cartes
void DistributionCarte(int NbJoueur)
{
	TCarte * aux;
	TCarte * prec;
        int i;
	int j;
	int alea;

	aux = Plateau;
        for (i=0; i<32  ;i++) //on random les cartes 32 fois
	{
		alea=Bornes(0,31);
                
		for (j=0; j<=alea; j++) //la carte à la position de l'aléa est envoyé à la fin
		{
			aux = aux->Suivant; //on arrive jusqu'à la position de l'aléa
		}
                
		InsertionTete(Plateau,aux); // on l'insère au début du plateau
	}


	for (i=1; i<=NbJoueur ;i++) //Distribution des cartes
	{
		for(j=0; j<=(32/NbJoueur) ;j++)
		{
			 prec = Plateau;
			 Plateau = Plateau->Suivant;
			 switch(i)
			 {
				case 1 :
					InsertionTrie(Joueur1,prec);
                                        break;
				
				case 2 :
					InsertionTrie(Joueur2,prec);
                                        break;
				
				case 3 :
					InsertionTrie(Joueur3,prec);
                                        break;
			 }
		}
	}
}

//Affichage d'une carte de la main du joueur ou du plateau
void AfficherCarte(TCarte * Joueur) 
{
        TCarte * aux;
	aux = Joueur;
        
	while (aux->Suivant != NULL)
	{
		aux = aux->Suivant;
                printf("******************************************************** \n \n");
                printf("id : %d %s \n",Joueur->id, Joueur->nom );
                printf("******************************************************** \n \n \n");
	}
}

void ChoisirCarte(TCarte * Joueur, int Position, int id1, int id2) //Position = (pépé/mémé...)
{
	TCarte * aux;
	TCarte * prec;
	int id;
	int trouve;
	int stop;
	
	aux = Joueur;
	prec = Joueur;

	printf("Voici vos cartes : \n" );
	AfficherCarte(Joueur);
	printf("Nous sommes sur la case : " );
	switch(Position)
	{
		case 1 :
			printf("Pépé");
		break;
				
		case 2 :
			printf("Mémé");
		break;
				
		case 3 :
			printf("Papa");
		break;
		
		case 4 :
			printf("Maman");
		break;
		
		case 5 :
			printf("Frérot");
		break;
		
		case 6 :
			printf("Soeurette");
		break;
		
		case 7 :
			printf("Bébé");
		break;
	}
	
	do
	{
		trouve = 0;
		printf("Laquelle de vos cartes voulez-vous jouez ? (indiquez son id) \n " );
		scanf("%d", &id);
		while ((aux!=NULL) && (trouve == 0))
		{
			if(aux->id == id)
			{
				trouve = 1;
				id1 = id;
                aux->position=Position;
				prec->Suivant = aux->Suivant;
				InsertionQueue(Plateau,aux);
			}
			else 
			{	
				prec = aux;
				aux = aux->Suivant;
			}
		}
		
		if( trouve == 0)
		{
			printf("Vous n'avez pas cette carte");
		}
	}
	while(trouve == 0);
	
	do
	{
		printf("Voulez vous jouez une deuxième carte ? \n (1: oui, 0: non" );
		scanf("%d", &stop);
	}
	while(stop<0 && stop>1 );
	
	if(stop == 1)
	{
		do
		{
			trouve = 0;
			printf("Laquelle de vos cartes voulez-vous jouez ? (indiquez son id) \n " );
			scanf("%d", &id);
			while ((aux!=NULL) && (trouve == 0))
			{
				if(aux->id == id)
				{
					trouve = 1;
					id2 = id;
                    aux->position=Position;
					prec->Suivant = aux->Suivant;
					InsertionQueue(Plateau,aux); // Pour l'instant insertion queue mais change en fonction de comment on gère le menteur
				}
				else 
				{	
					prec = aux;
					aux = aux->Suivant;
				}
			}
			
			if( trouve == 0)
			{
				printf("Vous n'avez pas cette carte");
			}
		}
		while(trouve == 0);
	}
	else
	{
		id2 = Position;	
	}
}	

void Menteur(int Reponse, int JoueurActif, int JoueurJuge) 
{
		do
		{
			printf("\n %d, est-ce que vous pensez que le joueur %d ment ? (1 : oui / 0 : non) \n",JoueurJuge,JoueurActif);
			scanf("%d", &Reponse);
		}
		while(Reponse<0 && Reponse>1 );
}	


void RamasserCarte(TCarte * JoueurActif,TCarte * JoueurJuge, TCarte * Plateau, int Position, int id1, int id2)
{
	TCarte * aux;
    TCarte * prec;

    prec = Plateau;
    aux = Plateau;

	if(id1 == Position && id2 == Position) //le joueur qui a dit menteur a faux et doit prend les cartes
	{
        while (aux->Suivant != NULL)
	    {
            if(aux->position>=Position)
            {
               aux->position=0; //remise à 0 de la position car la carte est dans la main du joueur
               prec->Suivant = aux->Suivant;
               InsertionTrie(JoueurJuge,aux);
            }
            else
            {
				prec = aux;
				aux = aux->Suivant;
            }
        }
	}
	else // le joueur qui a posé les cartes a menti et doit prendre les cartes
	{
        while (aux->Suivant != NULL)
	    {
            if(aux->position>=Position)
            {
               aux->position=0;  
               prec->Suivant = aux->Suivant;
               InsertionTrie(JoueurActif,aux);
            }
            else
            {
				prec = aux;
				aux = aux->Suivant;
            }
        }
	}
}







