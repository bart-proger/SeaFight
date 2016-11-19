#include "Game.h"
#include <iostream>
//#include <locale>

int SDL_main( int argc, char* args[] )
{
	Game app;

	if (app.Init("SeaFight v0.3a", 640, 480))
	{
		app.Run();
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