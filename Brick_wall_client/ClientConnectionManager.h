#pragma once
#include <string>
#include "winsock2.h"
#include "stdio.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define BUFLEN 1024
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
	int openUDPSocket(int addr, int port);
};

