#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>

struct article {
    unsigned ref; // référence
    char name[16]; // nom de l'article
    unsigned nb_items; // nombre d'exemplaires en stock
    off_t skip; // réservé pour usage interne
};

int read_next (int fd, struct article *ptr) {
    for(;;)
    {
        int r = read(fd,ptr,sizeof(struct article));
        if(r <= 0){
            return -1;
        }
        if(ptr->ref > 0){
            return 0;
        }
        lseek(fd, ptr->skip, SEEK_CUR);
    }
    return -1;
}

void display (char *filename)
{
    struct article a = {0, "", 0, 0};
    int fd = open (filename, O_RDONLY);

    printf ("Inventaire :\n");

    while (read_next (fd, &a) != -1)
        printf (" Reférence %2d, %-16s quantité en stock : %d\n", a.ref, a.name, a.nb_items);

    close (fd);
}

void add_new_ref(char *filename, int ref, char *name) {
    struct article a = {0, "", 0, 0};
    int fd = open (filename, O_RDWR);
    int r;
    off_t new_ref_skip = 0;

    while ((r = read(fd, &a, sizeof(struct article))) != 0) {
        if (a.skip != 0) {
            lseek(fd, -32, SEEK_CUR);

            new_ref_skip = a.skip - 32;
            a.skip = 0;
            write(fd, &a, sizeof(struct article));

            break;
        }
    }

    struct article new_article = {ref,name, 0, new_ref_skip};
    write(fd, &new_article, sizeof(struct article));

    close(fd);

}


int main(void) {

    struct article t[] = {{1, "stylo", 100, 32},
                            {0, "", 0, 0},
                            {41, "gomme", 50, 64},
                            {0, "", 0, 0},
                            {0, "", 0, 0},
                            {25, "bloc note uni", 20, 0},
                            {26, "bloc note ligne", 20, 0}};

    int fd = open("inventaire", O_CREAT | O_TRUNC | O_WRONLY, 0642);
    write(fd, t, sizeof(t));
    close(fd);

    display("inventaire");
    add_new_ref("inventaire", 42, "univers");
    display("inventaire");

    return EXIT_SUCCESS;
}