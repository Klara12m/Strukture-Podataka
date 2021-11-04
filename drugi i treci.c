#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

struct _osoba;
typedef struct _osoba* position;

typedef struct _osoba
{
    char ime[MAX];
    char prezime[MAX];
    int godina_rodenja;

    position next;

}osoba;

int umetanjeNaPocetak(position);
int umetanjeNaKraj(position);
int dodajIza(position);
int dodajIspred(position, position);
int ispis(position);
int pronadi(position);
int brisi(position);
int sortiraj(position);
int uDatoteku(position);
int citajIzDatoteke(position);
int menu(position);
int main()
{
    position head = NULL;
    head = (position)malloc(sizeof(osoba));
    head->next = NULL;

    menu(head);

    return 0;
}
int menu(position head)
{
    int odabir;
    printf("\nOdaberite:\n1-UMETANJE NA POCETAK LISTE\n2-UMETANJE NA KRAJ LISTE\n"
           "3-ISPIS\n4-PRONADI ELEMENT U LISTI\n5-BRISI ELEMENT IZ LISTE"
           "\n6-DODAJ NOVI ELEMENT IZA ODREDENOG ELEMENTA\n7-DODAJ NOVI ELEMENT ISPRED ODREDENOG ELEMENTA"
           "\n8-SORTIRAJ LISTU\n9-UPISI LISTU U DATOTEKU\n10-CITAJ LISTU IZ DATOTEKE\n11-KRAJ\n");
    scanf(" %d", &odabir);
    switch (odabir)
	{
	case (1):
		umetanjeNaPocetak(head);
		menu(head);
		break;
	case (2):
		umetanjeNaKraj(head->next);
		menu(head);
		break;
	case (3):
		ispis(head);
		menu(head);
		break;
	case (4):
        pronadi(head);
        menu(head);
		break;
    case (5):
        brisi(head);
        menu(head);
		break;
    case (6):
        dodajIza(head);
        menu(head);
		break;
    case (7):
        dodajIspred(head, head->next);
        menu(head);
		break;
    case (8):
        sortiraj(head);
        menu(head);
		break;
    case (9):
        uDatoteku(head->next);
        menu(head);
		break;
    case (10):
        citajIzDatoteke(head);
        menu(head);
		break;
    case (11):
        printf(":)");
		break;
	default:
		printf("Greska!");
		break;
	}


    return 0;
}
int umetanjeNaPocetak(position head)
{
    position novi = NULL;
    novi = (position)malloc(sizeof(osoba));

    if(novi==NULL)
    {
        perror("Greska!");
        return -1;
    }

    printf("\nUnesite ime: ");
    scanf(" %s", (*novi).ime);
    printf("Uneiste prezime: ");
    scanf(" %s", (*novi).prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &(*novi).godina_rodenja);

    novi->next = head->next;
    head->next = novi;

    return 0;
}
int umetanjeNaKraj(position prvi)
{
    position novi = NULL;
    novi = (position)malloc(sizeof(osoba));

    if(novi==NULL)
    {
        perror("Greska!");
        return -1;
    }
    printf("\nUnesite ime: ");
    scanf(" %s", (*novi).ime);
    printf("Uneiste prezime: ");
    scanf(" %s", (*novi).prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &(*novi).godina_rodenja);

    while(prvi->next!=NULL)
    {
        prvi = prvi->next;
    }
    novi->next = prvi->next;
    prvi->next = novi;

    return 0;
}
int ispis(position p)
{
    position pom = p->next;
    printf("\nIspis:\nIME\tPREZIME\t\tGODINA RODENJA\n");
    if(pom==NULL)
    {
        printf("Greska!");
    }

    while(pom!=NULL)
    {
        printf("%s\t%s\t\t%d\n", (*pom).ime, (*pom).prezime, (*pom).godina_rodenja);

        pom = pom->next;
    }

    return 0;
}
int dodajIza(position p)
{
    position novi = NULL;
    novi = (position)malloc(sizeof(osoba));
    char pr[50]={0};

    printf("\ndodaj iza: ");
    scanf(" %s", pr);

    printf("\nUnesite ime: ");
    scanf(" %s", (*novi).ime);
    printf("Uneiste prezime: ");
    scanf(" %s", (*novi).prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &(*novi).godina_rodenja);

    while(p->next!=NULL && strcmp(p->prezime, pr))
    {
        p = p->next;
    }
    novi->next=p->next;
    p->next=novi;

    return 0;
}
int dodajIspred(position q, position p)
{
    position novi = NULL;
    novi = (position)malloc(sizeof(osoba));
    position prvi=p;/*prvi*/
    prvi = (position)malloc(sizeof(osoba));
    position drugi=p->next;/*drugi*/
    drugi = (position)malloc(sizeof(osoba));
    char pr[50]={0};

    printf("\ndodaj ispred: ");
    scanf(" %s", pr);

    printf("\nUnesite ime: ");
    scanf(" %s", (*novi).ime);
    printf("Uneiste prezime: ");
    scanf(" %s", (*novi).prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &(*novi).godina_rodenja);

    while(q->next!=NULL && strcmp(q->next->prezime, pr))
    {
        q = q->next;

    }

    novi->next=q->next;
    q->next=novi;
    return 0;
}
int pronadi(position p)
{
    char prez[50]={0};
    printf("\nperzime osobe koju zelite pronaci : ");
    scanf(" %s", prez);

    while(p->next!=NULL && strcmp(p->prezime, prez))
    {
        p = p->next;
    }
    printf("%s\t%s\t\t%d\n", (*p).ime, (*p).prezime, (*p).godina_rodenja);

    return 0;
}
int brisi(position p)
{
    position drugi = NULL;
    drugi = (position)malloc(sizeof(osoba));
    char a[50];
    printf("\nprezime osobe koju zelite obrisati: ");
    scanf("%s", a);

    while(p!=NULL && strcmp(p->next->prezime, a))
    {
        p=p->next;


    }
    if(p==NULL)
    {
        perror("Greska!");
        return -1;
    }
    drugi = p->next;
    p->next = drugi->next;
    free(drugi);

    return 0;
}
int sortiraj(position p)
{
    position a = p;
    position b = NULL;
    position c = NULL;
    position d = NULL;

    while(p->next != d) {
        c=a;
        b=c->next;
        while(b->next!=d) {
            if(strcmp(b->prezime, b->next->prezime)>0) {
                c->next=b->next;
                b->next=b->next->next;
                c->next->next=b;
                b=c->next;
            }
            c=b;
            b=b->next;
        }
        d=b;
    }

    return 0;
}
int uDatoteku(position p)
{
    FILE* fp;
    fp = fopen("osoba.txt", "w");
    if (fp == NULL) {
		printf("Greska!");
		return -1;
	}
	while (p != NULL) {
		fprintf(fp, "Ime: %s \tPrezime: %s \tGodina: %d\n", p->ime, p->prezime, p->godina_rodenja);
		p = p->next;
	}

	fclose(fp);

	return 0;
}
int citajIzDatoteke(position p)
{
    FILE* fp;
    fp = fopen("osoba.txt", "r");
    if (fp == NULL) {
		printf("Greska!");
		return -1;
	}

	printf("\nCitanje iz datoteke:\n");
	while(!feof(fp))
    {
        printf("%c", getc(fp));
    }

    fclose(fp);

	return 0;
}
