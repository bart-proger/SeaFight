#include "WinNetwork.h"
#include <iostream>

bool WinNetwork::Init()
{
	WSADATA wsaData;
	WORD wsaVersion = MAKEWORD(2, 2);

	int error = WSAStartup(wsaVersion, &wsaData);

	if (error != 0) 
	{
		std::cerr << "[error] Sockets initialize failed: " << error << "\n";
		return false;
	}
	return true;
}

void WinNetwork::Free()
{
	int error = WSACleanup();					// очистка и деинициализаци¤ winsock

	if (error == SOCKET_ERROR)
	{
		std::cerr << "[error] Sockets free failed: " << error << "\n";
	}
}