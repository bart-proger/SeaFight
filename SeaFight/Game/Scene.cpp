#include "Scene.h"
#include "Game.h"

Scene::Scene(Game &game):
	game_(game)
{
}

void Scene::Draw(Graphics &g)
{
	for (auto &b: buttons_)
	{
		g.DrawSprite(b.sprite, b.rect);
	}
}

void Scene::onClick(SDL_Point p)
{
	for (auto &b: buttons_)
	{
		if (SDL_PointInRect(&p, &b.rect))
		{
			if (b.OnClick)
				b.OnClick(*this);
		}
	}
}

Game &Scene::game()
{
	return game_;
}

void Scene::AddButton_(string sprite, SDL_Rect rect, ButtonClickFunc clickFunc)
{
	buttons_.push_back(Button(sprite, rect, clickFunc));
}
