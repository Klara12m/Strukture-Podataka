/*7. Napisati program koji pomoću vezanih listi (stabala) predstavlja
strukturu direktorija. Omogućiti unos novih direktorija i
pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program
treba preko menija simulirati korištenje DOS naredbi:
1- "md-make direcotry", 2 - "cd dir-change directory",
3 - "cd..-parent directory", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10

struct _tree;
typedef struct _tree* PTree;
typedef struct _tree {
    char* name;
    PTree sibling;
    PTree child;
} Tree;

struct _stack;
typedef struct _stack* PStack;
typedef struct _stack{
    PTree dir;
    PStack parent;
    PStack next;
}Stack;

int menu(PTree, PStack);
int md(PTree);
int line(PStack, PTree, PTree);
int dir(PTree);
PTree FindByName(char*, PTree);
int push(PStack, PTree);
PTree GoToParent(PTree, PStack);
PTree cd(PTree, PStack);
int main()
{
    PTree root;
	root = (PTree)malloc(sizeof(Tree));
	root->child = NULL;
	root->sibling = NULL;
	PStack head;
	head = (PStack)malloc(sizeof(Stack));
	head->next = NULL;
	head->parent = NULL;
	root->name = (char*)malloc(MAX * sizeof(char));
	root->name = "C:";

    menu(root, head);

	return 0;
}
int menu(PTree root, PStack head)
{
    printf("md\tcd\tcd..\tdir\texit\n");
    int status = 0;
    PTree current = root;
    char x[MAX] = {0};


	while (!status) {
		printf("%s", current->name);
		line(head, root, current);
		scanf(" %s", x);

		if (!strcmp(x, "md")) {
			md(current);
		}

		else if (!strcmp(x, "cd")) {
			current=cd(current, head);
		}

		else if (!strcmp(x, "cd..")) {
			current = GoToParent(current, head);
		}

		else if (!strcmp(x, "dir")) {
			dir(current);
		}

		else if (!strcmp(x, "exit")) {
                status = 1;
			return status;
		}

		else
			printf("Try again\n");
	}

	return 0;
}
int line(PStack head, PTree root, PTree curr)
{
	PStack s;

	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}
	printf("\n");
	if (head->next == NULL) {
		printf(" %s", root->name);
		return 0;
	}

	while (s->parent!=NULL) {
		printf("%s", s->dir->name);
		s = s->parent;
	}

	printf("<%s> ", curr->name);

	return 0;
}
int md(PTree curr)
{
    PTree dir;
    dir = (PTree)malloc(sizeof(Tree));
    dir->name = (char*)malloc(MAX*sizeof(char));
    if(!dir){
            printf("error");
    }

    if (curr->child != NULL) {
		curr = curr->child;
		while (curr->sibling != NULL) {
			curr = curr->sibling;
		}
		curr->sibling=dir;
	}
	else
		curr->child=dir;

	scanf(" %s", dir->name);

	dir->sibling = NULL;
	dir->child = NULL;

	return 0;
}
int dir(PTree curr)
{
    if (curr->child == NULL) {
		printf("Empty directory!\n");
		return 0;
	}

	curr = curr->child;

	printf("DIRECTORIES: \n");
	printf("\t>%s\n", curr->name);

	while (curr->sibling != NULL) {
		printf("\t>%s\n", curr->sibling->name);
		curr = curr->sibling;
	}

	return 0;
}
PTree FindByName(char* name, PTree curr)
{
    if (curr->child == NULL) {
		printf("Directory is empty!");
		return 0;
	}

	curr = curr->child;

	while (strcmp(name, curr->name) != 0 && curr->sibling !=NULL) {
		curr = curr->sibling;
	}

	if (curr->sibling == NULL) {
		if (strcmp(name, curr->name) != 0)
			return 0;
		else
			return curr;
	}
	else
		return curr;
}
int push(PStack head, PTree dir)
{
    PStack s = (PStack)malloc(sizeof(Stack));

    s->next = head->next;
	s->parent = head;
	if (head->next != NULL) {
		head->next->parent = s;
	}
	head->next = s;
	s->dir = dir;

	 return 0;
}
PTree GoToParent(PTree curr, PStack head)
{
    PStack s = (PStack)malloc(sizeof(Stack));
	PTree p;

	if (head->next == NULL)
		return NULL;

	s = head->next;
	p = s->dir;
	head->next = head->next->next;
	if(head->next!=NULL)
		head->next->parent = head;
	free(s);

	PTree file;

	file = p;

	if (file == NULL) {
		file = curr;
	}

	return file;
}
PTree cd(PTree curr, PStack head)
{
    PTree file;
	char* dir;
	dir = (char*)malloc(MAX * sizeof(char));

	scanf(" %s", dir);

	if (curr->child == NULL) {
		printf("There is no directory to open!\n");
		return curr;
	}

	file=FindByName(dir, curr);
	if (file == 0) {
		printf("Directory not found\n");
		return curr;
	}

	push(head, curr);

	return file;
}
