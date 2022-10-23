#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*2. Definirati strukturu osoba (ime, prezime, godina rodenja) i napisati program koji:
A. dinamicki dodaje novi element na pocetak liste,
B. ispisuje listu,
C. dinamicki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. brise odredeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba
{
	char ime[50];
	char prezime[50];
	int godinaR;
	pozicija next;
}osoba;

pozicija inicijalizacija(pozicija);
int dodajNaPocetak(pozicija);
int dodajNaKraj(pozicija);
int ispis(pozicija);
int pronadjiPoPrez(pozicija);
int izbrisi(pozicija);
pozicija pronadjiPrethodni(pozicija,char*);
int oslobodiMemoriju(pozicija);


int main()
{
	pozicija head = NULL;
	int izbor = 0, uvjet = 1;

	head = inicijalizacija(head);
	

	while (uvjet)
	{
		printf("Unesi 1 za dodavanje elementa na pocetak liste, 2 za ispis, 3 za dodavanje na kraj, 4 za pronaci prezime i 5 za izbrisati element iz liste,");
		printf("6 za izlaz iz petlje: \n");
		scanf("%d", &izbor);

		switch (izbor) {
			
			case 1:
				dodajNaPocetak(head);
				break;
		
			case 2:
				ispis(head->next);
				break;

			case 3:
				dodajNaKraj(head);
				break;

			case 4:
				pronadjiPoPrez(head->next);
				break;

			case 5:
				izbrisi(head);
				break;

			case 6:
				uvjet = 0;
				break;
		}
	}
	
	printf("\n...OSLOBODANJE MEMORIJE...\n");
	oslobodiMemoriju(head);
	ispis(head->next);

	

	return 0;
}

pozicija inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(osoba));

	if (p == NULL)
	{
		printf("Greska u inicijalizaciji!\n");
		return NULL;
	}

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	p->godinaR = 0;
	p->next = NULL;

	return p;
}

int dodajNaPocetak(pozicija p)
{
	pozicija q = NULL;
	q = inicijalizacija(q);
	if (q == NULL)
	{
		printf("Greska u inicijalizaciji!\n");
		return -1;
	}

	printf("\nUnesi ime: ");
	scanf(" %s", q->ime);
	printf("\nUnesi prezime: ");
	scanf(" %s", q->prezime);
	printf("\nUnesi godinu rodjenja: ");
	scanf("%d", &q->godinaR);

	puts("\n");
	q->next = p->next;
	p->next = q;

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
		printf("%s %s %d\n", p->ime, p->prezime, p->godinaR);
		p = p->next;
	}

	return 0;
}

int dodajNaKraj(pozicija p)
{
	pozicija q = NULL;
	q = inicijalizacija(q);

	if (q == NULL)
	{
		printf("Greska u inicijalizaciji!\n");
		return -1;
	}

	while (p->next != NULL)
	{
		p = p->next;
	}

	printf("Unesi ime: ");
	scanf(" %s", q->ime);
	printf("\nUnesi prezime: ");
	scanf(" %s", q->prezime);
	printf("\nUnesi godinu rodjenja: ");
	scanf("%d", &q->godinaR);


	q->next = p->next;
	p->next = q;


	return 0;
}

int pronadjiPoPrez(pozicija p)
{
	char trazenoPrezime[40] = { 0 };
	printf("Unesi prezime koje zelis naci: \n");
	scanf(" %s", trazenoPrezime);
	
	while (p != NULL && strcmp(p->prezime, trazenoPrezime) != 0)
	{
		p = p->next;
	}

	if (p == NULL)
	{
		printf("Nema osobe s tim prezimenom!\n");
	}

	else
	{
		printf("Adresa trazene osobe: %p\n", p);
	}


	return 0;
}

pozicija pronadjiPrethodni(pozicija p, char* prezime)
{
	pozicija prethodni = NULL;
	pozicija trenutni = NULL;

	prethodni = p;
	trenutni = p->next;

	while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0)
	{
		prethodni = trenutni;
		trenutni = prethodni->next;
	}

	if (trenutni == NULL)
	{
		return NULL;
	}

	else
		return prethodni;
}


int izbrisi(pozicija p)
{
	pozicija prethodni = NULL;
	pozicija trenutni = NULL;
	char prezimeZaBrisanje[40] = { 0 };

	printf("Unesi prezime koje zelis izbrisati: ");
	scanf(" %s", prezimeZaBrisanje);

	prethodni = pronadjiPrethodni(p, prezimeZaBrisanje);
	if (prethodni == NULL)
	{
		printf("Osoba s tim prezimenom ne postoji!\n");
		return -1;
	}

	trenutni = prethodni->next;
	prethodni->next = trenutni->next;
	free(trenutni);

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