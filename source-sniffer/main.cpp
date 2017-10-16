#include <iostream>
#include <thread>
#include <sys/stat.h>
#include <signal.h>

#define LOG "./log/"

using namespace std;
#include "sniffig.h"
#if NO_X11 == 1
	#include "screen.h"
#endif

SniffingEvent sniff;
thread *sniffer;
#if NO_X11 == 1
	GetScreen screen;
	thread *capture;
#endif

void event_parser()
{
	sniff.run();
}

#if NO_X11 == 1
void capture_screen()
{
	screen.capture();
}
#endif

void quit(int s)
{
	sniff.close();
	sniffer->detach();
	#if NO_X11 == 1
		capture->detach();
	#endif
	exit(0);
}

int main(int argc, char ** argv)
{
	#if NO_X11 == 1
	if(argc<5) {
		cerr<<"Error: input-event ip port display"<<endl;
		exit(0);
	}
	#elif NO_X11 == 0
	if(argc<4) {
		cerr<<"Error: input-event ip port"<<endl;
		exit(0);
	}
	#endif

	string dev = argv[1];
	string ip  = argv[2];
	int port   = atoi(argv[3]);
	#if NO_X11 == 1
		string display = argv[4];
	#endif

	mkdir(LOG,0750);
	if (signal(SIGINT, quit) == SIG_ERR)
		cerr << "Error signal!"<<endl;
	if( sniff.init((char *)dev.c_str(),ip,port) )
	{
		#if NO_X11 == 1
			screen.setup((char *)display.c_str());
		#endif
		sniffer = new thread(event_parser);
		#if NO_X11 == 1
			capture = new thread(capture_screen);
		#endif
		sniffer->join();
		#if NO_X11 == 1
			capture->join();
		#endif
	}
	else
		cerr << "Error open event: "<<argv[1]<<endl;
	return 0;
}
