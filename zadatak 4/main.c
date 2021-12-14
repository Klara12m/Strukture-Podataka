#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAX 50

struct _polinom;
typedef struct _polinom* position;
typedef struct _polinom{
    int koeficijent;
    int eksponent;
    position next;
}polinom;
int citajIzDatoteke(position, position);
int ispis(position);
int unosSortirano(position, int, int);
int zbroji(position, position, position);
int pomnozi(position, position, position);
int main()
{
    position jedan = NULL; //polinom
    jedan = (position)malloc(sizeof(polinom));
    jedan->next = NULL;

    position drugi = NULL; //polinom
    drugi = (position)malloc(sizeof(polinom));
    drugi->next = NULL;

    position suma = NULL;
    suma = (position)malloc(sizeof(polinom));
    suma->next = NULL;

    position umnozak = NULL;
    umnozak = (position)malloc(sizeof(polinom));
    umnozak->next = NULL;

    citajIzDatoteke(jedan, drugi);

    zbroji(suma, jedan->next, drugi->next);

    pomnozi(umnozak, jedan->next, drugi->next);

    return 0;
}
int citajIzDatoteke(position jedan, position drugi)
{
    position pom1 = NULL;
    pom1 = jedan;
    position pom2 = drugi;
    pom2 = drugi;

    int n = 0, i = 0;
    int status = 0;
    char buf[MAX] = {0};
    int koef = 0;
    int eksp = 0;

    FILE* fp = fopen("polinomi.txt", "r");
    if(fp == NULL){
        perror("Greska! Neuspjelo otvaranje datoteke.");
        return 0;
    }
    rewind(fp);
    printf("datoteka: \n"); //ispisi datoteku
    while(!feof(fp))
    {
        printf("%c", getc(fp));
    }
    rewind(fp);
    //1
    fgets(buf, MAX, fp);
    n = strlen(buf);
    /*for(i=0; i<n; i++){
    printf("%c", buf[i]);
    }*/
    char *bufp1=buf;

    while(strlen(bufp1)>1)
    {
    status=sscanf(bufp1, " %d %d%n", &koef, &eksp, &n);
    if (status != 2)
		{
			perror("Greska!\n");
			return -1;
		}

		bufp1 += n;

        unosSortirano(pom1, koef, eksp);
        printf("\n");
    }
    printf("\nprvi polinom: ");
    ispis(pom1);
    //2
    fgets(buf, MAX, fp);
    n = strlen(buf);
    /*for(i=0; i<n; i++){
    printf("%c", buf[i]);
    }*/
    char *bufp2=buf;

    while(strlen(bufp2)>1)
    {
    status=sscanf(bufp2, " %d %d%n", &koef, &eksp, &n);
    if (status != 2)
		{
			perror("Greska!\n");
			return -1;
		}

		bufp2 += n;

        unosSortirano(pom2, koef, eksp);
        printf("\n");
    }
    printf("\ndrugi polinom: ");
    ispis(pom2);

    fclose(fp);
    return 0;
}
int unosSortirano(position head, int k, int e)
{
    position p = head;
    position temp;

    while(p->next!=NULL && p->next->eksponent > e)
        p = p->next;

    if (p->next != NULL && p->next->eksponent == e) {
            p->next->koeficijent+=k;
    }
    else {
        position novi = NULL;
        novi = (position)malloc(sizeof(polinom));

        if (!novi)
            return -1;

        novi->next=p->next;
        p->next=novi;

        novi->koeficijent=k;
        novi->eksponent=e;
    }
     while(p->next != NULL) {
        if (!p->next->koeficijent) {
            temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        p=p->next;
    }


    return 0;
}
int ispis(position head)
{
    position pom = head->next;
    if(pom==NULL)
    {
        perror("Greska!");
        return -1;
    }
    while(pom!=NULL)
    {
        printf("%dx^%d", pom->koeficijent, pom->eksponent);
        if(pom->next != NULL)
            {printf("+");}
        pom = pom->next;
    }

    return 0;
}
int zbroji(position suma, position jedan, position drugi)
{
    while(jedan!=NULL){
    unosSortirano(suma, jedan->koeficijent, jedan->eksponent);
    jedan = jedan->next;
    }
    printf("\n");
    while(drugi!=NULL){
    unosSortirano(suma, drugi->koeficijent, drugi->eksponent);
    drugi = drugi->next;
    }
    printf("\nzbroj: ");
    ispis(suma);

    return 0;
}
int pomnozi(position rez, position jedan, position drugi)
{
	position temp;
	temp = drugi->next;

	while (jedan != NULL) {
		while (drugi != NULL) {
			unosSortirano(rez, jedan->koeficijent * drugi->koeficijent, jedan->eksponent + drugi->eksponent);
			drugi = drugi->next;
		}
		drugi = temp;
		jedan = jedan->next;
	}
	printf("\n\numnozak: ");
	ispis(rez);
	printf("\n");
	return 0;
}
