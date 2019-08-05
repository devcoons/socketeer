#ifndef _SOCKETEER_H
	#define _SOCKETEER_H

	#include <stdio.h>
	#include <sched.h>
	#include <errno.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <memory>
	#include <stdio.h>
	#include <unistd.h>
	#include <string.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <list>
	#include <string>
	#include <iostream>
	#include <vector>
	#include <fcntl.h>
	#include <stdio.h>
	#include <sstream>
	#include <stdlib.h>

	typedef struct Parameters
	{
		int clientSocket; sockaddr_in clientAddr;
	}
	Parameters;

	std::string socketeer_server_getstr(Parameters* parameters);
	bool socketeer_server(int port,void(*callback)(Parameters * parameters, void * object));
	bool socketeer_server_start_keepalive(int port);
	bool socketeer_client(std::string hostname,int port,std::string message);
	bool socketeer_server_is_active(int port);
	bool socketeer_server_terminate();
#endif
