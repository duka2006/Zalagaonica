#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Objasnjenje(void);
void StartUpit(void);
void StartNew(void);
void StartSave(void);
void Komanda(int, int);
void KomandaHelp(void);
void KomandaSave(int, int);
void UcitajData(int*, int*);

typedef enum {
	LIST,
	HELP,
	SAVE,
	DEFAULT
} KOMANDA;