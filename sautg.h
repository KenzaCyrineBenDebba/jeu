#ifndef SAUT_G_H_INCLUDED
#define SAUT_G_H_INCLUDED
typedef struct
{
	int status;
	float x,y;
	float vx,vy;
} Sprite;

typedef struct perso perso;

struct perso
{
SDL_Surface *p[8];
SDL_Rect pp;
};

typedef struct background bak;

struct background
{
SDL_Surface *b;
SDL_Rect pb;
};
void initialiser_p(perso *p);
void initialiser_b(bak *b);
void afficher_back(bak *b,SDL_Surface *screen);
void afficher_pers(perso *p,SDL_Surface *screen,int *frame);
void InitSprite(Sprite* Sp,perso *p);
void animationd(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed);
void animationg(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed);
void accelerationg(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed);
void accelerationd(SDL_Surface *screen,bak *b,perso *p,int *frame,int *speed);
void Render(Sprite* Sp,perso *p,SDL_Surface* screen,bak *b,int *frame);
void Saute(Sprite* Sp,float impulsion);
void ControleSol(Sprite* Sp);
void Gravite(Sprite* Sp,float factgravite,float factsautmaintenu,Uint8* keys);
void Evolue(Sprite* Sp,Uint8* keys);

#endif // SAUT_G_H_INCLUDED
