#include "server.h"

	Server::Server()
	{
		
	}

	void Server::initialize(int port) 
	{
		this->port = port;
	}

	void Server::assignCallback(void(*function)(Parameters *, void*), void* self)
	{
		this->callbackFunction = function;
		this->callbackObject = self;
	
	}

	void Server::execute()
	{
		applicationThread = std::thread(&Server::execution, this);
		applicationThread.detach();
	}

	int Server::getPort()
	{
		return port;
	}

	void Server::execution()
	{
		socket= new Socket(port);

		if (!socket->isOpen()) 	{ 	socket->disconnect(); exit(1); }
		if (!socket->bind()) 	{	socket->disconnect(); exit(1); } 
		if (!socket->listen()) 	{	socket->disconnect(); exit(1); }

		while (true) 
		{      
			Parameters * params = socket->accept(); 
			if (params->clientSocket != -1) 
			{   
				struct in_addr inaddr = params->clientAddr.sin_addr;
				char buf[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &inaddr, buf, sizeof(buf));
				std::thread t(&Server::callback, this, params);
				t.detach();					
			}
			else 
			{
				free(params);
			}
			fflush(stdout); 
			fflush(stdin); 
		}
	}

	bool Server::isActive()
	{
		return (socket->isOpen()) ? true : false;
	}

	void Server::callback(Parameters * p)
	{
		if (Server::callbackFunction != NULL)
			Server::callbackFunction(p, this->callbackObject);
			
		free(p);
	}

