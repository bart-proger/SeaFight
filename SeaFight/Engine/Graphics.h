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
	bool init(SDL_Window *);
	void free();

	void clear();
	void present();

/*	bool LoadTexture(Texture &, string fileName, SDL_Color *transparent = NULL);
	void DrawTexture(Texture &, int x, int y);
	void DrawTextureClip(Texture &, SDL_Rect rect, SDL_Rect clip);
*/
	bool loadTexture(string fileName, SDL_Color *transparent = NULL);

	typedef SDL_Rect Sprite;

	void addSprite(string name, int x, int y, int w, int h);
	void drawSprite(string name, int x, int y);
	void drawSprite(string name, SDL_Rect rect);
	void drawSprite(string name, int x, int y, double angle);
	void drawSprite(string name, int x, int y, double angle, int centerX, int centerY);
	void drawText(const Font &font, SDL_Color color, string text, int x, int y);

private:
	SDL_Renderer *renderer_;
	Texture texture_;

	std::map<string, Sprite> sprites_;
public:
	void drawRect(SDL_Rect, SDL_Color);
};

