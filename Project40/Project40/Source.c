#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

struct _polinom;
typedef struct _polinom* position;

typedef struct _polinom {
	int k;
	int e;
	position next;
}polinom;

int menu(position);
int CitajIzDatoteke(position, position);
int main() {
	position jedan = (position)malloc(sizeof(polinom));
	position drugi = (position)malloc(sizeof(polinom));


	return 0;
}
int CitajIzDatoteke(position prvi, position drugi) {
	char buff[MAX] = { 0 };
	int n = 0;
	int status = 0;
	FILE* fp = fopen("polinomi.txt", "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return 1;
	}
	
	fgets(buff, MAX, fp);

	char* pBuff1 = buff;

	while (strlen(pBuff1) > 0) {

	}

	return 0;
}