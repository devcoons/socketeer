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

bool socketeer_server(int port,void(*callback)(Parameters * parameters, void * object))
{
	Server* server = new Server();
	server->initialize(port);
	server->assignCallback(callback,NULL);
	server->execute();
	usleep(10000);
	if(server->isActive()==true)
	{
		serversList.push_back(server);
		return true;
	}
	return false;
}

bool socketeer_client(std::string hostname,int port,std::string message)
{
	Client client(hostname, port);
	return client.send(message) == 0 ? true : false;
}

bool socketeer_server_is_active(int port)
{
	list <Server*> :: iterator it; 
	for(it = serversList.begin(); it!= serversList.end(); ++it)
		if((*it)->getPort() == port)	
			return (*it)->isActive();
	return false;
}
