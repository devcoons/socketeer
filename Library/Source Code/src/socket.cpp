#include "socket.h"

void socket_init(struct dvc_socket* s, int port)
{
	s->m_hostport = port;
	s->m_sock = socket(AF_INET6, SOCK_DGRAM, 0);
	usleep(5000);
	if (s->m_sock == -1)
		return socket_disconnect(s);
}

void socket_disconnect(struct dvc_socket* s)
{
	if (s->m_sock == -1)return;
	close(s->m_sock);
	s->m_sock = -1;
}

SOCK_Status socket_status(struct dvc_socket* s)
{
	return s->m_sock != -1 ? Open : Closed;
}

SOCK_Status socket_bind(struct dvc_socket* s)
{
	if(socket_status(s) != Open)
		return Error;

	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET6;
	my_addr.sin_port = htons(s->m_hostport);
	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(s->m_sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1)
		return Error;
	return Binded;
}

Parameters* socket_accept(struct dvc_socket* s)
{
	socklen_t addr_size = 0;
	addr_size = sizeof(struct sockaddr_in);
	struct sockaddr_in clientAddr;
	if (s->m_sock != -1)
	{
		Parameters* params = (Parameters*)malloc(sizeof(Parameters));
		int result = recvfrom(s->m_sock, params->buffer,2048,0, (struct sockaddr*) &clientAddr,&addr_size);
		params->clientSocket = result;
		memmove(&params->clientAddr, &clientAddr, sizeof(struct sockaddr_in));	
		return params;
	}
	return NULL;
}

SOCK_Status socket_connect(struct dvc_socket* s, char *hostname)
{
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(s->m_hostport);
	memset(&(my_addr.sin_zero), 0, sizeof(my_addr.sin_zero));
	inet_pton(AF_INET, hostname, &my_addr.sin_addr);
	return connect(s->m_sock, (struct sockaddr*) & my_addr, sizeof(my_addr)) == 0 ? Connected : Error;
}