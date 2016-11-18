#pragma once
#include "../Engine/Texture.h"
#include <vector>

class Game;

class Scene
{
public:
	Scene(Game &);
	virtual ~Scene() {}
	virtual void Init() {}
	virtual void Draw(Graphics &);
	virtual void Update(float dt) {}
	virtual void onClick(SDL_Point );
	virtual void onPress(SDL_Point );
	virtual void onRelease(SDL_Point );
	Game & game();

	typedef void (*ButtonClickFunc)(Scene &);
	template<typename MemberFunc>
	void AddButton(string sprite, SDL_Rect rect, MemberFunc clickFunc)
	{
		AddButton_(sprite, rect, static_cast<ButtonClickFunc>(clickFunc));
	}

private:
	struct Button
	{
		Button(string asprite, SDL_Rect arect, Scene::ButtonClickFunc func):
			sprite(asprite),
			rect(arect),
			visible(true),
			OnClick(func) {}

		string sprite;
		SDL_Rect rect;
		bool visible;
		Scene::ButtonClickFunc OnClick;
	};

	Game &game_;
	std::vector<Button> buttons_;

	void AddButton_(string sprite, SDL_Rect rect, ButtonClickFunc clickFunc);
};
