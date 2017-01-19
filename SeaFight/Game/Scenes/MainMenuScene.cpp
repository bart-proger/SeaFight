#include "MainMenuScene.h"
#include "../Game.h"
#include <iostream>


MainMenuScene::MainMenuScene(Game &game):
	Scene(game)
{
}

void MainMenuScene::init()
{
	SDL_Rect r1 = { 136, 97, 201, 44 };
	addButton("btn_PlayOnline", r1, PlayOnline_Click);

	SDL_Rect r2 = { 75, 150, 324, 44 };
	addButton("btn_PlayVsAI", r2, PlayVsAI_Click);

	SDL_Rect r3 = { 165, 237, 150, 44 };
	addButton("btn_Quit", r3, Quit_Click);
}

void MainMenuScene::draw(Graphics &g)
{
	Scene::draw(g);

	//...
}

void MainMenuScene::PlayOnline_Click(Scene &scene)
{
	std::clog << "click [Play online]\n";
	
	if (scene.game().connectToServer())
	{
		scene.game().setScene(scene.game().placeShipScene);
	}
	else
	{
		//TODO: показать сообщение "—ервер не доступен"
	}
}

void MainMenuScene::PlayVsAI_Click(Scene &scene)
{
	std::clog << "click [Play vs AI]\n";
	// TODO: click Play vs AI
	scene.game().setScene(scene.game().placeShipScene);
}

void MainMenuScene::Quit_Click(Scene &scene)
{
	std::clog << "click [Quit]\n";
	scene.game().quit();
}
