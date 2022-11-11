#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


/*Napisati program za zbrajanje i mnozenje polinoma. Koeficijenti i eksponenti se citaju iz datoteke.
Eksponenti u datoteci nisu nuzno sortirani.*/

struct _polinom;
typedef struct _polinom* pozicija;
typedef struct _polinom
{
	int eksponent;
	int koeficijent;
	pozicija next;
}polinom;

pozicija inicijalizacija(pozicija);
int procitajIzDatoteke(pozicija, pozicija, char*);
pozicija stvoriPolinom(int, int);
int zbrojiPolinome(pozicija, pozicija, pozicija);
int pomnoziPolinome(pozicija, pozicija, pozicija);
int ispis(pozicija);
int oslobodiMemoriju(pozicija);

int main()
{
	char imeDat[40] = { 0 };
	int zbroj = 0, umnozak = 0;
	pozicija head1 = NULL, head2 = NULL, headZbr = NULL, headUmn = NULL; //head1=polinom1, head2=polinom2

	head1 = inicijalizacija(head1);
	head2 = inicijalizacija(head2);
	headZbr = inicijalizacija(headZbr);
	headUmn = inicijalizacija(headUmn);

	printf("Unesi ime datoteke iz koje ces citati polinome: ");
	scanf(" %s", imeDat);

	procitajIzDatoteke(head1, head2, imeDat);

	zbrojiPolinome(head1, head2, headZbr);

	pomnoziPolinome(head1, head2, headUmn);

	printf("Zbroj: ");
	ispis(headZbr->next);

	printf("\nUmnozak: ");
	ispis(headUmn->next);

	oslobodiMemoriju(headZbr);
	ispis(headZbr->next);

	oslobodiMemoriju(headUmn->next);
	ispis(headUmn->next);

	return 0;
}

pozicija inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(polinom));

	if (!p)
	{
		printf("Greska u inicijalizaciji!\n");
		return NULL;
	}

	p->eksponent = 0;
	p->koeficijent = 0;
	p->next = NULL;

	return p;
}

int procitajIzDatoteke(pozicija p1, pozicija p2, char* imeDat)
{
	char prviBuffer[1024] = { 0 };
	char drugiBuffer[1024] = { 0 };
	char* pok1 = prviBuffer;
	char* pok2 = drugiBuffer;
	int n = 0, koef = 0, eksp = 0;
	int provjera = 0;

	FILE* fp = NULL;
	fp = fopen(imeDat, "r");

	if (!fp)
	{
		printf("Greska u ucitavanju datoteke!\n");
		return -1;
	}

	fgets(prviBuffer, 1024, fp);
	pok1 = prviBuffer;

	fgets(drugiBuffer, 1024, fp);
	pok2 = drugiBuffer;

	while (strlen(pok1) > 0)
	{
		provjera = sscanf(fp, " %d %d %n", &koef, &eksp, &n);

		if (provjera != 2)
		{
			printf("GRESKA!\n");
			return -1;
		}

		p1 = stvoriPolinom(koef, eksp);

		pok1 += n;
	}

	while (strlen(pok2) > 0)
	{
		provjera = sscanf(fp, " %d %d %n", &koef, &eksp, &n);

		if (provjera != 2)
		{
			printf("GRESKA!\n");
			return -1;
		}

		p2 = stvoriPolinom(koef, eksp);

		pok2 += n;
	}

	fclose(fp);

	return 0;
}


pozicija stvoriPolinom(int koef, int eksp)
{
	pozicija q = NULL;
	q = inicijalizacija(q);

	q->koeficijent = koef;
	q->eksponent = eksp;

	return q;
}

/*int zbrojiPolinome(pozicija p1, pozicija p2, pozicija zbroj)  NE RADI
{

	pozicija rez = NULL;

	//ako je polinom 2 null, zbroj je polinom 1
	if (p1 != NULL && p2 == NULL)
	{
		zbroj = p1;
		return zbroj;
	}

	//ako je polinom 1 null, zbroj je polinom 2
	if (p1 == NULL && p2 != NULL)
	{
		zbroj = p2;
		return zbroj;

	}

	//ako su oba polinoma != NULL
	while (p1 != NULL && p2 != NULL)
	{
		if (zbroj == NULL)
		{
			rez = zbroj;
		}

		else
		{
			rez = rez->next;
		}

		if (p1->eksponent > p2->eksponent)
		{
			rez->koeficijent = p1->koeficijent;
			rez->eksponent = p1->eksponent;
			p1 = p1->next;
		}

		else if (p1->eksponent < p2->eksponent)
		{
			rez->koeficijent = p2->koeficijent;
			rez->eksponent = p2->eksponent;
			p2 = p2->next;
		}

		else if (p1->eksponent == p2->eksponent)
		{
			rez->koeficijent = p1->koeficijent + p2->koeficijent;
			rez->eksponent = p1->eksponent;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	while (p1 != NULL)
	{
		rez = rez->next;
		rez->koeficijent = p1->koeficijent;
		rez->eksponent = p1->eksponent;
		p1 = p1->next;
	}

	while (p2 != NULL)
	{
		rez = rez->next;
		rez->koeficijent = p2->koeficijent;
		rez->eksponent = p2->eksponent;
		p2 = p2->next;

	}

	rez->next = NULL;

	return zbroj;
}*/

int zbrojiPolinome(pozicija p1, pozicija p2, pozicija p3)
{
	p1 = p1->next;
	p2 = p2->next;
	p3 = p3->next;
	pozicija q = NULL;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->eksponent == p2->eksponent)
		{
			q = stvoriPolinom(p1->koeficijent + p2->koeficijent, p1->eksponent);
			p1 = p1->next;
			p2 = p2->next;
			p3->next = q;
			q = p3->next;
		}

		else if (p1->eksponent > p2->eksponent)
		{
			q = stvoriPolinom(p1->koeficijent, p1->eksponent);
			p1 = p1->next;
			p3->next = q;
			q = p3->next;
		}

		else if (p1->eksponent < p2->eksponent)
		{
			q = stvoriPolinom(p2->koeficijent, p2->eksponent);
			p2 = p2->next;
			p3->next = q;
			q = p3->next;
		}
	}

	while (p1 != NULL)
	{
		q = stvoriPolinom(p1->koeficijent, p1->eksponent);
		p1 = p1->next;
		p3->next = q;
		q = p3->next;
	}

	while (p2 != NULL)
	{
		q = stvoriPolinom(p2->koeficijent, p2->eksponent);
		p2 = p2->next;
		p3->next = q;
		q = p3->next;
	}


	return 0;
}



int pomnoziPolinome(pozicija p1, pozicija p2, pozicija umnozak)
{
	p1 = p1->next;
	p2 = p2->next;
	pozicija temp = NULL;

	while (p1 != NULL)
	{
		while (p2 != NULL)
		{
			temp = inicijalizacija(temp);
			temp->koeficijent = p1->koeficijent * p2->koeficijent;
			temp->eksponent = p1->eksponent + p1->eksponent;
			zbrojiPolinome(p1, p2, umnozak);

			p2 = p2->next;
		}

		p1 = p1->next;
	}

	return 0;
}

int ispis(pozicija p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
		return -1;
	}

	while (p != NULL)
	{
		printf("%d^%d\n", p->koeficijent, p->eksponent);
		p = p->next;
	}

	return 0;
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

	return 0;
}