import socket
import sys

serveur = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = ""
port = int(sys.argv[1])
serveur.connect((host,port))
while True:
    line = sys.stdin.readline()
    serveur.send(line.encode("utf-8"))
    if line == "\n":
        serveur.close()
        break
serveur.close()