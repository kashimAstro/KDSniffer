#include <iostream>
#include <fstream>
#include <signal.h>
#include "TCPServer.h"

TCPServer tcp;
ofstream outfile;

void quit(int s)
{
	outfile.close();
        exit(0);
}

void * loop(void * m)
{
        pthread_detach(pthread_self());
	while(1)
	{
		string str = tcp.getMessage();
		if( str != "" )
		{
			cout << "Message:" << str ;
			outfile << str;
			tcp.Send("OK");
			tcp.clean();
		}
		usleep(1000);
	}
	tcp.detach();
}

int main(int argc, char ** argv)
{
	if(argc<2){
		cerr<<"Error: port"<<endl;
		exit(0);
	}
	outfile.open("keys.log", std::ios_base::app);
	if (signal(SIGINT, quit) == SIG_ERR)
                cerr << "Error signal!"<<endl;
	pthread_t msg;
	tcp.setup(atoi(argv[1]));
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{
		tcp.receive();
	}
	return 0;
}
