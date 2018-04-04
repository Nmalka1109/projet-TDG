#include "Sommet.h"
using namespace std;

Sommet::Sommet()
    :m_nom(" 3  ")
{

}

Sommet::Sommet(std::string pnom)
{
    m_nom = pnom;
}

Sommet::~Sommet()
{
    //dtor
}
