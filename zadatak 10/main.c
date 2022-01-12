#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 100

struct _drzava;
typedef struct _lista* plista;

struct _stablo;
typedef struct _stablo* pstablo;

typedef struct _lista
{
	char name[MAX];
	plista next;
	pstablo stablo;
}lista;

typedef struct _stablo
{
	char name[MAX];
	int population;
	pstablo left;
	pstablo right;
}stablo;

//drzava - lista
//grad - stablo
int citajIzDatotekeUListu(plista);
pstablo citajIzDatotekeUStablo(char*, pstablo);
pstablo uStablo(pstablo, pstablo);
int print(plista);
int printStablo(pstablo);
int main()
{
    lista head = {.name = {0}, .next = NULL, .stablo = NULL};
    citajIzDatotekeUListu(&head);
    //print(&head);
    return 0;
}
int citajIzDatotekeUListu(plista head)
{
    int n = 0, i = 0;
    int status = 0;
    char buf[MAX] = {0};
    FILE* fp = NULL;
    fp = fopen("drzave.txt", "r");
    if (fp == NULL) {
		perror("Greska! Neuspjelo otvaranje datoteke.");
        return 0;
	}
    plista novi = NULL;
    novi = (plista)malloc(sizeof(lista));

    if (!novi)
		{
			perror("Greska!");
			return -1;
		}

    rewind(fp);

    while(!feof(fp)){

        fgets(buf, MAX, fp);
        n=strlen(buf);
        for(i=0; i<n; i++){
            printf("%c", buf[i]);
        }

        status = sscanf(buf, " %s ", novi->name);
        printf("1: %s\n", novi->name);
        if (status == 1)
		{
			novi->next = NULL;
			novi->stablo = citajIzDatotekeUStablo(novi->name, novi->stablo);
			while (head->next != NULL && strcmp(head->next->name, novi->name) < 0)
            head = head->next;
            novi->next = head->next;
            head->next = novi;
		}
    }

    while(head){
        printf("\n2: %s", head->name);
        head = head->next;
    }

    fclose(fp);

    return 0;
}
pstablo citajIzDatotekeUStablo(char* name, pstablo p)
{
    //printf(" %s ", name);
    char buf[MAX] = {0};
    char grad[MAX] = {0};
    int br = 0, n = 0, i = 0, status = 0;
    pstablo novi = NULL;
    novi = (pstablo)malloc(sizeof(stablo));
	if (!novi)
	{
		perror("Greska pri alociranju!");
		return -1;
	}

    FILE* fp = NULL;
    fp = fopen(name, "r");
    if (fp == NULL) {
		perror("Greska! Neuspjelo otvaranje datoteke.");
        return 0;
	}

	while(!feof(fp)){
        fgets(buf, MAX, fp);
        n=strlen(buf);
        for(i=0; i<n; i++){
            printf("%c", buf[i]);
        }
        status = sscanf(buf, " %s %d", grad, &br);
        printf("3: %S %d ", grad, br);
        printf("\nstatus2: %d", status);
        printf("\n%s %d", grad, br);
        if (status == 2)
		{
			strcpy(novi->name, grad);
			printf("4: %s %d ", grad, br);
            novi->population = br;
            novi->left = NULL;
            novi->right = NULL;
			p = uStablo(novi, p);
        }
    }

    fclose(fp);

    return p;
}
pstablo uStablo(pstablo novi, pstablo p)
{
    if (p == NULL){
        return novi;
    }
    else if (p->population > novi->population){
        p->left = uStablo(novi, p->left);
    }
    else if (p->population < novi->population){
        p->right = uStablo(novi, p->right);
    }
    else{
        if (strcmp(p->name, novi->name) > 0){
            p->left = uStablo(novi, p->left);
        }

        else if (strcmp(p->name, novi->name) < 0){
            p->right = uStablo(novi, p->right);
        }
        else
        free(novi);
    }
    return p;
}
int print(plista l)
{
    while(l){
        printf("\n%s", l->name);
        printStablo(l->stablo);
        l = l->next;
    }
    return 0;
}
int printStablo(pstablo s)
{
    if(s == NULL)return 0;
    printStablo(s->left);
    printf("\n\t%s %d", s->name, s->population);
    printStablo(s->right);
    return 0;
}
