#KDSniffer

a simple sniffer for event keyboard and screen desktop x11
this demon it is divided into two pieces:

<code>bin/sniffer </code>
(to be placed on the machine to sniff)
<br> 
and 
<br>
<code>bin/receive </code>
(this piece is not mandatory, it can serve if you want to capture remote sniffer,
via a vpn or as shown in the example below with a raspberry via USB otg.)

a example use with raspberry pi zero otg usb and client pc:

connect your pi-zero via USB to PC you want to monitor. 

ZERO(receive) <---> PC(sniffer)

run the receive on the ZERO and run sniffer on PC, sniffer it takes care of sending all the keyboard info to the receive..

usb otg pi-zero:
<img src="1.png"/><br>

# /boot/config.txt
# dtoverlay=dwc2

# /boot/cmdline.txt
# modules-load=dwc2,g_ether

screen sniffig:
<img src="2.png"/><br>

# ip address show
# ip link set usb0 up

# ifconfig usb0 192.168.7.10
