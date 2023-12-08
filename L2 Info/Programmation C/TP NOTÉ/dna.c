#include "dna.h"

// Définissez la fonction createdna, qui étant donné un entier taille strictement positive donnée en entrée, 
// alloue l'espace pour un dna_t de cette taille (y compris l'espace pour le code). Elle renvoie l'adresse de l'espace nouvellement revervé.
// En cas d'erreur, la mémoire potentiellement allouée dans cette fonction devra être libérée correctement et on renverra le pointeur NULL.
/*Define the createdna function, which given a strictly positive integer size as input, allocates space for a dna_t of that size (including space for the code). 
It returns the address of the newly reserved space.
In the event of an error, the memory potentially allocated in this function must be freed correctly and the NULL pointer is returned.*/
dna_t* createdna(int size)
{
    if (size < 1) {
        fprintf(stderr, "size is too small");
        return NULL;
    }
    dna_t *dna = malloc(sizeof(dna_t));
    nucleo* dna->code = malloc(size*sizeof(nucleo));
    if (!dna) {
        fprintf(stderr, "not enough memory");
        return NULL;
    }
    if (!dna->code) {
        fprintf(stderr, "not enough memory");
        freedna(dna);
        return NULL;
    }
    return dna;
}

// Définissez la fonction freedna, qui libère l'espace alloué dans la fonction précédente. 
// Il devra tout de même libérer l'espace même si tout l'espace n'a pas été alloué correctement.
/*Define the freedna function, which frees the space allocated in the previous function.
It will still have to free the space even if all the space has not been allocated correctly.*/

void freedna(dna_t* d)
{
    if (d->code) {
        free(d->code);
    }
    free(d);
}

// Définissez les fonctions makeLeaf et makeNode, permettant de créer respectivement une feuille et un noeud. Elles renvoient l'adresse de l'espace nouvellement revervé.
// En cas d'erreur, par exemple si un des pointeurs d'entrée est NULL, la mémoire potentiellement allouée dans ces fonctions devra être libérée correctement et on renverra le pointeur NULL.
/*Define the makeLeaf and makeNode functions, which create a leaf and a node respectively. They return the address of the newly-allocated space.
In the event of an error, for instance if one of the input pointer is NULL, the memory potentially allocated in these functions will have to be freed correctly and the NULL pointer will be returned.
*/
tree_t* makeNode(tree_t* t1, tree_t*t2)
{
    if (!t1 || !t2) {
        fprintf(stderr, "invalid arguments");
        return NULL;
    }

}

tree_t* makeLeaf(dna_t* d)
{
    if (!d) {
        fprintf(stderr, "invalid arguments");
        return NULL;
    }
}


// Définissez la fonction freetree, qui libère l'espace alloué pour un arbre. Il devra libérer récursivement l'espace dans les sous-structures - faisant éventuellement appel à freedna.
// Il devra tout de même libérer l'espace même si tout l'espace n'a pas été alloué correctement.
/*Define the freetree function, which frees the space allocated for a tree_t. It should recursively free the space in the substructures - possibly using freedna.
It will still have to free the space even if all the space has not been allocated correctly.*/
void freetree(tree_t* t)
{}


// On définit la distance entre deux dna_t comme le nombre de nucléotides qui diffèrent entre les deux. 
// On supposera que l'alignement se fait sur le premier nucléotide (on compare donc le nucléotide 0 avec le 0, le 1 avec le 1...) et qu'une absence de nucléotide diffère de n'importe quel nucléotide.
// Par exemple, les codes ATAGCAG et ATCGC est de trois: un pour A contre C, et deux pour les deux derniers nucléotides manquants.
// Définissez la fonction distdna qui calcule la distance entre deux dna_t donnés en paramètres. Elle devra renvoyer -1 en cas d'erreur.
/*The distance between two dna_t is defined as the number of nucleotides that differ between them.
It will be assumed that the alignment is done on the first nucleotide (we therefore compare nucleotide 0 with 0, 1 with 1...) and that the absence of a nucleotide differs from any nucleotide.
For example, the ATAGCAG and ATCGC codes are three: one for A versus C, and two for the last two missing nucleotides.
Define the distdna function, which calculates the distance between two dna_t given as parameters. It should return -1 in the event of an error.*/
int distdna (dna_t* d1, dna_t* d2)
{  
    if (!d1 || !d2) {
        fprintf(stderr, "invalid arguments");
        return EXIT_FAILURE;
    }
    int distance = 0;

    if (d1->size > d2->size) {
        distance += d1->size - d2->size;
    } else if (d1->size < d2->size) {
        distance += d2->size - d1->size;
    }

    for (uint i = 0; i < d1->size; i++) {
        if (d1->code[i] != d2->code[i]) {
            distance++;
        }
    }

    return distance;
}

// Définissez la fonction readdna qui lit les deux prochaines lignes d'un fichier formatées de la manière suivante:
// une ligne avec seulement un entier correspondant à la taille du code.
// une ligne avec une lettre (A,T,C ou G) par nucleo à rentrer, sans séparation.
// La fonction doit allouer l'espace nécessaire pour le dna_t correspondant, et le remplir. Elle doit retourner NULL en cas d'erreur.
/*Define the readdna function that reads the next two lines of a file formatted as follows:
one line with only an integer corresponding to the size of the code.
one line with one letter (A,T,C or G) per nucleo to be entered, without separation.
The function must allocate the necessary space for the corresponding dna_t, and fill it. It must return NULL on error.*/
dna_t* readdna (FILE* f)
{
    if (!f) {
        fprintf(stderr, "no file given");
        return NULL;
    }
    char c = fgetc(f);
    dna_t *dna = createdna(c);
    for (uint i = 0; i < c; i++) {
        char n = fgetc(f);
        switch (n) {
            case 'A':
                dna->code[i] = A;
                break;
            case 'T':
                dna->code[i] = T;
                break;
            case 'G':
                dna->code[i] = G;
                break;
            case 'C':
                dna->code[i] = C;
                break;
        }
    }  
    return dna;
}

// Ecrivez une fonction main de sorte que le programme appelé avec un nom de fichier en argument, ouvre le fichier en question, lise tous les codes contenus dans le fichier, 
// et construise un arbre (de la forme que vous voulez) avec ces codes. 
// Le programme devra en suite, à partir de cet arbre, calculer la distance de chacun de ces codes avec le code "TATGCTTG", et afficher ces distances (sur la sortie standard).
// Votre programme devra en outre terminer en écrivant un message d'erreur sur l'erreur standard s'il rencontre une erreur.
// Vous prendrez garde à bien libérer l'espace mémoire utilisé.
/*Write a main function so that the program called with a file name as argument, opens the file in question, reads all the codes contained in the file, and constructs a tree_t (in any form you like) with these codes.
From this tree_t, the program will then calculate the distance of each of these codes with the code "TATGCTTG", and display these distances (on the standard output).
Your program should also end by writing an error message on the standard error if it encounters an error.
We will take special care to free up the memory space used.*/
int main(int argc, char* argv[])
{
    FILE *f = fopen("foo.txt", "r");
    readdna(f);
    return EXIT_SUCCESS;
}