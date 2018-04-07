#ifndef ALLEG_H_INCLUDED
#define ALLEG_H_INCLUDED
#include <allegro.h>
#include <iostream>
#include <png.h>
#include <loadpng.h>
#include <jpgalleg.h>
#include "sommet.h"
#include "graph.h"
#include "coords.h"

#define MODE_GRAPHIQUE GFX_AUTODETECT_WINDOWED
#define LARGEURECRAN 1024
#define HAUTEURECRAN 768

namespace Alleg
{
extern int page_color;

// Le buffer sur lequel tout est dessin�
extern BITMAP *page;

extern BITMAP *outil;

/// La frame associ�e pour les widgets
extern Frame page_frame;

/// Gestion des widget : avec quel widget la souris interagit ?
class Widget;
extern Widget *gui_over;
extern Widget *gui_last_over;
extern Widget *gui_focus;
extern Widget *gui_leave;


/// Les globales suivantes n�cessitent un appel � rafraichir_clavier_souris
/// en d�but de boucle d'interaction pour �tre mises � jour � chaque tour de boucle

/// La key_last appuy�e depuis le dernier tour de boucle
/// '\0' si aucun bouton appuy� au dernier tour de boucle
extern char key_last;

extern Coords mouse_pos;


/// Le clic souris depuis le dernier tour de boucle
/// s'utilise comme mouse_b mais contrairement � mouse_b
/// n'est valable que pendant un tour de boucle (pas de r�p�tition)
/// mouse_click&1 pour clic gauche, mouse_click&2 pour clic droit
extern int mouse_click;

/// Le rel�chement du clic souris depuis le dernier tour de boucle
/// d�tecte le passage de l'�tat enfonc� � l'�tat rel�ch�
/// n'est valable que pendant un tour de boucle (pas de r�p�tition)
/// mouse_unclick&1 pour clic gauche, mouse_unclick&2 pour clic droit
extern int mouse_unclick;

/// M�me principe que key mais d�tecte les transitions (press�<->non press�)
/// valable pendant un seul tour de boucle (pas de r�p�tition)
/// exemple : if (key_unpress[KEY_RIGHT]) printf("touche droite relachee !\n");
extern int key_press[KEY_MAX];
extern int key_unpress[KEY_MAX];

/// D�placement relatif de la souris depuis le dernier tour de boucle
extern int mouse_click_x;
extern int mouse_click_y;

extern int mouse_move_x;
extern int mouse_move_y;

extern int mouse_click;

extern Coords mouse_pos;

void init();

void effacer_page();

void afficher_page();

void fermer_allegro();

BITMAP *charger_image(int a, std::string name);

int affichage(graphe &a1,int fond);

void rafraichir_clavier_souris();

void deplacer(graphe &a1);

int menu();

int retour();

void ajout(graphe &a1);

void supprimersommet(graphe &a1);

void ms(graphe &a1);

void afficher_sommet();
}


#endif // ALLEG_H_INCLUDED
