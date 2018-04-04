#include "Arete.h"
#include "sommet.h"
using namespace std;

Arete::Arete()
{
    Sommet m_s1();
    Sommet m_s2();
}

Arete::Arete(Sommet ps1, Sommet ps2)
     : m_s1(ps1), m_s2(ps2)
{

}

Arete::~Arete()
{
    //dtor
}
