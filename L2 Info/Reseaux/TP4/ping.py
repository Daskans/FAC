#!/usr/bin/env python3
import sys
from scapy.all import *

ping = IP(dst='192.168.0.2')/ICMP(type='echo-request')
ping.show()
pong = sr1(ping)
pong.show()
