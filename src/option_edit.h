#define ECART 6

/*************************************************************************STRUCTURES***************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
typedef struct COULEUR
{
	MLV_Color couleur[4];
	
}Couleur;

typedef struct UNE_COULEUR_BASE
{
	int x;
	int y1;
	int y2;
	int y3;
	int rouge;
	int vert;
	int bleu;
	
}Coul_base;

typedef struct TYPES_COULEUR
{
	MLV_Color tab_rouge[256];
	MLV_Color tab_vert[256];
	MLV_Color tab_bleu[256];
	Coul_base couleur[256];
	int largeur;
	int sauvegarde;
	int rouge; 
	int vert; 
	int bleu;
	
}Types_couleur;

typedef struct COULEUR_PAR_DEFAUT
{
	MLV_Color base[4];
}Coul_def;

typedef struct CASES_OPTION
{
	int x[4];
	int y;
	int largeur;
	
}Cases_option;




/*************************************************************************FIN STRUCTURES***********************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/

/*************************************************************************INITIALISATION STRUCTURES************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/

Coul_def couleur_defaut(){
	Coul_def def;
	def.base[0] = MLV_rgba(255 ,0 ,0 ,255);
	def.base[1] = MLV_rgba(0, 255, 0, 255);
	def.base[2] = MLV_rgba(0, 0, 255, 255);
	def.base[3] = MLV_rgba(255, 255 ,0 ,255);

	return def;

}

Types_couleur initialisation_couleur_base(){
	Types_couleur base_coul;
	int i;
	for (i = 0; i < 256; i++)
	{
		base_coul.tab_rouge[i] = MLV_rgba(255 - i,0 ,0 ,255);
		base_coul.tab_vert[i] = MLV_rgba(0 ,255 - i ,0 ,255);
		base_coul.tab_bleu[i] = MLV_rgba(0 ,0 ,255 - i ,255);
		base_coul.couleur[i].rouge = 255 - i;
		base_coul.couleur[i].vert = 255 - i;
		base_coul.couleur[i].bleu = 255 - i;
		base_coul.rouge = 0;
		base_coul.vert = 0;
		base_coul.bleu = 0;


	}

	return base_coul;
}

Couleur initialisation_couleur(MLV_Color base[]){
	Couleur paint;
	paint.couleur[0] = base[0]; /*ROUGE*/
	paint.couleur[1] = base[1]; /*VERT*/
	paint.couleur[2] = base[2]; /*BLEU*/
	paint.couleur[3] = base[3]; /*JAUNE*/

	return paint;
}

