#include <iostream>
#include <allegro.h>
#include "Alleg.h"
#include "graph.h"
using namespace std;

int main()
{
    int choix;
    Alleg::init();
    choix = Alleg::menu();
    graphe ou(choix);
    while(!key[KEY_ESC])
        {
            Alleg::affichage(ou);
        }
Alleg::fermer_allegro();
    ou.save(choix);
    return 0;
}
END_OF_MAIN();
