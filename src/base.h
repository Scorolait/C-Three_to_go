#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/


																						/*CREATION STRUCTURES*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/


typedef struct token{
	int couleur;
	int forme;
	struct token *suivant;
	struct token *suivant_couleur;
	struct token *precedent_couleur;
	struct token *suivant_forme;
	struct token *precedent_forme;
} Tokens, *Liste;



/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/


																						/*ALLOUE ESPACE TOKEN*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/


/*Allouer notre token*/
Liste allouerToken(int couleur, int forme){
	Liste lst = NULL;
	lst= (Tokens*)malloc(sizeof(Tokens));
	
	if (lst == NULL)
		return NULL;

	/*valeur pour indentifier*/
	lst->couleur = couleur;
	lst->forme = forme;

	/*pour passer a l'element suivant*/
	lst->suivant = NULL;

	/*pour passer a l'element suivant par rapport à la forme ou la couleur*/
	lst->suivant_couleur = lst;
	lst->suivant_forme = lst;

	/*pour revenir a l'element precedent par rapport à la forme ou la couleur*/
	lst->precedent_forme= lst;
	lst->precedent_couleur= lst;

	return lst;

}


void libererListe(Liste *lst){
	/*Sert a libere notre liste prend chaque element 
	puis attribue a tmp notre *lst pour pouvoir passer au suivant */
	Liste tmp , initial = *lst;
	while ((*lst) != NULL && (*lst)->suivant != initial){
		tmp = *lst;
		*lst = (*lst)->suivant;
		free(tmp);
	}
	free((*lst));

}

void verifierListe(Liste lst){
	/*POur verifier les lelements*/
	int i;
	Liste initial = lst;

	for (i=0 ; lst != NULL && lst->suivant != initial ; lst = lst->suivant, i++){

		printf("n° : %d, couleur: %d, forme: %d\n",i, lst->couleur, lst->forme);
		printf("\n");
		
		printf("lst : %p // lst->precedent_forme : %p // lst->suivant_forme : %p\n",lst, lst->precedent_forme, lst->suivant_forme);
		printf("lst : %p // lst->precedent_couleur : %p // lst->suivant_couleur : %p\n",lst, lst->precedent_couleur, lst->suivant_couleur);
		
		printf("\n%p  %p\n",lst , lst->suivant);
		
		printf("\n");
	}

	printf("n° : %d, couleur: %d, forme: %d\n",i, lst->couleur, lst->forme);
	printf("\n");
	printf("lst : %p // lst->precedent_forme : %p // lst->suivant_forme : %p\n",lst, lst->precedent_forme, lst->suivant_forme);
	printf("lst : %p // lst->precedent_couleur : %p // lst->suivant_couleur : %p\n",lst, lst->precedent_couleur, lst->suivant_couleur);

	printf("\n%p et %p\n", lst, lst->suivant);
}


/************************************************************************************************************************************
*********************************************************PARTIE ALEATOIRE************************************************************
************************************************************************************************************************************/

int rand_a_b(int a, int b){
	srand(time(NULL));
    return rand()%(b-a) +a;
}






/************************************************************************************************************************************
*********************************************************INSERERE DANS LISTE************************************************************
************************************************************************************************************************************/

int insererEnTete(Liste *lst, int couleur, int forme){
	/*Cree un Token linsere en tete*/
 	Liste tmp;
 	tmp = allouerToken(couleur, forme);
 	if (tmp == NULL){
 		return 0;
 	}

 	tmp->suivant = (*lst);
 	(*lst) = tmp;

 	return 1;
 }


int insererEnFin(Liste *lst, int couleur, int forme){
	/*Parcous tout lisete jusqu'au avant dernier puis utilise insereEnTete*/
	Liste tmp = *lst; int i;

	for(;tmp != NULL && tmp->suivant != *lst; tmp = tmp->suivant);
	
	i = insererEnTete(&(tmp->suivant), couleur, forme);
	
	return i;
}


/************************************************************************************************************************************
*********************************************************CREE LIEN FORME COULEUR************************************************************
************************************************************************************************************************************
**************************************************************************************************************************************
*****************************************************************************************************************************************
**************************************************************************************************************************************/


/***************************************************************************************************************************************
**********************************************************Lien forme suivant precedent***************************************************/

