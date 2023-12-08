#!/usr/bin/python3

# Module: sendlib.py
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
TIMEOUT = 10
MAXLINE= 1024

###############################################
###               SMTP/CLIENT               ###
###############################################

def smtp_connect(host, port, secure, verbose):
    """
    Connects the socket to the specified SMTP server.

    Parameters:
        - host (str): The address of the SMTP server.
        - port (int): The port of the SMTP server.
        - secure (bool): Indicates whether the connection should be secure.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - s (socket): The socket connected to the SMTP server.
    """

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
###############################################

def smtp_hello(s, verbose):
    """
    Sends the EHLO command to the SMTP server.

    Parameters:
        - s (socket): The socket connected to the SMTP server.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""

    s.sendall(f"EHLO {DOMAIN}\r\n".encode("utf-8"))
    ans = s.recv(MAXLINE).decode("utf-8")
    if ans.startswith("2") or ans.startswith("3"):
        ok = True
    
    ans = ans.strip()
    
    if verbose:
        print(f"EHLO debugging : {ans}")
        
    return ok, ans

###############################################

def smtp_auth(s, login, password, verbose):
    """
    Authenticates the client with the SMTP server using AUTH PLAIN method.

    Parameters:
        - s (socket): The socket connected to the SMTP server.
        - login (str): The username for authentication.
        - password (str): The password for authentication.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if authentication is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    # ...
    return ok, ans

###############################################

def smtp_noop(s, verbose):
    """
    Sends the NOOP command to the SMTP server.

    Parameters:
        - s (socket): The socket connected to the SMTP server.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    # ...
    return ok, ans

###############################################

def smtp_send(s, msg, verbose):
    """
    Sends the specified message to the SMTP server.

    Parameters:
        - s (socket): The socket connected to the SMTP server.
        - msg (email.message.EmailMessage): The message to send.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the send is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    # ...
    return ok, ans

###############################################


def smtp_quit(s, verbose):
    """
    Sends the QUIT command to the SMTP server to terminate the connection.

    Parameters:
        - s (socket): The socket connected to the SMTP server.
        - verbose (bool): Indicates whether debug messages should be displayed.

    Returns:
        - ok (bool): Server status (True if the command is successful, False otherwise).
        - ans (str): Server response.
    """
    ok = False
    ans = ""
    # ...
    return ok, ans

### EOF
