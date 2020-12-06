#include "nim_ihm.h"


#define IHM_LARGEUR_ECRAN 140 //Largeur maximale de l'�cran en nombre de caract�res
#define IHM_HAUTEUR_ECRAN 45 //Hauteur maximale de l'�cran en nombre de caract�res
#define IHM_PLATEAU_MAX_LARGEUR (IHM_LARGEUR_ECRAN/2 - 2) //Moiti� de l'�cran - 2 pour les lignes 
#define IHM_PLATEAU_MAX_HAUTEUR (IHM_HAUTEUR_ECRAN - 3) //Hauteur de l'�cran -2 pour les lignes -1 pour texte en haut.
#define IHM_PLATEAU_DECAL_LIGNE 3 //D�calage de la premi�re ligne par rapport au haut du plateau de jeu
#define IHM_PLATEAU_DECAL_COLONNE 3 //D�calage de la premi�re colonne par rapport � la gauche du plateau de jeu
#define IHM_PLATEAU_LARGEUR_COLONNE 3 //Largeur d'une colonne dans le plateau de jeu
//Nombre max de colonnes: la largeur totale -2 pour les coordonn�es des lignes / largeur d'une colonne
#define IHM_PLATEAU_MAX_COLONNES ((IHM_PLATEAU_MAX_LARGEUR - IHM_PLATEAU_DECAL_COLONNE) / IHM_PLATEAU_LARGEUR_COLONNE)
#define IHM_PLATEAU_MAX_LIGNES (IHM_PLATEAU_MAX_HAUTEUR - IHM_PLATEAU_DECAL_LIGNE)

#define IHM_COLEUR_NORMALE 1 //Couleur blanc sur fond noir
#define IHM_COULEUR_SURLIGNEE 2 //Couleur blanc sur fond jaune
#define IHM_COULEUR_MESSAGE 3 //Couleur rouge sur fond blanc

//Message d'aide affich� pour la s�lection de colonne par l'usager.
#define IHM_MESSAGE_SELECTION_COLONNE "<- -> <ESPACE>: Changer la selection   <ENTREE>: Valider"

//Taille maximale du buffer de saisie
#define TAILLE_BUFFER_SAISIE 100

/******************************
* Variables priv�es du module *
*******************************/
//R�f�rences vers les zones de l'interface graphique
WINDOW *plateau_jeu;
WINDOW *zone_texte;

//Taille du plateau de jeu en lignes et colonnes. Initialement -1 pour "non-d�fini"
int nb_lignes = -1;
int nb_colonnes = -1;

/******************************
* Fonctions priv�es du module *
*******************************/
/*
IHM_AFFICHER_COORDS_PLATEAU
Affiche les coordonn�es (indices de lignes et colonnes) sur le plateau du jeu.
*/
void ihm_afficher_coords_plateau(WINDOW *plateau);

/*
IHM_SURLIGNER
Surligne la colonne "colonne" ou d�active le surlignage, selon la valeur du 
param�tre bool�en "on".
*/
void ihm_surligner(int colonne, int on);

/*
IHM_AFFICHER_ENTETE
Affiche le message dans la zone de titre, typiquement "Jeu de NIM".
*/
void ihm_afficher_entete(WINDOW *fenetre);

/*
IHM_VERIFIER_TAILLE_PLATEAU
V�rifie que les valeurs lignes et colonnes sont des valeurs valides
pour la taille d'un plateau de jeu.
*/
int ihm_verifier_taille_plateau(int lignes, int colonnes);

/*
IHM_EFFACER_PLATEAU
Efface le contenu du plateau de jeu. 
*/
void ihm_effacer_plateau(void);

/*
IHM_CREER_FENETRE
Cr�e une fen�tre virtuelle de hauteur*largeur � la position (debut_y,debut_x).
Si contour est Vrai, une bordure est dessin�e autour de la fen�tre.
*/
WINDOW *ihm_creer_fenetre(int hauteur, int largeur, int debut_y, int debut_x, int contour);


/**********************************************
D�finition des fonctions publiques et priv�es
***********************************************/

