#include "game.h"


int main (int argc, char* args[])
{
	game start; //objektai
	music begin;
	begin.Play(); //kreipiamasi i music klase, grojimui
	start.MainCycle(); //kreipiamasi i game klase, pagrindiniui zaidimo ciklui pradeti
	return 0;
}