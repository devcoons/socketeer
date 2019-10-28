#ifndef _SERVER_H
#define _SERVER_H

	#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	#include "socket.h"


struct dvc_server
{
	int port;
	int thread_active;
	pthread_t thread_id;
	struct dvc_socket* socket;
	void (*callbackFunction)(Parameters*, void*);
};

SOCK_Status server_start(struct dvc_server* srv);
SOCK_Status server_stop(struct dvc_server* srv);

#endif