#!/usr/bin/python3
import socket
import select
import sys


def get_adresse(user: socket.socket) -> str:
    adresse = user.getpeername()
    adresse = str(adresse[0])+":"+str(adresse[1])
    return adresse


def connect(user: socket.socket, nick_dict: dict) -> str:
    connection, adresse = user.accept()
    client_list.append(connection)
    port_client = adresse[1]
    adresse = str(adresse[0])+":"+str(port_client)
    nick_dict[adresse] = adresse
    print("user ["+nick_dict[adresse] + "] has joined !")
    for j in client_list:
        if j != client_list[-1] and j != server:
            j.sendall(("user ["+nick_dict[adresse] +
                       "] has joined !\n").encode("utf-8"))
    return adresse


def cmd(data: bytes, user: socket.socket, nick_dict: dict) -> None:
    input = data.decode("utf-8")
    command = input.split(' ')[0]
    if (len(input.split(' ')) < 2) and command != "NAMES\n":
        print(command)
        user.sendall("no command given\n".encode("utf-8"))
    else:
        if command != "NAMES\n":
            msg = input.split(' ', maxsplit=1)[1]
        if command == "MSG":
            cmd_MSG(nick_dict, msg, user)
        elif command == "NICK":
            cmd_NICK(nick_dict, msg, user)
        elif command == "NAMES\n":
            cmd_NAMES(nick_dict, user)
        elif command == "BYEBYE":
            cmd_BYEBYE(nick_dict, msg, user)
        elif command == "REMOVE":
            cmd_REMOVE(nick_dict, msg, user)
        else:
            user.sendall("invalid command\n".encode("utf-8"))
    return


def cmd_MSG(nick_dict: dict, msg: str, user: socket.socket) -> None:
    adresse = get_adresse(user)
    for j in client_list:
        if j != user and j != server:
            j.sendall(("["+nick_dict[adresse] + "] "+msg).encode("utf-8"))
    return


def cmd_NICK(nick_dict: dict, msg: str, user: socket.socket) -> None:
    adresse = get_adresse(user)
    msg = str(msg.split("\n")[0])
    if (len(msg.split(" "))) > 1:
        user.sendall("no space allowed\n".encode("utf-8"))
        return
    nick_dict[adresse] = msg
    user.sendall(("New nickname is now [" + nick_dict[adresse] +
                  "]\n").encode("utf-8"))
    return


def cmd_NAMES(nick_dict: dict, user: socket.socket) -> None:
    for j in nick_dict:
        user.sendall(("["+nick_dict[j]+"] ").encode("utf-8"))
    user.sendall(("\n").encode("utf-8"))
    return


def cmd_BYEBYE(nick_dict: dict, msg: str, user: socket.socket) -> None:
    cmd_MSG(nick_dict, msg, user)
    disconnect(nick_dict, user)
    return


def cmd_REMOVE(nick_dict: dict, msg: str, user: socket.socket) -> None:
    adresse = get_adresse(user)
    if len(msg.split(" ")) < 2:
        user.sendall("no message given\n".encode("utf-8"))
        return
    target = msg.split(" ")[0].split("\n")[0]
    msg = msg.split(" ", maxsplit=1)[1]
    for j in nick_dict:
        if nick_dict[j] == target:
            target_port = j.split(":")[-1]
    for j in range(len(client_list)):
        if str(client_list[j]).split(",")[-3] == " "+target_port:
            target = client_list[j]
            target.sendall(("["+nick_dict[adresse]+"] " +
                            msg).encode("utf-8"))
            disconnect(nick_dict, target)
            return
    user.sendall("user wasn't found\n".encode("utf-8"))
    return


def disconnect(nick_dict: dict, user: socket.socket):
    adresse = get_adresse(user)
    user.sendall(("You have been disconnected\n").encode("utf-8"))
    print("user ["+nick_dict[adresse] + "] has left !")
    for j in client_list:
        if j != server and j != user:
            j.sendall(("user ["+nick_dict[adresse] +
                       "] has left !\n").encode("utf-8"))
    del nick_dict[adresse]
    client_list.remove(user)
    user.close()
    return


try:
    server = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    host = ""
    port = 7777
    server.bind((host, port))
    server.listen(1)
    client_list = [server]
    nick_dict = {server: 'SERVER'}
    while True:
        lecture, _, _ = select.select(client_list, [], [])
        for user in lecture:
            if user == server:
                adresse = connect(user, nick_dict)
            else:
                data = user.recv(4096)
                if not data:
                    disconnect(nick_dict, user)
                else:
                    cmd(data, user, nick_dict)


except socket.error as e:
    print("socket error !", e)
    sys.exit(1)
