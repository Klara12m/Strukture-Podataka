#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct _stablo;
typedef struct _stablo* pstablo;
typedef struct _stablo{
  char* name;
  int population;
  pstablo left;
  pstablo right;
}stablo;

struct _lista;
typedef struct _lista* plista;
typedef struct _lista{
  char* name;
  pstablo root;
  plista next;
}lista;

int printS(pstablo);
int printL(plista);
int insert(pstablo, pstablo);
pstablo citajIzDatotekeUStablo(char *);
int printG(pstablo, int);
plista pronadiDrzavu(plista , char*);
int pronadiGrad(plista);
int citajIzDatotekeUListu(plista);
int main(){
    plista head = NULL;
    head = (plista)malloc(sizeof(lista));
    head -> name = NULL;
    head -> root = NULL;
    head -> next = NULL;

    citajIzDatotekeUListu(head);
    printL(head);
    pronadiGrad(head);

    return 0;
}
int printS(pstablo s)
{
    if(s == NULL){
        return 0;
    }
    printS(s -> right);
    printf("\n\t%s   %d", s -> name, s -> population);
    printS(s -> left);

    return 0;
}
int printL(plista head)
{
    plista temp = head -> next;

    while(temp){
        printf("%s", temp -> name);
        printS(temp -> root);
        printf("\n");
        temp = temp -> next;
    }
    return 0;
}
int insert(pstablo curr, pstablo novi)
{
    int status = 0;
    int relation = 0;

    if(curr == NULL){
        return 1;
    }
    relation = novi -> population - curr -> population;
    if(relation != 0){
        relation = strcmp(novi -> name, curr -> name);
    }
    if(relation == 0){
        free(novi);
        return 0;
    }
    if(relation < 0){
        if (curr -> left == NULL){
          curr -> left = novi;
          return 0;
        }
        status = insert(curr -> left, novi);
        return 0;
    }
    else{
        if(curr -> right == NULL){
          curr -> right = novi;
          return 0;
        }

        status = insert(curr -> right, novi);
        return 0;
    }

    return 0;
}
pstablo citajIzDatotekeUStablo(char* filename)
{
    pstablo temp = NULL;
    pstablo root = NULL;
    pstablo novi = NULL;
    char buffer[MAX];
    char name[MAX];
    int population = 0;
    int status = 0;

    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if(!fp){
        return NULL;
    }

    while(!feof(fp)){
        fgets(buffer, MAX, fp);
        status = sscanf(buffer, "%s %d", name, & population);

        if(status == 2){
            novi = (pstablo) malloc(sizeof(stablo));
            if (novi == NULL){
                return NULL;
            }
            novi -> name = (char * ) malloc(strlen(name));
            strcpy(novi -> name, name);
            novi -> population = population;
            novi -> left = NULL;
            novi -> right = NULL;

            temp = novi;

            if(temp){
                if(!root){
                    root = temp;
                }
                else{
                    insert(root, temp);
                }
            }
        }
    }

    fclose(fp);

    return root;
}
int printG(pstablo g, int br)
{
    if(g == NULL) {
        return 0;
    }

    printG(g -> left, br);
    if(g -> population > br){
        printf("\n\t%s   %d", g -> name, g -> population);
    }
    printG(g -> right, br);

    return 0;
}
plista pronadiDrzavu(plista head, char* name)
{
    plista temp = head;

    while(temp){
        if(temp -> name && !strcmp(temp -> name, name)){
            return temp;
        }
        temp = temp -> next;
    }
    return NULL;
}
int pronadiGrad(plista head)
{
    char* name = NULL;
    plista city = NULL;
    int br = 0;

    printf("Odaberi dr�avu: ");
    name = (char*) malloc(MAX);

    fgets(name, MAX, stdin);
    name[strcspn(name, "\n")] = 0;

    city = pronadiDrzavu(head, name);
    if (city == NULL){
    return 1;
    }

    printf("Unesite granicu: ");
    scanf("%d", &br);
    printf("\nVas rezultat:\n");
    printG(city -> root, br);

    return 0;
}
int citajIzDatotekeUListu(plista head)
{
    int status = 0;
    char buffer[MAX] = {0};
    plista templista = NULL;
    plista temp = head;
    plista novi = NULL;
    char name[MAX];
    char drzavatxt[MAX];

    FILE * fp = NULL;
    fp = fopen("drzave.txt", "r");
    if (fp == NULL){
        perror("Greska! Neuspjelo otvaranje datoteke.");
        return -1;
    }

    while (!feof(fp)){
        fgets(buffer, MAX, fp);
        status = sscanf(buffer,"%s %s", name, drzavatxt);
        if (status == 2){
            novi = (plista) malloc(sizeof(lista));
            if (novi == NULL) {
                return 0;
            }
            novi -> name = (char * ) malloc(strlen(name));

            strcpy(novi -> name, name);
            novi -> root = NULL;
            novi -> next = NULL;

            templista = novi;

            if (templista) {
                pstablo cities = citajIzDatotekeUStablo(drzavatxt);
                templista -> root = cities;

                while (temp -> next){
                    if (strcmp(templista -> name, temp -> next -> name) < 0){
                        templista -> next = temp -> next;
                        temp -> next = templista;
                        return 0;
                    }
                    temp = temp -> next;
                }
                templista -> next = temp -> next;
                temp -> next = templista;
            }
        }
    }

  fclose(fp);

  return 0;
}
