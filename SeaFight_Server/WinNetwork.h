#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>

// ����������, ����� �������� ����������� � DLL-����������� 
// ��� ������ � �������
#pragma comment(lib, "Ws2_32.lib")

class WinNetwork
{
private:
	WinNetwork() {}

public:
	static bool Init();
	static void Free();
};

enum SocketType { UDP = SOCK_DGRAM, TCP = SOCK_STREAM };