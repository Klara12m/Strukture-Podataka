#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 80

typedef struct {
	char ime[MAX];
	char prez[MAX];
	double bodovi;
}_studenti;
int BrojRedova(FILE*);
_studenti* Unos(_studenti*,FILE*);
void Ispis(_studenti*);
int main()
{
	_studenti *st = NULL;
	int n = 0;
	int i = 0;

	FILE *fp = NULL;
	fp = fopen("studenti.txt", "r");
	if (!fp)
	{
		printf("Greska!");
		return -1;
	}
	rewind(fp);
	n = BrojRedova(fp);
	st = (_studenti*)malloc(n * sizeof(_studenti));
	rewind(fp);
	for (i = 0; i < n; i++)
	{
		Unos(st+i,fp);
	}
	fclose(fp);
    for (i = 0; i < n; i++)
    {
        Ispis(st+i);
    }
    free(st);
	return 0;
}
int BrojRedova(FILE*fp)
{
	int brr = 0;
	char buf[MAX] = { 0 };

	while (!feof(fp))
	{
		fgets(buf, MAX, fp);
		brr++;
	}

	printf("Broj redova u datoteci: %d", brr);

	return brr;
}
_studenti* Unos(_studenti*st, FILE*fp)
{
    fscanf(fp, " %s %s %lf", st->ime, st->prez, &st->bodovi);
}
void Ispis(_studenti*st)
{
    printf(" \n%s %s\t%.0lf\t%lf", st->ime, st->prez, st->bodovi, st->bodovi/90*100);
}
