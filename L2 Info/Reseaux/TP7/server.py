#!/usr/bin/python3
import socket
import ssl

HOST = '127.0.0.1'
PORT = 7777
BUFSIZE = 1024

# echo server
def echo(sc):
    while True:
        data = sc.recv(BUFSIZE)
        if data == b'' or data == b'\n':
            break
        print(data.decode())
        sc.sendall(data)


# main program
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen()
context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
context.load_cert_chain("server.pem","server.key")
sslsock = context.wrap_socket(s, server_side=True)

while True:
    sc, addr = sslsock.accept()
    echo(sc)
    sc.close()

s.close()
