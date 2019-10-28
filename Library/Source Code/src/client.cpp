#include "client.h"


int client_send(char* host, int port, char* msg)
{
	struct sockaddr_in6 serveraddr;
	int    serveraddrlen = sizeof(serveraddr);
	struct dvc_socket* s = (struct dvc_socket*)malloc(sizeof(struct dvc_socket));
	socket_init(s, port);

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin6_family = AF_INET;
	serveraddr.sin6_port = htons(port);
	int rc = inet_pton(AF_INET, host, &serveraddr.sin6_addr.s6_addr);
	if (rc != 1)
	{
		int k;
	}
	rc = sendto(s->m_sock, msg, strlen(msg), 0,
		(struct sockaddr*) & serveraddr,
		sizeof(serveraddr));
	close(s->m_sock);

	return 0;
	int qq = socket_connect(s, host);

	if (qq != 0)
	{
		return -1;
	}
	int result = send(s->m_sock, msg, strlen(msg), MSG_DONTWAIT);
	socket_disconnect(s);
	free(s);
	return result;
}
