#pragma once

#include "WinTcpClient.h"
//#include "Map.h"
#include "WinThread.h"

class Server;

class Player: public WinThread
{
public:
	enum { MAP_WIDTH = 10, MAP_HEIGHT = 10 };
	enum PlayState { Disconnected, Connected, ReadyPlay, MyShot, EnemyShot };
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

	bool isDisconnected() const;
	bool readyPlay() const;

//	Cell & map(int x, int y);
	void InitMap(string data);
	void ClearMap();

private:
	void ParseCommand(string cmd);
	void fire(int x, int y);
	void surrender();
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
	int shipDecksLeft_;

	//TODO: player name & etc...
	bool shipKilledAt(int x, int y);
};

#define CMD_FIRST		">first"
#define CMD_SECOND		">second"
#define CMD_HIT			">hit"
#define CMD_GET_HIT		">get_hit"	//:x:y
#define CMD_MISS		">miss"
#define CMD_GET_MISS	">get_miss"	//:x:y
#define CMD_KILL		">kill"
#define CMD_GET_KILL	">get_kill"
#define CMD_ENEMY_DISCONNECTED ">enemy_disconnected"
#define CMD_WIN			">win"
#define CMD_LOSE		">lose" // :x:y:len,x:y:len,... - ships left
#define CMD_ENEMY_SURR	">enemy_surr"

#define CMD_READY_PLAY	">map"	//:01001101...
#define CMD_FIRE		">fire"	//:x:y
#define CMD_SURRENDER	">surrender"


#define CMD_OK			">ok"