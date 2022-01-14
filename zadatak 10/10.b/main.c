#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 248

struct _lista;
typedef struct _lista* plista;

struct _stablo;
typedef struct _stablo* pstablo;

typedef struct _lista
{
	char name[MAX];
	int population;
	plista next;
	pstablo stablo;
}lista;

typedef struct _stablo
{
	char name[MAX];
	pstablo left;
	pstablo right;
}stablo;

pstablo citajIzDatotekeUStablo(pstablo);
pstablo insert(pstablo, char*, char*);
int main()
{
    pstablo root = NULL;
    root = citajIzDatotekeUStablo(root);
    return 0;
}
pstablo citajIzDatotekeUStablo(pstablo root)
{
    pstablo temp = NULL;
    char buffer[MAX] = {0};
    char name[MAX] = {0};
    char drzavatxt[MAX] = {0};
    int status = 0;
    FILE* fp = NULL;
    fp = fopen("drzave.txt", "r");
    if(!fp){
        perror("Greska pri otvaranju datoteke!");
        return NULL;
    }
    while (!feof(fp))
	{
		fgets(buffer, MAX, fp);
		status = sscanf(buffer, "%s %s", name, drzavatxt);
		if(status == 2)
			root = insert(root, name, drzavatxt);
	}

	fclose(fp);

	return root;
}
pstablo insert(pstablo root, char* drzavaname, char* filename)
{
    pstablo temp = NULL;
	pstablo node = root;
	if (node == NULL){
		pstablo novi= NULL;
        novi = (pstablo) malloc(sizeof(stablo));
        if (novi == NULL) {
            return NULL;
        }
        novi -> name = (char*)malloc(strlen(drzavaname));
        strcpy(novi -> name, drzavaname);
        novi -> left = NULL;
        novi -> right = NULL;

        temp = novi;
		return temp;
	}
	else if (strcmp(node->name, drzavaname) > 0) {
		node->left = insert(node->left, drzavaname, filename);
	}
	else (strcmp(node->name, drzavaname) < 0) {
		node->right = insert(node->right, drzavaname, filename);
	}

	return root;
}
