#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 50

struct _osoba;
typedef struct _osoba* position;

typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godina_rodenja;

	position next;
}osoba;

int menu(position);
int DodajNaPocetak(position);
int DodajNaKraj(position);
int ispis(position);
int PronadiPoPrezimenu(position);
int brisi(position);
int DodajIza(position);
int DodajIspred(position);
int SortirajPoPrezimenu(position);
int uDatoteku(position);
int CitajIzDatoteke(position);
int CitajIzDatotekeUListu(position);
int main() {
	osoba head = { .ime = {0},.prezime = {0},.godina_rodenja = 0,.next = NULL };
	position pHead = &head;

	menu(pHead);

	return 0;
}
int menu(position head) {
	int x = 0;

	printf("Odaberite:\n1-DODAJ NA POCETAK\n2-DODAJ NA KRAJ\n3-ISPIS LISTE\n4-PRONADI PO PREZIMENU\n5-BRISI\n6-DODAJ IZA\n7-DODAJ ISPRED\n8-SORTIRAJ PO PREZIMENU\n9-U DATOTEKU\n10-CITAJ IZ DATOTEKE\n11-CITAJ IZ DATOTEKE U LISTU\n0-KRAJ\n");
	scanf(" %d", &x);

	switch (x) {
	case(1):
		DodajNaPocetak(head);
		menu(head);
		break;
	case(2):
		DodajNaKraj(head);
		menu(head);
		break;
	case(3):
		ispis(head);
		menu(head);
		break;
	case(4):
		PronadiPoPrezimenu(head);
		menu(head);
		break;
	case(5):
		brisi(head);
		menu(head);
		break;
	case(6):
		DodajIza(head);
		menu(head);
		break;
	case(7):
		DodajIspred(head);
		menu(head);
		break;
	case(8):
		SortirajPoPrezimenu(head);
		menu(head);
		break;
	case(9):
		uDatoteku(head->next);
		menu(head);
		break;
	case(10):
		CitajIzDatoteke(head);
		menu(head);
		break;
	case(11):
		CitajIzDatotekeUListu(head);
		menu(head);
		break;
	case(0):
		printf(":)");
		break;
	default:
		printf("Krivi unos!");
		break;
	}
	return 0;
}
int DodajNaPocetak(position head) {
	position novi = (position)malloc(sizeof(osoba));

	if (novi == NULL) {
		printf("Greska!(1)");
		return -1;
	}
	printf("\nUnesite ime: ");
	scanf(" %s", novi->ime);
	printf("\nUnesite prezime: ");
	scanf(" %s", novi->prezime);
	printf("\nUnesite godinu rodenja: ");
	scanf(" %d", &novi->godina_rodenja);

	novi->next = head->next;
	head->next = novi;

	return 0;
}
int DodajNaKraj(position head) {
	position novi = (position)malloc(sizeof(osoba));

	if (novi == NULL) {
		printf("Greska!(1)");
		return -1;
	}
	printf("\nUnesite ime: ");
	scanf(" %s", novi->ime);
	printf("\nUnesite prezime: ");
	scanf(" %s", novi->prezime);
	printf("\nUnesite godinu rodenja: ");
	scanf(" %d", &novi->godina_rodenja);

	while (head->next != NULL) {
		head = head->next;
	}

	novi->next = head->next;
	head->next = novi;

	return 0;
}
int ispis(position head) {
	position pom = head->next;

	printf("\nIME\t\tPREZIME\t\tGODINA");

	while (pom != NULL) {
		printf("\n%s\t\t%s\t\t%d", pom->ime, pom->prezime, pom->godina_rodenja);
		pom = pom->next;
	}
	printf("\n\n");
	return 0;
}
int PronadiPoPrezimenu(position head) {
	char pom[MAX];
	printf("\nUnesite prezime: ");
	scanf(" %s", pom);

	while (head != NULL && strcmp(pom, head->prezime)) {
		head = head->next;
	}
	printf("\n%s\t%s\t%d\n", head->ime, head->prezime, head->godina_rodenja);
	return 0;
}
int brisi(position head) {
	position temp;
	temp = (position)malloc(sizeof(osoba));
	char pom[MAX];
	printf("\nUnesite prezime: ");
	scanf(" %s", pom);

	while (head != NULL, strcmp(pom, head->next->prezime)) {
		head = head->next;
	}

	temp = head->next;
	head->next = temp->next;
	free(temp);

	return 0;
}
int DodajIza(position head) {
	position novi = (position)malloc(sizeof(osoba));
	char pom[MAX];

	printf("Dodaj iza: ");
	scanf(" %s", pom);

	while (head != NULL, strcmp(pom, head->prezime)) {
		head = head->next;
	}
	DodajNaPocetak(head);

	return 0;
}
int DodajIspred(position head) {
	position novi = (position)malloc(sizeof(osoba));
	char pom[MAX];

	printf("\nDodaj ispred: ");
	scanf(" %s", pom);

	while (head != NULL, strcmp(head->next->prezime, pom)) {
		head = head->next;
	}

	DodajNaPocetak(head);

	return 0;
}
int SortirajPoPrezimenu(position head) {
	position a = NULL;
	position b = NULL;	
	position c = NULL;
	position d = NULL;

	a = head;

	while (head->next != d) {
		c = a;
		b = c->next;
		while (b->next != d) {
			if (strcmp(b->prezime, b->next->prezime) > 0) {
				c->next = b->next;
				b->next = b->next->next;
				c->next->next = b;
				b = c->next;
			}
			c = b;
			b = b->next;
		}
		d = b;
	}

	
	return 0;
}
int uDatoteku(position head) {
	FILE* fp;
	fp = fopen("osoba.txt", "w");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	while (head != NULL) {
		fprintf(fp, "%s %s %d\n", head->ime, head->prezime, head->godina_rodenja);
		head = head->next;
	}
	fclose(fp);

	return 0;
}
int CitajIzDatoteke(position head) {
	FILE* fp;
	fp = fopen("osoba.txt", "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!(2)");
		return -1;
	}

	while (!feof(fp)) {
		printf("%c", getc(fp));
	}
	fclose(fp);
	return 0;
}
int CitajIzDatotekeUListu(position head) {
	FILE* fp = fopen("osoba.txt", "r");
	int br = 0;
	int  i = 0;

	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return 1;
	}

	while (!feof(fp)) {
		if (getc(fp) == '\n')
			br++;
	}

	rewind(fp);

	for (i = 0; i < br; i++) {
		position q = (position)malloc(sizeof(osoba));
		if (q == NULL)
		{
			printf("Neuspjesna alokacija memorije!\n");
			return 1;
		}

		fscanf(fp, "%s %s %d", q->ime, q->prezime, &q->godina_rodenja);

		q->next = head->next;
		head->next = q;
		head = head->next;
	}
	fclose(fp);

	return 0;
}