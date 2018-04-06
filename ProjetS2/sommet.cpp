#include "Sommet.h"
using namespace std;



Sommet::Sommet(int posx, int posy,BITMAP *som,int a,int d)
{
    actif = a;
    x = posx;
    y = posy;
    S = som;
    poids = 0;
    degre = d;
}

int Sommet::getx()
{
    return x;
}

int Sommet::gety()
{
    return y;
}
void Sommet::setx(int x1)
{
    if(x1 > 900) x1 = 850;
    if(x1 < 185) x1 = 155;
    x = x1;
}

void Sommet::sety(int y1)
{
    if(y1 > 600) y1 =600;
    y = y1;
}

Sommet::~Sommet()
{
    //dtor
}
