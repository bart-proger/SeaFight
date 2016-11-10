#pragma once
#include "../Scene.h"

class Game;

class MainMenuScene : public Scene
{
public:
	MainMenuScene(Game &);

	void Init() override;
	void Draw(Graphics &) override;

private:
	static void PlayOnline_Click(Scene &);
 	static void PlayVsAI_Click(Scene &);
 	static void Quit_Click(Scene &);
};