void mettre_en_lien_forme(Liste *lst){
	/*sauvergarde_d pour garder le premier
	sauvergarde_f pour garde le dernier par rapport a forme*/
	Liste tmp = *lst, sauvegarde_d = NULL, sauvegarde_f = NULL;

	/*sert a verifier si on a deja fait cette forme*/
	int tab_forme[4]={-1,-1,-1,-1} , i, j = 0, veri = 0;
	if (tmp->suivant == *lst){
		tmp->precedent_forme = *lst;
		tmp->suivant_forme = *lst;
		return;
	}

	while (tmp != NULL && tmp->suivant != *lst){
		/*tmp2 Pour deuxieme boucle qui permet de voir que les lien des formes du tmp*/
		Liste tmp2 = tmp;
		sauvegarde_d = tmp;
		sauvegarde_f =NULL;

		for (i = 0; i < 4; i++){
			/*verifier si on a deja fait cette forme*/
			if (tmp->forme == tab_forme[i]){
				tmp = tmp->suivant;
				break;
			}
		}		

		/*On met dans le tableau puis on dit veri = 1 puisque premier fois*/
		if (i >= 4){
			tab_forme[j] = tmp->forme;
			veri = 1;
			j++;
		}
		

		if (veri == 1){
		
			for (; tmp2 != NULL && tmp2->suivant != *lst; tmp2 = tmp2->suivant){
				
				/*Tmp bouge de lien en lien par rapport a forme*/
				if (tmp != tmp2 && tmp->forme == tmp2->forme){

					tmp->suivant_forme = tmp2;
					tmp2->precedent_forme = tmp;

					tmp = tmp2;

					sauvegarde_f = tmp2;
					}

			}
			if (tmp2->forme == sauvegarde_d->forme)
				sauvegarde_f = tmp2;

			if (tmp == sauvegarde_d && tmp->forme != tmp2->forme && tmp2->suivant == *lst){
				tmp->suivant_forme = tmp;
				tmp->precedent_forme = tmp;
			}

			if (tmp2 != NULL && tmp2->suivant == *lst && tmp->forme == tmp2->forme){
				tmp2->precedent_forme = tmp;
				tmp2->suivant_forme = sauvegarde_d;
				sauvegarde_d->precedent_forme = tmp2;
				tmp->suivant_forme = tmp2;
			}

			/*Pour relie dernier et premier*/
			if (sauvegarde_f != NULL){
				sauvegarde_d->precedent_forme = sauvegarde_f;
				sauvegarde_f->suivant_forme = sauvegarde_d;

				tmp = sauvegarde_d;
				
			}

			tmp = tmp->suivant;
			veri = 0;
		}
	}
}


/***************************************************************************************************************************************
**********************************************************Lien couleur suivant precedent***************************************************/

void mettre_en_lien_couleur(Liste *lst){
	/*sauvergarde_d pour garder le premier
	sauvergarde_f pour garde le dernier par rapport a couleur*/
	Liste tmp = *lst, sauvegarde_d = NULL, sauvegarde_f = NULL;

	/*sert a verifier si on a deja fait cette couleur*/
	int tab_couleur[4]={-1,-1,-1,-1} , i, j = 0, veri = 0;
	if (tmp->suivant == *lst){
		tmp->precedent_couleur = *lst;
		tmp->suivant_couleur = *lst;
		return;
	}

	while (tmp != NULL && tmp->suivant != *lst){
		/*tmp2 Pour deuxieme boucle qui permet de voir que les lien des couleurs du tmp*/
		Liste tmp2 = tmp;
		sauvegarde_d = tmp;
		sauvegarde_f =NULL;

		for (i = 0; i < 4; i++){
			/*verifier si on a deja fait cette couleur*/
			if (tmp->couleur == tab_couleur[i]){
				tmp = tmp->suivant;
				break;
			}
		}		

		/*On met dans le tableau puis on dit veri = 1 puisque premier fois*/
		if (i >= 4){
			tab_couleur[j] = tmp->couleur;
			veri = 1;
			j++;
		}
		

		if (veri == 1){
		
			for (; tmp2 != NULL && tmp2->suivant != *lst; tmp2 = tmp2->suivant){
				
				/*Tmp bouge de lien en lien par rapport a couleur*/
				if (tmp != tmp2 && tmp->couleur == tmp2->couleur){

					tmp->suivant_couleur = tmp2;
					tmp2->precedent_couleur = tmp;

					tmp = tmp2;

					sauvegarde_f = tmp2;
					}

			}
			if (tmp2->couleur == sauvegarde_d->couleur)
				sauvegarde_f = tmp2;

			if (tmp == sauvegarde_d && tmp->couleur != tmp2->couleur && tmp2->suivant == *lst){
				tmp->suivant_couleur = tmp;
				tmp->precedent_couleur = tmp;
			}

			if (tmp2 != NULL && tmp2->suivant == *lst && tmp->couleur == tmp2->couleur){
				tmp2->precedent_couleur = tmp;
				tmp2->suivant_couleur = sauvegarde_d;
				sauvegarde_d->precedent_couleur = tmp2;
				tmp->suivant_couleur = tmp2;
			}

			/*Pour relie dernier et premier*/
			if (sauvegarde_f != NULL){
				sauvegarde_d->precedent_couleur = sauvegarde_f;
				sauvegarde_f->suivant_couleur = sauvegarde_d;

				tmp = sauvegarde_d;
				
			}

			tmp = tmp->suivant;
			veri = 0;
		}
	}
}




