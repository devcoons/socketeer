#include "socketeer.h"
#include "client.h"
#include "server.h"

using namespace std;
/* 
	int exitrequest =0;

    void callback(Parameters* parameters,void * obj)
    {
        size_t bytecount;
		char buffer[4055];
		int buffer_len = 4055;
        memset(buffer, 0, buffer_len);
		bytecount = recv(parameters->clientSocket, buffer, buffer_len, 0);
		std::string temp = buffer;	
        std::cout<<temp<<"\n";
		if(temp=="exit")
		{
			exitrequest = 1;
		}

    }
*/
std::list<Server*> serversList;

std::string socketeer_server_getstr(Parameters* parameters)
{
	char buffer[4055];
	int buffer_len = 4055;
    memset(buffer, 0, buffer_len);
	recv(parameters->clientSocket, buffer, buffer_len, 0);
	std::string temp = buffer;	
	return temp;
}

void socketeer_server(int port,void(*callback)(Parameters * parameters, void * object))
{
	Server* server = new Server();
	server->initialize(port);
	server->assignCallback(callback,NULL);
	server->execute();
	serversList.push_back(server);
}

bool socketeer_client(std::string hostname,int port,std::string message)
{
	Client client(hostname, port);
	return client.send(message) == 0 ? true : false;
}

