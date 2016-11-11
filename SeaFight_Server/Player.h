#pragma once

#include "WinTcpClient.h"
//#include "Map.h"
#include "WinThread.h"

class Server;

class Player: public WinThread
{
public:
	enum { MAP_WIDTH = 10, MAP_HEIGHT = 10 };
	enum PlayState { Disconnected, Connected, ReadyPlay, MyStep, EnemyStep };
	struct Cell
	{
		bool hasShip;
		bool attacked;
	};

	Player(Server* );
	~Player();

	WinTcpClient & client();
// 	void setClient(WinTcpClient );
// 	void setEnemy(Player *);
// 	void setState(PlayState );
// 	PlayState state() const;

	bool IsDisconnected() const;
	bool IsReadyPlay() const;

//	Cell & map(int x, int y);
	void InitMap(string data);
	void ClearMap();

private:
	void ParseCommand(string cmd);
	void Fire(int x, int y);
	void PlayEnemy();
	void WaitNextEnemy();
	void StartBattle();

	void Process();

	Cell map_[MAP_HEIGHT][MAP_WIDTH];

	Server* server_;
	WinTcpClient client_;
	Player*  enemy_;
	PlayState state_;
	string name_;
	//TODO: player name & etc...
};

#define CMD_FIRST		">first"
#define CMD_SECOND		">second"
#define CMD_HIT			">hit"
#define CMD_GET_HIT		">get_hit"	//:x:y
#define CMD_MISS		">miss"
#define CMD_GET_MISS	">get_miss"	//:x:y
#define CMD_ENEMY_DISCONNECTED ">enemy_disconnected"

#define CMD_READY_PLAY	">map"	//:01001101...
#define CMD_FIRE		">fire"	//:x:y