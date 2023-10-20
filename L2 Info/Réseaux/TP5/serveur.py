#!/usr/bin/python3
import socket
import select
import sys


try:
    s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("", 7777))
    s.listen(1)
    l = []
    while True:
        l+=[s]
        select.select(l,[], [])
        connection, adresse = s.accept()
        print(s)
        print(l[0])
        for i in l:
            print("a")
            if i == s:
                print("connexion open", adresse)
                l.append(s.accept())
            else:
                data = connection.recv(1500)
                if not data:
                    print("connection closed")
                    i.close()
                    l[i].remove()
                    break
                connection.sendall(data)
        s.close()

except socket.error as e:
    print("socket error !", e)
    sys.exit(1)

except ConnectionError as e:
    print("connection error", e)
    sys.exit(1)