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

position menu(position);
position unos(position, int);
void ispis(position);
void inorder(position);
void preorder(position);
void postorder(position);
void levelorder(position);
position izbrisi(position, int);
position pronadi(position, int);
int main()
{
    position root;
    root = NULL;

    do {
		root = menu(root);
	} while (root);

    return 0;
}
position menu(position root)
{
    position p;
    int x = 0;
    int n = 0;
    printf("opcije:\n\t[1]unesi novi element\n\t[2]ispisi elemente stabla\n\t[3]izbrisi elsemnte stabla\n\t[4]pronadi element stabla");
    printf("\nodabir: ");
    scanf(" %d", &x);
    switch (x) {
		case 1:
		    printf("Unesite broj: ");
            scanf(" %d", &n);
			root = unos(root, n);
			return root;

		case 2:
			ispis(root);
			return root;

		case 3:
			printf("koji broj zelite izbrisati: ");
			scanf(" %d", &n);
			root = izbrisi(root, n);
			return root;

		case 4:
		    printf("Unesite broj: ");
            scanf(" %d", &n);
			root = pronadi(root, n);
			if (root)
				printf("Element postoji :)\n");
            else
                printf("Element ne postoji :(");
			return root;

		default:
			printf("Greska!");
	}
}
position unos(position root, int n)
{
    if (root == NULL) {
		root = (position)malloc(sizeof(position));
		root->el = n;
		root->left = NULL;
		root->right = NULL;
		return root;
	}

	else if (n > root->el) {
		root->right = unos(root->right, n);
	}

	else if (n < root->el) {
		root->left = unos(root->left, n);
	}

	return root;
}
void ispis(position root)
{
    int x = 0;
    printf("\t[2]odaberite ispis:\n\t\t[1]inorder\n\t\t[2]preorder\n\t\t[3]postorder\n\t\t[4]level order");
    scanf(" %d", &x);
    switch(x)
    {
    case 1:
        inorder(root);
        break;
    case 2:
        preorder(root);
        break;
    case 3:
        postorder(root);
        break;
    /*case 4:
        levelorder(root);
        break;*/
    default:
        printf("Greska!");
    }
}
void inorder(position p)
{
    if (p)
	{
        inorder(p->left);
		printf("%d\n", p->el);
		inorder(p->right);
	}
}
void preorder(position p)
{
    if (p)
	{
		printf("%d\n", p->el);
		preorder(p->left);
		preorder(p->right);
	}
}
void postorder(position p)
{
    if (p)
	{
		postorder(p->left);
		postorder(p->right);
		printf("%d\n", p->el);
	}
}
/*void levelorder(position p)
{

}*/
position izbrisi(position p, int el)
{
    position temp;
    position pom;

	if (!p)
		return p;
	else if (el < p->el)
		p->left = izbrisi(p->left, el);
	else if (el > p->el)
		p->right = izbrisi(p->right, el);
	else
	{
		if (p->left && p->right)
		{
			pom = p->right;
			while(pom->left)
                pom=pom->left;
            temp = pom;
			p->el = temp->el;
			p->right = izbrisi(p->right, temp->el);
		}
		else
		{
			temp = p;
			if (!p->left)
				p = p->right;
			else if (!p->right)
				p = p->left;
			free(temp);
		}
	}
	return p;
}
position pronadi(position p, int n)
{
    position temp;
	temp = p;

	if (temp == NULL)
		return NULL;

	else if (temp->el == n) {
		return temp;
	}

	else if (n > temp->el) {
		return pronadi(temp->right, n);
	}

	else if (n < temp->el) {
		return pronadi(temp->left, n);
	}

	return temp;
}
