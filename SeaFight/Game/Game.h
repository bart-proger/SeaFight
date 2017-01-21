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
	enum PlayState { WaitEnemy, /*ReadyPlay,*/ MyShot, EnemyShot, Win, Lose, EnemySurrender, EnemyDisconnected };
//	enum PlayState;

	Game();

	Scene & scene() { return *scene_; }
	void setScene(Scene &value) { scene_ = &value; scene_->onShow(); }
	PlayState state() const { return state_; }
	void setState(PlayState state);

	Player & player() { return player_; }
	Enemy & enemy() { return enemy_; }
	
	TcpClient & client() { return client_; }

	bool connectToServer();
	void readyPlay();
	void fire(SDL_Point coord);
	void surrender();
	void newBattle();

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
	SDL_mutex * commandsLock_;
};

//enum Game::PlayState { WaitEnemy, /*ReadyPlay,*/ MyStep, EnemyStep, Win, Lose };

#define CMD_FIRST		">first"
#define CMD_SECOND		">second"
#define CMD_HIT			">hit"	//:x:y
#define CMD_GET_HIT		">get_hit"	//:x:y
#define CMD_MISS		">miss"	//:x:y
#define CMD_GET_MISS	">get_miss"	//:x:y
#define CMD_KILL		">kill"
#define CMD_GET_KILL	">get_kill"
#define CMD_ENEMY_DISCONNECTED ">enemy_disconnected"
#define CMD_WIN			">win"
#define CMD_LOSE		">lose"	//:x:y:len,x:y:len,... - оставшиеся корабли
#define CMD_ENEMY_SURRENDER	">enemy_surr"

#define CMD_READY_PLAY	">map"	//:01001101...
#define CMD_FIRE		">fire"	//:x:y
#define CMD_SURRENDER	">surrender"

#define CMD_OK			">ok"	// опрос от сервера - игрок онлайн?