//Initialise la console en mode ncurses, dessine les 3 zones et d�finit le nombre de lignes
//et colonnes du plateua de jeu.
int ihm_init_ecran(int lignes, int colonnes)
{
	WINDOW *fenetre_entete; //Fenetre dans laquelle on affiche le titre du jeu.

#ifdef _WIN32
    char cmd[100];
    sprintf(cmd, "mode con:cols=%d lines=%d", IHM_LARGEUR_ECRAN, IHM_HAUTEUR_ECRAN);
    system("mode con:cols=140 lines=45");
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    //printf("\e[8;%d;%dt", IHM_HAUTEUR_ECRAN, IHM_LARGEUR_ECRAN);
    printf("\n\n*****\n* Veuillez agrandir la fenêtre de votre console (en plein écran ou presque) et pressez une ENTREE....\n*****");
    char entree = 0;
    do { entree = getchar(); } while ( entree != '\n');
#endif
	initscr();										   //Initialise ncurses
	resize_term(IHM_HAUTEUR_ECRAN, IHM_LARGEUR_ECRAN); //Redimentionnement du terminal

	cbreak(); //D�sactive le buffer de saisie
	
	if (lignes == 0 && colonnes == 0) {
		lignes = 35;
		colonnes = 20;
	}

	//Initialisation des dimensions du plateau de jeu apr�s v�rification de la validit�
	//des valeurs
	if (!ihm_verifier_taille_plateau(lignes, colonnes))
	{
		endwin();
		printf("La taille du plateau de jeu n'est pas valide."
			" (Permis: 0..%d lignes et 0..%d colonnes)\n",
			IHM_PLATEAU_MAX_LIGNES + 1,
			IHM_PLATEAU_MAX_COLONNES + 1);
		return FALSE;
	}
	nb_lignes = lignes; 
	nb_colonnes = colonnes;

	if (has_colors() == FALSE)
	{
		endwin();
		printf("D�sol�, votre terminal ne permet pas les couleurs. \n");
		return FALSE;
	}
	start_color();

	//On d�clare les paires de couleurs utilis�es dans l'interface
	init_pair(IHM_COLEUR_NORMALE, COLOR_WHITE, COLOR_BLACK);
	init_pair(IHM_COULEUR_SURLIGNEE, COLOR_WHITE, COLOR_YELLOW);
	init_pair(IHM_COULEUR_MESSAGE, COLOR_RED, COLOR_WHITE);

	//Cr�ation de la fenetre ent�te
	fenetre_entete = ihm_creer_fenetre(4, 70, 0, 0, TRUE);
	ihm_afficher_entete(fenetre_entete);

	//Cr�ation et configuration de la zone de texte
	zone_texte = ihm_creer_fenetre(34, 68, 5, 1, FALSE);
	scrollok(zone_texte, TRUE);

	//Cr�ation et configuration de la zone du plateau de jeu
	plateau_jeu = ihm_creer_fenetre(40, 70, 0, 70, TRUE);
	keypad(plateau_jeu, TRUE);
	ihm_afficher_coords_plateau(plateau_jeu);


	refresh();
    ihm_effacer_plateau();
	return TRUE;
}

//Retourne vrai si la taille du plateau est valide. 
int ihm_verifier_taille_plateau(int lignes, int colonnes)
{
	//lignes doit �tre entre [0..IHM_PLATEAU_MAX_LIGNES]
	//colonnes doit �tre dans [0..IHM_PLATEAU_MAX_COLONNES]
	if (lignes < 0 ||
		lignes > IHM_PLATEAU_MAX_LIGNES + 1 ||
		colonnes < 0 ||
		colonnes>IHM_PLATEAU_MAX_COLONNES + 1) {
		return FALSE;
	}
	return TRUE;
}

//Modifie la taille du plateau de jeu (apr�s l'avoir initialis�
int ihm_changer_taille_plateau(int lignes, int colonnes)
{
	//Si taille invalide, on affiche un message d'erreur et on retourne faux.
	if (!ihm_verifier_taille_plateau(lignes, colonnes))
	{
		wprintw(zone_texte, "ERREUR dans la fonction ihm_changer_taille_plateau:\n La taille du plateau de jeu n'est pas valide."
			" (Permis: 0..%d lignes et 0..%d colonnes)\n",
			IHM_PLATEAU_MAX_LIGNES + 1,
			IHM_PLATEAU_MAX_COLONNES + 1);
		return FALSE;
	}

	//Sinon on change la taille et on redessine le plateau.
	nb_lignes = lignes;
	nb_colonnes = colonnes;

	ihm_effacer_plateau();

	if(nb_lignes && nb_colonnes)
		ihm_afficher_coords_plateau(plateau_jeu);


	return TRUE;
}

//Efface le contenu du plateau de jeu.
void ihm_effacer_plateau(void)
{
	//On efface tout, puis on re-dessine la bordure.
	wclear(plateau_jeu);
	box(plateau_jeu, 0, 0);
	wrefresh(plateau_jeu);
}


//Affiche le nom du jeu dans la zone de titre
void ihm_afficher_entete(WINDOW *fenetre)
{
	mvwprintw(fenetre, 2, 1, "                              JEU DE NIM                     ");
	wrefresh(fenetre);
}

//Accesseur de la variable priv�e zone_texte
WINDOW* ihm_get_zone_texte() {
	return zone_texte;
}

//Cr�e une fen�tre dans la console aux dimensions sp�cifi�es, �ventuellement avec un contour d�ssin�
WINDOW *ihm_creer_fenetre(int hauteur, int largeur, int debut_y, int debut_x, int contour)
{
	WINDOW *fenetre;

	fenetre = newwin(hauteur, largeur, debut_y, debut_x);
	if(contour) 
		box(fenetre, 0, 0);	 //Dessine une bordure autour de la fen�tre
	wrefresh(fenetre);		//Et on affiche les changements

	return fenetre;
}

