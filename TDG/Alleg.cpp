#include "Alleg.h"
#include "graph.h"


namespace Alleg
{
BITMAP *page = NULL;
BITMAP *outil;
BITMAP *dino;
BITMAP *espace;
BITMAP *bambou;
BITMAP *ocean;
BITMAP *souris;
BITMAP *barre;
BITMAP *curseur;
BITMAP *buffer;
char key_last;
int mouse_click;
int mouse_unclick;
int key_press[KEY_MAX];
int key_unpress[KEY_MAX];

int mouse_click_x;
int mouse_click_y;

int mouse_move_x;
int mouse_move_y;
int verif;

Coords mouse_pos;
void init()
{
    srand(time(NULL));

    /// Gestion des caract�res accentu�s
    set_uformat(U_ASCII);

    allegro_init();
    install_timer();
    install_keyboard();
    set_keyboard_rate(0,0);
    install_mouse();
    verif=1;

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(MODE_GRAPHIQUE,LARGEURECRAN,HAUTEURECRAN,0,0)!=0)
    {
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,710,0,0)!=0)
        {
            allegro_message("prb gfx mode");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    set_display_switch_mode(SWITCH_BACKGROUND);

    //show_mouse(screen);
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    outil = create_bitmap(SCREEN_W,SCREEN_H);
    page = create_bitmap(SCREEN_W,SCREEN_H);
    outil = load_bitmap("images/Outils.bmp",NULL);
    ocean = load_bitmap("images/ocean.bmp",NULL);
    espace = load_bitmap("images/espace.bmp",NULL);
    dino = load_bitmap("images/dino.bmp",NULL);
    bambou = load_bitmap("images/bambou.bmp",NULL);
    souris = load_bitmap("images/souris.bmp",NULL);
    barre = load_bitmap("images/Curseur.bmp",NULL);
    curseur = load_bitmap("images/Cuseur2.bmp",NULL);
    rafraichir_clavier_souris();
    effacer_page();
    afficher_page();

}

void effacer_page()
{
    if (!page)
        return;
    clear_to_color(Alleg::page, 0xFFFFFF);
}

