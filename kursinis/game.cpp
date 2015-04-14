#include "game.h"



game::game()
{
	SDL_Init(SDL_INIT_EVERYTHING); //sdl paleidimas
	TTF_Init(); //ttf paleidimas
}


game::~game()
{
	exit(1);
	TTF_Quit(); //ttf uzdarymas, atminties atlaisvinimas
	SDL_Quit(); //sdl uzdarymas, atminties atlaisvinimas
}

void game::MainCycle() //pagrindinis ciklas eiti zaidimui
{
	points = 0;
	LoadGame();
	bool running = true;
	while (running == true)
	{
		SDL_PollEvent(&occur);
		if(occur.type == SDL_QUIT)
		{
			running = false;
		}
		Logic();
		Score();
		DrawScreen();
	}
}


void game::LoadGame() //mustuku ir kamuoliuko nupiesimas
{

	SDL_WM_SetCaption("Self - Pong", NULL); //zaidimo pavadinimas
	screen = SDL_SetVideoMode(800, 450, 32, SDL_HWSURFACE); //ekrano rezoliucija
	
	PlayerPaddle.x = 20; //kairiojo mustuko koordinates
	PlayerPaddle.y = 175;
	PlayerPaddle.h = 100;
	PlayerPaddle.w = 10;

	AIpaddle.x = 760; //desiniojo mustuko koordinates
	AIpaddle.y = 175;
	AIpaddle.h = 100;
	AIpaddle.w = 10;


	red = SDL_MapRGB(screen->format, 225, 32, 64); //mustuku spalva
	
	ResetBall();
}

void game::ResetBall() //kamuoliuko pastatymas i centra ir trajektorijos skaiciavimas
{
	blue = SDL_MapRGB(screen->format, 64, 160, 192); // kamuoliuko spalva

	Ball.w = 15; //ilgis ir plotis
	Ball.h = 15;

	Ball.x = 390; //kamuoliuko koordinates
	Ball.y = 175;

	srand(time(NULL)); //pasiruosimas atsitiktinio dydzio skaiciavimui

	int leftright, updown;
	leftright = rand() % 100; //atsitiktiniai dydziai nustatymui i kuri sona kamuoliukas leks
	updown = rand() % 100;


	if (leftright > 50)
	{
		if(updown > 50)
		{
			xVel = 2;
			yVel = 2; 
		}
		else
		{
			xVel = 2;
			yVel = -2;
		}
	}
	if (leftright < 50)
	{
		if(updown > 50)
		{
			xVel = -2;
			yVel = 2;
		}
		else
		{
			xVel = -2;
			yVel = -2;
		}
	}
}

void game::Logic() //veiksmai mygtuko paspaudimo metu
{
	Uint8 *keystates = SDL_GetKeyState(NULL);
	if(keystates[SDLK_w])
	{
		PlayerPaddle.y -= 2;
		AIpaddle.y -= 2;
	}
	if(keystates[SDLK_s])
	{
		PlayerPaddle.y += 2;
		AIpaddle.y += 2;
	}
	if(PlayerPaddle.y < 1)
	{
		PlayerPaddle.y = 1;
		AIpaddle.y = 1;
	}
	if(PlayerPaddle.y + PlayerPaddle.h> 449)
	{
		PlayerPaddle.y = 449 - PlayerPaddle.h;
		AIpaddle.y = 449 - AIpaddle.h;
	}

	Ball.x += xVel; //kamuoliuko judejimas
	Ball.y += yVel;

	if (Ball.y < 1) //kamuoliuko atsimusimai ir trajektorijos keitimas
	{
		pSFX.SFX(); //atsimusimo garsas
		yVel = -yVel;
	}
	if(Ball.y + Ball.h> 449)
	{
		pSFX.SFX();
		yVel = -yVel;
	}
	
	if(Ball.x < 1)
	{
		points = 0;
		ResetBall();
	}
	if(Ball.x + Ball.w > 799)
	{
		points = 0;
		ResetBall();
	}

	if (CheckCollision(Ball, PlayerPaddle) == true) //atsidauzimas i mustuka
	{
		pSFX.SFX(); //atsimusimo garsas
		points += 1; //tasku skaiciavimas
		xVel = -xVel;
		xVel = xVel + 0.1; //kamuoliuko greitejimas kiekvienu atmusimu
		yVel = yVel + 0.1;
	}
	if (CheckCollision(Ball, AIpaddle) == true)
	{
		pSFX.SFX();
		points += 1;
		xVel = -xVel;
		xVel = xVel + 0.1;
		yVel = yVel + 0.1;
	}
}

void game::Score()
{
	stringstream strs;
	strs << points;
	string temp_str = strs.str();
	char* char_type = (char*) temp_str.c_str(); //points konvertavimas, nes int nepriima


	koord.x = 387; //tasku koordinates
	koord.y = 185;

	SDL_Color textColor = { 32, 32, 64 };  //rezultato teksto spalva
	font = TTF_OpenFont( "capture.ttf", 54 );
	txt = TTF_RenderText_Solid( font, temp_str.c_str(), textColor );
}

bool game::CheckCollision(SDL_Rect r1, SDL_Rect r2) //tikrinamas kamuoliuko atsidauzimas i mustuka
{
	if(PointInRect(r1.x, r1.y, r2) == true || 
		PointInRect(r1.x + r1.w, r1.y, r2) == true ||
		PointInRect(r1.x, r1.y + r1.h, r2) == true ||
		PointInRect(r1.x + r1.w, r1.y + r1.h, r2) == true
		||PointInRect(r1.x + r1.h, r1.y + r1.w, r2) ==true
		||PointInRect(r1.x + r1.w, r1.y + r1.w, r2) == true
		)
		return true;
	else
		return false;

}

bool game::PointInRect(int x, int y, SDL_Rect rec) //atsimusimui tikrinami taskai
{
		if (x > rec.x && y > rec.y && x < rec.x + rec.w && y < rec.y + rec.h)
		return true;
	else
		return false;
}


void game::DrawScreen() //viskas nupiesiama i ekrana
{
	gBCG.Show(screen); //fonas
	SDL_BlitSurface(txt, NULL, screen, &koord); //rezultatas
	SDL_FillRect(screen, &PlayerPaddle, red); //kairysis mustukas
	SDL_FillRect(screen, &AIpaddle, red); //desinysis mustukas
	SDL_FillRect(screen, &Ball, blue); //kamuoliukas
	SDL_Flip(screen); //viskas inicializuojama
	SDL_FreeSurface(txt); //atlaisvinamas tekstas, kad nerytu atminties
}

