#pragma once

#include "WinNetwork.h"
#include <string>
using std::string;

class WinTcpClient
{
friend class WinTcpListener;
public:
	WinTcpClient();
	~WinTcpClient();

	bool Connect(string ip, unsigned short port);
	void Disconnect();
	bool Send(string data);
	bool Receive(string &data);

	bool Connected() const;
	string GetIp() const;
//	unsigned short GetPort() const;
//	string GetHostName() const;

private:
	SOCKET socket_;
	SOCKADDR_IN address_;
};