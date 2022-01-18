#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXL 100
#define MAX 100

struct _stablo;
typedef struct _stablo* pstablo;
typedef struct _stablo {
	char* name;
	int population;
	pstablo left;
	pstablo right;
}tree;

struct _lista;
typedef struct _lista* plista;
typedef struct _lista {
	char* name;
	char* drzavetxt;
	plista next;
	pstablo root;
}list;

char* napraviString(int);
plista stvoriHash(int);
int sortHashTab(plista, plista);
plista findPrev(plista, plista);
int addLast(plista, plista);
int inputDrzave(plista, char*, char*);
int stvoriHashKey(plista, int);
int inputGrad(pstablo, char*, int);
int insertStablo(pstablo, pstablo);
int citajIzDatoteke(plista);
int readFileGrad(plista);
int printH(plista, int);
int printL(plista);
int printS(pstablo);

int main()
{
	plista head = stvoriHash(MAXL);
	citajIzDatoteke(head);
	printH(head, MAXL);

	printf("\n");

	return 0;
}


char* napraviString(int length) {
	char* string = (char*)malloc(length * sizeof(char));
	return string;
}

plista stvoriHash(int red) {
	int i = 0;

	plista head = (plista)malloc(red * sizeof(list));
	if (head == NULL)
		return 0;

	for (i = 0; i < red; i++) {
		(head + i)->next = NULL;
		(head + i)->root = NULL;
	}

	return head;
}


int sortHashTab(plista head, plista drzava) {
	if (head->next == NULL) {
		head->next = drzava;
		return 0;
	}

	plista temp = NULL;
	plista prev = NULL;

	for (temp = head->next; temp != NULL; temp = temp->next) {
		if (strcmp(drzava->name, temp->name) < 0) {
			prev = findPrev(head, temp);
			drzava->next = prev->next;
			prev->next = drzava;
			return 0;
		}
	}
	addLast(head, drzava);
	return 0;
}

plista findPrev(plista head, plista node) {
	plista pom = NULL;

	for (pom = head; pom->next != NULL; pom = pom->next) {
		if (pom->next == node)
			return pom;
	}

	return pom;
}

int addLast(plista head, plista node) {
	plista temp = NULL;
	for (temp = head; temp->next != NULL; temp = temp->next);
	temp->next = node;

	return 0;
}

int inputDrzave(plista _drzava, char* name, char* filename) {
	_drzava->name = name;

	return 0;
}

int stvoriHashKey(plista drzava, int red) {
	int sum = 0;
	int i = 0;
	int pom = 0;

	char letter;

	for (i = 0; i < 5; i++) {
		letter = *(drzava->name + i);
		pom = (int)letter;
		sum += pom;
	}

	return sum % red;
}

int inputGrad(pstablo grad, char* ime, int population) {
	grad->name = ime;
	grad->population = population;

	return 0;
}

int insertStablo(pstablo branch, pstablo grad) {
	if (grad->population > branch->population) {
		if (branch->left == NULL) {
			branch->left = grad;
			return 0;
		}
		else
			insertStablo(branch->left, grad);
	}
	else {
		if (branch->right == NULL) {
			branch->right = grad;
			return 0;
		}
		else
			insertStablo(branch->right, grad);
    }

	return 0;
}

int citajIzDatoteke(plista head) {

	FILE* fp;

	fp = fopen("drzave.txt", "r");

	plista newDrzava = NULL;
	int key = 0;
	char* red;
	char* filename;
	char* drzava_ime;

	while (!feof(fp)) {
        plista temp = (plista)malloc(sizeof(list));
        if (temp == NULL)
            return NULL;

        temp->next = NULL;
        temp->root = NULL;
        newDrzava = temp;

		drzava_ime = napraviString(MAX);
		filename = napraviString(MAX);
		red = napraviString(MAX);

		fgets(red, MAX, fp);
		sscanf(red, "%s %s", drzava_ime, filename);

		inputDrzave(newDrzava, drzava_ime, filename);

		key = stvoriHashKey(newDrzava, MAXL);

        sortHashTab(head + key, newDrzava);

		readFileGrad(newDrzava);
	}

	fclose(fp);

	return 0;
}

int readFileGrad(plista drzava) {
	FILE* fp;

	fp = fopen(drzava->drzavetxt, "r");

	pstablo newGrad = NULL;
	char* grad = NULL;
	int population = 0;
	char* red = NULL;

	while (!feof(fp)) {
        pstablo temp = (pstablo)malloc(sizeof(tree));
        if (temp == NULL)
            return NULL;

        temp->population = 0;
        temp->left = NULL;
        temp->right = NULL;
        newGrad = temp;

		grad = napraviString(MAX);
		red = napraviString(MAX);

		fgets(red, MAX, fp);
		sscanf(red, "%s %d", grad, &population);
		inputGrad(newGrad, grad, population);

		if (drzava->name == NULL)
			drzava->name = newGrad;
		else {
			insertStablo(drzava->name, newGrad);
		}
	}

	fclose(fp);
	return 0;
}

int printH(plista head, int red) {
	int i = 0;
	for (i = 0; i < red; i++) {
		printf("\n%d row:", i + 1);
		printL(head + i);
	}
	return 0;
}

int printL(plista head) {
	plista temp = NULL;
	for (temp = head->next; temp != NULL; temp = temp->next) {
		printf("\n%s\n", temp->name);
		printS(temp->name);
	}
	return 0;
}

int printS(pstablo branch) {
	if (branch->left != NULL)
		printS(branch->left);
	printf("\n%s\t%d", branch->name, branch->population);
	if (branch->right != NULL)
		printS(branch->right);

	return 0;
}
