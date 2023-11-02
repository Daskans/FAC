#!/usr/bin/env python3
import sys
from scapy.all import *

x = UDP()/"hello\n"       # créer un datagramme UDP contenant un texte quelconque
x.show()                # regardons les valeurs par défaut
x.sport = 12345         # port source arbitraire
x.dport = 13            # port destination UDP du service daytime
x.show()

p = IP()                # créer un nouveau paquet IP
p.src = "147.210.0.2"   # adresse source
p.dst = "192.168.0.2"   # adresse destination
p.show()

p = p/x                 # encapsuler avec '/' le datagramme UDP dans le paquet IP
p.show()                # observer le champ proto mis à jour automatiquement

q = sr1(p)              # on envoie le paquet et on récupère la réponse
q.show()                # regardons la réponse
y = q.payload           # extraire le datagramme UDP
data = y.load           # extraire les données (la date)
print(data)