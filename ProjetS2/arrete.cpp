#include "arrete.h"
#include "sommet.h"
using namespace std;

Arete::Arete()
{
    Sommet m_s1();
    Sommet m_s2();
    Sommet m_pa();
}

Arete::Arete(int ps1, int ps2, int pa)
     : m_s1(ps1), m_s2(ps2), m_pa(pa)
{

}

Arete::~Arete()
{
    //dtor
}
