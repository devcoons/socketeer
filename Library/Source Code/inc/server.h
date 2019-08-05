#pragma once

	#include <thread>
	#include "socket.h"

	class Server
	{
	public:
		Server();
		void initialize(int);
		void execute();
		void stop();	
		bool isActive();
		int getPort();
		void assignCallback(void(*)(Parameters*, void*), void*);
	private:
		Socket* socket;
		std::thread applicationThread;
		int port;
		int selected;
		void execution();
		void *callbackObject;
		void callback(Parameters*);
		void (*callbackFunction)(Parameters*, void*);	
	};

