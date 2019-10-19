
#include "pch.h"
#include "ClientConnectionManager.h"
/*
	Create connections between Game Interface in java and Server that gives game data.
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
int ClientConnectionManager::openUDPSocket(int addr, int port) {
	// Initialize an UDP socket that you can use to send messages
	
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf(" Could not create socket : %d", WSAGetLastError());
	}
	printf(" Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	//Bind
	if (bind(s, (struct sockaddr *)&amp; server, sizeof(server)) == SOCKET_ERROR)
	{
		printf(" Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts(" Bind done");

	//keep listening for data
	while (1)
	{
		printf(" Waiting for data...");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf(" recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		printf(" Received packet from %s:%d\n" , inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf(" Data: %s\n", buf);

		//now reply the client with the same data
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf(" sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	closesocket(s);
	WSACleanup();
	return 0;
}

