#include "Sommet.h"
using namespace std;



Sommet::Sommet(int posx, int posy,BITMAP *som,int a,int d,int ps,int l,float r)
{
    actif = a;
    x = posx;
    y = posy;
    S = som;
    poids = ps;
    p_sim=ps;
    degre = d;
    ind=l;
    rythme=r;
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
    if(x1 > 900) x1 = 880;
    if(x1 < 100) x1 = 90;
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



