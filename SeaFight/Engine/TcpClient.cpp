#include "TcpClient.h"
#include <iostream>

TcpClient::TcpClient():
	//connected_(false),
	socket_(nullptr)
{
	//cs_ = SDL_CreateSemaphore(1);
}

TcpClient::~TcpClient()
{
	Disconnect();
//	SDL_DestroySemaphore(cs_);
}

bool TcpClient::Connect(string ip, unsigned short port)
{
	if (SDLNet_ResolveHost(&address_, ip.c_str(), port) < 0)
	{
		std::cerr << "[error] SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
		return false;
	}

	if (!(socket_ = SDLNet_TCP_Open(&address_)))
	{
		socket_ = nullptr;
		std::cerr << "[error] SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
		return false;
	}
	
	return true;
}

void TcpClient::Disconnect()
{
//	SDL_SemWait(cs_);

	if (socket_)
	{
		SDLNet_TCP_Close(socket_);
		socket_ = nullptr;
	}

//	SDL_SemPost(cs_);
}

bool TcpClient::Send(string msg)
{
	int sz = msg.length()+1;

	int result = SDLNet_TCP_Send(socket_, &sz, sizeof(sz));
	if (result < sizeof(sz)) 
	{
		std::cerr << "[error] SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl;
		return false;
	}

	result = SDLNet_TCP_Send(socket_, msg.c_str(), sz);
	if (result < sz) 
	{
		std::cerr << "[error] SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl;
		return false;
	}
	return true;
}

bool TcpClient::Receive(string &msg)
{
	int sz = 0;
	int result = SDLNet_TCP_Recv(socket_, &sz, sizeof(sz));
	if (result <= 0)
	{
		std::cerr << "[error] SDLNet_TCP_Recv: " << SDLNet_GetError() << std::endl;
		Disconnect();
		return false;
	}

	char* data = new char[sz];

	result = SDLNet_TCP_Recv(socket_, data, sz);
	if (result <= 0)
	{
		std::cerr << "[error] SDLNet_TCP_Recv: " << SDLNet_GetError() << std::endl;
		Disconnect();
		delete [] data;
		return false;
	}

	msg = data;
	delete [] data;
	return true;
}

bool TcpClient::Connected() const
{
	return socket_;
}
