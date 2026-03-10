#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define PORT 2022

void end_if_error(bool error_condition, char *msg) {
    if (error_condition) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char *argv[]) {
    int s, ret;
    socklen_t len;
    struct sockaddr_in server_addr, client_addr;
    char msg[100];
    char *answer = "Hello, client!";

    //create a socket (which will be a file descriptor)
    s = socket(AF_INET, SOCK_DGRAM, 0);
    end_if_error(s == -1, "socket");

    //prepare a struct with server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    //bind socket with the server address
    ret = bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
    end_if_error(ret == -1, "bind");

    //receive a message from the client
    //recvfrom will fill the client_addr structure
    printf("The server will wait for a client message\n");
    len = sizeof(client_addr);
    memset(&client_addr, 0, len);
    ret = recvfrom(s, msg, 100, 0, (struct sockaddr *)&client_addr, &len); //we did not know the client address, we'll find it out when we receive its message
    end_if_error(ret <= 0, "recvfrom");

    printf("The client received the client message '%s'. It'll now send an answer.\n", msg);
    //send an answer to the client
    ret = sendto(s, answer, strlen(answer)+1, 0, (struct sockaddr *)&client_addr, len);//we send strlen + 1 bytes to include the \0 at the end of the string
    end_if_error(ret == -1, "sendto");

    printf("The server sent its answer to the client.\n");
    //close and end
    close(s);

    return EXIT_SUCCESS;
}

