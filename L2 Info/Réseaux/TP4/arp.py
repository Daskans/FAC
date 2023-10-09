import sys
from scapy.all import *

print('###############################')
ether = Ether(dst='FF:FF:FF:FF:FF')
arp = ARP(pdst='192.168.0.2')
ping = ether/arp
ping.show()
print('-------------------------------')
pong = srp1(ping)
pong.show()
print('###############################')