/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su
spremljeni u čvorove binarnog stabla.
a)  Napisati funkciju insert  koja dodaje element u stablo tako da se
pozivima te funkcije za sve element zadanog niza brojeva stvori stablo
kao na slici Slika 1. Funkcije vraća pokazivač na korijen stabla.
b)  Napisati funkciju replace  koja će svaki element stabla zamijeniti
sumom elemenata u njegovom lijevom i desnom podstablu (tj. sumom svih
potomaka prije zamjene vrijednosti u tim potomcima). Npr. stablo sa
slike Slika 1 transformirat će se u stablo na slici Slika 2.
c)  Prepraviti program na način da umjesto predefiniranog cjelobrojnog
polja korištenjem funkcije rand()  generira slučajne brojeve u rasponu
<10, 90>. Također, potrebno je upisati u datoteku sve brojeve u
inorder prolasku nakon korištenja funkcije iz a), zatim b) dijela zadatka.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MAX 1024

struct _tree;
typedef struct _tree *position;
typedef struct _tree{
    int el;
    position left;
    position right;
}tree;

position insert(position, int);
void print(position);
int main()
{
    position root;
    root = NULL;
    int i = 0;
    int brojevi[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};

    while(i<10){
        root = insert(root, brojevi[i]);
        i++;
    }
    printf("stablo:\n");
    print(root);
    return 0;
}
position insert(position root, int n)
{
    if (root == NULL) {
		root = (position)malloc(sizeof(position));
		root->el = n;
		root->left = NULL;
		root->right = NULL;
		return root;
	}

	else if (n >= root->el) {
		root->left = insert(root->left, n);
	}

	else if (n < root->el) {
		root->right = insert(root->right, n);
	}

	return root;
}
void print(position root)
{
    if (root)
	{
		printf("%d\n", root->el);
		print(root->left);
		print(root->right);
	}
}
