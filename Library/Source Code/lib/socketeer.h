#ifndef _SOCKETEER_H
	#define _SOCKETEER_H

	#include <stdio.h>
	#include <sched.h>
	#include <errno.h>
	#include <stdio.h>
	#include <stdlib.h>
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

struct dvc_socket
{
	int m_sock;
	int m_hostport;
};

typedef struct Parameters
{
	int clientSocket;
	struct sockaddr_in clientAddr;
	char buffer[2048];
}
Parameters;

typedef enum
{
	Open = 0,
	Binded = 1,
	Listening = 2,
	OK = 4,
	Connected = 3,
	Closed = -1,
	Error = -2
}SOCK_Status;
	// Server-Controller API

	bool socketeer_server(int port,void(*callback)(Parameters * parameters, void * object));
	bool socketeer_server_start_keepalive(int port);
	bool socketeer_server_is_active(int port);
	bool socketeer_server_terminate();
	bool socketeer_server_is_client_alive(std::string);
	int socketeer_server_alive_clients_count();
	std::string socketeer_server_get_alive_clients();
	std::string socketeer_server_getstr(Parameters* parameters);
	void keepalive_set_timeout(int timeout);
	// Client API

	bool socketeer_client(std::string hostname,int port,std::string message);
	bool socketeer_client_start_keepalive(std::string host,int port,std::string application_name) ;
	
#endif
