#include "WinTcpClient.h"
#include <iostream>

WinTcpClient::WinTcpClient():
	socket_(INVALID_SOCKET)
{}

WinTcpClient::~WinTcpClient()
{
	Disconnect();
}

bool WinTcpClient::Connect(string ip, unsigned short port)
{
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_ == INVALID_SOCKET)
	{
		std::cerr << "[error] WinSock2 socket(): " << WSAGetLastError() << std::endl;
		return false;
	}

	ZeroMemory(&address_, sizeof(SOCKADDR_IN));
	address_.sin_family = AF_INET;
	address_.sin_port = htons(port);
	address_.sin_addr.s_addr = inet_addr(ip.c_str());

	int result = connect(socket_, (SOCKADDR*)&address_, sizeof(SOCKADDR_IN));
	if (result == SOCKET_ERROR)
	{
		std::cerr << "[error] WinSock2 connect(): " << WSAGetLastError() << "\n";
		return false;
	}
	return true;
}

void WinTcpClient::Disconnect()
{
	if (socket_ != INVALID_SOCKET)
	{
		shutdown(socket_, SD_BOTH);
		closesocket(socket_);
	}
	socket_ = INVALID_SOCKET;
}

bool WinTcpClient::Send(string msg)
{
	int sz = msg.length()+1;
	char sd[sizeof(sz)];
	memcpy(sd, &sz, sizeof(sz));

	int result = send(socket_, &sd[0], sizeof(sz), 0);
	if (result == SOCKET_ERROR) 
	{
		std::cerr << "[error] WinSock2 send(): " << WSAGetLastError() << std::endl;
		return false;
	}

	result = send(socket_, msg.c_str(), sz, 0);
	if (result == SOCKET_ERROR) 
	{
		std::cerr << "[error] WinSock2 send(): " << WSAGetLastError() << std::endl;
		return false;
	}

	return true;
}

bool WinTcpClient::Receive(string &msg)
{
	int sz = 0;
	char sd[sizeof(sz)];

	int result = recv(socket_, &sd[0], sizeof(sz), 0);
	if (result <= 0 || result == SOCKET_ERROR)
	{
		std::cerr << "[error] WinSock2 recv(): " << WSAGetLastError() << std::endl;
		Disconnect();
		return false;
	}
	memcpy(&sz, sd, sizeof(sz));

	char* data = new char[sz];

	result = recv(socket_, data, sz, 0);
	if (result <= 0 || result == SOCKET_ERROR)
	{
		std::cerr << "[error] WinSock2 recv(): " << WSAGetLastError() << std::endl;
		Disconnect();
		delete [] data;
		return false;
	}

	msg = data;
	delete [] data;
	return true;
}

bool WinTcpClient::Connected() const
{
	return socket_ != INVALID_SOCKET;
}

string WinTcpClient::GetIp() const
{
	string ip(inet_ntoa(address_.sin_addr));
	return ip;
}
