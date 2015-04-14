#include "SDL_mixer.h"

#pragma once
class music
{
private:
Mix_Music *melody; //muzikos rodykle
Mix_Chunk *hit; //atsimusimo garso efekto rodykle
public:
	music(void);
	~music(void);
	void Play();
	void SFX();
};

