#include <iostream>
#include "Server.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8000


int main(int argc, char** argv)
{
	//setlocale(LC_ALL, "Russian");

	std::cout	<< "***********************\n"
				<< "*** SeaFight server ***\n"
				<< "***********************\n\n";

	if (WinNetwork::Init())
	{
		Server server;

		if (server.Init(SERVER_IP, SERVER_PORT))
		{
			std::cout << "-Server started: " << SERVER_IP << ":" << SERVER_PORT << "\n"
					  << "Waiting for connections players...\n";

			server.Run();

			std::cout << "-Server stopped.\n";
		}
		WinNetwork::Free();
	}


	system("pause");
	return 0;
}