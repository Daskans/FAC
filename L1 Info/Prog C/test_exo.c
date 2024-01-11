#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 100

int sumSquareDigit(int n)
{
    int somme=0;
    int temp=0;
    while (n>=1)
    {
        temp=n%10;
        n=n/10;
        somme+=temp*temp;
        
    }
    printf("somme = %d\n",somme);
    return somme;
}

bool isHappyNumber(int n)
{
    if (n==1)
    {
        return true;
    }
    else if (n==4)
    {
        return false;
    }
    
    else
    {
        printf("n isHappy= %d\n",n);
        isHappyNumber(sumSquareDigit(n));
        
    }
}

int *computeHappyNumbers(int *tab[],int taille)
{
    int i=0;
    int n=1;
    printf("n = %d\n",n);
    while (i<taille)
    {
        if (isHappyNumber(n)==true)
        {
            printf("hello there\n");
            tab[i]=n;
            i++;
            printf("i = %d\n",i);
        }
        n++;
        printf("n = %d\n",n);
        printf("i = %d\n",i);
    }
    return tab;
}

void printHappyNumbers(int tab[],int taille)
{
    //int taille=sizeof(tab)/sizeof(tab[0]);
    //printf("taille = %d\n",taille);
    printf("[ ");
    for (int i=0; i<taille; i++)
    {
        printf("%d ",tab[i]);
    }
    printf("]\n");
}

int lastHappyNumber(int tab[], int taille)
{
    int last=0;
    for (int i=0; i<taille&&tab[i]!=0; i++)
    {
        last=tab[i];
    }
    return last;
}

void main()
{
    int taille=10;
    int tab[taille];
    printHappyNumbers(computeHappyNumbers(&tab,taille),taille);
    printf("last happy number ; %d\n",lastHappyNumber(tab,taille));
}