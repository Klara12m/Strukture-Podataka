#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

struct _element;
typedef struct _element* position;
typedef struct _element
{
    double number;
    position next;
}element;

int CalculatePostfixFromFile(double*);
int Push(position, double);
int DeleteAfter(position);
int DeleteAll(position);
int PerformOperation(position, char);
int Pop(double*, position);
int main()
{
    double result = 0.0;

    CalculatePostfixFromFile(&result);

    printf("result: %lf", result);

    return 0;
}
int CalculatePostfixFromFile(double* result)
{
    int fileLength = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	double number = 0;
	int status = 0;
	char operation = 0;
	element head = { .next = NULL, .number = 0 };
    FILE*fp = NULL;
    fp = fopen("postifix.txt", "rb");
    if(fp == NULL)
    {
        perror("Greska pri otvaranju datoteke! :(\n");
        return -1;
    }
    /*printf("postfix: ");
    while(!feof(fp))
    {
        printf("%c", getc(fp));
    }
    rewind(fp);*/

    fseek(fp, 0, SEEK_END); //dođemo na kraj
	fileLength = ftell(fp);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Can't allocate memory!\n");
		return -2;
	}
	rewind(fp);
	fread(buffer, sizeof(char), fileLength, fp); //iz datoteke u buffer
	printf("postfix: |%s|\n", buffer);
	fclose(fp);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status == 1)
		{
			status = Push(&head, number);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return -3;
			}
			currentBuffer += numBytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = PerformOperation(&head, operation);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return -4;
			}
			currentBuffer += numBytes;
		}
	}

	free(buffer);

    status = Pop(result, &head);
	if (status != EXIT_SUCCESS)
	{
		DeleteAll(&head);
		return -5;
	}

	if (head.next)
	{
		printf("Postfix not valid! Please check your file! :) \n");
		DeleteAll(&head);
		return -6;
	}

	return EXIT_SUCCESS;
}
int Push(position head, double number)
{
	position newElement = NULL;

	newElement = (position)malloc(sizeof(element));
	if (!newElement)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}
	newElement->number = number;
	newElement->next = NULL;

	if (!newElement)
	{
		return -1;
	}

	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
int DeleteAll(position head)
{
	while (head->next)
	{
		DeleteAfter(head);
	}

	return EXIT_SUCCESS;
}
int DeleteAfter(position p)
{
	position temp = p->next;

	if (!temp)
	{
		return EXIT_SUCCESS;
	}

	p->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}
int PerformOperation(position head, char operation)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return -1;
	}

	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return -2;
	}

	switch (operation)
	{
	case '+':
		result = operand1 + operand2;
		break;
	case '-':
		result = operand1 - operand2;
		break;
	case '*':
		result = operand1 * operand2;
		break;
	case '/':
		if (operand2 == 0)
		{
			perror("Cannot divide with zero!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	default:
		printf("This operation is not supported yet!");
		return -4;
	}

	return Push(head, result);
}
int Pop(double* result, position head)
{
	position first = head->next;

	if (!first)
	{
		perror("Postfix not valid! Please check your file! (pop)\n");
		return -1;
	}

	*result = first->number;
	DeleteAfter(head);

	return EXIT_SUCCESS;
}
