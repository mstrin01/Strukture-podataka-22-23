#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_FAILURE -1;
#define EXIT_SUCCESS 0;

/*
Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/

struct _direktorij;
typedef struct _direktorij* DirPozicija;
typedef struct _direktorij {
	char ime[40];
	DirPozicija dijete;
	DirPozicija brat;
}direktorij;

struct _stog;
typedef struct _stog* StogPozicija;
typedef struct _stog {
	DirPozicija roditelj;
	StogPozicija next;
}stog;


StogPozicija stvoriStog();
DirPozicija stvoriDirektorij();
DirPozicija md(DirPozicija, DirPozicija);
DirPozicija cd_dir(StogPozicija, DirPozicija);
int dir(DirPozicija);
int push(StogPozicija, DirPozicija);
StogPozicija pop(StogPozicija);
int obrisiMemoriju(DirPozicija);

int main()
{
	int flag = 1;
	char izbor = { 0 };

	StogPozicija stog = NULL;
	DirPozicija roditelj = NULL, trenutni = NULL, element = NULL;

		stog = stvoriStog();
	roditelj = stvoriDirektorij();
	trenutni = roditelj;

	while (flag)
	{
		printf("\n  MENI: \n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf(" 1 - md\n 2 - cd dir\n 3 - cd..\n 4 - dir\n 5 - izlaz\n ");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("\nUnesi broj: ");
		scanf(" %c", &izbor);
		puts("\n");

		switch (izbor) {
		case '1':
			
			element = stvoriDirektorij();
			trenutni->dijete = md(trenutni->dijete, element);
			break;
			
		case '2':

			element = cd_dir(stog, trenutni);
			trenutni = element;
			break;

		case '3':
			element = pop(stog);
			if (!element)
				printf("Ne moze ici dalje od root-a!\n");
			else
				trenutni = element;
			break;

		case '4':
			dir(trenutni);
			break;
			
		case '5':
			obrisiMemoriju(roditelj);
			flag = 0; 
			break;

		default:
			
			printf("Pogresno ste unijeli znak, ponovite!\n");
			break;

		}

	}

	return EXIT_SUCCESS;
}


StogPozicija stvoriStog()
{
	StogPozicija p = NULL;
	p = (StogPozicija)malloc(sizeof(stog));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return EXIT_FAILURE;
	}
	p->next = NULL;

	return p;
}
DirPozicija stvoriDirektorij()
{
	DirPozicija p = NULL;
	p = (DirPozicija)malloc(sizeof(direktorij));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return EXIT_FAILURE;
	}
	p->dijete = NULL;
	p->brat = NULL;

	printf("Unesi naziv: \n");
	scanf(" %s", p->ime);

	return p;
}

DirPozicija md(DirPozicija trenutni, DirPozicija element)
{
	if (trenutni == NULL)
	{
		return element;
	}

	if (strcmp(trenutni->ime, element->ime) < 0)
	{
		trenutni->brat = md(trenutni->brat, element);
	}
	else if (strcmp(trenutni->ime, element->ime) > 0)
	{
		element->brat = trenutni;
		return element;
	}
	else if (strcmp(trenutni->ime, element->ime) == 0)
	{
		printf("Taj naziv vec postoji!\n");
	}

	return trenutni;
}

DirPozicija cd_dir(StogPozicija stog, DirPozicija trenutni)
{
	DirPozicija q = NULL, temp = NULL;
	char nazivDir[40] = { 0 };

	printf("Unesi naziv direktorija kojem zelis pristupiti: \n");
	scanf(" %s", nazivDir);

	if (trenutni->dijete == NULL)
	{
		printf("Direktorij je prazan!\n");
		return NULL;
	}

	temp = trenutni->dijete;
	while (temp != NULL)
	{
		if (strcmp(temp->ime, nazivDir) == 0)
		{
			q = temp;
		}
		temp = temp->brat;
	}
	push(stog, trenutni);
	
	return q;
}

int dir(DirPozicija trenutni)
{
	DirPozicija temp = NULL;
	printf(" %s: \n", trenutni->ime);

	if (trenutni->dijete != NULL)
	{
		temp = trenutni->dijete;
		while (temp != NULL)
		{
			printf(" %s\t", temp->ime);
			temp = temp->brat;
		}
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int push(StogPozicija stog, DirPozicija trenutni)
{
	StogPozicija q = NULL;
	q = stvoriStog();

	q->roditelj = trenutni;
	q->next = stog->next;
	stog->next = q;

	return EXIT_SUCCESS;
}

StogPozicija pop(StogPozicija stog)
{
	StogPozicija temp = NULL;
	DirPozicija p = NULL;

	if (stog == NULL || stog->next == NULL)
	{
		return NULL;
	}

	temp = stog->next;
	p = temp->roditelj;
	stog->next = temp->next;

	free(temp);

	return p;
}

int obrisiMemoriju(DirPozicija roditelj)
{
	if (roditelj == NULL)
	{
		return 0;
	}

	obrisiMemoriju(roditelj->brat);
	obrisiMemoriju(roditelj->dijete);

	return EXIT_SUCCESS;
}

