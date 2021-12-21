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
#include<time.h>

struct _tree;
typedef struct _tree *position;
typedef struct _tree{
    int el;
    position left;
    position right;
}tree;

struct _list;
typedef struct _list* pl;
typedef struct _list{
    int el;
    pl next;
}list;

position insert(position, int);
void print(position);
int replace(position);
void uDatoteku(position);
void krozStablo(position root, FILE* fp);
int main()
{
    //a)
    printf("a)\n");
    position root;
    root = NULL;
    int i = 0;
    int brojevi[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};

    while(i<10){
        root = insert(root, brojevi[i]);
        i++;
    }
    print(root);
    uDatoteku(root);

    //b)
    printf("\nb)");
    root->el = replace(root->left) + replace(root->right);
    printf("\n");
    print(root);
    uDatoteku(root);

    //c)
    printf("\nc)");
    srand(time(NULL));
    position root2;
    FILE* fp;
    struct _list head = {.el = 0, .next = NULL};

    root2 = (position)malloc(sizeof(tree));
    root2->el = rand() % 80 + 10;
    root2->left = NULL;
    root2->right = NULL;

    for(i = 1; i < 10; i++)
    {
        root2 = insert(root2, rand() % 80 + 10);
    }
    printf("\n");
    print(root2);

    uDatoteku(root2);

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
        print(root->left);
		printf("%d\n", root->el);
		print(root->right);
	}
}
int replace(position root)
{
    int temp = 0;
    if(root==NULL){
        return 0;
    }
    temp = root->el;
    root->el = replace(root->left)+replace(root->right);
    return temp + root->el;
}
void uDatoteku(position root)
{
    char filename[20];
    FILE* fp;
    printf("\nime datoteke: ");
    scanf(" %s", &filename);
    fp = fopen(filename, "w");
    krozStablo(root, fp);
    fprintf(fp, "\n");
    fclose(fp);
}
void krozStablo(position root, FILE* fp)
{
    if (root)
	{
        krozStablo(root->left, fp);
		fprintf(fp, "%d ", root->el);
		krozStablo(root->right, fp);
	}
}
