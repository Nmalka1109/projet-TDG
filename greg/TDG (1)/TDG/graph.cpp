#include "graph.h"
#include "Alleg.h"
#include <iostream>
#include <fstream>

///soure openclassroom


using namespace std;

graphe::graphe(int a)
{
    tps = 0;
    BITMAP *im = NULL;
    int x,y,j,act,pa,ps,ind;
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
    else
        std::cout <<"Erreur menu";
    std::ifstream fic1(name,std::ios::in);

    fic1 >> m_ordre;
    for(int i=0; i< m_ordre; i++)
    {
        fic1 >>act;
        fic1 >>loc;
        fic1 >>ind;
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
        m_som.push_back(Sommet(x,y,im,act,j,ps,ind));

    }
    if(!fic1)
        std::cout <<"pas de fichier";
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
    else
        std::cout <<"Erreur menu";

    ofstream file(name);
    if(!file)
    {
        std::cout <<"erreur fichier de sauvegarde";
    }
    else
    {
        file << m_som.size()<<endl;
        for(int i =0; i < m_som.size(); i++)
        {
            file << m_som[i].actif<<endl;
            file << i<< endl;
            file << i<< endl;
            file << m_som[i].poids<< endl;
            file << m_som[i].getx()<<" ";
            file << m_som[i].gety()<<endl;
            file << m_som[i].degre;
            if(m_som[i].degre != 0)
            {
                for(int f = 0; f< m_som[i].degre; f++)
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
    else
        m_som[n].actif = 1;
}

void graphe::modif_sommet(int ps,int i)
{
    if(m_som[i].actif==0)
    {
        allegro_message("on ne peut pas modifier ce sommet. Il 'est pas présent sur le graphe");
    }
    else
        m_som[i].poids=ps;
}

void graphe::modif_arete(int pa, int i, int j)
{
    for(int x=0; x< m_ar.size(); x++)
    {
        if(m_ar[x].m_s1==i && m_ar[x].m_s2==j || m_ar[x].m_s1==j && m_ar[x].m_s2==i)
        {
            m_ar[x].m_pa=pa;
        }
    }
}

int graphe::gettemps()
{
    return tps;
}

void graphe::settemps(int t)
{
    if(t>300) t = 300;
    if (t<0) t = 0;
    tps = t;
}
std::vector<int> graphe::RechercheCFC(int s)
{
    //VARIABLES
    std::vector< std::vector<int> > adj;
    std::vector<int> mo;
    std::vector <int> c1;
    std::vector <int> c2;
    std::vector <int> c;
    std::vector <int> lro;
    std::vector <int> marques;
    int a,b;
    int ajoute =1;
    int blind=0;

//RECUPERATION DU SOMMET DE REFERENCE

    //INITIALISATION DE LA MATRICE D ADJACENCE
    for(int j=0; j<m_ordre; j++)
    {
        mo.push_back(0);
    }
    for(int i=0; i<m_ordre; i++)
    {
        adj.push_back(mo);
    }
    //REMPLISSAGE DE LA MATRICE D ADJACENCE.
    for(int i=0; i<m_ar.size(); i++)
    {
        for(int j=0; j<m_som.size(); j++)
        {
            if(m_som[j].ind==m_ar[i].m_s1)
            {
                a=j;
            }
        }
        for(int t=0; t<m_som.size(); t++)
        {
            if(m_som[t].ind == m_ar[i].m_s2)
            {
                b=t;
            }
        }
        adj[a][b]=1;
    }

    //INTIALISATIONS DES VECTEURS
    for(int i=0; i<m_som.size(); i++)
    {
        c1.push_back(0);
        c2.push_back(0);
        c.push_back(0);
        lro.push_back(0);
        marques.push_back(0);
    }
    //LE SOMMET S DEVIENT CONNEXE
    for(int i=0; i<m_ordre; i++)
    {
        if(m_som[i].ind==s)
        {
            c1[i]=1;
            c2[i]=1;
        }
    }
//RECHERCHE C1
    while(ajoute==1)
    {
        ajoute=0;


        for(int x=0; x<m_ordre; x++)
        {
            if(marques[x]==0 && c1[x]==1)
            {
                marques[x]=1;
                for(int y=0; y<m_ordre; y++)
                {
                    if(adj[x][y]==1 && marques[y]==0)
                    {
                        c1[y]=1;
                        ajoute=1;
                    }
                }
            }
        }
    }

    //RECHERCHE C2
    for(int i=0; i<m_ordre; i++)
    {
        //RESET DE MARQUES et lro

        for(int t=0; t<m_ordre; t++)
        {
            marques[t]=0;
            lro[t]=0;
        }
        //LE SOMMET S DEVIENT CONNEXE
        for(int t=0; t<m_ordre; t++)
        {
            if(m_som[t].ind==m_som[i].ind)
            {
                lro[t]=1;
            }
        }
        //
        ajoute=1;
        while(ajoute==1)
        {
            ajoute=0;


            for(int x=0; x<m_ordre; x++)
            {
                if(marques[x]==0 && lro[x]==1)
                {
                    marques[x]=1;
                    for(int y=0; y<m_ordre; y++)
                    {
                        if(adj[x][y]==1 && marques[y]==0)
                        {
                            lro[y]=1;
                            ajoute=1;
                        }
                    }
                }
            }
        }
        //REGARDER SI CE TRUC PEUT ALLER A S
        for(int g=0; g<m_ordre; g++)  //PARCOURS DE mo
        {
            if(m_som[g].ind==s)
            {
                if(lro[g]==1)
                {

                    c2[i]=1;
                }
            }
        }

    }
    //CREATION DE LA COMPOSANTE FORTEMENT CONNEXE
    for(int i=0; i<m_ordre; i++)
    {
        c[i]=c1[i]&c2[i];
    }

    return c;
}

std::vector <std::vector<int> > graphe::CFCS(int s)
{
    std::vector< std::vector<int> > adj;
    std::vector<int > mo;
    std::vector<int > lro;
    std::vector<std::vector<int>>tabc;
    std::vector<int>marques;
    int x,y,a,b;

    //INITIALISATION DE LA MATRICE D ADJACENCE
    for(int j=0; j<m_ordre; j++)
    {
        mo.push_back(0);
    }
    for(int i=0; i<m_ordre; i++)
    {
        adj.push_back(mo);
    }
    //REMPLISSAGE DE LA MATRICE D ADJACENCE.
    for(int i=0; i<m_ar.size(); i++)
    {
        for(int j=0; j<m_som.size(); j++)
        {
            if(m_som[j].ind==m_ar[i].m_s1)
            {
                a=j;
            }
        }
        for(int t=0; t<m_som.size(); t++)
        {
            if(m_som[t].ind == m_ar[i].m_s2)
            {
                b=t;
            }
        }
        adj[a][b]=1;
    }
    //INTIALISATIONS DES VECTEURS
    for(int i=0; i<m_som.size(); i++)
    {
        marques.push_back(0);
        lro.push_back(0);
        tabc.push_back(lro);
    }

    //POUR TOUS LES SOMMETS X NON MARQUES
    //RECHERCHER LA COMPOSANTE FORTEMENT CONNEXE DE X
    for(x=0;x<m_ordre;x++)
    {
        if(!marques[x])
        {
            tabc[x]=RechercheCFC(s);
            marques[x]=1;
            for(y=0; y<m_ordre;y++)
            {
                if(tabc[x][y] && !marques[y])
                {
                    marques[y]=1;
                }
            }
        }
    }
   return tabc;
}

