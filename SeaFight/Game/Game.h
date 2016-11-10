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


class Scene;

//#include "Scene.h"

class Game: public SDLApplication
{
public:
	enum PlayState { WaitEnemy, /*ReadyPlay,*/ MyStep, EnemyStep };

	Game();

	void setScene(Scene &);
	Scene & scene();
	PlayState state() const;

	Player & player();
	Player & enemy();

	TcpClient & client();

	bool connectToServer();
	void parseCommand(string cmd);
	void readyPlay();
	void fire(SDL_Point coord);
	
	MainMenuScene mainMenuScene;
	PlaceShipScene placeShipScene;
	PlayScene playScene;

private:
	bool OnInit() override;
	void OnFree() override;
	void OnDraw() override;
	void OnKeyEvent() override;
	void OnMouseEvent(SDL_Point ) override;

	Scene *scene_;
	PlayState state_;
	SDL_Point lastFire_;

	Player player_;
	Player enemy_;

	TcpClient client_;
	ReceiveThread receiveThread_;
	
	Font font_;
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