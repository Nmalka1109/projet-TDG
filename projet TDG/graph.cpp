#include "graphe.h"
#include <iostream>
#include <fstream>

///soure openclassroom


using namespace std;

graphe::graphe()
{
    m_ordre = 6 ;
}

graphe::graphe(int pordre)
    :m_ordre(pordre)
{

}
graphe::~graphe()
{

}

void graphe::creation()
{


    for(int i = 0; i < m_ordre ; i++)
    {
        m_som.push_back(Sommet());
    }





}
///récuperation des données du fichier
void graphe::recuperation(string name1)
{

    string n1 = name1 + ".txt" ;

   ifstream fichier(n1);

   if(fichier)
   {



int v1;
/// stockage dans la matrice
         for (int i = 0; i < m_ordre  ; i++)
         {

             vector<int> temp;
             for(int j = 0; j < m_ordre ; j++ )
             {
                 fichier >> v1;
                 temp.push_back(v1);

             }

             m_Matrice.push_back(temp);

         }


   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }



   if(fichier)
   {


string v2;
///stockage dans le vecteur de sommet
         for (int i = 0; i < m_ordre  ; i++)
         {
            fichier >> v2;
            m_som[i].m_nom = v2;
         }


   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }


}

void graphe::affichage()
{
    for (int i = 0 ; i < m_ordre ; i++)
    {
        for (int j = 0 ; j < m_ordre ; j++)
        {
            if(m_Matrice[i][j] == 1)
            {
                string n1,n2;
                n1 = m_som[i].m_nom;
                n2 = m_som[j].m_nom;

                cout << n1 << " influence " << n2 << endl;
            }
        }

}
}
