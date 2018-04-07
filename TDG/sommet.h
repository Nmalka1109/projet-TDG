#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>
#include <vector>
#include <allegro.h>
using namespace std;

class Sommet
{
    public:
        ///attribut
        int poids=0, actif;
        BITMAP *S;
        int degre;
        int getx();
        int gety();
        int ind;
        void setx(int x1);
        void sety(int y1);

        ///constructeurs
        Sommet(int posx, int posy,BITMAP *som,int a,int d,int poids, int ind);

        ///destructeur
        ~Sommet();


    private:
        int x,y;
};

#endif // SOMMET_H_INCLUDED
