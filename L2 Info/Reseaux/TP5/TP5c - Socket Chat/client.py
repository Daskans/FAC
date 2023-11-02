import socket
import sys

serveur = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = ""
port = int(sys.argv[1])
serveur.connect((host, port))
while True:
    line = sys.stdin.readline()
    serveur.sendall(line.encode("utf-8"))
    if line == "\n":
        serveur.close()
        break
    data = serveur.recv(4096)
    print(data.decode("utf-8"), end="")
serveur.close()