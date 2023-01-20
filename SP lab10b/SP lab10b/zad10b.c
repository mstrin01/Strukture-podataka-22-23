#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	char grad[max];
	int stanovnici;
	pozicija next;
}lista;

struct _stablo;
typedef struct _stablo* position;
typedef struct _stablo
{
	char drzava[max];
	pozicija listaP;
	position left;
	position right;
}stablo;

position inicijalizacijaStabla(position);
position procitajDrzaveIzDat(position, char*);
position unosUStablo(position, char*, char*);
position pronadjiDrzavu(position, char*);
int inorder(position);
int stvoriListu(pozicija, char*, int);
pozicija procitajGradoveIzDat(pozicija, char*);
int ispisListe(pozicija);
pozicija inicijalizacijaListe(pozicija);
int ispisSt(pozicija, int);


int main()
{
	position root = NULL, current = NULL;
	pozicija head = NULL;
	int uvjet = 1, broj = 0;
	char imeDat[max] = "drzave.txt";
	char imeDrzave[max] = { 0 };
	char izbor = { 0 };

	root = inicijalizacijaStabla(root);
	head = inicijalizacijaListe(head);

	root = procitajDrzaveIzDat(root, imeDat);
	inorder(root);

	printf("Upisi 1 za izabrati drzavu ili 2 za izlaz iz petlje: ");
	while (uvjet)
	{
		scanf("%s", izbor);

		switch (izbor)
		{
		case'1':

			printf("Upisi drzavu: ");
			scanf(" %s", imeDrzave);
			current = pronadjiDrzavu(root, imeDrzave);

			if (current == NULL)
			{
				printf("Upisana drzava nije unesena u datoteku.\n");
				return 0;
			}

			printf("Unesi broj: ");
			scanf("%d", &broj);
			printf("\nPrikaz brojeva s brojem stanovnika manjim od unesenog broja:\n");
			ispisSt(current->listaP, broj);
			break;

		case '2':
			printf("\nIZLAZ IZ PETLJE...\n");
			uvjet = 0;
			break;

		default:
			printf("Pogresan broj!\n");
			break;
		}


	}

	return 0;
}

position inicijalizacijaStabla(position p)
{
	p = (position)malloc(sizeof(stablo));

	if (!p)
	{
		printf("Greska u alokaciji stabla!\n");
		return -1;
	}

	p->left = NULL;
	p->right = NULL;
	p->listaP = NULL;
	strcpy(p->drzava, "");

	return p;
}

pozicija inicijalizacijaListe(pozicija p)
{
	p = (pozicija)malloc(sizeof(lista));
	if (!p)
	{
		printf("Greska u alokaciji liste!\n");
		return -1;
	}

	p->next = NULL;
	strcpy(p->grad, "");
	p->stanovnici = 0;

	return p;
}


position procitajDrzaveIzDat(position p, char* imeDat)
{
	FILE* fp = NULL;
	char imeDrz[max] = { 0 }, imeDatDrzave[max] = { 0 };

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Nemoguce procitati drzave iz datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", imeDatDrzave, imeDrz);
		p = unosUStablo(p, imeDatDrzave, imeDrz);
	}

	fclose(fp);

	return p;
}
position unosUStablo(position p, char* datDrz, char* imeDrz)
{
	if (p == NULL)
	{
		p = inicijalizacijaStabla(p);
		strcpy(p->drzava, imeDrz);
		p->listaP = procitajGradoveIzDat(p->listaP, datDrz);
	}

	else if (strcmp(p->drzava, imeDrz) > 0)
	{
		p->left = unosUStablo(p->left, datDrz, imeDrz);
	}

	else if (strcmp(p->drzava, imeDrz) < 0)
	{
		p->right = unosUStablo(p->right, datDrz, imeDrz);
	}

	return p;
}

pozicija procitajGradoveIzDat(pozicija p, char* datDrz)
{
	FILE* fp = NULL;
	char imeGrada[max] = { 0 };
	int brStGrada = 0;

	fp = fopen(datDrz, "r");
	if (!fp)
	{
		printf("Nemoguce procitati gradove iz datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d", imeGrada, &brStGrada);
		p = stvoriListu(p, imeGrada, brStGrada);
	}

	fclose(fp);

	return p;
}
int stvoriListu(pozicija p, char* imeGrada, int brStan)
{
	pozicija q = NULL;
	q = inicijalizacijaListe(q);

	strcpy(q->grad, imeGrada);
	q->stanovnici = brStan;


	while (p->next != NULL)
	{
		if (q->stanovnici < p->next->stanovnici)
			break;

		else if (q->stanovnici == p->next->stanovnici)
		{
			if (strcmp(q->grad, p->next->grad) < 0)
				break;
			else if (strcmp(q->grad, p->next->grad) > 0)
			{
				p = p->next;
				continue;
			}
		}
		p = p->next;

	}
	q->next = p->next;
	p->next = q;

	return 0;
}

int inorder(position p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		inorder(p->left);
		printf("%s\n", p->drzava);
		ispisListe(p->listaP);
		inorder(p->right);
	}

	return 0;
}


int ispisListe(pozicija p)
{
	if (p == NULL)
		return 0;

	else
	{
		p = p->next;

		while (p != NULL)
		{
			printf(" %s-%d ", p->grad, p->stanovnici);
			p = p->next;
		}
	}

	return 0;

}

position pronadjiDrzavu(position p, char* imeDrz)
{
	if (p == NULL)
		return NULL;

	else if (strcmp(imeDrz, p->drzava) == 0)
		return p;

	else if (strcmp(imeDrz, p->drzava) > 0)
		return pronadjiDrzavu(p->right, imeDrz);

	return pronadjiDrzavu(p->left, imeDrz);

}

int ispisSt(pozicija p, int br)
{
	while (p != NULL)
	{
		if (br < p->stanovnici)
			printf(" %s: %d\n", p->grad, p->stanovnici);

		p = p->next;
	}

	return 0;
}