void afficher_page()
{
    if (!page)
        return;
    acquire_screen();

    masked_blit(souris,page,0,0,mouse_x+7,mouse_y+7,SCREEN_W,SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();
}

void ms(graphe &a1)
{
    int m_sommet,i;
    allegro_message("saisissez le num�ro du sommet � modifier");
    std::cout<<"saisissez le numero du sommet a modifier"<<std::endl;
    std::cin>>i;
    do
    {
        std::cout<<"saisissez le poids du sommet � changer"<<std::endl;
        std::cin>>m_sommet;

    }
    while(m_sommet<0 || m_sommet>150);
    a1.modif_sommet(m_sommet,i);
}

void ma(graphe &a1)
{
    int m_arete,i,j;
    allegro_message("saisissez le num�ro du sommet � modifier");
    std::cout<<"saisissez le numero du sommet initial"<<std::endl;
    std::cin>>i;
    std::cout<<"saisissez le numero du sommet final"<<std::endl;
    std::cin>>j;
    std::cout<<"saisissez le poids de l'arete � changer"<<std::endl;
    std::cin>>m_arete;
    a1.modif_arete(m_arete,i,j);

}

void simulation(graphe &a1)
{
    int a,b,cmp;
    float greg;
    std::vector< std::vector<int> > adj;
    std::vector< std::vector<int> > pre;
    std::vector< std::vector<int> > suc;
    std::vector<int>test;
    std::vector<int>nat;
    std::vector<int > mo;
    float k;

    std::cout <<"test";

    //INITIALISATION DE LA MATRICE D ADJACENCE
    for(int j=0; j<a1.m_ordre; j++)
    {
        mo.push_back(0);
    }
    for(int i=0; i<a1.m_ordre; i++)
    {
        adj.push_back(mo);
        pre.push_back(mo);
        suc.push_back(mo);
    }
    //REMPLISSAGE DE LA MATRICE D ADJACENCE.

    for(int i=0; i<a1.m_ar.size(); i++)
    {
        for(int j=0; j<a1.m_som.size(); j++)
        {
            if(a1.m_som[j].ind==a1.m_ar[i].m_s1)
            {
                a=j;
            }
        }
        for(int t=0; t<a1.m_som.size(); t++)
        {
            if(a1.m_som[t].ind == a1.m_ar[i].m_s2)
            {
                b=t;
            }
        }
        adj[a][b]=1;
    }

    for(int x=0; x<a1.m_ordre; x++)
    {
        for(int y=0; y<a1.m_ordre; y++)
        {
            if(adj[y][x]==1)
            {
                test.push_back(y);
            }
        }
        pre.push_back(test);

    }
    for(int x=0; x<a1.m_ordre;x++)
    {
            k=0;
            for(int i=0; i<pre[x].size();i++)
            {
                k+=a1.m_ar[pre[x][i]].m_pa*a1.m_som[pre[x][i]].poids;
                //std::cout << x <<"  " <<k << std::endl;
            }
            cmp=0;
            for(int y=0;y<a1.m_ordre;y++)
            {
                if(adj[x][y]==1)
                {
                    cmp++;
                    nat.push_back(y);
                }
            }
            suc.push_back(nat);
            for(int i=0;i<cmp;i++)
            {
                greg+=a1.m_ar[suc[x][i]].m_pa*a1.m_som[suc[x][i]].poids;
            }
            a1.m_som[x].poids=a1.m_som[x].rythme*a1.m_som[x].poids*(1-a1.m_som[x].poids/k)-greg;
    }


    /*///somme des poids de aretes et des sommets de tous les pr�decesseurs (nourriture disponible)
        k=m_ar[x].m_pa*m_som[x].ps+m_ar[y].m_pa*m_som[y].ps+m_ar[z].m_pa*m_som[z].ps;
        ///d�veloppement de la populatm_ar[x].m_pa*m_som[x].psion - le nombre de successeurs (tous les pr�dateurs)
        m_som[x].ps= m_som[x].rythme *m_som[x].ps(1- m_som[x].ps/K)-m_ar[y].m_pa*m_som[y].ps;*/
}

void connexite(graphe &a1)
{
    int s;
    allegro_message("saisissez le num�ro du sommet de d�part");
    std::cout<<"saisissez le numero du sommet de d�part"<<std::endl;
    std::cin>>s;

    ///Comment lire un vect<vect<int>>? et de quelle mani�re l'afficher?
    a1.CFCS(s);

}

void fermer_allegro()
{
    if (!page)
        return;
    destroy_bitmap(page);
    page=NULL;
    allegro_exit();
}

BITMAP *charger_image(int a, std::string name)
{
    std::string path;
    std::string pic;
    std::string type;
    type = ".bmp";
    BITMAP *image;
    if( a == 1)
        path ="Dinosaure/";
    if( a == 2)
        path ="Ocean/";
    if( a == 3)
        path = "Foret/";
    if (a == 4)
        path = "Bonus/";

    pic = path + name + type;
    std::cout <<pic;
    image = load_bitmap(pic.c_str(), NULL);

    return image;

}

void supprimersommet(graphe &a1)
{
    int n=0;
    allegro_message("saisissez le numero de votre sommet a supprimer");
    std::cout << "saisissez le numero du sommet a supprimer";
    std::cin >> n;
    a1.supprimer(n);

}

void deplacer(graphe &a1,int choix)
{
    int a,b;

    for(int i=0; i<a1.m_ordre; i++)
    {
        if((mouse_x < a1.m_som[i].getx() + 100) && (mouse_x > a1.m_som[i].getx()) && (mouse_y < a1.m_som[i].gety() + 100) && (mouse_y > a1.m_som[i].gety()) && mouse_b == 1)
        {

            do
            {
                a = mouse_x;
                b = mouse_y;
                a1.m_som[i].setx(a);
                a1.m_som[i].sety(b);
                affichage(a1,choix);
            }
            while(mouse_b==1);
        }
    }

}

int affichage(graphe &a1, int fond)
{
    int a,b,c,d;
    int fin;
    std::string n;

    effacer_page();

    ///afficher un fond d'�cran en fonction du choix de l'utilisateur
    if(fond==1)
    {
        draw_sprite(page,dino,0,0);
    }
    if(fond==2)
    {
        draw_sprite(page,ocean,0,0);
    }
    if(fond==3)
    {
        draw_sprite(page,bambou,0,0);
    }
    if(fond==4)
    {
        draw_sprite(page,espace,0,0);
    }

    draw_sprite(page,outil,0,0); ///Affichage de la barre d'outils

    rectfill(page, 0, 650, 83, 768, makecol(150, 30, 30));///Affichage bouton retour
    textprintf_centre_ex(page, font, 45, 675, makecol(255,255,255), -1,"retour");
    for(int i=0; i<a1.m_ordre; i++)
    {
        if( a1.m_som[i].actif == 1)
        {
            draw_sprite(page, a1.m_som[i].S, a1.m_som[i].getx(), a1.m_som[i].gety()); ///Affichage des sommets actifs
            ///affichage du num�ro de sommet
            textprintf_centre_ex(page, font,a1.m_som[i].getx()+15, a1.m_som[i].gety()+110,makecol(255,0,0),-1,"%d", i);
            ///affichage du poids du sommet
            textprintf_centre_ex(page, font,a1.m_som[i].getx()+100, a1.m_som[i].gety()+110,makecol(255,0,0),-1,"%d", a1.m_som[i].poids);

        }
    }
    for(int j=0; j<a1.m_ar.size(); j++)
    {
        if(a1.m_som[a1.m_ar[j].m_s1].actif!=0 && a1.m_som[a1.m_ar[j].m_s2].actif!=0)
        {
            if(a1.m_som[a1.m_ar[j].m_s1].gety() > a1.m_som[a1.m_ar[j].m_s2].gety())
            {
                if(a1.m_som[a1.m_ar[j].m_s1].getx() < a1.m_som[a1.m_ar[j].m_s2].getx())
                {
                    a = 75;
                    b = 0;
                    c = 0;
                    d = 110;
                }
                else if(a1.m_som[a1.m_ar[j].m_s1].getx() > a1.m_som[a1.m_ar[j].m_s2].getx())
                {
                    a = 75;
                    b = 0;
                    c = 75;
                    d = 110;
                }
                else
                {
                    a = 75;
                    b = 0;
                    c = 75;
                    d = 110;
                }

            }
            else if(a1.m_som[a1.m_ar[j].m_s1].gety() == a1.m_som[a1.m_ar[j].m_s2].gety())
            {
                if(a1.m_som[a1.m_ar[j].m_s1].getx() < a1.m_som[a1.m_ar[j].m_s2].getx())
                {
                    a = 125;
                    b = 75;
                    c = 0;
                    d = 75;
                }
                else
                {
                    a = 0;
                    b = 75;
                    c = 125;
                    d = 75;
                }
            }
            else
            {
                if(a1.m_som[a1.m_ar[j].m_s1].getx() < a1.m_som[a1.m_ar[j].m_s2].getx())
                {
                    a = 75;
                    b = 110;
                    c = 75;
                    d = 0;
                }
                else if(a1.m_som[a1.m_ar[j].m_s1].getx() > a1.m_som[a1.m_ar[j].m_s2].getx())
                {
                    a = 75;
                    b = 110;
                    c = 75;
                    d = 0;
                }
                else
                {
                    a = 75;
                    b = 110;
                    c = 75;
                    d = 0;
                }
            }

            line(page,a1.m_som[a1.m_ar[j].m_s1].getx()+a,a1.m_som[a1.m_ar[j].m_s1].gety()+b,a1.m_som[a1.m_ar[j].m_s2].getx()+c,a1.m_som[a1.m_ar[j].m_s2].gety()+d,0XFF6347);///Affichage des aretes
            circlefill(page,a1.m_som[a1.m_ar[j].m_s2].getx()+c,a1.m_som[a1.m_ar[j].m_s2].gety()+d,7,0XFF6347);///Affichage des cercle
            ///affichage du poids de l'arete
            textprintf_centre_ex(page, font,(a1.m_som[a1.m_ar[j].m_s1].getx()+a+a1.m_som[a1.m_ar[j].m_s2].getx()+c)/2,
                                 (a1.m_som[a1.m_ar[j].m_s1].gety()+b+a1.m_som[a1.m_ar[j].m_s2].gety()+d)/2,makecol(255,255,255),12,"%d",a1.m_ar[j].m_pa);
        }
    }
    if(verif < 0)
        {
            Duree(a1);
            simulation(a1);
        }
    deplacer(a1,fond);
    afficher_page();

    ajout(a1);
    ///si on clique sur la case +/- sommets
    if(mouse_x>0 && mouse_x<85 && mouse_y>212 && mouse_y<245 && mouse_b&1)
    {
        ms(a1);
    }
    ///si on clique sur supprimer
    if(mouse_x>0 && mouse_x<85 && mouse_y>40 && mouse_y<72 && mouse_b&1)
    {
        supprimersommet(a1);
    }
    ///si on clique sur +/- aretes
    if(mouse_x>0 && mouse_x<85 && mouse_y>305 && mouse_y<340 && mouse_b&1)
    {
        ma(a1);
    }
    ///si on clique sur simulation
    if(mouse_x>0 && mouse_x<85 && mouse_y>474 && mouse_y<510 && mouse_b&1)
    {
        verif = -verif;
    }
    ///si on clique sur connexit�
    if(mouse_x>0 && mouse_x<85 && mouse_y>396 && mouse_y<429 && mouse_b&1)
    {
        connexite(a1);
    }



    fin = retour();
    return fin;

}


void rafraichir_clavier_souris()
{
    static int mouse_prev, mouse_now;
    static int key_prev[KEY_MAX], key_now[KEY_MAX];
    int k;

    mouse_prev = mouse_now;
    mouse_now = mouse_b;
    mouse_click = mouse_now & ~mouse_prev;
    mouse_unclick = ~mouse_now & mouse_prev;

    mouse_pos = Coords(mouse_x, mouse_y);

    for (k=0; k<KEY_MAX; k++)
    {
        key_prev[k] = key_now[k];
        key_now[k] = key[k];
        key_press[k] = key_now[k] && !key_prev[k];
        key_unpress[k] = !key_now[k] && key_prev[k];
    }

    key_last = '\0';
    while (keypressed())
        key_last = (char)readkey();

    get_mouse_mickeys(&mouse_move_x, &mouse_move_y);

    if (mouse_click)
    {
        mouse_click_x = mouse_x;
        mouse_click_y = mouse_y;
    }
}

int menu()
{
    int a = 0;
    BITMAP *bmp;
    BITMAP *souris;
    BITMAP * menu;
    BITMAP *rick;
    BITMAP *texte;
    BITMAP *decor;
    BITMAP *option;

    int test_acc=0;        //initialisation test pour g�rer l'accueil

    bmp = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(bmp);

    souris=load_bitmap("images/souris.bmp",NULL);
    rick=load_bitmap("images/rick.bmp",NULL);
    texte=load_bitmap("images/texte.bmp",NULL);
    decor=load_bitmap("images/decor.bmp",NULL);
    option=load_bitmap("images/option.bmp",NULL);

    while (a==0 && test_acc != -1)   //o BOUCLE DE JEU
    {
        clear(bmp);//commencer par nettoyer la bitmap

///ACCUEIL
        if(test_acc==0)
        {
            masked_blit(decor,bmp,0,0,0,0,SCREEN_W,SCREEN_H);
            //JOUER
            rectfill(bmp, 362, 300, 662, 400, makecol(20, 20, 150));
            rectfill(bmp, 367, 305, 657, 395, makecol(0, 0,0));
            textprintf_centre_ex(bmp, font, 512, 350, makecol(255,255,255), -1," COLLECTIONS ");

            if(mouse_x>362 && mouse_x<662 && mouse_y>300 && mouse_y<400 && mouse_b&1)
            {
                test_acc=1;
            }

            //PROFILS
            rectfill(bmp, 462, 500, 562, 550, makecol(20, 150, 20));
            rectfill(bmp, 467, 505, 557, 545, makecol(0,0,0));
            textprintf_centre_ex(bmp, font, 512, 525, makecol(255,255,255), -1," OPTIONS ");

            if(mouse_x>462 && mouse_x<562 && mouse_y>500 && mouse_y<550 && mouse_b&1)
            {
                test_acc=2;

            }

            //QUITTER

            rectfill(bmp, 462, 600, 562, 650, makecol(150, 30, 30));
            rectfill(bmp, 467, 605, 557, 645, makecol(0,0,0));
            textprintf_centre_ex(bmp, font, 512, 625, makecol(255,255,255), -1,"QUITTER");

            if(mouse_x>462 && mouse_x<562 && mouse_y>600 && mouse_y<650 && mouse_b&1)
            {
                test_acc=-1;
                a=-1;
            }

            masked_blit(rick,bmp,0,0,840,460,SCREEN_W,SCREEN_H);
            masked_blit(texte,bmp,0,0,650,460,SCREEN_W,SCREEN_H);
        }


///SI ON A CLIQUE SUR COLLECTION

        if(test_acc==1)
        {
            masked_blit(decor,bmp,0,0,0,0,SCREEN_W,SCREEN_H);

            rectfill(bmp, 362, 121, 662, 171, makecol(167, 103, 38));
            rectfill(bmp, 367, 126, 657, 166, makecol(0, 0, 0));
            textprintf_centre_ex(bmp, font, 512, 146, makecol(255,255,255), -1,"DISPARUS");
            if(mouse_x>362 && mouse_x<662 && mouse_y>121 && mouse_y<171 && mouse_b&1)
            {
                test_acc=3;
            }

            rectfill(bmp, 362, 271, 662, 321, makecol(30, 127, 203));
            rectfill(bmp, 367, 276, 657, 316, makecol(0,0, 0));
            textprintf_centre_ex(bmp, font, 512, 296, makecol(255,255,255), -1,"NAGEOIRE");
            if(mouse_x>362 && mouse_x<662 && mouse_y>271 && mouse_y<321 && mouse_b&1)
            {
                test_acc=4;
            }

            rectfill(bmp, 362, 421, 662, 471, makecol(58, 137, 35));
            rectfill(bmp, 367, 426, 657, 466, makecol(0, 0, 0));
            textprintf_centre_ex(bmp, font, 512, 446, makecol(255,255,255), -1,"BAMBOU");
            if(mouse_x>362 && mouse_x<662 && mouse_y>421 && mouse_y<471 && mouse_b&1)
            {
                test_acc=5;
            }

            rectfill(bmp, 362, 571, 662, 621, makecol(36, 68, 92));
            rectfill(bmp, 367, 576, 657, 616, makecol(0, 0, 0));
            textprintf_centre_ex(bmp, font, 512, 596, makecol(255,255,255), -1,"BONUS");
            if(mouse_x>362 && mouse_x<662 && mouse_y>571 && mouse_y<621 && mouse_b&1)
            {
                test_acc=6;
            }


            //case retour
            rectfill(bmp, 0, 650, 100, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 45, 675, makecol(255,255,255), -1,"retour");

            if(mouse_x>0 && mouse_x<100 && mouse_y>650 && mouse_y<768 && mouse_b&1)
            {
                test_acc=0;
            }
        }

///SI ON A CLIQUE SUR LA CASE "OPTION"
        if(test_acc==2)
        {
            masked_blit(option,bmp,0,0,0,0,SCREEN_W,SCREEN_H);
            //case retour
            rectfill(bmp, 0, 650, 100, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 45, 675, makecol(255,255,255), -1,"retour");

            if(mouse_x>0 && mouse_x<100 && mouse_y>650 && mouse_y<768 && mouse_b&1)
            {
                test_acc=0;
            }

        }

        ///UNE FOIS AVOIR CLIQUE SUR DISPARUS

        if(test_acc==3)
        {
            a = 1;
        }

        ///UNE FOIS AVOIR CLIQUE SUR NAGEOIRE
        if(test_acc==4)
        {
            a = 2;
        }

        ///UNE FOIS AVOIR CLIQUE SUR BAMBOU
        if(test_acc==5)
        {
            a = 3;
        }

        ///UNE FOIS AVOIR CLIQUE SUR BONUS

        if(test_acc==6)
        {
            a = 4;
        }


        ///AFFICHAGE

        masked_blit(souris,bmp,0,0,mouse_x,mouse_y,SCREEN_W,SCREEN_H);
        blit(bmp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    return a;
}

int retour()
{
    int a;
    if(mouse_x < 83 && mouse_y > 660 && mouse_b ==1)
    {
        a = 1;
    }
    else
        a = 0;
    return a;
}

void ajout(graphe &a1)
{
    int n_sommet;
    if (mouse_x>0 && mouse_x<85 && mouse_y>126 && mouse_y<160 && mouse_b==1)
    {
        allegro_message("saisissez le numero du sommet � ajouter sur la console");
        std::cout<<"saisissz le numero du sommet a ajouter"<<std::endl;
        std::cin>>n_sommet;
        a1.ajouter(n_sommet);
    }
}


void Duree(graphe &a1)
{
    draw_sprite(page,barre,600,600);
    if(mouse_x>580+a1.gettemps() && mouse_x<620+a1.gettemps() && mouse_y > 640 && mouse_y < 670 && mouse_b==1)
        {
            while(mouse_b==1)
                {
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,curseur,590+a1.gettemps(),630);
                    a1.settemps(mouse_x - 600);
                    textprintf_centre_ex(buffer, font,680,680,makecol(255,255,255),12,"Ann�e : %d",a1.gettemps());
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
        }
        else
            {
                draw_sprite(page,curseur,590+a1.gettemps(),630);
                textprintf_centre_ex(page, font,680,680,makecol(255,255,255),12,"Ann�e : %d",a1.gettemps());
            }
}

}




