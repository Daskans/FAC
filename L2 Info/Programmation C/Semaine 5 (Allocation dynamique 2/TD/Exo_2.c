#include <stdlib.h>
#include <stdio.h>

typedef struct point {
    float x;
    float y;
} point_t;

typedef unsigned int uint;

point_t *alloc_tab(uint lenght) {
    point_t *tab = malloc(lenght*sizeof(point_t));
    if (tab == NULL) {
        fprintf(stderr,"Not enough memory");
        exit(EXIT_FAILURE);
    }
    return tab;
}

int free_tab(point_t *tab) {
    if (tab == NULL) {
        fprintf(stderr,"Argument not valide");
        return EXIT_FAILURE;
    }
    free(tab);
    return EXIT_SUCCESS;
}

int fill_index(point_t *tab, uint lenght, uint index, point_t *point) {
    if (tab == NULL || index >= lenght) {
        fprintf(stderr,"Argument not valide");
        return EXIT_FAILURE;
    }
    (tab+index)->x = point->x;
    (tab+index)->y = point->y;
    return EXIT_SUCCESS;
}

int display_tab(point_t *tab, uint lenght) {
    if (tab == NULL) {
        fprintf(stderr,"Argument not valide");
        return EXIT_FAILURE;
    }
    for (uint i=0; i<lenght; i++) {
        printf("Point %d : (%f,%f)\n", i+1, (tab+i)->x, (tab+i)->y);
    }
}

static void usage(char * command) {
    fprintf(stderr,"%s <integer array size> \n", command);
    exit(EXIT_FAILURE);
}

void main(int argc, char *argv[]) {
    if (argc<2 || (argc-1)%2!=0) {
        usage(argv[0]);
    }
    uint lenght = (argc-1)/2;
    point_t *tab = alloc_tab(lenght);
    for (uint i=1, j=0; i<argc-1; i=i+2, j++) {
        point_t point;
        point.x = atof(argv[i]);
        point.y = atof(argv[i+1]);
        fill_index(tab, lenght, j, &point);
    }
    display_tab(tab, lenght);
    free_tab(tab);
}