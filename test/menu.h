
#include<iostream>
#include <allegro.h>
#include <png.h>
#include <loadpng.h>
#include <jpgalleg.h>
#include <ctime>

///test chargement image
BITMAP * load_bitmap_check(char *nomImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage,NULL);
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}

void menu()
{
    BITMAP *bmp;
    BITMAP *souris;
    BITMAP * menu;
    BITMAP *rick;
    BITMAP *texte;
    BITMAP *decor;

    int test_acc=0;        //initialisation test pour gérer l'accueil
    int joueur=0;
    int x=0;          //initialisation de l'identifiant du joueur

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    bmp = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(bmp);

    souris=load_bitmap_check("images/souris.bmp");
    rick=load_bitmap_check("images/rick.bmp");
    texte=load_bitmap_check("images/texte.bmp");
    decor=load_bitmap_check("images/decor.bmp");

     while (!key[KEY_ESC] && test_acc!=-1)   //o BOUCLE DE JEU
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
            rectfill(bmp, 0, 718, 100, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 45, 743, makecol(255,255,255), -1,"retour");

            if(mouse_x>0 && mouse_x<100 && mouse_y>718 && mouse_y<768 && mouse_b&1)
            {
                test_acc=0;
            }
        }

///SI ON A CLIQUE SUR LA CASE "OPTION"
        if(test_acc==2)
        {
              //case retour
            rectfill(bmp, 0, 718, 100, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 45, 743, makecol(255,255,255), -1,"retour");

            if(mouse_x>0 && mouse_x<100 && mouse_y>718 && mouse_y<768 && mouse_b&1)
            {
                test_acc=0;
            }

        }

        ///UNE FOIS AVOIR CLIQUE SUR DISPARUS

        if(test_acc==3)
        {
            //case retour
            rectfill(bmp, 924, 718, 1024, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 974, 743, makecol(255,255,255), -1,"retour");

            if(mouse_x>924 && mouse_x<1024 && mouse_y>718 && mouse_y<768 && mouse_b&1)
            {
                test_acc=1;
            }
        }

        ///UNE FOIS AVOIR CLIQUE SUR NAGEOIRE
        if(test_acc==4)
        {
             //case retour
            rectfill(bmp, 924, 718, 1024, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 974, 743, makecol(255,255,255), -1,"retour");

            if(mouse_x>924 && mouse_x<1024 && mouse_y>718 && mouse_y<768 && mouse_b&1)
            {
                test_acc=1;
            }
        }

        ///UNE FOIS AVOIR CLIQUE SUR BAMBOU
         if(test_acc==5)
        {
            //case retour
            rectfill(bmp, 924, 718, 1024, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 974, 743, makecol(255,255,255), -1,"retour");

            if(mouse_x>924 && mouse_x<1024 && mouse_y>718 && mouse_y<768 && mouse_b&1)
            {
                test_acc=1;
            }
        }

        ///UNE FOIS AVOIR CLIQUE SUR BONUS

         if(test_acc==6)
        {
            //case retour
            rectfill(bmp, 924, 718, 1024, 768, makecol(150, 30, 30));
            textprintf_centre_ex(bmp, font, 974, 743, makecol(255,255,255), -1,"retour");

            if(mouse_x>924 && mouse_x<1024 && mouse_y>718 && mouse_y<768 && mouse_b&1)
            {
                test_acc=1;
            }
        }


        ///AFFICHAGE

        masked_blit(souris,bmp,0,0,mouse_x,mouse_y,SCREEN_W,SCREEN_H);
        blit(bmp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}
