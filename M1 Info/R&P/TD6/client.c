#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2301
#define SERVER "127.0.0.1"

void end_if_error(bool error_condition, char *msg) {
    if (error_condition) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char *argv[]) {
    int s, ret;
    struct sockaddr_in server_addr;
    char buf[100];
    // char *msg = "Hello, server!";

    //create a tcp socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    end_if_error(s == -1, "socket");

    //fill a structure with the server's address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER);

    //connect to the server
    ret = connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
    end_if_error(ret == -1, "connect");

    while (1) {
        
        ret = read(s, buf, sizeof(buf));
        end_if_error(ret <= 0, "read");
        printf("%s\n", buf);
        
    }
    printf("Client received message %s\n", buf);
    //close and end
    close(s);

    return EXIT_SUCCESS;
}


