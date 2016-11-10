#pragma once
#include "Network.h"
#include <string>
using std::string;

class TcpClient
{
public:
	TcpClient();
	~TcpClient();
	bool Connect(string ip, unsigned short port);
	void Disconnect();
	bool Send(string );
	bool Receive(string &);
	bool Connected() const;

private:
	TCPsocket socket_;
	IPaddress address_;

//	SDL_sem* cs_;
};