//Ajoute une pi�ce sur le plateau du jeu
int ihm_ajouter_piece(int ligne, int colonne)
{

	if (ligne  > nb_lignes || colonne > nb_colonnes)
		return 0;
	colonne = (colonne+1)*IHM_PLATEAU_LARGEUR_COLONNE;
	mvwprintw(plateau_jeu, ligne+ IHM_PLATEAU_DECAL_LIGNE, colonne-1+IHM_PLATEAU_DECAL_COLONNE, "*");
	wrefresh(plateau_jeu);
	return 1;
}

//Affiche les nums. de ligne et de colonne du plateau de jeu
void ihm_afficher_coords_plateau(WINDOW *plateau)
{
	int i;
	//Affichage des nums de colonnes
	wmove(plateau, IHM_PLATEAU_DECAL_LIGNE-1, IHM_PLATEAU_DECAL_COLONNE);
	for (i = 0; i < nb_colonnes; i++)
	{
		wprintw(plateau, "%*d", IHM_PLATEAU_LARGEUR_COLONNE, i );
	}
	//Affichage des num de ligne
	for (i = 0; i < nb_lignes; i++)
	{
		mvwprintw(plateau, i+IHM_PLATEAU_DECAL_LIGNE, 1 , "%*d",2,i);
	}
	wrefresh(plateau_jeu);
}

//Met une colonne du plateau de jeu en surbrillance
void ihm_surligner(int colonne, int on) 
{
	int i;
	int couleur; 

	colonne = (colonne+1)*IHM_PLATEAU_LARGEUR_COLONNE;

	//si on est vrai, on surligne. Sinon, on r�tablit la couleur normale.
	couleur = on ? IHM_COULEUR_SURLIGNEE : IHM_COLEUR_NORMALE;

	//On doit surligner chaque caract�re de la colonne, ligne par ligne
	for (i = 0; i <= IHM_PLATEAU_MAX_LIGNES; i++)
	{
		mvwchgat(plateau_jeu, i+IHM_PLATEAU_DECAL_LIGNE, colonne + IHM_PLATEAU_DECAL_COLONNE-2, 3, 0, couleur, NULL);
	}

	//On montre les changements � l'�cran
	wrefresh(plateau_jeu);
}

//Permet de choisir une colonne du plateau de jeu avec les touches fl�ch�es
int ihm_choisir_colonne(void)
{
	int ch;
	int colonne_courante = 0;

	if (!nb_colonnes || nb_colonnes == -1  || nb_lignes == -1)
		return -1;
	
	//On d�sactive le mode echo: ne pas afficher les lettres saisies au clavier
	noecho(); 
	//On met en surbrillance la colonne 0
	ihm_surligner(colonne_courante, TRUE);

	//Affiche le message d'instructions
	wattron(plateau_jeu, COLOR_PAIR(IHM_COULEUR_MESSAGE));
	mvwprintw(plateau_jeu, 1, 3, "%s", IHM_MESSAGE_SELECTION_COLONNE);
	wattroff(plateau_jeu, COLOR_PAIR(IHM_COULEUR_MESSAGE));

	while ((ch = wgetch(plateau_jeu)) != '\n')
	{
		switch (ch)
		{
		case '\x4': 
		case KEY_LEFT: //On d�sactive la surbrillance et on change la colonne courante
			ihm_surligner(colonne_courante, FALSE); 
			colonne_courante--; 
			break;
		case '\x5':
		case ' ':
		case KEY_RIGHT: //Idem touche gauche
			ihm_surligner(colonne_courante, FALSE);  
			colonne_courante++;
			break;
		}
		//Rotation de la colonne courante si on est avant la 1ere colonne ou apr�s la derni�re
		colonne_courante = colonne_courante < 0 ? nb_colonnes - 1: colonne_courante;
		colonne_courante = colonne_courante >= nb_colonnes ? 0 : colonne_courante;

		//On met la nouvelle colonne courante en surbrillance
		ihm_surligner(colonne_courante, TRUE);
	}

	//On d�sactive la surbrillance et on r�tablit le mode echo.
	ihm_surligner(colonne_courante, FALSE);
	echo();
	//Efface le message d'aide
	mvwprintw(plateau_jeu, 1, 3, "%*c", strlen(IHM_MESSAGE_SELECTION_COLONNE), ' ');

	wrefresh(plateau_jeu);
	return colonne_courante;
}


int ihm_scanf(const char* format, void* address)
{
    char saisie[TAILLE_BUFFER_SAISIE];

    wgetnstr(ihm_get_zone_texte(),saisie, TAILLE_BUFFER_SAISIE);

    if(!strncmp(format,"%d", 3)) {
        *((int*)address) = atoi(saisie);
    } else if(!strncmp(format,"%lf", 3)){
        *((double*)address) = atof(saisie);
    } else {
        return 0;
    }

    return 1;
}