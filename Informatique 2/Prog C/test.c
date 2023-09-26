#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sumSquareDigit(int n) {
    /* Retourne la somme des carrés des chiffres de n. */
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool isHappyNumber(int n) {
    /* Retourne true si n est un nombre heureux, false sinon. */
    int visited[1000] = {0}; // tableau pour stocker les nombres visités
    while (n != 1 && !visited[n]) {
        visited[n] = 1;
        n = sumSquareDigit(n);
    }
    return n == 1;
}

void computeHappyNumbers(int arr[], int size) {
    /* Stocke les size premiers entiers heureux dans le tableau arr. */
    int n = 1, count = 0;
    while (count < size) {
        if (isHappyNumber(n)) {
            arr[count++] = n;
        }
        n++;
    }
}

void printHappyNumbers(int arr[], int size) {
    /* Affiche les nombres heureux stockés dans le tableau arr. */
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int main() {
    /* Calcule, stocke et affiche les 10 premiers nombres heureux. */
    int arr[10];
    computeHappyNumbers(arr, 10);
    printHappyNumbers(arr, 10);
    return 0;
}