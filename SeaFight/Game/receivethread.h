#pragma once
#include "../Engine/Thread.h"

class Game;

class ReceiveThread : public Thread
{
public:
	ReceiveThread(Game &);

private:
	int Process() override;

	Game &game_;
};

