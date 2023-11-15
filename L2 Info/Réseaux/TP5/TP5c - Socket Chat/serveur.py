#!/usr/bin/python3
import socket
import select
import sys


try:
    s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    host = ""
    port = 7777
    s.bind((host, port))
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
                for j in l:
                    if j != i and j != s:
                        print(adresse)
                        #j.sendall((adresse ,":",  port).encode("utf-8"))
            else:
                data = i.recv(4096)
                if not data:
                    print("connection closed")
                    l.remove(i)
                    i.close()
                else :
                    print(data.decode("utf-8"), end="")
                    input = data.decode("utf-8")
                    command = input.split(' ')[0]
                    if (len(input.split(' '))<2):
                        i.sendall("no command given\n".encode("utf-8"))
                    else :
                        msg = input.split(' ', maxsplit=1)[1]
                        if command == "MSG":
                            for j in l:
                                if j != i and j != s:
                                    j.sendall(msg.encode("utf-8"))
                        else :
                            i.sendall("invalide command\n".encode("utf-8"))

except socket.error as e:
    print("socket error !", e)
    sys.exit(1)

except ConnectionError as e:
    print("connection error", e)
    sys.exit(1)