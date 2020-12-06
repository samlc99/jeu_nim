/*
MODULE NIM_IHM

Module qui d�finit l'interface homme-machine du jeu de nim. Ce module 
repose sur la librairie ncurses et subdivise l'�cran en 3 zones: 
- La zone de titre (qui affiche "Jeu de NIM")
- La zone de plateau, qui affiche les pi�ces r�parties sur des colonnes
- La zone console, o� sont faits les affichages et les lectures au clavier.

Le module comporte des fonctions et des macros fontions permettant au programmeur
de faire abstraction de l'interface usager. Les principales sont: 

- ihm_init_ecran: Initialise l'interface (les 3 zones d'affichage)
- int ihm_changer_taille_plateau: sp�cifie le nombre de lignes et de colonnes du plateau
  de jeu.
- ihm_ajouter_piece: Ajoute une pi�ce sur le plateau de jeu, � l'endroit d�sir�
- ihm_choisir_colonne: Fait choisir � l'usager une colonne, en utilisant les touches
  fl�ch�es.
- ihm_effacer_plateau: Efface le plateau de jeu.
- ihm_printf: Affiche une chaine format�e (� la printf) dans la console de NIM
- ihm_scanf: Lit une valeur depuis la console de NIM (� la scanf)
- ihm_effacer_ecran: Efface le contenu de la console de NIM
- ihm_pause: Interrompe l'ex�cution du programme jusqu'� ce que l'usager presse
  sur une touche.
*/
#ifndef IHM__H
#define IHM__H

//Inclusion de la librairie ncurses (selon l'OS)
#if defined(_WIN32)
#include <ncurses/curses.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <curses.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
* MACRO_FONCTIONS
*/

/*
IHM_PRINTF (macro-fonction)
Fonction �quivalente � printf, � utiliser dans l'environnement de l'interface du 
jeu de NIM. Elle affiche une chaine de caract�res format�e dans la console du jeu. 
Les codes de formatage du printf (%d, %lf, etc.) peuvent �tre utilis�s avec cette
fonction.

Param�tres:
- chaine: chaine format�e � afficher
- ...: ensemble variable de param�tres, selon ce qui est requis par chaine.
Retour: Aucun
*/
#define ihm_printf(...) wprintw(ihm_get_zone_texte(),__VA_ARGS__);wrefresh(ihm_get_zone_texte())

/*
IHM_PAUSE (macro-fonction)
Interrompe l'ex�cution du programme jusqu'� ce que l'utilisateur
presse sur une touche.

Param�tres: Aucun
Retour: Aucun
*/
#define ihm_pause() wgetch(ihm_get_zone_texte());

/*
IHM_EFFACER_ECRAN (macro-fonction)
Efface la zone console de l'interface usager de NIM.

Param�tres: Aucun
Retour: Aucun
*/
#define ihm_effacer_ecran() wclear(ihm_get_zone_texte());wrefresh(ihm_get_zone_texte())

/*
IHM_INIT_ECRAN
Initialise l'affichage du jeu de NIM en subdivisant l'�cran en trois zones: 
	- La zone de titre
	- Le plateau de jeu ayant nb_lignes et nb_colonnes
	- La console du jeu
La fonction renvoie Faux si l'environnement ne supporte par l'affichage du jeu de
NIM. Si le nombre de lignes et de colonnes du jeu n'est pas connu, la fonction
doit �tre appel�e avec des param�tres nuls.

Param�tres: 
nb_lignes: le nombre de lignes du plateau de jeu
nb_colonnes: le nombre de colonnes du plateau de jeu
*/
int ihm_init_ecran(int nb_lignes, int nb_colonnes);

/*
IHM_AJOUTER_PIECE
Ajoute une piece de monnaie sur le plateau de jeu � la coordonn�e sp�cifi�e. 
Les indices des coordonn�es commencent � 0. La fonction v�rifie que les 
coordonn�es sp�cifi�es sont valides. 

Param�tres: 
- ligne (entier): Indice de la ligne sur le plateau
- colonne (entier): Indice de la colonne sur le plateau
Retour: (entier) Vrai si la pi�ce a bien �t� plac�e, faux sinon. 
*/
int ihm_ajouter_piece(int ligne, int colonne);

/*
IHM_CHOISIR_COLONNE
Permet � l'utilisateur de choisir une des colonnes du plateau de jeu de fa�on int�ractive
(en utilisant les touches fl�ch�es). 
Note: La zone de jeu doit avoir �t� initialis�e et le nombre de colonnes et de lignes de la
zone de jeu a �t� d�fini � une valeur non-nulle (avec ihm_init_ecran ou ihm_changer_taille_plateau).

Param�tres: Aucun
Retour (entier): La colonne choisie par l'utilisateur, ou -1 si une erreur s'est produite.
*/
int ihm_choisir_colonne(void);

/*
�HM_CHANGER_TAILLE_PLATEAU
Modifie le nombre de colonnes et de lignes du plateau de jeu. Le plateau de jeu
est effac� puis redessin� en cons�quence.

NOTE: Le nombre de lignes et de colonnes doit �tre positif et ne pas exc�der la 
limite d�finie par les constantes IHM_PLATEAU_MAX_LIGNES et 
IHM_PLATEAU_MAX_COLONNES.

Param�tres: 
lignes (entier): nouveau nombre total de lignes du plateau.
colonnes (entier): nouveau nombre total de colonnes du plateau.
Retour: (entier): Vrai si la modification a bien eu lieu. Faux sinon.
*/
int ihm_changer_taille_plateau(int lignes, int colonnes);

/*
IHM_GET_ZONE_TEXT
Fonction utilitaire qui renvoie une r�f�rence vers la zone zonsole de l'interface.
Cette fonction sert aux macro-fonctions ihm_printf, ihm_scanf et ihm_pause et ne devrait
pas �tre utialis�e pour d'autres contextes.
Param�tres: Aucun
Retour: (WINDOWS*) R�f�rence vers la zone console.
*/
WINDOW* ihm_get_zone_texte();

/*
IHM_SCANF (macro-fonction)
Fonction �quivalente � scanf, � utiliser dans l'environnement de l'interface du
jeu de NIM. Elle lit une valeur depuis la console du jeu.
Les codes de formatage du scanf (%d, %lf, etc.) peuvent �tre utilis�s avec cette
fonction.

Param�tres:
- chaine: chaine format�e sp�cifiant la/les valeur(s) � lire
- ...: liste de pointeurs, selon ce qui est requis par chaine.
Retour: Aucun
*/
int ihm_scanf(const char* format, void* address);

#endif