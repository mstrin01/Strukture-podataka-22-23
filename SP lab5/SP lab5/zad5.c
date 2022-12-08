#define _CRT_SECURE_NO_WARNINGS
#define EXIT_FAILURE (-1);
#define EXIT_SUCCESS (0);
#define MAX_FILE_LINE (1024);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Napisati program koji iz datoteke cita postfiks izraz i zatim koristenjem stoga racuna rezultat.
Stog je potrebno realizirati preko vezane liste.
*/

struct _stog;
typedef struct _stog* pozicija;
typedef struct _stog {
	int el;
	pozicija next;
}stog;

pozicija inicijalizacija(pozicija);
int procitajDatoteku(pozicija, char*);
int push(pozicija, int);
int pop(pozicija);
int oslobodiMemoriju(pozicija);
int ispis(pozicija);

int main()
{
	pozicija head = NULL;
	char imeDat[50] = { 0 };

	head = inicijalizacija(head);
	procitajDatoteku(head, imeDat);

	oslobodiMemoriju(head);
	ispis(head->next);

	return EXIT_SUCCESS;
}

pozicija inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(stog));
	if (!p)
	{
		printf("Greska u inicijalizaciji!\n");
		return EXIT_FAILURE;
	}

	p->el = 0;
	p->next = NULL;

	return p;
}

int procitajDatoteku(pozicija p, char* imeDat)
{
	FILE* fp = NULL;
	int duljina = 0, brojac = 0, n = 0, broj = 0;
	int prviBroj = 0, drugiBroj = 0, rezultat = 0;
	char operator;
	char* buffer=NULL;
	buffer = (char*)malloc(1024);
	

	printf("Unesi ime datoteke koju zelis procitati: \n");
	scanf(" %s", imeDat);

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return EXIT_FAILURE;
	}

	fgets(buffer, 1024, fp);
	duljina = strlen(buffer);

	while (brojac <= duljina)
	{
		if (sscanf(buffer, "%d %n", &broj, &n) == 1)
		{
			push(p, broj);
		}
		else if (sscanf(buffer, "%c %n", &operator, &n) == 1)
		{
			if (operator == '+')
			{
				drugiBroj = pop(p);
				prviBroj = pop(p);
				rezultat = prviBroj + drugiBroj;
				
				push(p, rezultat);
			}
			else if (operator == '-')
			{
				drugiBroj = pop(p);
				prviBroj = pop(p);
				rezultat = prviBroj - drugiBroj;

				push(p, rezultat);
			}
			else if (operator == '*')
			{
				drugiBroj = pop(p);
				prviBroj = pop(p);
				rezultat = prviBroj * drugiBroj;

				push(p, rezultat);
			}
			else if (operator == '/')
			{
				drugiBroj = pop(p);
				prviBroj = pop(p);
				rezultat = prviBroj / drugiBroj;

				push(p, rezultat);
			}
			else
			{
				printf("Krivi znak!\n");
			}
		}
		brojac += n;
		buffer += n;
	}
	printf("Rezultat: %d\n", rezultat);

	fclose(fp);
	return EXIT_SUCCESS;
}


int push(pozicija p, int br)
{
	pozicija q = NULL;
	q = inicijalizacija(q);

	q->el = br;
	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int pop(pozicija p)
{
	pozicija q = NULL;
	q = inicijalizacija(q);

	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		return q->el;
		free(q);
	}
	

	return EXIT_SUCCESS;
}

int oslobodiMemoriju(pozicija p)
{
	pozicija temp = NULL;
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}
int ispis(pozicija p)
{
	if (p == NULL) {
		printf("Lista je prazna!\n");
	}
	else
		printf("Memorija nije oslobodjena!\n");
	return EXIT_SUCCESS;
}