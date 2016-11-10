#pragma once
#include <SDL2/SDL.h>
#ifndef SDL2_TTF_LIB
	#define SDL2_TTF_LIB
	#pragma comment(lib, "SDL2_ttf.lib")
#endif
#include <SDL2/SDL_ttf.h>
#include <string>
using std::string;

class Graphics;

class Font
{
friend class Graphics;
public:
	Font();
	~Font();

	bool LoadFromFile(string fileName);
	void Free();
	bool Loaded() const;

private:
	TTF_Font* sdlFont_;
};
