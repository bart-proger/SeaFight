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
	disconnect();
//	SDL_DestroySemaphore(cs_);
}

bool TcpClient::connect(string ip, unsigned short port)
{
	if (connected())
		disconnect();

	if (SDLNet_ResolveHost(&address_, ip.c_str(), port) < 0)
	{
		std::cerr << "[error] SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
		return false;
	}

	if (!(socket_ = SDLNet_TCP_Open(&address_)))
	{
		std::cerr << "[error] SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
		return false;
	}
	
	return true;
}

void TcpClient::disconnect()
{
//	SDL_SemWait(cs_);

	if (socket_)
	{
		SDLNet_TCP_Close(socket_);
		socket_ = nullptr;
	}

//	SDL_SemPost(cs_);
}

bool TcpClient::send(string msg)
{
	if (!connected())
		return false;

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

bool TcpClient::receive(string &msg)
{
	if (!connected())
		return false;

	int sz = 0;
	int result = SDLNet_TCP_Recv(socket_, &sz, sizeof(sz));
	if (result <= 0)
	{
		std::cerr << "[error] SDLNet_TCP_Recv: " << SDLNet_GetError() << std::endl;
		disconnect();
		return false;
	}

	char* data = new char[sz];

	result = SDLNet_TCP_Recv(socket_, data, sz);
	if (result <= 0)
	{
		std::cerr << "[error] SDLNet_TCP_Recv: " << SDLNet_GetError() << std::endl;
		disconnect();
		delete [] data;
		return false;
	}

	msg = data;
	delete [] data;
	return true;
}

bool TcpClient::connected() const
{
	return (socket_ != nullptr);
}
