# KDSniffer

a simple sniffer for event keyboard and screen desktop x11,
this demon it is divided into two pieces:

<code><b>bin/sniffer</b></code><br>
<b><small>(to be placed on the machine to sniff)</small></b>
<br> 
and 
<br>
<code><b>bin/receive</b></code><br>
<b><small>(this piece is not mandatory, it can need if you want to capture remote sniffer,
via a vpn or as shown in the example below with a raspberry via USB otg.)</small></b><br>

a example use with raspberry pi zero otg usb and client pc:<br>

connect your pi-zero via USB to PC you want to monitor.<br>

<code><b>PC(sniffer) <---> ZERO(receive)</b></code><br>

run the receive on the pi-zero and run sniffer on PC, sniffer it takes care of sending all the keyboard info to the receive.<br>

usb otg pi-zero:<br>
<img src="1.jpg"/><br>

configure otg usb network on pi-zero:
<br>
<code><b>edit /boot/config.txt</b></code><br>
and add:
<code><b>dtoverlay=dwc2</b></code><br>
<code><b>edit /boot/cmdline.txt</b></code><br>
and add:
<code><b>modules-load=dwc2,g_ether</b></code><br>

assign static ip on pi-zero:
<pre><code><b>allow-hotplug usb0<br>
iface usb0 inet static<br>
        address 192.168.7.2<br>
        netmask 255.255.255.0<br>
        network 192.168.7.0<br>
        broadcast 192.168.7.255<br>
        gateway 192.168.7.1<br>
</b></code></pre>
screen sniffig:<br>
<img src="2.jpg"/><br>
<br>

if client side <code>ifconfig does</code> not return USB device, try with:<b><br>
<b>ip address show</b><br>
<b>ip link set usb0 up</b><br>
<b>ifconfig usb0 192.168.7.10</b><br>
