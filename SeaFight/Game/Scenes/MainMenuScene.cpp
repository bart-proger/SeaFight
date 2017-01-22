#include "MainMenuScene.h"
#include "../Game.h"
#include <iostream>


MainMenuScene::MainMenuScene(Game &game):
	Scene(game)
{
}

void MainMenuScene::init()
{
	addButton("btn_PlayOnline", SDL_Rect{ 136, 97, 201, 44 }, playOnline_click);
// 	addButton("btn_PlayVsAI", SDL_Rect{ 75, 150, 324, 44 }, PlayVsAI_Click);
	addButton("btn_Quit", SDL_Rect{ 165, 237, 150, 44 }, quit_click);
}

void MainMenuScene::draw(Graphics &g)
{
	//...

	Scene::draw(g);
}

void MainMenuScene::onShow()
{
	game().setScene(game().placeShipScene);
}

void MainMenuScene::playOnline_click(Scene &scene)
{	
	if (scene.game().connectToServer())
		scene.game().setScene(scene.game().placeShipScene);
	else
	{
		//TODO: показать сообщение "Сервер не доступен"
	}
}

void MainMenuScene::playVsAI_click(Scene &scene)
{
	//TODO: играть против ИИ
	scene.game().setScene(scene.game().placeShipScene);
}

void MainMenuScene::quit_click(Scene &scene)
{
	scene.game().quit();
}
