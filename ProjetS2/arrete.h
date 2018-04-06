#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "Sommet.h"
using namespace std;

class Arete
{
    public:
        ///attributs
       int  m_s1;
       int m_s2;

        ///constructeurs
        Arete();
        Arete(int ps1,int ps2);

        ///destructeur
        ~Arete();


};

#endif // ARRETE_H_INCLUDED
