import sys
import socket

"""/!\ penser à écrir dans le terminal 'chmod +x httpget.py' /!\ """
try:
    print('###############################')
    s = socket.socket(socket.AF_INET , socket.SOCK_STREAM )
    host = sys.argv[1]
    port = 80
    s.connect((host,port))
    request = "GET / HTTP/1.1\r\n"  \
        "Host: " + host + "\r\n"    \
        "Connection: close\r\n\r\n"
    print(request)

    print('-------------------------------')
    request = request.encode("utf-8")
    print(request)
    print('-------------------------------')
    s.sendall(request)
    a = 0
    while True:
        data = s.recv(1024)
        if not data:
            print("no data")
            break
        elif b"HTTP" in data:
            status_code = int(data.split(b' ')[1])
            if status_code == 200:
                print("Le serveur a bien compris la requête. La requête a été traitée avec succès.")
            else:
                print(f"Le serveur a rencontré une erreur. Code de statut HTTP : {status_code}")
        else:
            print("Réponse du serveur invalide : ", data)
        print('-------------------------------')
        print(data)
        print('-------------------------------')
        print(data.decode("utf-8"), end="")
    print('###############################')

except socket.error as e:
    print("socket error !", e)
    sys.exit(1)

except ConnectionError as e:
    print("connection error", e)
    sys.exit(1)