#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include "Sommet.h"
#include "arrete.h"

using namespace std;

class graphe
{
public :

    int m_ordre;
    vector<Sommet> m_som;
    vector<Arete> m_ar;

///constructeurs
    graphe(int a);
    ///destructeur
    ~graphe();

    ///méthodes
    void recuperation(string name1);
    void affichage();
    void save(int a);
    void supprimer(int sommet);
    void ajouter(int n);
    void modif_sommet(int ps, int i);
    void modif_arete(int pa, int i, int j);


};


#endif // GRAPH_H_INCLUDED
