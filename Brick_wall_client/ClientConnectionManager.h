#pragma once
class ClientConnectionManager
{
public:
	ClientConnectionManager();
	~ClientConnectionManager();
	int openConnection();
	int openUDPSocket();
};

