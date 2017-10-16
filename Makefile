NO_X11=1
CFLAGS=--std=c++11 -lpthread 

ifeq ($(NO_X11), 1)
CFLAGS+=`pkg-config --cflags --libs x11`
CFLAGS+=`pkg-config --cflags --libs cairo`
endif

MK=`mkdir -p bin`

all: mkdir sniffer receive

receive:
	g++ -Wall -o bin/receive source-receive/main.cpp source-receive/TCPServer.cpp --std=c++11 -lpthread

sniffer:
	g++ -Wall -o bin/sniffer source-sniffer/main.cpp source-sniffer/TCPClient.cpp $(CFLAGS) -DNO_X11=$(NO_X11)
mkdir:
	$(MK)
