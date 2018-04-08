#include <iostream>
#include <allegro.h>
#include "Alleg.h"
#include "graph.h"
using namespace std;

int main()
{
    int choix = 0;
    int b;

    Alleg::init();
    while( choix != -1)
    {
        b = 0;
        choix = Alleg::menu();
        if(choix != -1)
        {
            graphe ou(choix);
            while(b == 0)
                {
                    b = Alleg::affichage(ou,choix);
                }
            //ou.save(choix);
        }
    }
    Alleg::fermer_allegro();

    return 0;
}
END_OF_MAIN();
