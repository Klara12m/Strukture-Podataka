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
		fscanf(fp, " %s %s %lf", st[i].ime, st[i].prez, &st[i].bodovi);
	}
	fclose(fp);
    for (i = 0; i < n; i++)
    {
        printf(" \n%s %s %.0lf %lf", st[i].ime, st[i].prez, st[i].bodovi, st[i].bodovi/90*100);
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
