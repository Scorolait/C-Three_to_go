#include "base.h"
#include "option_edit.h"



																						/*CREATION STRUCTURES*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/


typedef struct CASE_DEPART
{
	int x1;
	int x2;
	int largeur_y;
	int decalage[4];
	char* message[4];

}Case_depart;

typedef struct UNE_FIGURE_COULEUR_ALEATOIRE
{
	int x;
	int forme;
	int couleur;
}Fig_Coul_aleatoire;

typedef struct  FIGURES_COULEURS_ALEATOIRE
{
	Fig_Coul_aleatoire tab[5];
	int y;
	int largeur;
	
}FC_aleatoire;

typedef struct CASE_INSERTION_UN_COTE
{
	int x1;

}Cote_insertion;

typedef struct CASES_INSERTION
{
	Cote_insertion tab[2];
	int x2;
	int y1;
	int y2;
	
}Cases_insertion;

typedef struct CASES_DEPLACEMENT
{
	int x1;
	int x2;
	int y1[2];
	int y2;
	
}Cases_deplacement;

typedef struct UNE_FORME_GEOMETRIQUE
{
	int x;
	int couleur;
	int forme;

}Figure;

typedef struct FORMES_GEOMETRIQUES
{
	Figure tab[30];
	Liste lst;
	int nb_ele;
	int distance;
	int y;
	int case_clique;
	
}Geometrie;




/**********************************************************INITIALISATION DE STRUCTURES************************************************************************/

/* FONCTIONS POUR GÉNÉRER LES 5 TOKENS ALÉATOIREMENT */
void initialisation_figure_couleur_aleatoire(FC_aleatoire *fc,int taille_x, int taille_y, int largeur){
	fc->y = taille_y; fc->largeur = largeur;
	int a = -1,b = -1, i;
	srand(time(NULL));
	for (i = 0; i < 5; i++)
	{
		a = rand()%4;
		b = rand()%4;
		fc->tab[i].x = taille_x - 2 * largeur *( 5 - i);
		fc->tab[i].forme = a;
		fc->tab[i].couleur = b;

	}

}

/* lorsqu'un token est placé dans la liste, permet de générer un nouveau token en décalant les 4 autres tokens */
void decalage_figure_couleur_aleatoire(FC_aleatoire *fc, int taille_x, int taille_y, int largeur){
	Fig_Coul_aleatoire temp1 = fc->tab[0], temp2;
	fc->y = taille_y; fc->largeur = largeur;
	int i;


	for(i = 1; i < 5; i++)
	{
		temp2 = fc->tab[i];
		fc->tab[i] = temp1;
		temp1 = temp2;

	}

	fc->tab[0].forme = rand()%4;
	fc->tab[0].couleur = rand()%4;

	for(i = 0;i < 5; i++)
		fc->tab[i].x = taille_x - 2 * largeur *( 5 - i);
}

/* coordonnées des onglets du menu */
Case_depart initialisation_case_depart(int taille_x, int taille_y){

	Case_depart cases;
	int i;
	cases.message[0] = "COMMENCER";
	cases.message[1] = "AIDE";
	cases.message[2] = "EDITER";
	cases.message[3] = "QUITTER";

	cases.x1 = taille_x/10; 
	cases.x2 = taille_x - (2* cases.x1);

	cases.largeur_y = taille_y/10;
	cases.decalage[0] = cases.largeur_y;

	for (i = 1; i <= 3; i++)
		cases.decalage[i] = cases.decalage[i - 1] + 2 * cases.largeur_y;

	return cases;

}

Cases_insertion initialisation_case_insertion(int taille_x, int taille_y, int largeur){
	int hauteur = taille_y/10;
	Cases_insertion points;

	points.tab[0].x1 = taille_x;	points.tab[1].x1 = taille_x + 2*largeur;
	points.x2 = largeur;

	points.y1 = taille_y - hauteur;
	points.y2 = hauteur;	
	
	return points;
}

Cases_deplacement initialisation_case_deplacement(Geometrie geo, int largeur){
	Cases_deplacement dep;
	dep.x1 = geo.tab[geo.case_clique].x;
	dep.x2 = largeur;

	dep.y1[0] = geo.y - (1.5) * largeur;
	dep.y1[1] = geo.y + (1.5) * largeur;
	dep.y2 = largeur;

	return dep;
}

