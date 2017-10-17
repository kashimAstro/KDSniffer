# KDSniffer

a simple sniffer for event keyboard and screen desktop x11,
this demon it is divided into two pieces:

<code><b>bin/sniffer</b></code><br>
<h6>(to be placed on the machine to sniff)</h6>
<h6>and</h6> 
<code><b>bin/receive</b></code>
<h6>(this piece is not mandatory, it can need if you want to capture remote sniffer,
via a vpn or as shown in the example below with a raspberry via USB otg.)</h6><br>

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
<b>for disable X11 capture screen edit Makefile and change value variable NO_X11=0</b><br>
<b>Example use receive and sniffer:</b><br>

<h5>server receive event keyboard from sniffer</h5>
<pre><code>./bin/receive 11999</code></pre><br>

<h5>with network receive, sniffig keyboard by input event and capture display X11</h5>
<pre><code>sudo ./bin/sniffer /dev/input/event0 192.168.7.2 11999 :0.0</code></pre><br>
<h5>without network receive sniffig keyboard by input event and capture display X11</h5>
<pre><code>sudo ./bin/sniffer /dev/input/event0 0 0 :0.0</code></pre><br>

<h5>without x11 capture (only compile with NO_X11=0)</h5>
<pre><code>sudo ./bin/sniffer /dev/input/by-path/pci-0000\:00\:14.0-usb-0\:7\:1.0-event-kbd 127.0.0.1 11999</code></pre><br>
<br>
if client side <code>ifconfig does</code> not return USB device, try with:<b><br>
<b>ip address show</b><br>
<b>ip link set usb0 up</b><br>
<b>ifconfig usb0 192.168.7.10</b><br>


