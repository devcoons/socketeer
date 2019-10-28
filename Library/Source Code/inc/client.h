#ifndef _CLIENT_H
#define _CLIENT_H

#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int client_send(char* host, int port, char* msg);
#endif