/***************************************************************************************************************************************
**********************************************************Lien suivant + forme couleur***************************************************/



/*Faire en sorte que notre liste soit circulaire
utilise i pour differencier quand on utilise insereEnTete ou on devoir rentre dasn if
sinon passe directement aux foctions mettre_en_lien_couleur et mettre_en_lien_forme*/
void mettre_en_lien(Liste *lst, int i){



	if (i == 0){
		/*Tout d'abord verifie si la liste est nul quittela fonction*/
		Liste tmp = *lst, initial;
		if (tmp == NULL)
			return;

		/*Verifie si pour linstant on a qun seul element car
		on creant celleule suivant est nul. Attribue adresse de premier valeur
		pour rendre circulaire*/
		if (tmp->suivant == NULL){
			tmp->suivant = *lst;
		}

		/*passe directement a suivant on a pas encore la nouvelle l'adresse
		or je compare avec la premier de ce quon avait puisque
		a chaque fois que je rajoute avant cetait mon initial le premier element
		je recherche jusqua la fin pour retouver le premier element*/
		tmp = tmp->suivant;
		initial = tmp;
		for(; tmp->suivant != NULL && tmp->suivant != initial && tmp != tmp->suivant; tmp = tmp->suivant);
		tmp->suivant = *lst;
	}


	mettre_en_lien_couleur(lst);
	mettre_en_lien_forme(lst);

}


/**********************************************************************************************************************************************************
***********************************************************************************************************************************************************
*********************************************************FIN DE CREATION LIEN******************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************/


/*Sert a extraire une balise de notre liste*/
Liste Extraire(Liste *lst){
	if (*lst == NULL)
		return NULL;
	Liste tmp = *lst;
	*lst = (*lst)->suivant;
	tmp->suivant = NULL;

	return tmp;
}

/**********************************************************************************************************************************************************
***********************************************************************************************************************************************************
*********************************************************DEPLACER LES BALISES******************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************/


int compte_cellule_deplacer(Liste lst, int forme, int couleur){
	Liste initial = NULL;
	int j = 0;
	if (forme != -1)
	{
		for( initial = lst; lst->suivant != initial; lst = lst->suivant)
		{
			if(lst->forme == forme)
				j+=1;
		}
		if(lst->forme == forme)
			j+=1;
	}
	else 
	{
		for( initial = lst; lst->suivant != initial; lst = lst->suivant)
		{
			if(lst->couleur == couleur)
				j+=1;
		}
		if(lst->couleur == couleur)
			j+=1;
	}

	return j;
}

void nouveau_depart(Liste *lst, Liste initial){
	/*Si efface premier balise*/
	Liste tmp = *lst;
	for(; tmp->suivant != initial; tmp = tmp->suivant);

	tmp->suivant = *lst;
}