int definir_point_depart(Geometrie geo, int largeur){
	Liste initial; int i;

	for (initial = geo.lst, i = 0; geo.lst->suivant != initial; geo.lst = geo.lst->suivant, i++);

	i = i * largeur;

	return i;

}

/* insertion de tokens dans la liste */
void attribue_une_valeur_geometrique(int veri, int couleur, int forme, Geometrie *geo){

	if (geo->nb_ele <= 0){
		insererEnTete(&(geo->lst), couleur, forme);
		mettre_en_lien(&(geo->lst), 0);
		geo->nb_ele = 1;
		return;

	}

	if (veri == 1)
	{

		insererEnTete(&(geo->lst), couleur, forme);
		mettre_en_lien(&(geo->lst), 0);


	}
	else 
	{

		insererEnFin(&(geo->lst), couleur, forme);
		mettre_en_lien(&(geo->lst), 1);

	}
	geo->nb_ele += 1;
}

/*********************************************************FIN DE INITIALISATION DE STRUCTURES******************************************************************/



																	/*FIN DE CREATION DE STRUCTURES*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/




																	/*GESTION DES SONS*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/

MLV_Music* music_jeu(char* nom_music ){
	MLV_init_audio( );

	MLV_Music* music = MLV_load_music( nom_music );


	
	MLV_play_music( music, 1.0, -1 );


	return music;

}

void arrete_music(MLV_Music* music){
	MLV_stop_music();

	MLV_free_music( music );
	MLV_free_audio();

}

MLV_Sound* initialise_bruit_sonores(char* nom_son){
	MLV_Sound* sound = MLV_load_sound( nom_son );
	return sound;

}

void effets_sonores(MLV_Sound* sound){
	MLV_play_sound( sound, 1.0 );
}

void libere_son(MLV_Sound* sound){
	MLV_stop_all_sounds();

	MLV_free_sound( sound );

}
																	/*FIN DE GESTION DES SONS*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/




																		/*MENU DE DEPART*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/

void menu_depart(Case_depart cases){
	int i;

	MLV_clear_window(MLV_COLOR_BLACK);

	for(i = 0; i < 4; i++)
	{
		MLV_draw_text_box(
			cases.x1, cases.decalage[i],
			cases.x2, cases.largeur_y,
			cases.message[i], 0,
			MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE,
			MLV_TEXT_CENTER,
			MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
			);
	}

	MLV_actualise_window();
}

/* permet de vérifier si les coordonnées du curseur sont positionnées sur un onglet cliquable */
int verification_position_souris(Case_depart cases, int x, int y, int *veri){
	int i, retour = 0;
	for(i = 0; i<4; i++)
	{
		if ((cases.x1 <= x && x <= cases.x2) && (cases.decalage[i] <= y && y <= cases.decalage[i] + cases.largeur_y))
		{

			MLV_draw_text_box(
				cases.x1, cases.decalage[i],
				cases.x2, cases.largeur_y,
				cases.message[i], 0,
				MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_DARK_BLUE,
				MLV_TEXT_CENTER,
				MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
			);
			retour = 1;
			*veri = i;
		}
		else
		{
			MLV_draw_text_box(
			cases.x1, cases.decalage[i],
			cases.x2, cases.largeur_y,
			cases.message[i], 0,
			MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_WHITE,
			MLV_TEXT_CENTER,
			MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
			);
		}
		
	}
	
	return retour;
}

void cliquer_sur_menu_depart(Case_depart cases, int *veri){
	MLV_Sound* sound1 = initialise_bruit_sonores( "SONS_MUSIC/SONS/plastic_crash.ogg" );
	while (1){
		MLV_clear_window(MLV_COLOR_BLACK);
		int x, y, i;
		MLV_get_mouse_position( &x, &y );
		i = verification_position_souris(cases, x, y, veri);
		MLV_actualise_window();
		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED && i == 1)
			break;
		
	}
	effets_sonores( sound1 );
	MLV_wait_seconds( 1 );
	libere_son( sound1 );
}

