#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define PORT 2022
#define SERVER "127.0.0.1"  //localhost

void end_if_error(bool error_condition, char *msg) {
    if (error_condition) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char *argv[]) {
    int s,ret;
    struct sockaddr_in server_addr;
    char *msg = "Hello, server!";
    char answer[100];

    //create a socket (which will be a file descriptor)
    s = socket(AF_INET, SOCK_DGRAM, 0);
    end_if_error(s == -1, "socket");

    //prepare a struct with server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER);

    //send a message to the server
    printf("The client will send a message to the server.\n");
    ret = sendto(s, msg, strlen(msg)+1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)); //we send strlen + 1 bytes to include the \0 at the end of the string
    end_if_error(ret == -1, "sendto");

    printf("The client sent its message to the server, now it'll wait for an answer.\n");
    //receive an answer
    ret = recvfrom(s, answer, 100, 0, NULL, NULL); //we don't need to recover the address of who is sending us this message (we know it is the server)
    end_if_error(ret <= 0, "recvfrom");

    printf("The client received answer %s\n", answer);
    //close and end
    close(s);

    return EXIT_SUCCESS;
}
