#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <socketeer.h>

	void print_usage()
	{
		printf("Usage : -c[(as client) -h(host) -p(port) -m(message)] -s[(as server) -p(port)-h(host)]\n");
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
        	bool is_client=false,is_server=false;
        	std::string host;
		std::string msg;

		static struct option long_options[] = {
			{"client",   	no_argument,  0,  'c' },
			{"server", 		no_argument,  0,  's' },
			{"host",  		required_argument,	0,  'h' },
			{"port",		required_argument,	0,	'p' },
			{"message",		required_argument,	0,	'm' },
			{0,				0,					0,	0   }
		};

        	while ( (opt = getopt_long(argc, argv, "csh:p:m:", long_options, &long_index )) != -1 )
            		switch (opt) 
			{
				case 'h' :
					host.assign(optarg);
					break;
				case 'p' :
					port =  atoi(optarg);
					break;
				case 'm' : 
					msg.assign(optarg);
					break;
				case 'c' : 
					is_client = true;
                    			is_server = false;
					break;
				case 's' : 
				    	is_server = true;
                    			is_client = false;
					break;
				default:
					print_usage();
					exit(EXIT_FAILURE);
			}

        if(is_client == true)
        {
		printf(socketeer_client(host,port,msg)==true ? "Message successfully sent..\n" : "Message failed to send..\n");
        	return 0;
        }   

	printf("Starting socket server..\n");
        if(socketeer_server(port,callback) == false)
	{
		printf("Socket failed during the initializatio\nCheck is port is already used.\n");
		fflush(stdout);
		fflush(stdin);
		usleep(10000);
		return 0;
	}
	printf("Socket server active\n");

		
        while(1)
		{
			fflush(stdout); 
			fflush(stdin); 
		}

        return 0;
    }
