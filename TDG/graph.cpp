#include "graph.h"
#include "Alleg.h"
#include <iostream>
#include <fstream>

///soure openclassroom


using namespace std;

graphe::graphe(int a)
{
    BITMAP *im = NULL;
    int x,y,j,act,pa,ps;
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
            fic1 >>ps;
            fic1 >>x;
            fic1 >>y;
            fic1 >>j;
            if(j != 0)
            {
                for(int f=0; f<j ; f++ )
                {
                    fic1 >> b;
                    fic1 >>pa;
                    m_ar.push_back(Arete(i,b,pa));

                }
            }
            im = Alleg::charger_image(a,loc);
            m_som.push_back(Sommet(x,y,im,act,j,ps));

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
int j = 0, pa,ps;
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
                    file << m_som[i].poids<< endl;
                    file << m_som[i].getx()<<" ";
                    file << m_som[i].gety()<<endl;
                    file << m_som[i].degre;
                    if(m_som[i].degre != 0)
                        {
                        for(int f = 0; f< m_som[i].degre;f++)
                        {
                            file << " "<<m_ar[j].m_s2;
                            file <<" "<<m_ar[j].m_pa;
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

void graphe::ajouter(int n)
{
    if (m_som[n].actif==1)
    {
        allegro_message("on ne peut pas ajouter ce sommet. Il est déjà présent sur le graphe.");
    }
    else m_som[n].actif = 1;
}

void graphe::modif_sommet(int ps,int i)
{
    if(m_som[i].actif==0)
    {
        allegro_message("on ne peut pas modifier ce sommet. Il 'est pas présent sur le graphe");
    }
    else m_som[i].poids=ps;
}

void graphe::modif_arete(int pa, int i, int j)
{
    for(int x=0;x< m_ar.size();x++)
    {
        if(m_ar[x].m_s1==i && m_ar[x].m_s2==j || m_ar[x].m_s1==j && m_ar[x].m_s2==i)
        {
            m_ar[x].m_pa=pa;
        }
    }
}



