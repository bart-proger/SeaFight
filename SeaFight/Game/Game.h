#pragma once
#include "../Engine/SDLApplication.h"
#include "../Engine/Texture.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/PlaceShipScene.h"
#include "Scenes/PlayScene.h"
#include "Player.h"
#include "../Engine/TcpClient.h"
#include "ReceiveThread.h"
#include "../Engine/Font.h"
#include "Enemy.h"
#include <queue>

class Scene;

class Game: public SDLApplication
{
public:
	enum PlayState { WaitEnemy, /*ReadyPlay,*/ MyStep, EnemyStep };

	Game();

	void setScene(Scene &value) {	scene_ = &value; }
	Scene & scene() { return *scene_; }
	Game::PlayState state() const { return state_; }

	Player & player() { return player_; }
	Enemy & enemy() { return enemy_; }
	
	TcpClient & client() { return client_; }

	bool connectToServer();
	void readyPlay();
	void fire(SDL_Point coord);

	void pushCommand(string cmd);
	void parseCommands();
	
	MainMenuScene mainMenuScene;
	PlaceShipScene placeShipScene;
	PlayScene playScene;

private:
	bool onInit() override;
	void onFree() override;
	void onUpdate() override;
	void onDraw() override;
//	void onKeyEvent() override;
	void onPress(SDL_Point ) override;
	void onRelease(SDL_Point ) override;
	void onMouseMove(SDL_Point) override;

	Scene *scene_;
	PlayState state_;
	SDL_Point lastFire_;

	Player player_;
	Enemy enemy_;

	TcpClient client_;
	ReceiveThread receiveThread_;
	std::queue<string> commands_;
};

#define CMD_FIRST		">first"
#define CMD_SECOND		">second"
#define CMD_HIT			">hit"	//:x:y
#define CMD_GET_HIT		">get_hit"	//:x:y
#define CMD_MISS		">miss"	//:x:y
#define CMD_GET_MISS	">get_miss"	//:x:y
#define CMD_KILL		">kill"
#define CMD_GET_KILL	">get_kill"
#define CMD_ENEMY_DISCONNECTED ">enemy_disconnected"
//TODO: #define CMD_WIN , CMD_LOSE

#define CMD_READY_PLAY	">map"	//:01001101...
#define CMD_FIRE		">fire"	//:x:y

#define CMD_OK			">ok"