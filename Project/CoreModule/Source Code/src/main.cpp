#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <socketeer.h>

    void callback(Parameters* parameters,void * obj)
    {
		std::string temp = socketeer_server_getstr(parameters);	
       	std::cout<<temp;
    }

    int main(int argc, char ** argv)
	{
    	int Keepalive_Inbound = 8000;
		int GUIModule_Inbound = 8001;
		int RFIDModule_Inbound = 8002;
		
		printf("Starting CoreModule.\n");
        
		if(socketeer_server(GUIModule_Inbound,callback) == false || socketeer_server(RFIDModule_Inbound,callback) == false)
		{
			printf("Socket failed during the initializatio\nCheck if port is already used.\nExiting...\n");
			return 0;
		}

		printf("Socket server active\nActivating Keepalive mechanism\n");
		if(socketeer_server_start_keepalive(Keepalive_Inbound) == false)
		{
			printf("KeepAlive failed during the initializatio\nCheck is port is already used.\nExiting...\n");
			return 0;
		}
		printf("KeepAlive server active\nWaiting for other modules..\n");

		while(1)
		{
			if(socketeer_server_is_client_alive("GUIModule")== true && socketeer_server_is_client_alive("RFIDModule")== true)
			{
				printf("Extra Modules are active..\n");
				break;
			}
			fflush(stdout); 
			fflush(stdin); 
			sleep(1);
		}

		while(1)
		{




			fflush(stdout); 
			fflush(stdin); 
			usleep(10000);
		}
        return 0;
    }
