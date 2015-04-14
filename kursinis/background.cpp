#include "background.h"

background::background(void)
{
}


background::~background(void)
{
}

void background::Show(SDL_Surface *scrn)
{
	bckgrnd = SDL_LoadBMP("background.bmp"); //backgroundo paveiksliukas
	SDL_BlitSurface(bckgrnd, NULL, scrn, NULL); //isvedamas i ekrana
	SDL_FreeSurface(bckgrnd); //atlaisvinama atmintis
}