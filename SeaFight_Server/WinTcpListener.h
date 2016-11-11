#pragma once

#include "WinNetwork.h"
#include "WinTcpClient.h"
/*#include <process.h>

struct ReceiveThreadParams;
*/
class WinTcpListener
{
public:
	WinTcpListener();
	~WinTcpListener();

	bool Listen(string ip, unsigned short port);
	bool Accept(WinTcpClient &);
//	void Send(ClientTcpSocket& to, const char* data);
//	bool Receive(ClientTcpSocket& from, char* data);
	void Stop();

	string GetIp() const;
//	unsigned short GetPort() const;
//	string GetHostName() const;

private:
	SOCKET socket_;
	SOCKADDR_IN address_;

	/*static void ReceiveThread(void* params);
	void _ReceiveThread(ReceiveThreadParams* params);*/
};
/*
struct ReceiveThreadParams
{
	ListenTcpSocket* owner;
	SOCKET clientSocket;
	HOSTENT clientHost;
	SOCKADDR_IN clientAddress;
};*/