void deplacer_forme(Liste *lst, int i){
	Liste parcourt = *lst, sauvegarde = NULL, sauvegarde2 = NULL, recherche = NULL,extr1 = *lst, extr2 = *lst;
	/*compte nombre de cellules a deplacer*/
	int j = compte_cellule_deplacer(*lst, i, -1), cp;

	if (parcourt->forme == i)
	{	/*si que que un token de ctte forme fait rien*/
		if (parcourt == parcourt->suivant_forme)
			return;

		/*si je dois deplacer la premier cellule*/
		sauvegarde2 = parcourt->suivant_forme;
		sauvegarde = parcourt->suivant;
		for (recherche = parcourt; recherche->suivant != sauvegarde2; recherche = recherche->suivant);

		
		/*recherche la prochaine avec la meme forme*/

		/*extrait la premier et la place juste avant la deuxieme si la premier et deuxieme
		se suivent pas*/

	if ((*lst)->forme != (*lst)->suivant->forme)
	{
		extr1 = Extraire( lst );
		nouveau_depart(lst, extr1);
		extr1->suivant = sauvegarde2->suivant;
		sauvegarde2->suivant = extr1;
		mettre_en_lien(lst, 1);
	}
		

		/*extrait la deuxieme et place au debut*/
		extr2 = Extraire( &(recherche->suivant) );
		extr2->suivant = *lst;
		*lst = extr2;

		
		mettre_en_lien(lst, 0);
		/*recommence a partir de lancienne premiere cellule*/
		sauvegarde = NULL;
		sauvegarde2 = NULL;
		parcourt = *lst;
		j-=1;

	}

	/*tant que jai pas echange tout les cellules reste dans la boucle*/
	for(cp = 0; parcourt->suivant != *lst && cp < j-1; parcourt = parcourt->suivant)
	{

		if( parcourt->suivant->forme == i){
			/*si trouve la premiere je garde puis je garde directement la deuxime*/
			
			sauvegarde = parcourt;
			sauvegarde2 = parcourt->suivant->suivant_forme;
		}

		if(sauvegarde != NULL && sauvegarde2 != NULL)
		{
			/*extrait la premiere cellule met apres la deuxieme*/
			extr1 = Extraire( &(sauvegarde->suivant) );
			extr1->suivant = sauvegarde2->suivant;
			sauvegarde2->suivant = extr1;

			/*recherhe la cellule juste avant la deuxieme*/
			for(recherche = parcourt; recherche->suivant != sauvegarde2; recherche = recherche->suivant);


			/*extrait la deuxieme puis met ou il avait la premiere*/
			extr2 = Extraire( &(recherche->suivant) );
			extr2->suivant = sauvegarde->suivant;
			sauvegarde->suivant = extr2;
			/*resout les lien et recommence*/
			mettre_en_lien(lst, 1);
			cp++;
			sauvegarde = NULL;
			sauvegarde2 = NULL;

		}

	}
	mettre_en_lien(lst, 1);
	
}

void deplacer_couleur(Liste *lst, int i){
	Liste parcourt = *lst, sauvegarde = NULL, sauvegarde2 = NULL, recherche = NULL,extr1 = *lst, extr2 = *lst;
	/*compte nombre de cellules a deplacer*/
	int j = compte_cellule_deplacer(*lst, -1, i), cp;

	if (parcourt->couleur == i)
	{	
		/*si que que un token de ctte forme fait rien*/
		if (parcourt == parcourt->suivant_couleur)
			return;
		/*si je dois deplacer la premier cellule*/
		sauvegarde2 = parcourt->suivant_couleur;
		for (recherche = parcourt; recherche->suivant != sauvegarde2; recherche = recherche->suivant);
		sauvegarde = recherche;
		
		/*recherche la prochaine avec la meme couleur*/

		/*extrait la premier et la place juste avant la deuxieme si la premier et deuxieme
		se suivent pas*/

	if ((*lst)->couleur != (*lst)->suivant->couleur)
	{
		extr1 = Extraire( lst );
		nouveau_depart(lst, extr1);
		extr1->suivant = sauvegarde2->suivant;
		sauvegarde2->suivant = extr1;
		mettre_en_lien(lst, 1);
	}
		

		/*extrait la deuxieme et place au debut*/
		extr2 = Extraire( &(recherche->suivant) );
		extr2->suivant = *lst;
		*lst = extr2;


		mettre_en_lien(lst, 0);
		/*recommence a partir de lancienne premiere cellule*/
		sauvegarde = NULL;
		sauvegarde2 = NULL;
		parcourt = *lst;
		j-=1;

	}

	/*tant que jai pas echange tout les cellules reste dans la boucle*/
	for(cp = 0; parcourt->suivant != *lst && cp < j-1; parcourt = parcourt->suivant)
	{

		if( parcourt->suivant->couleur == i){
			/*si trouve la premiere je garde puis je garde directement la deuxime*/
		
			sauvegarde = parcourt;
			sauvegarde2 = parcourt->suivant->suivant_couleur;
		}

		if(sauvegarde != NULL && sauvegarde2 != NULL)
		{
			/*extrait la premiere cellule met apres la deuxieme*/
			extr1 = Extraire( &(sauvegarde->suivant) );
			extr1->suivant = sauvegarde2->suivant;
			sauvegarde2->suivant = extr1;

			/*recherhe la cellule juste avant la deuxieme*/
			for(recherche = parcourt; recherche->suivant != sauvegarde2; recherche = recherche->suivant);


			/*extrait la deuxieme puis met ou il avait la premiere*/
			extr2 = Extraire( &(recherche->suivant) );
			extr2->suivant = sauvegarde->suivant;
			sauvegarde->suivant = extr2;
			/*resout les lien et recommence*/
			mettre_en_lien(lst, 1);
			cp++;
			sauvegarde = NULL;
			sauvegarde2 = NULL;

		}

	}
	mettre_en_lien(lst, 1);
}


