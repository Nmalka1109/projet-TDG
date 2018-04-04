#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include "Sommet.h"
#include "Arete.h"

using namespace std;

class graphe
{
public :

    ///attributs
    vector<vector<int>> m_Matrice;
    int m_ordre;
    vector<Sommet> m_som;

///constructeurs
    graphe();
    graphe(int pordre);
    ///destructeur
    ~graphe();

    ///méthodes
    void creation();
    void recuperation(string name1);
    void affichage();


};


#endif // GRAPH_H_INCLUDED
