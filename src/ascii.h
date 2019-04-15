#include "base.h"


void viderBuffer() {
	int c = 0;
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}

void afficherTab(int taille, int tab[]) {
	int i;
	printf("[ ");
	for (i = 0; i < taille; i++) {
		printf("%d", tab[i]);
		if (i < taille-1)
			printf(", ");
	}
	printf(" ]\n");
}


/*
*************************************************************
*************************************************************

FONCTIONS TRAVAILLANT SUR LES 5 TOKENS GÉNÉRÉS ALÉATOIREMENT

*************************************************************
*************************************************************
*/

void genererTokenAleatoire(int taille, int tab_couleur[], int tab_forme[]) {
	int couleur = 0, forme = 0, i;

	for (i = 0; i < taille; i++) {
		couleur = rand()%4;
		tab_couleur[i] = couleur;
	}

	for (i = 0; i < taille; i++) {
		forme = rand()%4;
		tab_forme[i] = forme;
	}
}

/*
Couleur 0 : rouge
Couleur 1 : vert
Couleur 2 : bleu
Couleur 3 : jaune

Forme 0 : cercle
Forme 1 : carré
Forme 2 : triangle
Forme 3 : diamant
*/
void afficheToken(int forme, int couleur) {
	switch(forme) {
		case 0: printf("0"); break;
		case 1: printf("C"); break;
		case 2: printf("T"); break;
		case 3: printf("D");
	}

	printf(".");

	switch(couleur) {
		case 0: printf("r"); break;
		case 1: printf("v"); break;
		case 2: printf("b"); break;
		case 3: printf("j");
	}
}

void afficheCinqTokens(int tab_couleur[], int tab_forme[], int taille) {
	int i;

	printf("=== Les Tokens suivants ===\n");
	for (i = 0; i < taille-1; i++) {
		afficheToken(tab_forme[i], tab_couleur[i]);
		printf("\n");
	}
	printf("------------------------\nLe Token à insérer : ");
	afficheToken(tab_forme[taille-1], tab_couleur[taille-1]);
	printf("\n------------------------\n");
}


/* décale les éléments du tableau vers la droite
en générant un nombre aléatoire entre 0 et 3 qui remplace l'élément indice 0 qui est décalé vers la droite */
void decaleElemTab(int tab[], int taille) {
	int actuel, suivant, tmp;
	int tampon = rand()%4;

	for (actuel = 0; actuel < taille; actuel+=2) {
		suivant = actuel+1;
		tmp = tab[suivant];
		tab[suivant] = tab[actuel];
		tab[actuel] = tampon;
		tampon = tmp;
	}
}



/*
*************************************************************
*************************************************************

			FONCTIONS POUR LA MISE EN PLACE DU JEU

*************************************************************
*************************************************************
*/

int compteToken(Liste lst) {
	int i;
	Liste initial = lst;
	for (i = 1; lst != NULL && lst->suivant != initial; lst = lst->suivant, i++);
	return i;
}

/* demande à l'utilisateur s'il veut insérer le Token à gauche ou à droite 
   1 : gauche
   0 : droite
   s'il veut faire une rotation de Tokens
   R : pour la rotation
   Q : quitter */
int demandeInsertion() {
	char choix;
	printf("Votre choix : ");
	scanf("%c", &choix);
	viderBuffer();

	while (choix != 'G' && choix != 'D' && choix != 'g' && choix != 'd' && choix != 'R' && choix != 'r' && choix != 'Q' && choix != 'q') {
		printf("Votre choix : ");
		scanf("%c", &choix);
		viderBuffer();
	}

	if (choix == 'G' || choix == 'g')
		return 1;
	else if (choix == 'D' || choix == 'd')
		return 0;
	else if (choix == 'R' || choix == 'r')
		return 2;
	else
		return -1;
}

void afficheListeToken(Liste lst) {
	Liste initial = lst;
	int i;

	printf("\n=== Les Tokens placés ===\n");
	
	for (i = 0; lst != NULL && lst->suivant != initial; lst = lst->suivant, i++) {
		afficheToken(lst->forme, lst->couleur);
		printf(" --> ");
	}

	afficheToken(lst->forme, lst->couleur);
	printf("\n\n");
}

/*  1 : formes
	0 : couleurs */
int choix_rotation() {
	char c;
	printf("F : rotation des formes\n");
	printf("C : rotation des couleurs\n");
	printf("Votre choix : ");
	scanf("%c", &c);
	viderBuffer();

	while (c != 'F' && c != 'f' && c != 'C' && c != 'c') {
		printf("Votre choix : ");
		scanf("%c", &c);
		viderBuffer();
	}

	if (c == 'F' || c == 'f')
		return 1;
	else
		return 0;
}

/* le numéro de couleur ou forme */
int num_rotation() {
	int c;
	printf("Entrez le numéro : ");
	scanf("%d", &c);
	viderBuffer();

	while (!(c >= 0 && c <= 3)) {
		printf("Entrez le numéro : ");
		scanf("%d", &c);
		viderBuffer();
	}
	return c;
}

void menu() {
	int a;
	printf("\n=== Touches ===\n");
	printf("\nG : placer le Token à gauche\n");
	printf("D : placer le Token à droite\n");
	printf("R : rotation de Tokens\n");
	printf("Q : quitter\n");
	printf("\nEntrez une touche pour continuer : ");
	scanf("%d", &a);
	viderBuffer();
}

/* permet le fonctionnement du jeu */
void jeu(int tab_couleur[], int tab_forme[], int taille) {
	Liste lst = NULL;
	int choix, rotation, no_rotation;
	int nb = 0, nb_tokens = compteToken(lst);
	int score = 0, efface;

	menu();
	/* 10 tokens au max dans la liste */
	while (nb_tokens < 10) {
		printf("\n\n\n\n\n");
		afficheCinqTokens(tab_couleur, tab_forme, taille);
		printf("\n");
		choix = demandeInsertion();

		/* si le choix est "q" */
		if (choix == -1)
			break;

		/* si c'est le premier token à insérer */
		else if (nb == 0) {
			insererEnTete(&lst, tab_couleur[taille-1], tab_forme[taille-1]);
			mettre_en_lien(&lst, 0);
			nb++;

			decaleElemTab(tab_couleur, taille);
			decaleElemTab(tab_forme, taille);
		}

		else {
			if (choix == 1) {
				insererEnTete(&lst, tab_couleur[taille-1], tab_forme[taille-1]);
				mettre_en_lien(&lst, 0);

				decaleElemTab(tab_couleur, taille);
				decaleElemTab(tab_forme, taille);
			}

			else if (choix == 0) {
				insererEnFin(&lst, tab_couleur[taille-1], tab_forme[taille-1]);
				mettre_en_lien(&lst, 1);

				decaleElemTab(tab_couleur, taille);
				decaleElemTab(tab_forme, taille);
			}

			else {
				printf("\n");
				rotation = choix_rotation();
				no_rotation = num_rotation();
				if (rotation == 1)
					deplacer_forme(&lst, no_rotation);
				else
					deplacer_couleur(&lst, no_rotation);
			}
		}

		efface = analyse_et_efface(&lst);
		if (efface != -1)
			score = score + efface;
		nb_tokens = compteToken(lst);
		afficheListeToken(lst);
	}
	printf("\nScore : %d\n", score);
	libererListe(&lst);
}

void lancement_jeu() {
	int tab_couleur[5] = {0}, tab_forme[5] = {0};
	int nb = 5;

	srand(time(NULL));
	genererTokenAleatoire(nb, tab_couleur, tab_forme);

	jeu(tab_couleur, tab_forme, nb);
}