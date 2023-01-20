#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50


struct _stablo;
typedef struct _stablo* position;
typedef struct _stablo {
	char grad[max];
	int brojStan;
	position left;
	position right;

}stablo;

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista {
	char drzava[max];
	pozicija next;
	position stabloP;
}lista;

pozicija inicijalizacijaListe(pozicija);
position inicijalizacijaStabla(position);
int citajDrzave(position, char*);
int sortiraniUnos(pozicija, char*, char*);
int citajGradoveIzDat(pozicija, char*);
position stvoriStablo(position, char*, int);
pozicija pronadjiDrzavu(pozicija, char*);
int inorder(position);
int print(pozicija);
int inorderIspisVeceOd(position, int);

int main()
{

	position root = NULL;
	pozicija head = NULL, p = NULL;
	char datDrz[max] = "drzave.txt";
	char drzava[max] = { 0 };
	char izbor = { 0 };
	int uvjet = 1;
	int broj = 0;

	head = inicijalizacijaListe(head);
	p = inicijalizacijaListe(p);
	root = inicijalizacijaStabla(root);

	citajDrzave(head, datDrz);
	print(head->next);

	printf("\n\t Upisi 1 za izabrati drzavu ili 2 za izaci iz petlje: ");

	while (1)
	{
		scanf(" %s", izbor);
		switch (izbor)
		{
		case '1':

			printf("Unesi ime drzave: ");
			scanf(" %s", drzava);
			p = pronadjiDrzavu(head, drzava);

			if (!p)
			{
				printf("Odabrana drzava ne postoji u datoteci!\n");
				return EXIT_FAILURE;
			}

			printf("Prikaz gradova s brojem stanovnika vecim nego uneseni. Unesi broj: ");
			scanf("%d", &broj);
			inorderIspisVeceOd(p->stabloP, broj);
			break;

		case '2':
			printf("IZLAZ IZ PETLJE...\n");
			uvjet = 0;
			break;

		default:
			printf("Unijeli ste krivi broj!\n");
			break;
		}
	}


	return 0;
}


position stvoriStablo(position p, char* imeGrada, int stanovnici)
{
	if (!p)
	{
		p = (position)malloc(sizeof(stablo));

		if (!p)
		{
			printf("Greska u alokaciji memorije!\n");
			return NULL;
		}

		strcpy(p->grad, imeGrada);
		p->brojStan = stanovnici;
		p->left = NULL;
		p->right = NULL;
	}

	else if (stanovnici == p->brojStan)
	{
		if (strcmp(imeGrada, p->grad) < 0)
		{
			p->left = stvoriStablo(p->left, imeGrada, stanovnici);
		}
		else if (strcmp(imeGrada, p->grad) > 0)
		{
			p->right = stvoriStablo(p->right, imeGrada, stanovnici);
		}
	}

	else
	{
		if (stanovnici < p->brojStan)
			p->left = stvoriStablo(p->left, imeGrada, stanovnici);

		else if (stanovnici > p->brojStan)
			p->right = stvoriStablo(p->right, imeGrada, stanovnici);
	}
	return p;
}

int citajGradoveIzDat(position p, char* drzavaDat)
{
	FILE* fp = NULL;
	char imeGrada[max];
	int stanovnici = 0;

	fp = fopen(drzavaDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d", imeGrada, &stanovnici);

	}

	fclose(fp);
	return 0;
}


int sortiraniUnos(pozicija p, char* imeDrzave, char* drzavaDat)
{
	pozicija q = NULL;

	q = inicijalizacijaListe(q);
	if (!q)
	{
		printf("Greska u alokaciji memorije.\n");
		return EXIT_FAILURE;
	}

	strcpy(q->drzava, imeDrzave);
	q->stabloP = NULL;
	q->stabloP = citajGradoveIzDat(q->stabloP, drzavaDat);

	strcpy(q->drzava, imeDrzave);
	q->stabloP = NULL;
	q->stabloP = citajGradoveIzDat(q->stabloP, drzavaDat);

	while (p != NULL)
	{
		if (p->next != NULL)
		{
			p->next = q;
			q->next = NULL;
			break;
		}
		else if (strcmp(imeDrzave, p->next->drzava) < 0)
		{
			q->next = p->next;
			p->next = q;
			break;
		}
		p = p->next;
	}

	return 0;
}

int citajDrzave(position p, char* dat)
{
	FILE* fp = NULL;
	char imeDrzave[max], drzavaDat[max];

	fp = fopen(dat, "r");
	if (!fp)
	{
		printf("Greska u citanju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", imeDrzave, drzavaDat);
		sortiraniUnos(p, imeDrzave, drzavaDat);
	}

	fclose(fp);
	return 0;
}

position inicijalizacijaStabla(position p)
{
	p = (position)malloc(sizeof(stablo));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	strcpy(p->grad, "");
	p->brojStan = 0;
	p->right = NULL;
	p->left = NULL;

	return p;
}

pozicija inicijalizacijaListe(pozicija p)
{
	p = (pozicija)malloc(sizeof(lista));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	strcpy(p->drzava, "");
	p->next = NULL;

	return p;
}

pozicija pronadjiDrzavu(pozicija p, char* imeDrzave)
{
	while (p->next != NULL && strcmp(imeDrzave, p->drzava) != 0)
		p = p->next;

	return p;
}

int inorder(position p)
{
	if (p == NULL)
		return 0;

	inorder(p->left);
	printf("%s %d\n", p->grad, p->brojStan);
	inorder(p->right);

	return 0;
}


int print(pozicija p)
{
	while (p != NULL)
	{
		printf("\n%s:\n", p->drzava);
		inorder(p->stabloP);
		p = p->next;
	}

	return 0;
}

int inorderIspisVeceOd(position p, int broj)
{
	if (p == NULL)
		return 0;

	inorderIspisVeceOd(p->left, broj);

	if (broj < p->brojStan)
	{
		printf("%s %d\n", p->grad, p->brojStan);
	}

	inorderIspisVeceOd(p->right, broj);

	return 0;
}