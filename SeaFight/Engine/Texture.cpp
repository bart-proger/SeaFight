#include "Texture.h"
#include "Graphics.h"

Texture::Texture():
	sdlTexture_(NULL),
	width_(0),
	height_(0)
{
}

Texture::~Texture()
{
	Free();
}

void Texture::Free()
{
	if (sdlTexture_)
	{
		SDL_DestroyTexture(sdlTexture_);
		sdlTexture_ = NULL;
		width_ = 0;
		height_ = 0;
	}
}

int Texture::width() const
{
	return width_;
}

int Texture::height() const
{
	return height_;
}

bool Texture::Loaded() const
{
	return (sdlTexture_);
}