#!/usr/bin/python3
import socket
import ssl

HOST = "127.0.0.1"
PORT = 7777
BUFSIZE = 1024

# main program
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
context.load_verify_locations("ca.pem","ca.key")
s.connect((HOST, PORT))
sslsock = context.wrap_socket(s, server_hostname=HOST)
msg = b"Hello World!"
sslsock.sendall(msg)
answer = sslsock.recv(BUFSIZE)
print(answer.decode())
sslsock.close()
