#include <MLV/MLV_all.h>
#include "partie_start.h"


int main(int argc, char const *argv[])
{
	int taille_x, taille_y;
	taille_x = 640; taille_y = 480;

	MLV_create_window("JEU", "JEU", taille_x, taille_y);
	
	partie_start(taille_x, taille_y);

	return 0;
}