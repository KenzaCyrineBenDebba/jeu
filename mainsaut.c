#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "saut_g.h"
#define largeur 1200
#define hauteur 800
#define STAT_SOL 0
#define STAT_AIR 1
int main(int argc,char** argv)
{
	SDL_Surface* screen;
	int numkeys;
	Uint8 * keys;
	Sprite S;
	perso p;
    bak b;
	int frame=0,speed=10;
	Uint32 timer,elapsed;
	SDL_Init(SDL_INIT_VIDEO);
	screen=SDL_SetVideoMode(largeur,hauteur,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
	initialiser_p(&p);
	initialiser_b(&b);
	afficher_back(&b,screen);
	afficher_pers(&p,screen,&frame);
	InitSprite(&S,&p);
	SDL_EnableKeyRepeat(10,10);
	do
	{
	    int t=1;
	    InitSprite(&S,&p);
		afficher_back(&b,screen);
		afficher_pers(&p,screen,&frame);
		timer = SDL_GetTicks();
		SDL_PumpEvents();
		keys = SDL_GetKeyState(&numkeys);

		  if(keys[SDLK_v])
                  {
		  accelerationg(screen,&b,&p,&frame,&speed);
                  frame++;
		  }
		  if(keys[SDLK_n])
                  {
		  accelerationd(screen,&b,&p,&frame,&speed);
                  frame++;
		  }


                  if(keys[SDLK_SPACE])
		  {
                  while(t)
		  {
		  timer=SDL_GetTicks();
		  Evolue(&S,keys);
		  Render(&S,&p,screen,&b,&frame);
		  SDL_Flip(screen);
		  elapsed = SDL_GetTicks() - timer;
		  if (elapsed<20)
		  {
		  SDL_Delay(20-elapsed);
		  }
                  if(S.status==STAT_SOL)
                  {
                     t=0;
                  }
                  }
                  }


		  if(keys[SDLK_LEFT])
		  {
                  animationg(screen,&b,&p,&frame,&speed);
                  frame++;
		  }


          if (keys[SDLK_RIGHT])
		  {
                  animationd(screen,&b,&p,&frame,&speed);
                  frame++;
          }



	} while (!keys[SDLK_ESCAPE]);
	int i=0;
        for(;i<8;i++)
	{
  		SDL_FreeSurface(p.p[i]);
        }
        SDL_FreeSurface(b.b);
	SDL_Quit();
	return 0;
}
