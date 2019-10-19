#pragma once
#include <string>
#include "winsock2.h"
#include "stdio.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;
class ClientConnectionManager
{
private:
	WSADATA wsa;
	SOCKET s;
public:
	ClientConnectionManager();
	~ClientConnectionManager();
	int openConnection();
	int openConnection(string ip);
	int openConnection(string ip, int port);
	int openUDPSocket();
};

