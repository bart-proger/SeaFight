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

bool SDLApplication::Init(string title, int width, int height)
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
			if (graphics_.Init(window_))
			{
				width_ = width;
				height_ = height;

				result = OnInit();
			}
		}
	}
	return result;
}

void SDLApplication::Free()
{
	OnFree();

	graphics_.Free();
	if (window_)
	{
		SDL_DestroyWindow(window_);
		window_ = NULL;
	}
}

void SDLApplication::Run()
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
					case SDL_KEYUP:
						OnKeyEvent(/* TODO: OnKeyEvent params*/);
						break;
					case SDL_MOUSEBUTTONUP:
						SDL_Point p = {e.button.x, e.button.y};
						OnMouseEvent(p);
						break;
				}
				
				/*	switch(e.key.keysym.sym)
				{
				case SDLK_UP:
				gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
				break;

				case SDLK_DOWN:
				gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
				break;

				case SDLK_LEFT:
				gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
				break;

				case SDLK_RIGHT:
				gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
				break;

				default:
				gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
				break;
				}*/
			}
		}

		OnUpdate();
		OnDraw();

        graphics_.Present();
	}
	Free();
}

void SDLApplication::Quit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}

Graphics & SDLApplication::graphics()
{
	return graphics_;
}

int SDLApplication::width()
{
	return width_;
}

int SDLApplication::height()
{
	return height_;
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

