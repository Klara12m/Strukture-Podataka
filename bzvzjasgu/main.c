#include<stdio.h>
#define R 3
#define S 3

int main()
{
	int mat[R][S];
	int i, j;
	int a;
	int b[R], c[S];

	for (i = 0; i < R; i++)
	{
		for (j = 0; j < S; j++)
		{
			printf("Upisi [%d][%d] vrijednost  ", i, j);
			scanf_s("%d", &a);
			mat[i][j] = a;
		}
	}

	for (i = 0; i < R; i++)
	{
		for (j = 0; j < S; j++)
		{
			printf("%d", mat[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < R; i++)
	{
		b[i] = mat[i][i];
		c[i] = mat[i][S - 1 - i];
	}
	printf("Glavna dijagonala: ");
	for (i = 0; i < R; i++)
	{
		printf("%d", b[i]);
	}
	printf("Sporedna dijagonala: ");
	for (i = 0; i < R; i++)
	{
		printf("%d", c[i]);
	}

	return 0;
}
