#include "pch.h"
#include "ClientConnectionManager.h"
#include "winsock2.h"
#include <string>
#include "stdio.h"
/*
	Create a TCP socket
*/

#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;
ClientConnectionManager::ClientConnectionManager(){
}


ClientConnectionManager::~ClientConnectionManager(){
}

// This will open the clients TCP connection to the server
// Another method will open the udp multicast to the GUI application
int ClientConnectionManager::openConnection(){
	WSADATA wsa;
	SOCKET s;
	
	struct sockaddr_in server;

	printf(" \nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2),&wsa) != 0)
	{
		printf(" Failed.Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf(" Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf(" Could not create socket : %d" , WSAGetLastError());
	}

	printf(" Socket created.\n");
	string server_address;
	server_address = "127.0.0.1";
	const char* s_addr_cstr = server_address.c_str();
	server.sin_addr.s_addr = inet_addr(s_addr_cstr);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)), 0)
	{
		puts(" connect error");
		return 1;
	}

	puts(" Connected");
}
// This is the function that opens the UDP Socket
int ClientConnectionManager::openUDPSocket() {

}
