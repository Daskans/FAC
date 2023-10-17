import sys
from scapy.all import *

print('###############################')
ping = IP(dst='192.168.0.2')
for i in range(1, 101):
    tcp = TCP(dport=i,flags="S")
ping = ping/tcp
ping.show()
print('-------------------------------')
pong = sr1(ping)
pong.show()
print('###############################')