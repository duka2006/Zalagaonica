#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include "gameplay.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Objasnjenje()
{
	printf("Ovo je tvoj 1. dan kao sluzbeni vlasnik vlastite zalagaonice.\n");
	printf("Tvoj pocetni balans je: 1000\n");
	printf("Cilj je procijeniti predmete koji tvoji kupci donose i pretpostaviti cijenu za njih.");
	printf("Mozes dovesti jednog strucnjaka dnevno, te svaki predmet koji procijenis ce biti TRAJNO memoriziran u tvojem sustavu(s komandom LIST dohvacas sve poznate predmete).\n");
	printf("Takoder predmeti mogu doci u razlicitim stanjima: novo, rabljeno i potrgano. Ovisno o stanju i vrsti predmeta, predmet moze znatno izgubiti monetarnu vrijednost.\n");
	printf("Ako slucajno zaboravis kako glase komande, u bilo kojem trenutku mozes pozvati komandu HELP\n");
	printf("Ovo su sve informacije koje trebas znati za pocetak.");
	printf("Sretno!\n");
}
void StartUpit()
{
	printf("Zapocni novu partiju?(Ako ne zapocnes novu, ucitat ce se podatci iz prijasnjeg filea)(Y/N)");
	char unos;
	do
	{
		scanf("%c", &unos);
	} while (unos != 'Y' && unos != 'N');
	if (unos == 'Y')
	{
		StartNew();
	}
	else
	{
		StartSave();
	}
}


KOMANDA DohvatiKomandu(const char* str) {
	if (strcmp(str, "HELP") == 0) return HELP;
	else if (strcmp(str, "SAVE") == 0) return SAVE;
	else if (strcmp(str, "LIST") == 0) return LIST;
	else if (strcmp(str, "INSPECT") == 0) return LIST;
	else return DEFAULT;
}

void Komanda(int balans, int dan) {
	printf("\nUpisi komandu(HELP): ");
	char input[10];
	scanf("%s", input);

	switch (DohvatiKomandu(input)) {
	case HELP:
		KomandaHelp();
		break;
	case LIST:
		break;
	case SAVE:
		KomandaSave(balans, dan);
		break;
	case DEFAULT:
		printf("\nNe poznajem ovu komandu");
		break;
	}
	Komanda(balans, dan);
}
void StartNew()
{

	int balans = 1000;
	int dan = 1;
	PozoviKupce(dan);
	Komanda(balans,dan);
}
void StartSave()
{
	int balans = 0;
	int dan = 0;
	UcitajData(&balans, &dan);
	printf("\nPodatci su: BALANS = %d, DAN=%d", balans, dan);
}
void KomandaHelp()
{
	printf("\nHELP - prikazuje listu svih komandi");
	printf("\nLIST - prikazuju sve objekte u skladistu");
	printf("\nSAVE - sacuva trenutne podatke potrebne za igru");
	printf("\nINSPECT - zove strucnjaka koji procijenjuje objekt");
}
void KomandaSave(int balans, int dan)
{
	FILE* fp = NULL;
	fp = fopen("data.txt", "w");
	fprintf(fp, "balans = %d\n", balans);
	fprintf(fp, "dan = %d\n", dan);
	printf("Uspjesno sacuvao");
	fclose(fp);
}
void UcitajData(int* balans, int* dan)
{
	FILE* fp = NULL;
	fp = fopen("data.txt", "r");
	char linija[20];
	char kljuc[20];
	int vrijednost;
	while (fgets(linija, sizeof(linija), fp)) {
		if (sscanf(linija, "%s = %d", kljuc, &vrijednost) == 2) {
			char* jednakost = strchr(kljuc, '=');
			if (jednakost) *jednakost = '\0';
			
			if (strcmp(kljuc, "balans") == 0)
			{
				*balans = vrijednost;
				printf("%d", *balans);
			}
			if (strcmp(kljuc, "dan") == 0)
			{
				*dan = vrijednost;
			}
			
		}
	}
	fclose(fp);
}
