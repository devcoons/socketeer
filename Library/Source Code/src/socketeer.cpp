#include "socketeer.h"
#include "client.h"
#include "server.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

Server* server_keepalive;
std::thread keepalive_thread;

std::list<Server*> serversList;
std::vector<pair<std::string,milliseconds>> keepaliveList;

std::string keepalive_client_host;
std::string keepalive_client_name;
int keepalive_client_port;


void keepalivecb(Parameters* parameters,void * obj)
{
	size_t bytecount;
	char buffer[4055];
	int buffer_len = 4055;
    memset(buffer, 0, buffer_len);
	bytecount = recv(parameters->clientSocket, buffer, buffer_len, 0);
	std::string temp = buffer;
	for(int i=0;i<keepaliveList.size();i++)
	{
		if(keepaliveList[i].first == temp)
		{
			keepaliveList[i].second = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			return;
		}
	}
	keepaliveList.push_back(std::make_pair(temp,duration_cast<milliseconds>(system_clock::now().time_since_epoch())));
}

void KeepAliveClientThread()
{
	while(1)
	{
		socketeer_client(keepalive_client_host,keepalive_client_port,keepalive_client_name);
		sleep(2);
	}
}

void KeepAliveThread()
{
	while(1)
	{
		milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		for(int i=0;i<keepaliveList.size();i++)
		{
			if(keepaliveList[i].second.count() +5000 < now.count())
			{
				std::cout<<"Remove: "<<keepaliveList[i].first<<"\n";
				keepaliveList.erase(keepaliveList.begin()+i);
			}
		}
		usleep(1000);
	}
}

bool socketeer_client_start_keepalive(std::string host,int port,std::string application_name)
{
	keepalive_client_host = host;
	keepalive_client_port = port;
	keepalive_client_name = application_name;
	keepalive_thread = std::thread(KeepAliveClientThread);
	keepalive_thread.detach();
}

bool socketeer_server_start_keepalive(int port)
{
	server_keepalive = new Server();
	server_keepalive->initialize(port);
	server_keepalive->assignCallback(keepalivecb,NULL);
	keepalive_thread = std::thread(KeepAliveThread);
	server_keepalive->execute();
	usleep(10000);
	keepalive_thread.detach();
	return server_keepalive->isActive();
}

std::string socketeer_server_getstr(Parameters* parameters)
{
	char buffer[4055];
	int buffer_len = 4055;
    memset(buffer, 0, buffer_len);
	recv(parameters->clientSocket, buffer, buffer_len, 0);
	std::string temp = buffer;	
	return temp;
}

bool socketeer_server_is_client_alive(std::string arg)
{
	for(int i=0;i<keepaliveList.size();i++)
        if(keepaliveList[i].first == arg)
        	return true;
	return false;
}


std::string socketeer_server_get_alive_clients()
{
	std::string clients;
	for(int i=0;i<keepaliveList.size();i++)
		clients+= keepaliveList[i].first+"|";
	return clients;
}

bool socketeer_server(int port,void(*callback)(Parameters * parameters, void * object))
{
	Server* server = new Server();
	server->initialize(port);
	server->assignCallback(callback,NULL);
	server->execute();
	usleep(10000);
	if(server->isActive()==false)
		return false;
	serversList.push_back(server);
	return true;
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

int socketeer_server_alive_clients_count()
{
	return keepaliveList.size();
}