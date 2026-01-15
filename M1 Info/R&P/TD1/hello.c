#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyse_str (char** str_array, int len) {
    for (int i = 0; i < len; i++) {
        char* str = str_array[i];
        int string_len = strlen(str);
        printf("%s, %d, %c\n", str, string_len, str[string_len]);
    }
}

int main (int argc, char *argv[]) {
    char* endptr;
    strtol(argv[argc - 1], &endptr, 0);
    if (argc < 3 || *endptr != '\0') {
        fprintf(stderr, "ERROR : at least 3 arguments are needed, and the last one needs to be a number\n");
        exit(EXIT_FAILURE);
    }
    int len = atoi(argv[argc - 1]);
    if (atoi(argv[argc-1]) == -1) len = argc - 2;
    analyse_str(argv + 1, len);
    
    return EXIT_SUCCESS;
}