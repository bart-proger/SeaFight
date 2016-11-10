#pragma once
#include <string>
using std::string;
#include <SDL2/SDL_rect.h>
#include "Texture.h"
#include <map>
#include "Font.h"

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
public:
	Graphics();
	~Graphics();
	bool Init(SDL_Window *);
	void Free();

	void Clear();
	void Present();

/*	bool LoadTexture(Texture &, string fileName, SDL_Color *transparent = NULL);
	void DrawTexture(Texture &, int x, int y);
	void DrawTextureClip(Texture &, SDL_Rect rect, SDL_Rect clip);
*/
	bool LoadTexture(string fileName, SDL_Color *transparent = NULL);

	typedef SDL_Rect Sprite;

	void AddSprite(string name, int x, int y, int w, int h);
	void DrawSprite(string name, int x, int y);
	void DrawSprite(string name, SDL_Rect rect);
	void DrawSprite(string name, int x, int y, double angle);
	void DrawText(const Font &font, SDL_Color color, string text, int x, int y);

private:
	SDL_Renderer *renderer_;
	Texture texture_;

	std::map<string, Sprite> sprites_;
};

