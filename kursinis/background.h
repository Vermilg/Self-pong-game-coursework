#include "SDL.h"


#pragma once
class background
{
private:
	SDL_Surface *bckgrnd; //fono rodykle
public:
	background(void); 
	~background(void);
	void Show(SDL_Surface *scrn);
};

