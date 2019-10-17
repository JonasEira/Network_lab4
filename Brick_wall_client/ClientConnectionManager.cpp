#include "pch.h"
#include "ClientConnectionManager.h"
#include "winsock2.h"
#include "stdio.h"
/*
	Create a TCP socket
*/

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc, char *argv[])
{
	

	return 0;
}

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

	printf(&quot; \nInitialising Winsock...&quot;);
	if (WSAStartup(MAKEWORD(2, 2), &amp; wsa) != 0)
	{
		printf(&quot; Failed.Error Code : %d&quot;, WSAGetLastError());
		return 1;
	}

	printf(&quot; Initialised.\n&quot;);

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf(&quot; Could not create socket : %d&quot; , WSAGetLastError());
	}

	printf(&quot; Socket created.\n&quot;);


	server.sin_addr.s_addr = inet_addr(&quot; 74.125.235.20&quot;);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&amp; server, sizeof(server)) &lt; 0)
	{
		puts(&quot; connect error&quot;);
		return 1;
	}

	puts(&quot; Connected&quot;);
}
// This is the function that opens the UDP Socket
int ClientConnectionManager::openUDPSocket() {

}
