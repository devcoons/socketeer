#include "socketeer.h"
#include "client.h"
#include "server.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

static struct dvc_server* srv_ka;
std::thread keepalive_thread;



std::list<struct dvc_server*> serversList;
std::vector<pair<std::string,milliseconds>> keepaliveList;

std::string keepalive_client_host;
std::string keepalive_client_name;
int keepalive_client_port;
int keepalive_timeout = 5000;



void keepalive_set_timeout(int timeout)
{
	keepalive_timeout = timeout;
}


void keepalivecb(Parameters* parameters,void * obj)
{
	std::string temp = parameters->buffer;
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
		client_send((char*)keepalive_client_host.c_str(), keepalive_client_port, (char*)keepalive_client_name.c_str());
		if(keepalive_timeout < 500)
			keepalive_timeout = 500;
		usleep(keepalive_timeout - 350);
	}
}

void KeepAliveThread()
{
	while(1)
	{
		milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		for(int i=0;i<keepaliveList.size();i++)
		{
			if(keepalive_timeout < 500)
				keepalive_timeout = 500;
			
			if((keepaliveList[i].second.count() + keepalive_timeout) < now.count())
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
	return true;
}

bool socketeer_server_start_keepalive(int port)
{
	srv_ka = (struct dvc_server*)malloc(sizeof(struct dvc_server));
	srv_ka->port = port;
	srv_ka->callbackFunction = keepalivecb;
	keepalive_thread = std::thread(KeepAliveThread);
	server_start(srv_ka);
	usleep(10000);
	keepalive_thread.detach();
	return true;
}

std::string socketeer_server_getstr(Parameters* parameters)
{
	int i = 0;
	string s = "";
	while (parameters->buffer[i] != '\0')
	{
		s = s + parameters->buffer[i];
		i++;
	}
	return s;
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

	struct dvc_server* srv_ = (struct dvc_server*)malloc(sizeof(struct dvc_server));
	srv_->port = port;
	srv_->callbackFunction = callback;
	server_start(srv_);
	usleep(10000);
	serversList.push_back(srv_);
	return true;
}

bool socketeer_client(std::string hostname,int port,std::string message)
{
	client_send((char*)hostname.c_str(), port, (char*)message.c_str());
	return true;
}

bool socketeer_server_is_active(int port)
{
	list <struct dvc_server*> :: iterator it;
	for (it = serversList.begin(); it != serversList.end(); ++it)
		if ((*it)->port == port)
			return socket_status((*it)->socket) != -1 ? true : false;
	return false;
}

int socketeer_server_alive_clients_count()
{
	return keepaliveList.size();
}
