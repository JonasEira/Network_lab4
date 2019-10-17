#pragma once
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;
class ClientConnectionManager
{
public:
	ClientConnectionManager();
	~ClientConnectionManager();
	int openConnection();
	int openConnection(string ip);
	int openConnection(string ip, int port);
	int openUDPSocket();
};

