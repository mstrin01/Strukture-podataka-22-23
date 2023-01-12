#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

/*Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u cvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici 1. Funkcije vraæa
pokazivac na korijen stabla.
b) Napisati funkciju replace koja ce svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike  1 transformirat ce se u stablo na
slici 2.
c) Prepraviti program na nacin da umjesto predefiniranog cjelobrojnog polja koristenjem
funkcije rand() generira slucajne brojeve u rasponu <10, 90>. Takoder, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon koristenja funkcije iz a), zatim b)
dijela zadatka.
*/

struct _cvor;
typedef struct _cvor* position;
typedef struct _cvor
{
	int broj;
	position left;
	position right;
}cvor;

struct _lista;
typedef struct _lista* posL;
typedef struct _lista
{
	int el;
	posL next;
}lista;

int inorder(position, posL);
posL inicijalizacijaListe(posL);
position StvoriPrazno(position);
position insert(position, int);
position replace(position);
int suma(position);
position slucajniBrojevi(position);
int UmetniNaKraj(posL, int);
posL PronadiZadnji(posL);
int umetni(posL, int);
int ispisDat(posL, posL, posL, char*);
int oslobodiMemoriju(posL);

int main()
{
	srand(time(NULL));
	position root = NULL;
	posL p1 = NULL;
	posL p2 = NULL;
	posL p3 = NULL;
	char imeDat[50] = "stablo.txt";

	root = StvoriPrazno(root);
	p1 = inicijalizacijaListe(p1);
	p2 = inicijalizacijaListe(p2);
	p3 = inicijalizacijaListe(p3);

	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 11);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 7);

	
	inorder(root, p1);

	root = replace(root);
	inorder(root, p2);

	root = StvoriPrazno(root);
	root = slucajniBrojevi(root);
	inorder(root, p3);
	ispisDat(p1->next, p2->next, p3->next, imeDat);

	oslobodiMemoriju(p1);
	oslobodiMemoriju(p2);
	oslobodiMemoriju(p3);

	return 0;
}

posL inicijalizacijaListe(posL p)
{
	p = (posL)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	p->el = 0;
	p->next = NULL;
	return p;
}
position StvoriPrazno(position p)
{
	if (p != NULL)
	{
		p->left = StvoriPrazno(p->left);
		p->right = StvoriPrazno(p->right);
		free(p);
	}
	return NULL;
}

int inorder(position p, posL head)
{
	if (p == NULL)
		return 0;

	inorder(p->left, head);
	UmetniNaKraj(head, p->broj);
	inorder(p->right, head);

	return 0;
}

position insert(position p, int el)
{
	if (p == NULL)
	{
		p = (position)malloc(sizeof(cvor));
		p->broj = el;
		p->left = NULL;
		p->right = NULL;
	}
	else if (el >= p->broj)
	{
		p->left = insert(p->left, el);
	}
	else if (el <= p->broj)
	{
		p->right = insert(p->right, el);
	}

	return p;
}

int suma(position p)
{
	int zbroj = 0;
	if (p == NULL)
	{
		return zbroj;
	}

	if (p->left != NULL)
	{
		zbroj += p->left->broj + suma(p->left);
	}

	if (p->right != NULL)
	{
		zbroj += p->right->broj + suma(p->right);
	}

	return zbroj;
}
position replace(position p)
{
	if (p != NULL)
	{
		p->broj = suma(p);
		p->left = replace(p->left);
		p->right = replace(p->right);
	}
	return p;
}

position slucajniBrojevi(position p)
{
	int i = 0, broj = 0;
	for (i = 0; i < 10; i++)
	{
		broj = (rand() % (90 - 10 + 1)) + 10;
		p = insert(p, broj);
	}

	return p;
}

int UmetniNaKraj(posL head, int broj)
{
	posL zadnji = NULL;
	zadnji = PronadiZadnji(head);
	umetni(zadnji, broj);

	return 0;
}

posL PronadiZadnji(posL head)
{
	while (head->next != NULL)
		head = head->next;

	return head;
}

int umetni(posL head, int broj)
{
	posL q = NULL;
	q = (posL)malloc(sizeof(lista));

	if (q == NULL)
	{
		return -1;
	}
	q->el = broj;
	q->next = head->next;
	head->next = q;

	return 0;
}

int ispisDat(posL p1, posL p2, posL p3, char* imeDat)
{
	FILE* fp = NULL;
	fp = fopen(imeDat, "w");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}


	while (p1 != NULL)
	{
		fprintf(fp, "%d\t", p1->el);
		p1 = p1->next;
	}
	fprintf(fp, "\n");
	while (p2 != NULL)
	{
		fprintf(fp, "%d\t", p2->el);
		p2 = p2->next;
	}
	fprintf(fp, "\n");
	while (p3 != NULL)
	{
		fprintf(fp, "%d\t", p3->el);
		p3 = p3->next;
	}


	fclose(fp);
	return 0;
}

int oslobodiMemoriju(posL p)
{
	posL temp = NULL;
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return 0;
}
