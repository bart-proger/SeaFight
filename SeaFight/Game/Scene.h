#pragma once
#include "../Engine/Texture.h"
#include <vector>
//#include "Game.h"

class Game;
//enum Game::PlayState;

class Scene
{
public:
	Scene(Game &);
	virtual ~Scene() {}
	virtual void init() {}
	virtual void draw(Graphics &);
	virtual void update(float dt) {}
	virtual void onShow() {}
//	virtual void onClick(SDL_Point );
	virtual void onPress(SDL_Point );
	virtual void onRelease(SDL_Point );
	virtual void onMove(SDL_Point) {}
	virtual void onChangeGameState(/*Game::PlayState*/) {}
	Game & game();

	typedef void (*ButtonClickFunc)(Scene &);
	template<typename MemberFunc>
	void addButton(string sprite, SDL_Rect rect, MemberFunc clickFunc)
	{
		addButton_(sprite, rect, static_cast<ButtonClickFunc>(clickFunc));
	}

	void showButton(string sprite);
	void hideButton(string sprite);

private:
	struct Button
	{
		Button(string asprite, SDL_Rect arect, Scene::ButtonClickFunc func):
			sprite(asprite),
			rect(arect),
			visible(true),
			pressed(false),
			onClick(func) {}

		string sprite;
		SDL_Rect rect;
		bool visible;
		bool pressed;
		Scene::ButtonClickFunc onClick;
	};

	Game &game_;
	std::vector<Button> buttons_;

	void addButton_(string sprite, SDL_Rect rect, ButtonClickFunc clickFunc);
};
