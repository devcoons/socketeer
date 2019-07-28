#pragma once
#include "socket.h"

class Client
{
public:
	Client(std::string, int);
	std::string receive();
	int send(std::string);
	void close();
private:
	int port;
	Socket socket;
	std::string host;
};

