#pragma once
#include "Network.h"
#include <string>
using std::string;

class TcpClient
{
public:
	TcpClient();
	~TcpClient();
	bool connect(string ip, unsigned short port);
	void disconnect();
	bool send(string );
	bool receive(string &);
	bool connected() const;

private:
	TCPsocket socket_;
	IPaddress address_;

//	SDL_sem* cs_;
};
