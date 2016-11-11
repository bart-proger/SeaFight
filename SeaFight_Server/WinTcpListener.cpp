#include "WinTcpListener.h"
#include <iostream>
#include <sstream>
#include <string>

WinTcpListener::WinTcpListener():
	socket_(INVALID_SOCKET) 
{
	ZeroMemory(&address, sizeof(SOCKADDR_IN));
	// Создание сокета
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	// Если создание сокета завершилось с ошибкой, выводим сообщение,
	// освобождаем память, выделенную под структуру addr,
	// выгружаем dll-библиотеку и закрываем программу
	if (socket_ == INVALID_SOCKET)
	{
		std::cerr << "[error] WinSock2 socket(): " << WSAGetLastError() << std::endl;
	}
}


WinTcpListener::~WinTcpListener()
{
	Stop();
}

bool WinTcpListener::Listen(string ip, unsigned short port)
{
	// Шаблон для инициализации структуры адреса
	ZeroMemory(&address, sizeof(SOCKADDR_IN));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip.c_str());

	// Привязываем сокет к IP-адресу
	int result = bind(socket_, (SOCKADDR*)&address, sizeof(SOCKADDR_IN));
	// Если привязать адрес к сокету не удалось, то выводим сообщение
	// об ошибке, освобождаем память, выделенную под структуру addr.
	// и закрываем открытый сокет.
	// Выгружаем DLL-библиотеку из памяти и закрываем программу.
	if (result == SOCKET_ERROR) 
	{
		std::cerr << "[error] WinSock2 bind: " << WSAGetLastError() << "\n";
		Stop();
		return false;
	}

	// Инициализируем слушающий сокет
	if (listen(socket_, SOMAXCONN) == SOCKET_ERROR) 
	{
		std::cerr << "[error] WinSock2 listen: " << WSAGetLastError() << "\n";
		Stop();
		return false;
	}

	return true;
}

bool WinTcpListener::Accept(WinTcpClient &client)
{
	// Принимаем входящие соединения
	SOCKADDR_IN clientAddress;
	int clientAddressLen = sizeof(SOCKADDR_IN);

	SOCKET clientSocket = accept(socket_, (SOCKADDR*)&clientAddress, &clientAddressLen);
	if (clientSocket == INVALID_SOCKET) 
	{
		std::cerr << "[error] WinSock2 accept: " << WSAGetLastError() << "\n";
		Stop();
		return false;
	}

	client.socket_ = clientSocket;
	client.address_ = clientAddress;

	return true;
}
/*
bool ListenTcpSocket::Receive(char* data)
{
	if (!data)
		return false;

	int result;
	if (result = recv(params->clientSocket, data, MAX_MSG_SIZE, 0) > 0)
	{
		std::cout << "[" << inet_ntoa(params->clientAddress.sin_addr) << "] " << params->clientHost.h_name << " sent: " << msg << "\n";
	}

	if (result == SOCKET_ERROR) 
	{
		// ошибка получения данных
		std::cerr << "[error] Error recv() failed: " << result << "\n";
		closesocket(params->clientSocket);
	} 
	else if (result == 0) 
	{
		// соединение закрыто клиентом
		std::cerr << "[error] Client " << "[" << inet_ntoa(params->clientAddress.sin_addr) << "] " << params->clientHost.h_name << " closed connection...\n";
	} 
	closesocket(params->clientSocket);
}
*/
void WinTcpListener::Stop()
{
	if (socket_ != INVALID_SOCKET)
		closesocket(socket_);
	socket_ = INVALID_SOCKET;
}

/*
void ListenSocket::Listen()
{
	int clientSockAddrLen = sizeof(SOCKADDR_IN);
	ReceiveThreadParams params;
	ZeroMemory(&params, sizeof(ReceiveThreadParams));

	while (true)
	{
		// Принимаем входящие соединения
		params.clientSocket = accept(listenSocket, (SOCKADDR*)&params.clientAddress, &clientSockAddrLen);
		if (params.clientSocket == INVALID_SOCKET) 
		{
			std::cerr << "[error] accept failed: " << WSAGetLastError() << "\n";
			closesocket(listenSocket);
			return;
		}

		char clientIP[INET_ADDRSTRLEN+1];
		inet_ntop(AF_INET, &(params.clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN+1);

		HOSTENT* host = gethostbyaddr((char*) &(params.clientAddress.sin_addr.s_addr), 4, AF_INET);
		if (host)
		{
			params.clientHost = *host;
		}
		std::cout << "Client [" << clientIP << "] " << host->h_name << " connected\n";

		_beginthread(ListenSocket::ReceiveThread, 0, (void*)&params);
	}
}

void ListenSocket::ReceiveThread(void* params)
{
	ReceiveThreadParams* p = reinterpret_cast<ReceiveThreadParams*>(params);
	p->owner->_ReceiveThread(p);
}

void ListenSocket::_ReceiveThread(ReceiveThreadParams* params)
{
	char msg[MAX_MSG_SIZE];

	int result;
	while (result = recv(params->clientSocket, msg, MAX_MSG_SIZE, 0) > 0)
	{
		std::cout << "[" << inet_ntoa(params->clientAddress.sin_addr) << "] " << params->clientHost.h_name << " sent: " << msg << "\n";
	}

	if (result == SOCKET_ERROR) 
	{
		// ошибка получения данных
		std::cerr << "[error] Error recv() failed: " << result << "\n";
		closesocket(params->clientSocket);
	} 
	else if (result == 0) 
	{
		// соединение закрыто клиентом
		std::cerr << "[error] Client " << "[" << inet_ntoa(params->clientAddress.sin_addr) << "] " << params->clientHost.h_name << " closed connection...\n";
	} 
	closesocket(params->clientSocket);

}
*/