int gestion_menu_depart(Case_depart cases){
	int veri;

	menu_depart(cases);
	cliquer_sur_menu_depart(cases, &veri);

	return veri;
}





																	/*FIN DE MENU DE DEPART*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/


																		/*FIGURES GEOMETRIQUES*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/


/*************************************************************************DESSIN DE FIGURES GEOMETRIQUES*******************************************************/

void flecher_cote_gauche(int taille_x, int taille_y, int largeur, int hauteur){
	int x1, x2, y1, y2;
	x1 = (taille_x + taille_x/3) + largeur/2 - largeur/6;
	x2 = x1 + largeur/2 - largeur/6;

	y1 = y2 = taille_y - hauteur/2;
	MLV_draw_line(
		x1, y1,
		x2, y2,
		MLV_COLOR_WHITE
	);

	MLV_draw_line(
		x1 , y1,
		x1 + largeur/20, taille_y - hauteur/(1.5),
		MLV_COLOR_WHITE
		);

	MLV_draw_line(
		x1 , y1,
		x1 + largeur/20, taille_y - hauteur/3,
		MLV_COLOR_WHITE
		);
}

void flecher_cote_droit(int taille_x, int taille_y, int largeur, int hauteur){
	int x1, x2, y1, y2;
	x1 = ((taille_x + taille_x/3) + 2*largeur) + largeur/2 - largeur/6;
	x2 = x1  + largeur/2 - largeur/6;

	y1 = y2 = taille_y - hauteur/2;
	MLV_draw_line(
		x1, y1,
		x2, y2,
		MLV_COLOR_WHITE
	);

	MLV_draw_line(
		x2 , y1,
		x2 - largeur/20, taille_y - hauteur/(1.5),
		MLV_COLOR_WHITE
		);

	MLV_draw_line(
		x2 , y1,
		x2 - largeur/20, taille_y - hauteur/3,
		MLV_COLOR_WHITE
		);
}

void dessiner_fleches(int taille_x, int taille_y, int largeur, int hauteur){
	flecher_cote_gauche	(taille_x, taille_y, largeur, hauteur);
	flecher_cote_droit(taille_x, taille_y, largeur, hauteur);
}

/* les fonctions suivantes permettent de dessiner les Tokens */
void dessin_case_insertion_debut_fin(int taille_x,int taille_y, Cases_insertion points, MLV_Color couleur1, MLV_Color couleur2){
	int i;
	MLV_Color couleur_tab[2] = {couleur1, couleur2};

	for (i = 0; i < 2; i++)
	{
		MLV_draw_filled_rectangle(
		points.tab[i].x1, points.y1,
		points.x2, points.y2, 
		couleur_tab[i]
		);
	}
	dessiner_fleches(taille_x, taille_y, points.x2, points.y2);
}


void dessiner_figures_avant_insertion(FC_aleatoire fc, Coul_def def){
	int i;
	for(i = 0; i < 5; i++)
		figures(fc.tab[i].x, fc.y, fc.largeur, fc.tab[i].forme, fc.tab[i].couleur, def);
}

void dessiner_case_cercle_deplacement(Geometrie geo, Cases_deplacement *dep, int largeur, Coul_def def){
	Couleur paint = initialisation_couleur( def.base );
	*dep = initialisation_case_deplacement(geo, largeur);
	MLV_draw_filled_rectangle(
			dep->x1, dep->y1[0],
			dep->x2, dep->y2,
			paint.couleur[geo.tab[geo.case_clique].couleur]
			);

	MLV_draw_filled_circle(
			dep->x1 + dep->x2/2, dep->y1[1] + dep->x2/2,
			dep->x2/2,
			MLV_COLOR_WHITE
			);

}

/*********************************************************************FIN DESSIN DE FIGURES GEOMETRIQUES*******************************************************/

/*********************************************************************AFFICHAGE SCORE**************************************************************************/
void affiche_score(int taille_x, int taille_y, int score){
	MLV_draw_text(taille_x, taille_y, 
		"SCORE : %d", 
		MLV_COLOR_RED,
		score);
}

/*****************************************************************FIN AFFICHAGE SCORE**************************************************************************/


