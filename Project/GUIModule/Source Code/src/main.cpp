#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <socketeer.h>

	int terminate = 0;


    void callback(Parameters* parameters,void * obj)
    {
		std::string temp = socketeer_server_getstr(parameters);	
       	std::cout<<temp;

		if(temp == "EXIT")
			terminate = 1;
    }

    int main(int argc, char ** argv)
	{
		int RFIDModule_Inbound = 8011;
		int CoreModule_Outbound = 8001;
		int KeepAlive_Outbound = 8000;

		printf("Starting GUI Module..\n");
        
		if(socketeer_server(RFIDModule_Inbound,callback) == false)
		{
			printf("Socket failed during the initializatio\nCheck is port is already used.\n");
			return 0;
		}
		if(socketeer_client_start_keepalive("127.0.0.1",KeepAlive_Outbound,"GUIModule") == false)
		{
			printf("KeepAlive failed during the initializatio\nCheck is port is already used.\n");
			return 0;
		}

        while(1)
		{
			fflush(stdout); 
			fflush(stdin); 
			usleep(10000);
		}

        return 0;
    }
