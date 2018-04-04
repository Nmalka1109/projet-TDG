#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "Sommet.h"
using namespace std;

class Arete
{
    public:
        ///attributs
        Sommet m_s1;
        Sommet m_s2;

        ///constructeurs
        Arete();
        Arete(Sommet ps1, Sommet ps2);

        ///destructeur
        ~Arete();


};

#endif // ARRETE_H_INCLUDED
