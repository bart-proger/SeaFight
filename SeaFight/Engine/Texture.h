#pragma once
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <string>
using std::string;

class Graphics;

class Texture
{
friend class Graphics;
public:
	Texture();
	~Texture();

	void Free();
	bool Loaded() const;

	int width() const;
	int height() const;

private:
	SDL_Texture* sdlTexture_;
	int width_;
	int height_;
};
