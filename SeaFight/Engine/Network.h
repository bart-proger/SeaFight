#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#ifndef LINK_LIB_SDL2_NET
	#define LINK_LIB_SDL2_NET
	#pragma comment(lib, "SDL2_net.lib")
#endif

class Network
{
public:
	static bool Init();
	static void Free();

private:
	Network() {}
};

