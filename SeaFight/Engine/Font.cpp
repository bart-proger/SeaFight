#include "Font.h"
#include "Graphics.h"
#include <iostream>

Font::Font():
	sdlFont_(NULL)
{
}

Font::~Font()
{
	Free();
}

bool Font::loadFromFile(string fileName)
{
	//Open the font
	sdlFont_ = TTF_OpenFont(fileName.c_str(), 28);
	if (sdlFont_ == NULL)
	{
		std::cerr << "[error] Failed to load font from '" << fileName.c_str() <<"'! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

void Font::Free()
{
	if (sdlFont_)
	{
		TTF_CloseFont(sdlFont_);
		sdlFont_ = NULL;
	}
}

bool Font::Loaded() const
{
	return (sdlFont_);
}