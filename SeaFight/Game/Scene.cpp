#include "Scene.h"
#include "Game.h"

Scene::Scene(Game &game):
	game_(game)
{
}

void Scene::draw(Graphics &g)
{
	for (const auto &b: buttons_)
	{
		g.drawSprite(b.sprite, b.rect);
	}
}

// void Scene::onClick(SDL_Point p)
// {
// 	for (auto &b: buttons_)
// 	{
// 		if (SDL_PointInRect(&p, &b.rect))
// 		{
// 			if (b.onClick)
// 			{
// 				b.onClick(*this);
// 				break;
// 			}
// 		}
// 	}
// }

void Scene::onPress(SDL_Point p)
{
	for (auto &b : buttons_)
	{
		if (SDL_PointInRect(&p, &b.rect))
		{
			b.pressed = true;
//			if (b.onPress)
//				b.onPress(*this);
			break;
		}
	}
}

void Scene::onRelease(SDL_Point p)
{
	for (auto &b : buttons_)
	{
		if (SDL_PointInRect(&p, &b.rect))
		{
			if (b.pressed && b.onClick)
				b.onClick(*this);
//			b.onRelease();

			b.pressed = false;
			break;
		}
	}
}

void Scene::onMouseMove(SDL_Point p)
{
}

Game &Scene::game()
{
	return game_;
}

void Scene::addButton_(string sprite, SDL_Rect rect, ButtonClickFunc clickFunc)
{
	buttons_.push_back(Button(sprite, rect, clickFunc));
}