/*********************************************************************AFFICHAGE TEMPS**************************************************************************/
int affiche_temps(int taille_x, int taille_y, int time){
	int elapsed_time = MLV_get_time();
	int minutes = 0, secondes, temps_base = 0;

	secondes = (elapsed_time - time)/1000;
	if ((elapsed_time - time)/1000 - temps_base> 60*( minutes+1 ))
	{
		minutes += 1;
		temps_base = 60 * minutes;
	}

	if (secondes - temps_base < 10)
	{
		MLV_draw_text(taille_x, taille_y, 
		"TEMPS : 0%d : 0%d", 
		MLV_COLOR_RED,
		minutes, secondes - temps_base);
		return (elapsed_time - time)/1000;
	}

	MLV_draw_text(taille_x, taille_y, 
		"TEMPS : 0%d : %d", 
		MLV_COLOR_RED,
		minutes, secondes - temps_base);

	return (elapsed_time - time)/1000;

}


void effacer_temps(int taille_x, int taille_y){
		MLV_draw_filled_rectangle(
		0, 0,
		taille_x * 4, taille_y + taille_y/3,
		MLV_COLOR_BLACK);
	}
/*****************************************************************FIN AFFICHAGE TEMPS**************************************************************************/



/*********************************************************************DEBUT GESTION DE FIGURES GEOMETRIQUES****************************************************/

/* permet de vérifier si l'utilisateur clique sur la flèche de gauche ou droite pour insérer un Token */
int deuxieme_verification_position_souris(Cases_insertion points, int x, int y, int taille_x, int taille_y){
	int veri = 0;
	
	if ((points.tab[0].x1 <= x && x <= points.tab[0].x1 + points.x2) && (points.y1 <= y && y <= points.y1 + points.y2))
	{
		dessin_case_insertion_debut_fin(taille_x, taille_y, points, MLV_rgba(255 ,0 ,0 ,255), MLV_rgba(0, 0, 255, 255));
		veri = 1;
	}
	else if ((points.tab[1].x1 <= x && x <= points.tab[1].x1 + points.x2) && (points.y1 <= y && y <= points.y1 + points.y2))
	{
		dessin_case_insertion_debut_fin(taille_x, taille_y, points, MLV_rgba(0, 0, 255, 255) ,MLV_rgba(255 ,0 ,0 ,255) );
		veri = 2;

	}
	else
		dessin_case_insertion_debut_fin(taille_x, taille_y, points, MLV_rgba(0, 0, 255, 255), MLV_rgba(0, 0, 255, 255));

	MLV_actualise_window();
	return veri;
}

/* permet de vérifier si l'utilisateur clique sur un Token de la liste pour effectuer un décalage */
int troisieme_verification_position_souris(Geometrie *geo, int x, int y, int largeur){
	int i;
	
	for(i = 0; i < geo->nb_ele; i++)
	{
		if ((geo->tab[i].x <= x && x <= geo->tab[i].x + largeur) && (geo->y <= y && y <= geo->y + largeur))
		{
			geo->case_clique = i;
			return 1;
		}
		
	}
	return 0;
}

int clique_pour_deplacer(Cases_deplacement dep, Geometrie *geo){
	int x, y;
	MLV_wait_mouse(&x, &y);

	if ((dep.x1 <= x && x <= dep.x1 + dep.x2) && (dep.y1[0] <= y && y <= dep.y1[0] + dep.y2))
	{
		deplacer_couleur(&(geo->lst), geo->tab[ geo->case_clique ].couleur);

		return 1;
	}

	else if ((dep.x1 <= x && x <= dep.x1 + dep.x2) && (dep.y1[1] <= y && y <= dep.y1[1] + dep.y2))
	{
		deplacer_forme(&(geo->lst), geo->tab[ geo->case_clique].forme);

		return 1;
	}

	else
		return 0;
}

void garde_geo(Geometrie *geo, int x, int couleur, int forme, int i){
	geo->tab[i].x = x;

	geo->tab[i].couleur = geo->lst->couleur;	
	geo->tab[i].forme = geo->lst->forme;
}

