#include "music.h"


music::music(void)
{
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);
}


music::~music(void)
{
}

void music::Play()
{
	 melody = Mix_LoadMUS( "music.flac" ); //muzika
	 Mix_PlayMusic(melody, -1);
}


void music::SFX()
{
	hit = Mix_LoadWAV("hit.flac"); //atsimusimo garsas
	Mix_PlayChannel( -1, hit, 0 );
}
