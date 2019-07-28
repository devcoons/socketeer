#pragma once

#include <memory>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socketeer.h"
#ifndef TCP_USER_TIMEOUT
#define TCP_USER_TIMEOUT 18 
#endif

#define DEFAULT_TEST_PORT       1101
#define DEFAULT_TIMEOUT         1000


class Socket 
{
private:
	int m_sock = -1;
	int m_hostPort = -1;
		
public:
	Socket();
	Socket(int hostPort);
	~Socket();
	bool bind(void);
	bool isOpen(void);
	void disconnect();
	bool listen(void);	
	int currSocket(void);
	Parameters* accept(void);  
	bool connect(std::string host_name); 	
};

