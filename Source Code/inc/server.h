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
		void assignCallback(void(*)(Parameters*, void*), void*);
	private:
		int port;
		int selected;
		void execution();
		void *callbackObject;
		void callback(Parameters*);
		void (*callbackFunction)(Parameters*, void*);	
	};

