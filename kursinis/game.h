#include "SDL.h" //visam zaidimui
#include "SDL_ttf.h" //tekstui isvesti
#include <cstdlib> //rand funkcijai
#include <ctime> //norint, kad rank butu tikrai atsitiktinis
#include <sstream> //norint isvesti teksta ekranan reikalingas string
#include <string.h>
#include "background.h" //background klase
#include "music.h" //music klase


using namespace std;


#pragma once
class game
{
private:
	SDL_Surface *screen; //rodykle norint isvesti viska i ekrana
	TTF_Font *font; //rodykle norint tureti srifta
	SDL_Surface *txt; //rodykle norint isspausdinti teksta ekranan
	music pSFX; //parnesamas garso efektas
	SDL_Rect koord; //koordinates kuriose bus padetas score
	int points; //skaiciuojamas score
	background gBCG; //parnesamas fonas
	SDL_Event occur; //SDL ar kasnors vyksta
	Uint32 red; //spalva kuria nudazyti mustukai
	Uint32 blue; //spalva kuria nudazytas rutuliukas
	SDL_Rect PlayerPaddle; //kairysis mustukas
	SDL_Rect AIpaddle; //desinysis mustukas
	SDL_Rect Ball; //kamuokiukas
	double xVel, yVel; //kamuoliuko greitis
public:
	game();
	~game();
	void MainCycle();
	void LoadGame();
	void ResetBall();
	void Logic();
	bool CheckCollision(SDL_Rect r1, SDL_Rect r2);
	bool PointInRect(int x, int y, SDL_Rect rec);
	void DrawScreen();
	void Score();
};

