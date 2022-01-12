#include <stdio.h>
#include <stdlib.h>
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
int dodajIza(plista);
int main()
{
    plista head = NULL;
    head = (plista)malloc(sizeof(lista));
    head->next = NULL;
    head->stablo = NULL;
    dodajIza(head);
    return 0;
}
int dodajIza(plista p)
{
    int n = 0, i = 0, br = 0;
    char c;
    int status = 0;
    char buf = {0};
    char name[MAX] = {0};
    int population = 0;
    plista temp = NULL;
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

        if (sscanf(buf, " %s %s", novi->name, ime) == 2)
		{
			novi->next = NULL;
			novi->stablo=NULL;
		}
    }

    fclose(pf);

    return 0;
}
