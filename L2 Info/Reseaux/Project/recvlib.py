#!/usr/bin/python3

# Module: recvlib.py
# Copyright: University of Bordeaux, France (2023).

import sys
import socket
import base64
import ssl
import email

###############################################
###                DEFAULT                  ###
###############################################

DOMAIN = "pouet.com"
TIMEOUT = 2
MAXLINE = 1024

###############################################
###               POP3/CLIENT               ###
###############################################

def pop3_connect(host, port, secure, verbose):
    """
    Connects to the POP3 server.

    Parameters:
        - host (str): The address of the POP3 server.
        - port (int): The port of the POP3 server.
        - secure (bool): Indicates whether the connection should be secure.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - s (socket): The socket connected to the POP3 server.
    """
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        if secure:
            context = ssl.create_default_context();
            s = context.wrap_socket(s, server_hostname = host)

        s.connect((host, port))

        if verbose:
            debug = s.recv(MAXLINE).decode("utf-8")
            print(f"connect debugging : {debug}")

        return s
    
    except socket.error as e:
        print(f"Error POP3 connect: {e}")
        sys.exit(1)

###############################################

def pop3_auth(s, login, password, verbose):
    """
    Authenticates the client with the POP3 server using the provided login information.

    Parameters:
        - s (socket): The socket connected to the POP3 server.
        - login (str): The username for authentication.
        - password (str): The password for authentication.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if authentication is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    
    s.sendall(f"USER {login}\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True

    s.sendall(f"PASS {password}\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True

    if verbose:
        print(f"AUTH debugging : {ans}")

    return ok, ans

###############################################

def pop3_noop(s, verbose):
    """
    Sends the NOOP command to the POP3 server.

    Parameters:
        - s (socket): The socket connected to the POP3 server.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    
    s.sendall(f"NOOP\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True

    if verbose:
        print(f"NOOP debugging : {ans}")

    return ok, ans

###############################################

def pop3_stat(s, verbose):
    """
    Sends the STAT command to the POP3 server.

    Parameters:
        - s (socket): The socket connected to the POP3 server.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    
    s.sendall(f"STAT\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True

    if verbose:
        print(f"STAT debugging : {ans}")

    return ok, ans

###############################################

def pop3_list(s, verbose):
    """
    Sends the LIST command to the POP3 server.

    Parameters:
        - s (socket): The socket connected to the POP3 server.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
        - info (str): List information.
    """
    ok = False
    ans = ""
    info = ""
    
    s.sendall(f"LIST\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True

    info = ans

    if verbose:
        print(f"LIST debugging : {ans}")

    return ok, ans, info

###############################################

def pop3_retr(s, rank, verbose):
    """
    Sends the RETR command to the POP3 server to retrieve a message.

    Parameters:
        - s (socket): The socket connected to the POP3 server.
        - rank (int): The rank of the message to retrieve.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
        - msg (email.message.Message): Retrieved message.
    """
    ok = False
    ans = ""
    msg = None
    
    s.sendall(f"RETR {rank}\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True
        msg = ans

    if verbose:
        print(f"RETR debugging : {ans}")

    return ok, ans, msg

###############################################

def pop3_dele(s, rank, verbose):
    """
    Sends the DELE command to the POP3 server to delete a message.

    Parameters:
        - s (socket): The socket connected to the POP3 server.
        - rank (int): The rank of the message to delete.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    
    s.sendall(f"DELE {rank}\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True

    if verbose:
        print(f"DELE debugging : {ans}")

    return ok, ans

###############################################

def pop3_quit(s, verbose):
    """
    Sends the QUIT command to the POP3 server to terminate the connection.

    Parameters:
        - s (socket): The socket connected to the POP3 server.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    
    s.sendall(f"QUIT\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("+OK"):
        ok = True

    s.close()

    if verbose:
        print(f"QUIT debugging : {ans}")

    return ok, ans

### EOF
