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
    int n = 0, i = 0;
    int status = 0;
    char *buf = 0;
    FILE* fp;
    fp = fopen("drzave.txt", "r");
    if (fp == NULL) {
		perror("Greska! Neuspjelo otvaranje datoteke.");
        return 0;
	}
    plista novi = NULL;
    novi = (plista)malloc(sizeof(lista));

    buf = (char*)malloc(MAX*sizeof(char));

    rewind(fp);

    fgets(buf, MAX, fp);
    n = strlen(buf);
    for(i=0; i<n; i++){
    printf("%c", buf[i]);
    }

    /*while(!feof(fp))
    {
        fscanf(fp, );
        while(p->next!=NULL && strcmp(p->prezime, pr))
        {
            p = p->next;
        }
        novi->next=p->next;
        p->next=novi;
    }*/



    return 0;
}
