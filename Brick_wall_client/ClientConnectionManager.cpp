
#include "pch.h"
#include "ClientConnectionManager.h"
#include "winsock2.h"

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

int ClientConnectionManager::openConnection()
{
	string ip = "127.0.0.1";
	return openConnection(ip);
}

int ClientConnectionManager::openConnection(string ip)
{
	int port = 80;
	return openConnection(ip, port);
}

// This will open the clients TCP connection to the server
// Another method will open the udp multicast to the GUI application
int ClientConnectionManager::openConnection(string ip, int port){
	WSADATA wsa;
	SOCKET s;
	
	struct sockaddr_in server;

	printf(" \nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2),&wsa) != 0)
	{
		printf(" Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf(" Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf(" Could not create socket : %d" , WSAGetLastError());
	}

	printf(" Socket created.\n");
	
	const char* s_addr_cstr = ip.c_str();
	server.sin_addr.s_addr = inet_addr(s_addr_cstr);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) != 0)
	{
		wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
		puts(" connect error");
		return 1;
	}

	puts(" Connected");
	return 0;
}
// This is the function that opens the UDP Socket
int ClientConnectionManager::openUDPSocket() {
	return 0;
}