/**********************************************************************************************************************************************************
***********************************************************************************************************************************************************
*********************************************************FIN DE DEPLACEMENT BALISE******************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************/





/**********************************************************************************************************************************************************
***********************************************************************************************************************************************************
*********************************************************EFFACER LES BALISES******************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************
***********************************************************************************************************************************************************/


Liste point_depart(Liste *lst, int *val1, int *val2){
	/*Verifier ou on doit commencer a effacer*/

	Liste tmp = *lst, initial = *lst;
	int i, j;
	
	for(i = 1, j = 1; tmp->suivant != *lst && tmp->suivant->suivant != *lst; tmp = tmp->suivant)
	{
		if (tmp->forme == tmp->suivant->forme && tmp->suivant->forme == tmp->suivant->suivant->forme)
		{
			i = 3;
			break;
		}

		if (tmp->couleur == tmp->suivant->couleur && tmp->suivant->couleur == tmp->suivant->suivant->couleur)
		{
			j = 3;
			break;
		}

		initial = tmp;
		
	}

	/*renvoie null si riean a efface*/
	if (i < 3 && j<3)
		return NULL;

	*val1 = i;
	*val2 = j;

	/*renvoie ou commence*/
	return initial;
}

int combien_effacer(int *val1, int *val2, int *veri, Liste tmp, Liste initial){
	int forme = tmp->suivant->forme, couleur = tmp->suivant->couleur, i = 0, j = 0;
	if (*val1 == 3)
	{
		if (tmp->forme == forme){
			i += 1;
			*veri = 1;
		}

		for (; tmp->suivant->forme == forme && tmp->suivant != initial; tmp = tmp->suivant, i++);
	}

	else
	{
		if (tmp->couleur == couleur){
			j += 1;
			*veri = 1;
		}

		for (; tmp->suivant->couleur == couleur && tmp->suivant != initial; tmp = tmp->suivant, j++);
	}
	*val1 = i; *val2 = j;

	return i + j;

}

int compte_cellules(Liste lst){
	int i;
	Liste initial = NULL;
	for(i = 1, initial = lst; lst->suivant != initial; lst = lst->suivant, i++);

	return i;
}

/* effacer un élément en liste et libérer la mémoire */
int efface(Liste *lst){
	int i, j, cp, veri = 0, total = 0, total_token = 0;
	Liste tmp = point_depart(lst, &i, &j), tmp2 = NULL, initial = *lst;


	if (tmp == NULL)
		return -1;

	total = combien_effacer(&i, &j, &veri, tmp, initial);
	total_token = compte_cellules( initial );

	if (total == total_token)
	{
		return total;
	}

	else{
		for(cp = 0; tmp->suivant != initial  && cp < total; cp++)
		{	
			if (veri == 1) {
				tmp2 = Extraire( lst );
				free( tmp2 );
				tmp = *lst;
			}
				
			else{
				tmp2 = Extraire(&(tmp->suivant));
				free( tmp2 );
			}

		}
		if (veri == 1)
			nouveau_depart(&tmp, initial);

		mettre_en_lien(&tmp, 1);
	}
	return total;

}

int analyse_et_efface(Liste *lst){
	int cp = 0,score = 0, total_token = compte_cellules( *lst );


	for(; cp != -1; score += cp)
	{
		cp = efface( lst );
		if (cp == total_token)
		{
			libererListe( lst );
			*lst = NULL;
			return score + cp;
		}
	}

	return score + 1;

}
