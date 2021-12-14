/*8. Napisati program koji omogućava rad s binarnim stablom pretraživanja.
Treba omogućiti unošenje novog elementa u stablo, ispis elemenata
(inorder, preorder, postorder i level order), brisanje i
pronalaženje nekog elementa.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _tree;
typedef struct _tree *position;
typedef struct _tree{
    int el;
    position left;
    position right;
}tree;
int main()
{

    return 0;
}
