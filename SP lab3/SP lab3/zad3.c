#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
3. Prethodnom zadatku dodati funkcije:
A. dinamicki dodaje novi element iza odredenog elementa,
B. dinamicki dodaje novi element ispred odredenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. cita listu iz datoteke.
*/

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
pozicija pronadjiPrethodni(pozicija, char*);
int oslobodiMemoriju(pozicija);

//FUNKCIJE 3.ZADATKA:

int dodajIza(pozicija);
int dodajIspred(pozicija);
int sortirajListu(pozicija);
int upisiUDatoteku(pozicija, char*);
int procitajIzDatoteke(pozicija, char*);

int unesiPodatke(pozicija p);

int main()
{
	pozicija head = NULL;
	int izbor = 0, uvjet = 1;
	char imeDat[40] = { 0 };
	char imeDat2[40] = { 0 };
	head = inicijalizacija(head);


	while (uvjet)
	{
		printf("Unesi 1 za dodavanje elementa na pocetak liste, 2 za ispis, 3 za dodavanje na kraj, 4 za pronaci prezime i 5 za izbrisati element iz liste,");
		printf("6 za izlaz iz petlje, ");
		printf("7 za dodati element iza odredjenog, 8 za dodati ispred elementa, 9 za sortirati listu, 10 za upisati u datoteku i 11 za procitati iz datoteke: ");
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

		case 7:
			dodajIza(head);
			break;

		case 8:
			dodajIspred(head);
			break;

		case 9:
			sortirajListu(head);
			break;

		case 10:
			printf("Upisi ime datoteke: ");
			scanf(" %s", imeDat);
			upisiUDatoteku(head->next, imeDat);
			break;

		case 11:
			printf("Upisi ime datoteke: ");
			scanf(" %s", imeDat2);
			procitajIzDatoteke(head, imeDat2);
			break;

		default:
			printf("GRESKA! POKUSAJ PONOVO!\n");
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


int dodajIza(pozicija p)
{
	pozicija q = NULL;
	char prezimeOsobe[40] = { 0 };

	printf("Unesi prezime iza kojeg zelis dodati novu osobu: ");
	scanf(" %s", prezimeOsobe);

	q = inicijalizacija(q);

	while (p->next != NULL && strcmp(p->prezime, prezimeOsobe) != 0)
	{
		p = p->next;
	}



	if (p != NULL)
	{
		unesiPodatke(q);
		q->next = p->next;
		p->next = q;
	}

	return 0;
}


int unesiPodatke(pozicija p)
{
	char novoIme[50] = { 0 }, novoPrezime[50] = { 0 };
	int novaGodinaR = 0;

	printf("Unesi ime osobe koju dodajes: ");
	scanf(" %s", novoIme);
	printf("Unesi prezime osobe koju dodajes: ");
	scanf(" %s", novoPrezime);
	printf("Unesi godinu rodjenja osobe koju dodajes: ");
	scanf("%d", &novaGodinaR);

	strcpy(p->ime, novoIme);
	strcpy(p->prezime, novoPrezime);
	p->godinaR = novaGodinaR;

	return 0;
}


int dodajIspred(pozicija p)
{
	char prez[40] = { 0 };
	pozicija q = NULL;

	printf("Unesi prezime ispred kojeg ces ubaciti element: ");
	scanf(" %s", prez);

	while (p->next != NULL && strcmp(p->next->prezime, prez) != 0)
	{
		p = p->next;
	}

	if (p->next != NULL)
	{
		q = inicijalizacija(q);
		unesiPodatke(q);
		q->next = p->next;
		p->next = q;
	}

	return 0;
}


int sortirajListu(pozicija p)
{
	pozicija a = NULL, b = NULL;
	pozicija pret = NULL, kraj = NULL;
	pozicija pom = NULL;

	for (a = p; a->next != kraj;)
	{
		pret = a;

		for (b = a->next; b->next != kraj; b = b->next)
		{
			if (strcmp(b->prezime, b->next->prezime) > 0)
			{
				pom = b->next;
				pret->next = pom;
				b->next = pom->next;
				pom->next = b;
				b = pom;
			}

			pret = b;
		}

		kraj = b;
	}

	return 0;
}


int upisiUDatoteku(pozicija p, char* imeDat)
{
	FILE* fp = NULL;

	fp = fopen(imeDat, "w");


	if (!fp)
	{
		printf("Greska u ucitavanju datoteke!\n");
		return -1;
	}

	while (p != NULL)
	{
		fprintf(fp, " %s %s %d", p->ime, p->prezime, p->godinaR);
		p = p->next;
	}

	fclose(fp);

	return 0;
}


int procitajIzDatoteke(pozicija p, char* imeDat)
{
	pozicija q = NULL;
	FILE* fp = NULL;
	fp = fopen(imeDat, "r");

	if (!fp)
	{
		printf("Greska u ucitavanju datoteke!\n");
		return -1;
	}


	while (!feof(fp))
	{
		q = inicijalizacija(q);

		fscanf(fp, " %s %s %d", q->ime, q->prezime, &q->godinaR);
		q->next = p->next;
		p->next = q;
	}

	fclose(fp);

	return 0;
}