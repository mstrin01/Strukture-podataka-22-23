#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

#define MAX_LINE 1024
#define MAX_SIZE 128
#define EXIT_SUCCESS 1
#define EXIT_FAILURE -1 

/* Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100 */

struct _student;
typedef struct _student
{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int bodovi;
}student;

int procitajBrSt(char*);
student* alokacijaSt(char*, int);

int main()
{
	student* st = NULL;
	int bodoviSt = 0, brojStudenata = 0;
	float relativniBodovi[MAX_SIZE];
	char dat[MAX_SIZE] = "rez.txt";


	brojStudenata = procitajBrSt(dat);
	printf("Broj studenata u datoteci: %d\n", brojStudenata);

	st = alokacijaSt(dat, brojStudenata);

	printf("\nIspis podataka o studentima:\n");
	printf("IME PREZIME BODOVI  \n ");

	for (int i = 0; i < brojStudenata; i++)
	{
		printf("%s %s %d\n", st[i].ime, st[i].prezime, st[i].bodovi);

	}

	printf("\nRELATIVNI BODOVI:\n");
	for (int i = 0; i < brojStudenata; i++)
	{
		relativniBodovi[i] = (float)st[i].bodovi / 50 * 100;
		printf("%s %s %f\n", st[i].ime, st[i].prezime, relativniBodovi[i]);
	}

	return EXIT_SUCCESS;
}

int procitajBrSt(char* imeDat)
{
	int brojSt = 0;
	char buffer[MAX_SIZE] = { 0 };

	FILE* fp = NULL;
	fp = fopen(imeDat, "r");

	if (!fp)
	{
		printf("GRESKA U UCITAVANJU DATOTEKE!\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX_SIZE, fp);

		if (strcmp(buffer, "\n") != 0)
			++brojSt;
	}

	fclose(fp);

	return brojSt;
}

student* alokacijaSt(char* dat, int br)
{
	student* studenti = NULL;
	studenti = (student*)malloc(br * sizeof(student));

	int i = 0;

	FILE* fp = NULL;
	fp = fopen(dat, "r");

	if (!fp)
	{
		printf("GRESKA U UCITAVANJU DATOTEKE!\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
		++i;
	}

	fclose(fp);

	return studenti;
}