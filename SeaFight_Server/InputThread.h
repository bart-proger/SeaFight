#pragma once
#include "WinThread.h"

class Server;

class InputThread : public WinThread
{
public:
	InputThread(Server &);

	void Process() override;

private:
	Server &server_;
};

