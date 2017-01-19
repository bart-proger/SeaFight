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
	bool init(string title, int width, int height);
	void free();
	void run();
	void quit();

	Graphics & graphics() { return graphics_; }
	//Network & network();
	int width() const { return width_; }
	int height() const { return height_; }

protected:
	virtual bool onInit() { return true; }
	virtual void onFree() {}
	virtual void onUpdate() {}
	virtual void onDraw() {}
//	virtual void onKeyEvent() {}
	virtual void onPress(SDL_Point) {}
	virtual void onRelease(SDL_Point ) {}
	virtual void onMouseMove(SDL_Point dp) {}

private:
	int width_;
	int height_;
	SDL_Window *window_;
	Graphics graphics_;
	//Network network_;
};