/* fonctions pour affichage */
int redessiner_cases(int taille_x,int taille_y, int largeur, Geometrie *geo, Coul_def def){
	Liste initial; int i;
	geo->distance = definir_point_depart(*geo, largeur);

	taille_x = taille_x + geo->distance;

	if (geo->lst->suivant == geo->lst)
		figures(taille_x , taille_y, largeur, geo->lst->forme, geo->lst->couleur, def);


	for(initial = geo->lst, i = 0; geo->lst->suivant != initial; geo->lst = geo->lst->suivant, geo->distance = geo->distance - largeur, i++)
	{
		figures(taille_x - 2 * geo->distance , taille_y, largeur, geo->lst->forme, geo->lst->couleur, def);
		garde_geo(geo, taille_x - 2 * geo->distance, geo->lst->couleur, geo->lst->forme, i);
	}
	figures(taille_x - 2 * geo->distance , taille_y, largeur, geo->lst->forme, geo->lst->couleur, def);
	garde_geo(geo, taille_x - 2 * geo->distance, geo->lst->couleur, geo->lst->forme, i);
	geo->lst = initial;
	
	return i + 1;

}

/* fonction permettant la mise en place du jeu */
int gestion_jeu(int taille_x, int taille_y, Coul_def def){

	int score, time = MLV_get_time(), temps_ecoule = 0;

	score = 0;

	MLV_clear_window(MLV_COLOR_BLACK);
	Cases_insertion points = initialisation_case_insertion(taille_x + taille_x/3, 2 * taille_y, taille_x/2);
	Cases_deplacement dep;

	FC_aleatoire fc;
	initialisation_figure_couleur_aleatoire(&fc ,taille_x * 2, taille_y, taille_x/10);

	MLV_Sound* sound1 = initialise_bruit_sonores( "SONS_MUSIC/SONS/comical_liquid_gel_splat.ogg" );
	MLV_Sound* sound2 = initialise_bruit_sonores( "SONS_MUSIC/SONS/large_cork_pop.ogg" );

	Geometrie geo; 

	geo.nb_ele = 0; geo.distance = 0; geo.lst = NULL; geo.case_clique = 0;
	geo.tab[0].x = 1;
	int x, y, i, veri = 0, veri2 = 0, veri3 = 0, veri4 = 0, deplacer = 0;

	int temp_x = taille_x*2 , temp_y = 2 * taille_y + taille_y/3;
	geo.y = temp_y;

	dessiner_figures_avant_insertion( fc , def);
	dessin_case_insertion_debut_fin(taille_x  , 2 * taille_y, points, MLV_rgba(0, 0, 255, 255), MLV_rgba(0, 0, 255, 255));
	affiche_score(taille_x/2, taille_y/2, score );

		
	while ( temps_ecoule < 60 * 2 ){
		if ( MLV_is_full_screen() && MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
			MLV_disable_full_screen( );

		if (MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
			MLV_enable_full_screen( );


		if ( geo.tab[geo.nb_ele - 1].x >= taille_x * 4 && geo.tab[0].x <= 0 )
		{
			MLV_clear_window( MLV_COLOR_BLACK );
			return -1;
		}

		if (veri3 == 2)
		{
			deplacer = clique_pour_deplacer(dep, &geo);
			if (deplacer == 1){
				if (geo.lst != NULL)
				{
					geo.nb_ele = redessiner_cases(temp_x, temp_y, taille_x/10, &geo, def);
					MLV_actualise_window();
				}
				else{
					geo.nb_ele = 0;
				}


				veri2 = analyse_et_efface(&(geo.lst));
				if (veri2 > 0){
					effets_sonores( sound2 );
					MLV_wait_milliseconds( 300 );
					score += veri2 ;
				}
				MLV_clear_window( MLV_COLOR_BLACK );
			}
		}

		dessin_case_insertion_debut_fin(taille_x , 2 * taille_y, points, MLV_rgba(0, 0, 255, 255), MLV_rgba(0, 0, 255, 255));


		MLV_get_mouse_position( &x, &y );

		i = deuxieme_verification_position_souris(points, x, y, taille_x, 2 * taille_y );

		veri3 = troisieme_verification_position_souris(&geo, x, y, taille_x/10);

		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED && (i >= 1 || veri3 == 1))
		{
			while(MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED);

			if(i>=1)
				veri4 = 1;

			
			MLV_clear_window(MLV_COLOR_BLACK);
			dessin_case_insertion_debut_fin(taille_x , 2 * taille_y, points, MLV_rgba(0, 0, 255, 255), MLV_rgba(0, 0, 255, 255));

			if (veri3 == 1)
			{
				dessiner_case_cercle_deplacement(geo, &dep, taille_x/10, def);
				if (geo.nb_ele >= 1)
					veri3 = 2;
			}
				
			else
			{
				effets_sonores( sound1 );
				attribue_une_valeur_geometrique(i, fc.tab[4].couleur, fc.tab[4].forme, &geo);

				veri = 1;
				
			}

			if (geo.lst != NULL)
			{
				geo.nb_ele = redessiner_cases(temp_x, temp_y, taille_x/10, &geo, def);
				MLV_actualise_window();
			}
			else{
				geo.nb_ele = 0;
			}

			veri2 = analyse_et_efface(&(geo.lst));
			if (veri2 > 0){
				effets_sonores( sound2 );
				MLV_wait_milliseconds( 300 );
				score += veri2;

			}			

		}


		if (veri == 1){
			if (veri4 == 1)
				decalage_figure_couleur_aleatoire( &fc ,taille_x * 2, taille_y, taille_x/10);

			dessiner_figures_avant_insertion( fc , def);
		}
		

		if (geo.lst != NULL)
		{
			if (veri2 > 0){

				MLV_clear_window( MLV_COLOR_BLACK );
				dessiner_figures_avant_insertion( fc , def);
				dessin_case_insertion_debut_fin(taille_x , 2 * taille_y, points, MLV_rgba(0, 0, 255, 255), MLV_rgba(0, 0, 255, 255));


			}
			geo.nb_ele = redessiner_cases(temp_x, temp_y, taille_x/10, &geo, def);
		}
		else{
			geo.nb_ele = 0;
		}

		affiche_score(taille_x/2, taille_y/2, score * 10);

		effacer_temps(taille_x, taille_y/3);
		temps_ecoule = affiche_temps(taille_x/2, taille_y/3, time);
		veri4 = 0;

		if (geo.nb_ele <= 0)
			MLV_draw_filled_rectangle(0, 2 * taille_y + taille_y/10, taille_x * 4, taille_y * 4, MLV_COLOR_BLACK);

		MLV_actualise_window();


		if (MLV_get_keyboard_state( MLV_KEYBOARD_q ) == MLV_PRESSED)
			break;
	}

	libere_son( sound1 );
	libere_son( sound2 );

	if (geo.nb_ele > 0)
		libererListe(&(geo.lst));

	MLV_clear_window( MLV_COLOR_BLACK );
	MLV_actualise_window();

	return score * 10;
}

/*********************************************************************FIN GESTION FIGURES GEOMETRIQUES*********************************************************/


																		/*FIN DE FIGURES GEOMETRIQUES*/

/**************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
***************************************************************************************************************************************************************
*/

void partie_start(int taille_x, int taille_y)
{
	MLV_Music* music =  music_jeu("SONS_MUSIC/MUSIC/bensound-epic.ogg");
	Case_depart cases = initialisation_case_depart(taille_x, taille_y);
	int veri, score = 0;

	if ( MLV_is_full_screen() && MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
		MLV_disable_full_screen( );

	if (MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
		MLV_enable_full_screen( );


	veri = gestion_menu_depart(cases);
	Coul_def def = couleur_defaut();
	while (veri != 3){

		if (veri == 0){
			score = gestion_jeu(taille_x/4, taille_y/4, def);
			if (score < 0)
				MLV_draw_text(taille_x/2, taille_y /2, "GAME OVER !", MLV_COLOR_RED);
			else
				MLV_draw_text(taille_x/3, taille_y/2, "GAME OVER ! SCORE FINAL : %d", MLV_COLOR_RED, score);
			MLV_actualise_window();
			MLV_wait_seconds( 2 );
		}

		if (veri == 1){

			Menu_Help(taille_x, taille_y);
		}

		if (veri == 2){
			dessiner_figures_pour_selectionner_couleur(taille_x, taille_y, &def);
		}

		veri = gestion_menu_depart(cases);

		MLV_actualise_window();
	}
	arrete_music(music);
	MLV_wait_seconds( 1 );

	MLV_free_window();
}