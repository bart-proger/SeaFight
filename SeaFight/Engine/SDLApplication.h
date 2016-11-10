#pragma once
#include <SDL2/SDL.h>
#ifndef LINK_LIBS_SDL2
	#define	LINK_LIBS_SDL2
	#pragma comment(lib, "SDL2.lib")
	#pragma comment(lib, "SDL2main.lib")
	#pragma comment(lib, "SDL2_image.lib")
#endif
#include <string>
using std::string;
#include "Graphics.h"

class SDLApplication
{
public:
	SDLApplication();
	virtual ~SDLApplication();
	bool Init(string title, int width, int height);
	void Free();
	void Run();
	void Quit();

	Graphics & graphics();
	//Network & network();
	int width();
	int height();

protected:
	virtual bool OnInit() { return true; }
	virtual void OnFree() {}
	//TODO: virtual void OnUpdate() {}
	virtual void OnDraw() {}
	virtual void OnKeyEvent() {}
	virtual void OnMouseEvent(SDL_Point ) {}

private:
	int width_;
	int height_;
	SDL_Window *window_;
	Graphics graphics_;
	//Network network_;
};
