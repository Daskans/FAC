#!/usr/bin/python3
import socket
import select
import sys


try:
    s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("", 7777))
    s.listen(1)
    l = [s]
    while True:
        lecture, _, _ = select.select(l,[], [])
        for i in lecture:
            if i == s:
                connection, adresse = i.accept()
                print("pending connection", adresse)
                l.append(connection)
                print("connection successfull")
            else:
                data = i.recv(1500)
                if not data:
                    print("connection closed")
                    l.remove(i)
                    i.close()
                else :
                    print(data.decode("utf-8"), end="")
                    i.sendall(data)

except socket.error as e:
    print("socket error !", e)
    sys.exit(1)

except ConnectionError as e:
    print("connection error", e)
    sys.exit(1)