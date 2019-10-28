#ifndef _SOCKET_H
#define _SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "socketeer.h"


void socket_disconnect(struct dvc_socket* s);
void socket_init(struct dvc_socket* s, int port);
SOCK_Status socket_status(struct dvc_socket* s);
SOCK_Status socket_bind(struct dvc_socket* s);
SOCK_Status socket_listen(struct dvc_socket* s);
Parameters* socket_accept(struct dvc_socket* s);
SOCK_Status socket_connect(struct dvc_socket* s, char* hostname);

#endif
