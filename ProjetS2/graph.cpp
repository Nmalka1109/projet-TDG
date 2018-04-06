#include "graph.h"
#include "Alleg.h"
#include <iostream>
#include <fstream>

///soure openclassroom


using namespace std;

graphe::graphe(int a)
{
    BITMAP *im = NULL;
    int x,y,j,act;
    string name;
    string loc;
    int b;
    if (a == 1)
        name = "Dinosaures.txt";
    else if (a == 2)
        name = "Ocean.txt";
    else if (a == 3)
        name = "Foret.txt";
    else if (a == 4)
        name = "Bonus.txt";
    else std::cout <<"Erreur menu";
    std::ifstream fic1(name,std::ios::in);

        fic1 >> m_ordre;
        for(int i=0; i< m_ordre; i++)
        {
            fic1 >>act;
            fic1 >>loc;
            fic1 >>x;
            fic1 >>y;
            fic1 >>j;
            if(j != 0)
            {
                for(int f=0; f<j ; f++ )
                {
                    fic1 >> b;
                    m_ar.push_back(Arete(i,b));
                }
            }
            im = Alleg::charger_image(a,loc);
            m_som.push_back(Sommet(x,y,im,act,j));

        }
    if(!fic1) std::cout <<"pas de fichier";
    fic1.close();
}
graphe::~graphe()
{

}

void graphe::save(int a)
{
string name;
int j = 0;
if (a == 1)
        name = "Dinosaures.txt";
    else if (a == 2)
        name = "Ocean.txt";
    else if (a == 3)
        name = "Foret.txt";
    else if (a == 4)
        name = "Bonus.txt";
    else std::cout <<"Erreur menu";

    ofstream file(name);
    if(!file)
        {
            std::cout <<"erreur fichier de sauvegarde";
        }
    else
        {
            file << m_som.size()<<endl;
            for(int i =0;i < m_som.size();i++)
                {
                    file << m_som[i].actif<<endl;
                    file << i<< endl;
                    file << m_som[i].getx()<<" ";
                    file << m_som[i].gety()<<endl;
                    file << m_som[i].degre;
                    if(m_som[i].degre != 0)
                        {
                        for(int f = 0; f< m_som[i].degre;f++)
                        {
                            file << " "<<m_ar[j].m_s2;
                    std::cout <<j<<std::endl;
                            j++;
                        }
                        }

                        file <<endl;
                }
        }

}

void graphe::supprimer(int sommet)
{
    m_som[sommet].actif = 0;
}