/*********************************************************************FIN INITIALISATION STRUCTURES************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/

/*************************************************************************CLIQUE SUR PARTIE OPTION*************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/

int position_souris_option_1(Types_couleur *base_coul, int x, int y,int taille_x, int taille_y){
	int i;
	for (i = 0; i < 256; i++)

	{
		if( base_coul->couleur[i].x <= x && x <= base_coul->couleur[i].x + base_coul->largeur)
		{
			
			
			if (base_coul->couleur[i].y3 <= y && y <= base_coul->couleur[i].y3 + ECART * base_coul->largeur  )
			{	
				base_coul->sauvegarde = 255 - base_coul->couleur[i].x/base_coul->largeur;
				return 3;
			}

			if (base_coul->couleur[i].y2 <= y && y <= base_coul->couleur[i].y2 + ECART * base_coul->largeur  )
			{	base_coul->sauvegarde = 255 - base_coul->couleur[i].x/base_coul->largeur;
				return 2;
			}

			if (base_coul->couleur[i].y1 <= y && y <= base_coul->couleur[i].y1 + ECART * base_coul->largeur  )
			{	base_coul->sauvegarde = 255 - base_coul->couleur[i].x/base_coul->largeur;
				return 1;
			}
		}
	}

	return 0;
}

int position_souris_option_2(Cases_option c_option, int x, int y){
	if (c_option.y <= y && y <= c_option.y + c_option.largeur)
	{
		if (c_option.x[0] <= x && x <= c_option.x[0] + c_option.largeur)
			return 0;

		if (c_option.x[1] <= x && x <= c_option.x[1] + c_option.largeur)
			return 1;

		if (c_option.x[2] <= x && x <= c_option.x[2] + c_option.largeur)
			return 2;

		if (c_option.x[3] <= x && x <= c_option.x[3] + c_option.largeur)
			return 3;
	}

	return -1;
}


int clique_sur_case_option(Cases_option c_option){
	int x, y, veri = -1;
	while( veri < 0 )
	{
		MLV_wait_mouse(&x, &y);
		veri = position_souris_option_2(c_option, x, y);
	}

	return veri;
}




/*************************************************************************DESSIN DE FIGURES GEOMETRIQUES*******************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/


void dessiner_couleur_base(Types_couleur *base_coul, int taille_x, int taille_y){
	int largeur = taille_x/256;
	int i, x, y = taille_y;
	base_coul->largeur = largeur;

	for(x = 0, i = 0; i < 256; x += largeur, i++)
	{
		MLV_draw_filled_rectangle(x, y, largeur, 10 * largeur, base_coul->tab_rouge[i]);
		MLV_draw_filled_rectangle(x, y + ECART*largeur, largeur, ECART * largeur, base_coul->tab_vert[i]);
		MLV_draw_filled_rectangle(x, y + (2 * ECART) * largeur, largeur, ECART * largeur, base_coul->tab_bleu[i]);
		base_coul->couleur[i].x = x;

		base_coul->couleur[i].y1 = y;
		base_coul->couleur[i].y2 = y + ECART*largeur;
		base_coul->couleur[i].y3 = y + (2 * ECART) * largeur;
	}


}

void triangle(int taille_x, int taille_y, int largeur, MLV_Color couleur){
	int point_x[3], point_y[3];

	point_x[0] = taille_x; point_x[1] = taille_x + largeur; point_x[2] = taille_x + largeur/2;
	point_y[0] = point_y[1] = taille_y + largeur; point_y[2] = taille_y ;

	MLV_draw_filled_polygon(
		point_x, point_y,
		3, 
		couleur
		);
}

void losange(int taille_x, int taille_y, int largeur, MLV_Color couleur){
	int point_x[4], point_y[4];

	point_x[0] = taille_x;
	point_x[1] = point_x[3] = taille_x + largeur/2; 
	point_x[2] = taille_x + largeur;  

	point_y[0] = point_y[2] = taille_y + largeur/2; 
	point_y[1] = taille_y; 
	point_y[3] = taille_y + largeur;

	MLV_draw_filled_polygon(
		point_x, point_y,
		4, 
		couleur
		);

}

void figures(int taille_x, int taille_y, int largeur, int rand_a, int rand_b, Coul_def def){

	Couleur paint = initialisation_couleur( def.base );

	if (rand_a == 0)
	{
		MLV_draw_filled_circle(
			taille_x + largeur/2, taille_y + largeur/2,
			largeur/2,
			paint.couleur[rand_b]
			);
	}

	if (rand_a == 1){
		MLV_draw_filled_rectangle(
			taille_x, taille_y,
			largeur, largeur,
			paint.couleur[rand_b]
			);
	}

	if (rand_a == 2)
		triangle(taille_x, taille_y, largeur, paint.couleur[rand_b]);


	if (rand_a == 3)
		losange(taille_x, taille_y, largeur, paint.couleur[rand_b]);

}


/*************************************************************************TAILLE FENETRE***********************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/

void Menu_Help(int taille_x, int taille_y){
	MLV_clear_window( MLV_COLOR_BLACK );
	char* message = "THREE TO GO : à propos du jeu\n\n\nCliquez sur les flèches (GAUCHE / DROITE) pour insérer un Token\n\nCliquez sur un Token de la liste pour effectuer un décalage\nLa forme apparaissant au dessus correspond au décalage des Tokens de même couleur\nLa forme apparaissant au dessous correspond au décalage des Tokens de même forme\n\nOnglet 'EDITER' : éditer la couleur de vos Tokens\nTouches associées :\nR : Réinitialiser les couleurs\nQ : Retour\nECHAP : Plein écran / Fenêtré";
	
	MLV_actualise_window();
	while ( 1 ){
		MLV_clear_window( MLV_COLOR_BLACK );
		if (MLV_get_keyboard_state( MLV_KEYBOARD_q ) == MLV_PRESSED)
			break;

		if ( MLV_is_full_screen() && MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
		MLV_disable_full_screen( );

		if (MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
			MLV_enable_full_screen( );

		MLV_draw_text_box(
			0, 0,
			taille_x, taille_y,
			message, 5,
			MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
			MLV_TEXT_CENTER,
			MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
		);

		MLV_actualise_window();
	}	
	
}


/*********************************************************************FIN TAILLE FENETRE***********************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/



void dessiner_figures_pour_selectionner_couleur(int taille_x, int taille_y, Coul_def *def){
	MLV_clear_window( MLV_COLOR_BLACK );
	Cases_option c_option;
	
	Types_couleur base_coul = initialisation_couleur_base(def->base);
	int x, y ,veri, veri2 = -1, memoire, sauvegarde[3] = {0, 0, 0}, sauvegarde2[3] = {0, 0, 0}, cp;


	int x1, i, largeur = taille_x/10;
	c_option.y = taille_y/3; c_option.largeur = largeur/2;

	for(i = 0, x1 = 0 ;i < 4; i++, x1 += largeur){
		figures(x1 + 3*largeur, taille_y/3, largeur/2, 1, i, *def);
		c_option.x[i] = x1 + 3*largeur;
	}

	dessiner_couleur_base(&base_coul, taille_x, taille_y/(1.5));

	if ( MLV_is_full_screen() && MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
		MLV_disable_full_screen( );

	if (MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) == MLV_PRESSED)
		MLV_enable_full_screen( );



	MLV_actualise_window();
	veri2 = clique_sur_case_option( c_option );
	memoire = veri2;

	while ( 1 ){

		if (MLV_get_keyboard_state( MLV_KEYBOARD_r ) == MLV_PRESSED){
			*def = couleur_defaut();
		}

		if (MLV_get_keyboard_state( MLV_KEYBOARD_q ) == MLV_PRESSED)
			break;

		MLV_get_mouse_position( &x, &y );
		veri = position_souris_option_1( &base_coul, x, y, taille_x, taille_y/(1.5) );


		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED)
		{
			memoire = veri2;
			veri2 = position_souris_option_2(c_option, x, y);
			if (veri2 < 0)
				veri2 = memoire;
			else
			{

				for(cp = 0;cp < 3; cp++)
				{
					sauvegarde[cp] = 0;

				}
			}
		}
			

		if (veri > 0)
		{
			
			MLV_clear_window( MLV_COLOR_BLACK);
			dessiner_couleur_base(&base_coul, taille_x, taille_y/(1.5));

			if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED )
			{
				while(MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED);
				sauvegarde[veri - 1] = 1;
			}

			else{
				for (cp = 0; cp < 3; cp++)
				{
					if (sauvegarde[cp] != 1)
						sauvegarde2[cp] = 0;
				}
				
			}


			if (veri == 1){
				base_coul.rouge = base_coul.sauvegarde;
				sauvegarde2[0] = base_coul.rouge;
				def->base[veri2] = MLV_rgba(sauvegarde2[0], sauvegarde2[1], sauvegarde2[2], 255);
			
			}

			if (veri == 2){
				base_coul.vert = base_coul.sauvegarde;
				sauvegarde2[1] = base_coul.vert;
				def->base[veri2] = MLV_rgba(sauvegarde2[0], sauvegarde2[1], sauvegarde2[2], 255);

			
			}

			if (veri == 3)
			{
				base_coul.bleu = base_coul.sauvegarde;
				sauvegarde2[2] = base_coul.bleu;
				def->base[veri2] = MLV_rgba(sauvegarde2[0], sauvegarde2[1], sauvegarde2[2], 255);
			}


				

		}

		for(i = 0, x1 = 0 ;i < 4; i++, x1 += largeur)
			figures(x1 + 3*largeur, taille_y/3, largeur/2, 1, i, *def);

		if (sauvegarde[0] == 0 ){
			sauvegarde2[0] = 0;
			def->base[veri2] = MLV_rgba(sauvegarde2[0], sauvegarde2[1], sauvegarde2[2], 255);
		}

		MLV_actualise_window();
		

	}
}


/*********************************************************************FIN DESSIN DE FIGURES GEOMETRIQUES*******************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
