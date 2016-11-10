#include "Network.h"
#include <iostream>

bool Network::Init()
{
	if (SDLNet_Init() < 0) {
		std::cerr << "[error] SDLNet_Init: " << SDLNet_GetError() << std::endl;
		return false;
	}
	else
		return true;
}

void Network::Free()
{
	SDLNet_Quit();
}
