#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Enums
typedef enum { 
	LIST, 
	HELP, 
	SAVE, 
	INSPECT, 
	SETPRICE,
	ENDDAY,
	DEFAULT 
} KOMANDA;

typedef enum { 
	NOVO, 
	RABLJENO, 
	POTRGANO 
} STANJE;

typedef enum {
	SAT,
	NARUKNICA,
	SLIKA,
	TELEFON,
	LAPTOP,
	GITARA,
	BICIKL,
	ZLATO,
	BROJ_VRSTA
} VRSTA_PREDMETA;

// Structures
typedef struct {
	VRSTA_PREDMETA vrsta;
	float osnovna_cijena;
	STANJE stanje;
	float prodajna_cijena;
	int dan_dobavljen;
} Predmet;

typedef struct {
	Predmet* predmeti;
	int broj_predmeta;
	int kapacitet;
} Skladiste;

// Function declarations
void Objasnjenje(void);
void StartUpit(void);
void StartNew(void);
void StartSave(void);
void Komanda(int*, int*, Skladiste*);
void KomandaHelp(void);
void KomandaSave(int, int, const Skladiste*);
void UcitajData(int*, int*, Skladiste*);
void PozoviKupce(int, int*, Skladiste*);
void SimulirajProdaju(int*, Skladiste*);
void IspisiSkladiste(const Skladiste*);
void DodajPredmet(Skladiste*, Predmet);
void UkloniPredmet(Skladiste*, int);
void PostaviCijenu(Skladiste*);
void PozoviStrucnjaka(Skladiste*);
void IspisiPredmet(const Predmet*);
const char* DohvatiNazivVrste(VRSTA_PREDMETA vrsta);
const char* DohvatiNazivStanja(STANJE stanje);
float DohvatiFaktorStanja(STANJE stanje);
void InicijalizirajSkladiste(Skladiste*);
void ProsiriSkladiste(Skladiste*);
void OslobodiSkladiste(Skladiste*);
void SpremiSkladiste(FILE*,  const Skladiste*);
void UcitajSkladiste(FILE*, Skladiste*);
void GameEnd(int*);
KOMANDA DohvatiKomandu(const char* str);