#include "SDLApplication.h"
#include <iostream>

SDLApplication::SDLApplication():
window_(NULL) 
{
}

SDLApplication::~SDLApplication()
{
	SDL_Quit();
}

bool SDLApplication::init(string title, int width, int height)
{
	bool result = true;

	//Initialize SDL subsystems
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "[error] SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		result = false;
	}
	else
	{
		//Create window
		window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			width, height, SDL_WINDOW_SHOWN);
		if (!window_)
		{
			std::cerr << "[error] Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			result = false;
		}
		else
		{
			//Create renderer for window
			if (graphics_.init(window_))
			{
				width_ = width;
				height_ = height;

				result = onInit();
			}
		}
	}
	return result;
}

void SDLApplication::free()
{
	onFree();

	graphics_.free();
	if (window_)
	{
		SDL_DestroyWindow(window_);
		window_ = NULL;
	}
}

void SDLApplication::run()
{
	SDL_Event e;
	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else 
			{
				switch (e.type)
				{
					case SDL_KEYDOWN:
						onKeyDown(e.key.keysym.sym);
						break;
					case SDL_MOUSEBUTTONDOWN:
						onPress({ e.button.x, e.button.y });
						break;
					case SDL_FINGERDOWN:
						onPress({ (int)(e.tfinger.x * width_), (int)(e.tfinger.y * height_) });
						break;
					case SDL_MOUSEBUTTONUP:
						onRelease({ e.button.x, e.button.y });
						break;
					case SDL_FINGERUP:
						onRelease({ (int)(e.tfinger.x * width_), (int)(e.tfinger.y * height_) });
						break;
					case SDL_MOUSEMOTION:
						onMove({ e.motion.x, e.motion.y });
						break;
					case SDL_FINGERMOTION:
						onMove({ (int)(e.tfinger.x * width_), (int)(e.tfinger.y * height_) });
						break;
				}
			}
		}

		onUpdate();
		onDraw();

        graphics_.present();
	}
	free();
}

void SDLApplication::quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}

//SDL_Surface *SDLApplication::LoadSurface(string fileName)
//{
//	SDL_Surface* optimizedSurf = NULL;
//	SDL_Surface* surf = IMG_Load(fileName.c_str());
//
//	if (!surf)
//	{
//		std::cerr << "[error] Unable to load image '" << fileName.c_str() << "'! SDL Error: " << IMG_GetError() << std::endl;
//	}
//	else
//	{
//		optimizedSurf = SDL_ConvertSurface(surf, screen_->format, 0);
//		if (!optimizedSurf)
//		{
//			std::cerr << "[error] Unable to optimize image '" << fileName.c_str() << "'! SDL Error: " << SDL_GetError() << std::endl;
//		}
//		SDL_FreeSurface(surf);
//	}
//
//	return optimizedSurf;
//}

