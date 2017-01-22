#pragma once
#include "../Scene.h"

class Game;

class MainMenuScene : public Scene
{
public:
	MainMenuScene(Game &);

	void init() override;
	void draw(Graphics &) override;
	void onShow() override;

private:
	static void playOnline_click(Scene &);
 	static void playVsAI_click(Scene &);
 	static void quit_click(Scene &);
};

