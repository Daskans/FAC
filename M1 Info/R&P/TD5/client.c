#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define PORT 2022
#define SERVER "127.0.0.1"  //localhost
#define MAX_PINGS 10

#define TIMESPEC_DIFF(t1, t2)  ((t2.tv_nsec - t1.tv_nsec) + ((t2.tv_sec - t1.tv_sec)*1000000000L))


void end_if_error(bool error_condition, char *msg) {
    if (error_condition) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char *argv[]) {
    int s,ret;
    struct sockaddr_in server_addr;
    char *msg = "PING";
    char answer[100];
    struct timespec start, end;

    //create a socket (which will be a file descriptor)
    s = socket(AF_INET, SOCK_DGRAM, 0);
    end_if_error(s == -1, "socket");

    //timeout
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0.001;

    ret = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    end_if_error(ret < 0, "setsockopt");
    
    //prepare a struct with server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER);
    
    for (int i = 0; i < MAX_PINGS; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        ret = sendto(s, msg, strlen(msg)+1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        end_if_error(ret == -1, "sendto");

        //receive an answer
        ret = recvfrom(s, answer, sizeof(answer), 0, NULL, NULL); //we don't need to recover the address of who is sending us this message (we know it is the server)
        if (ret < 0) {
            // If errno is EAGAIN or EWOULDBLOCK, it means the timeout hit
            printf("Ping %d: Request timed out (Packet lost)\n", i);
        } else {

            clock_gettime(CLOCK_MONOTONIC, &end);
            long nanosecs = TIMESPEC_DIFF(start, end);
            double millisecs = nanosecs / 1000000.0;
            printf("Ping %d: Reply from %s | RTT = %.3f ms\n", i, SERVER, millisecs);
        }
    }

    printf("The client received answer %s\n", answer);
    //close and end
    close(s);

    return EXIT_SUCCESS;
}
