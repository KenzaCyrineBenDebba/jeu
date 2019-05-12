#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "saut_g.h"
#define STAT_SOL 0
#define STAT_AIR 1
#define largeur 1200
#define hauteur 800

void initialiser_p(perso *p)
{
 p->p[0]=IMG_Load("p1.png");
 p->p[1]=IMG_Load("p2.png");
 p->p[2]=IMG_Load("p3.png");
 p->p[3]=IMG_Load("p4.png");
 p->p[4]=IMG_Load("p5.png");
 p->p[5]=IMG_Load("p6.png");
 p->p[6]=IMG_Load("p7.png");
 p->p[7]=IMG_Load("p8.png");

 p->pp.x=10;
 p->pp.y=500;
}

void initialiser_b(bak *b)
{
b->b=IMG_Load("backk.png");
b->pb.x=0;
b->pb.y=0;
}

void afficher_back(bak *b,SDL_Surface *screen)
{
SDL_BlitSurface(b->b,NULL,screen,&b->pb);
SDL_Flip(screen);
}

void afficher_pers(perso *p,SDL_Surface *screen,int *frame)
{
SDL_BlitSurface(p->p[*frame],NULL,screen,&p->pp);
SDL_Flip(screen);
}

void InitSprite(Sprite* Sp,perso *p)
{
	Sp->x = p->pp.x;
	Sp->y = p->pp.y;
	Sp->status = STAT_SOL;
	Sp->vx = Sp->vy = 0.0f;
}

void Render(Sprite* Sp,perso *p,SDL_Surface* screen,bak *b,int *frame)
{
	p->pp.x = (Sint16)Sp->x;
	p->pp.y = (Sint16)Sp->y;
	afficher_back(b,screen);
	afficher_pers(p,screen,frame);
	SDL_Flip(screen);
}

void Saute(Sprite* Sp,float impulsion)
{
	Sp->vy = -impulsion;
	Sp->status = STAT_AIR;
}

void ControleSol(Sprite* Sp)
{
	if (Sp->y>500.0f)
	{
		Sp->y = 500.0f;
		if (Sp->vy>0)
			Sp->vy = 0.0f;
		Sp->status = STAT_SOL;
	}
}

void Gravite(Sprite* Sp,float factgravite,float factsautmaintenu,Uint8* keys)
 {
	if (Sp->status == STAT_AIR && keys[SDLK_SPACE])
		factgravite/=factsautmaintenu;
	Sp->vy += factgravite;
}

void accelerationg(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed)
{
     afficher_back(b,screen);
    if((*frame)<=3||(*frame)>=6)
    {
        *frame=4;
    }
    afficher_pers(p,screen,frame);
    p->pp.x-=((*speed)*3);
    SDL_Delay(20);
}

void accelerationd(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed)
{
   afficher_back(b,screen);
    if((*frame)>=2)
    {
        *frame=0;
    }
    afficher_pers(p,screen,frame);
    p->pp.x+=((*speed)*3);
    SDL_Delay(20);
}

void animationd(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed)
{
    afficher_back(b,screen);
    if((*frame)>=2)
    {
        *frame=0;
    }
     p->pp.x+=(*speed);
     afficher_pers(p,screen,frame);
     SDL_Delay(50);
}

void animationg(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed)
{
    afficher_back(b,screen);
    if((*frame)<=3||(*frame)>=6)
    {
        *frame=4;
    }
    p->pp.x-=(*speed);
    afficher_pers(p,screen,frame);
    SDL_Delay(50);
}


void Evolue(Sprite* Sp,Uint8* keys)
{
	float lateralspeed = 0.5f;
	float airlateralspeedfacteur = 1.0f;
	float maxhspeed = 3.0f;
	float adherance = 1.5f;
	float impulsion = 6.0f;
	float factgravite = 0.5f;
	float factsautmaintenu = 3.0f;
// controle lateral
	if (Sp->status == STAT_AIR) // (*2)
		lateralspeed*= airlateralspeedfacteur;
	if (keys[SDLK_LEFT]) // (*1)
		Sp->vx-=lateralspeed;
	if (keys[SDLK_RIGHT])
		Sp->vx+=lateralspeed;
	if (Sp->status == STAT_SOL && !keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) // (*3)
		Sp->vx/=adherance;
// limite vitesse
	if (Sp->vx>maxhspeed) // (*4)
		Sp->vx = maxhspeed;
	if (Sp->vx<-maxhspeed)
		Sp->vx = -maxhspeed;
// saut
	if (keys[SDLK_SPACE] && Sp->status == STAT_SOL)
		Saute(Sp,impulsion);
	Gravite(Sp,factgravite,factsautmaintenu,keys);
	ControleSol(Sp);
// application du vecteur à la position.
	Sp->x +=2;
	Sp->y +=Sp->vy;
}


