#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX];
	char surname[MAX];
	int birthYear;
	Position next;
}Person;

int PrependList(Position, char*, char*, int);
int AppendList(Position, char*, char*, int);
int Print(Position );
Position CreatePerson(char*, char*, int);
int InsertAfter(Position, Position);
Position FindLast(Position);
int FindBySurname(Position, char*);
Position FindBefore(Position, Position);
int DeleteAfter(Position, char*);

int main(int argc, char** argv) {

	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;

    PrependList(p, "Domina", "Amizic", 2001);
    AppendList(p, "Stella", "Andelic", 1993);
    PrependList(p, "Filip", "Antolovic", 1999);
    PrependList(p, "Noa", "Baric", 1976);

    Print(p->next);

    FindBySurname(Head.next, "Amizic");

    DeleteAfter(p, "Amizic");

    printf("\n");
    Print(p->next);

    FindBySurname(Head.next, "Amizic");

	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{

	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
        perror("Can't allocate memory!\n");
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int Print(Position first)
{
	Position temp = first;

	while (temp) {
		printf("Name: %s\tsurname: %s\tbirthyear: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next)
    {
        temp = temp->next;
	}

	return temp;
}

int FindBySurname(Position first, char* surname)
{
	Position temp = first;
	while (temp) {
		if (strcmp(temp->surname, surname) == 0)
        {
            printf("\n%s found.\n", surname);
			return temp;
		}
		temp = temp->next;
	}
	printf("\n%s not found.\n", surname);
	return NULL;
}
Position FindBefore(Position Head, Position first)
{
    Position temp = Head;

	while (temp != NULL && temp->next != first)
		temp = temp->next;

	return temp;
}
int DeleteAfter(Position Head, char* surname)
{
    Position temp = Head;
    Position del = NULL;

    for(temp; temp->next; temp=temp->next)
        if(strcmp(temp->next->surname, surname)==0)
            break;
    del=temp->next;
    temp->next=del->next;

    return 0;
}
