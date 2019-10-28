#include "server.h"

void* server_execution(void* arg);

SOCK_Status server_start(struct dvc_server*srv)
{
	srv->socket = (struct dvc_socket*)malloc(sizeof(struct dvc_socket));

	socket_init(srv->socket,srv->port);

	if (socket_status(srv->socket) != Open)
		goto error;

	if (socket_bind(srv->socket) != Binded)
		goto error;

	srv->thread_active = 1;
	pthread_create(&srv->thread_id, NULL, server_execution, srv);
	return Connected;

error:
	socket_disconnect(srv->socket);
	free(srv->socket);
	return Error;
}


void* server_execution(void* arg)
{

	struct in_addr inaddr;
	char buf[INET_ADDRSTRLEN];

	struct dvc_server* srv = (struct dvc_server*)arg;
	Parameters* params;
	while (srv->thread_active == 1)
	{
		if (srv->socket != NULL)
		{
			params = socket_accept(srv->socket);
			if (params->clientSocket != -1 && params!=NULL)
			{
				memmove(&inaddr, &params->clientAddr.sin_addr, sizeof(struct in_addr));
				inet_ntop(AF_INET, &inaddr, buf, sizeof(buf));
				usleep(1000);
				if (srv->callbackFunction != NULL)
					srv->callbackFunction(params,NULL);
				fflush(stdout);
				fflush(stdin);
			}
		}
		usleep(2000);
		if(params!=NULL)
			free(params);
		fflush(stdout);
		fflush(stdin);
	}
	printf("\nExit!\n");
	return NULL;
}

SOCK_Status server_stop(struct dvc_server* srv)
{
	srv->thread_active = 0;
	pthread_join(srv->thread_id, NULL);
	socket_disconnect(srv->socket);
	free(srv->socket);
	return OK;
}