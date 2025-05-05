#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void Objasnjenje()
{
	printf("Ovo je tvoj 1. dan kao sluzbeni vlasnik vlastite zalagaonice.\n");
	printf("Tvoj pocetni balans je: 1000\n");
	printf("Cilj je procijeniti predmete koji tvoji kupci donose i pretpostaviti cijenu za njih.");
	printf("Mozes dovesti jednog strucnjaka dnevno, te svaki predmet koji procijenis ce biti TRAJNO memoriziran u tvojem sustavu(s komandom LISTA dohvacas sve poznate predmete).\n");
	printf("Takoder predmeti mogu doci u razlicitim stanjima: novo, rabljeno i potrgano. Ovisno o stanju i vrsti predmeta, predmet moze znatno izgubiti monetarnu vrijednost.\n");
	printf("Ako slucajno zaboravis kako glase komande, u bilo kojem trenutku mozes pozvati komandu HELP\n");
	printf("Ovo su sve informacije koje trebas znati za pocetak.");
	printf("Sretno!");
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
		StartOld();
	}
}
void StartNew()
{
	int balans = 1000;

}
void StartOld()
{

}
