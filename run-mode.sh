#!/bin/bash

# server receive event keyboard from sniffer 
./bin/receive 11999

# with network receive sniffig keyboard by input event and capture display x11 
sudo ./bin/sniffer /dev/input/by-path/pci-0000\:00\:14.0-usb-0\:7\:1.0-event-kbd 127.0.0.1 11999 :0.0

# without network receive sniffig keyboard by input event and capture display x11 
sudo ./bin/sniffer /dev/input/by-path/pci-0000\:00\:14.0-usb-0\:7\:1.0-event-kbd 0 0 :0.0

# without x11 capture 
sudo ./bin/sniffer /dev/input/by-path/pci-0000\:00\:14.0-usb-0\:7\:1.0-event-kbd 127.0.0.1 11999


