#include "Game.h"
#include <iostream>
//#include <locale>

int SDL_main( int argc, char* args[] )
{
	Game app;

	if (app.init("SeaFight v0.3a бла бла бла", 640, 480))
	{
		app.run();
	}
#ifdef _DEBUG
	else
	{
		system("pause");
		return 1;
	}
#endif
	return 0;
}