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

int lastHappyNumber(int tab[], int taille)
{
    int last=0;
    for (int i=0; i<taille&&tab[i]!=0; i++)
    {
        last=tab[i];
    }
    return last;
}

bool isHappyNumber(int tab[],int n, int taille)
{
    int stop=0;
    while (n<1001)
    {
        if (n<=lastHappyNumber(tab,n))
        {
            for (int i=0; i<taille&&tab[i]!=0; i++)
            {
                if (n==tab[i])
                {
                    return true;
                }
            }
            return false;
        }
        n=sumSquareDigit(n);
        stop++;
        if (stop==100) return false;
    }
}

int computeHappyNumbers(int tab[],int taille)
{
    int i=0;
    int n=1;
    printf("n = %d\n",n);
    while (i<taille)
    {
        if (isHappyNumber(tab,n,taille)==true)
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
    printf("[ ");
    for (int i=0; i<taille; i++)
    {
        printf("%d ",tab[i]);
    }
    printf("]");
}

void main()
{
    int taille=10;
    int tab[taille];
    printHappyNumbers(computeHappyNumbers(tab,taille),taille);
}