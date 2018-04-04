#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>
using namespace std;

class Sommet
{
    public:
        ///attribut
        string m_nom;

        ///constructeurs
        Sommet();
        Sommet(string pnom);

        ///destructeur
        ~Sommet();


    private:
};

#endif // SOMMET_H_INCLUDED
