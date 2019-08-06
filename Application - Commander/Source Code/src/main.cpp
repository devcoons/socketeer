#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <socketeer.h>

	void print_usage()
	{
		printf("Usage : (as server) -p(port) -h(host)]\n");
		exit(-1);
	}


    void callback(Parameters* parameters,void * obj)
    {
		std::string temp = socketeer_server_getstr(parameters);	
       	std::cout<<temp;
    }

    int main(int argc, char ** argv)
	{
    	int long_index = 0, opt = 0,port = 0;

		static struct option long_options[] = {
			{"port",		required_argument,	0,	'p' },
			{0,				0,					0,	0   }
		};

        while ( (opt = getopt_long(argc, argv, "p:", long_options, &long_index )) != -1 )
        	switch (opt) 
			{
				case 'p' :
					port =  atoi(optarg);
					break;
				default:
					print_usage();
					exit(EXIT_FAILURE);
			}

		printf("Starting socket server..\n");
        
		if(socketeer_server(port,callback) == false)
		{
			printf("Socket failed during the initializatio\nCheck is port is already used.\n");
			return 0;
		}

		printf("Socket server active\nActivating Keepalive mechanism\n");
		if(socketeer_server_start_keepalive(port+1) == false)
		{
			printf("KeepAlive failed during the initializatio\nCheck is port is already used.\n");
			return 0;
		}
		printf("KeepAlive server active\n");
		
		int c = socketeer_server_alive_clients_count();

        while(1)
		{
			fflush(stdout); 
			fflush(stdin); 
			usleep(10000);
			if(c != socketeer_server_alive_clients_count())
			{
				std::cout<<"Clients list changed: "<<socketeer_server_get_alive_clients()<<"\n";
				c = socketeer_server_alive_clients_count();
				usleep(10000);
			}
		}

        return 0;
    }
