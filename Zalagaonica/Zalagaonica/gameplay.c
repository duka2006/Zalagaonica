#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

// Cijene predmeta (osnovne vrijednosti)
const float OSNOVNE_CIJENE[] = {
    500.0f,   // SAT
    300.0f,   // NARUKNICA
    1500.0f,  // SLIKA
    800.0f,   // TELEFON
    1200.0f,  // LAPTOP
    450.0f,   // GITARA
    700.0f,   // BICIKL
    2000.0f   // ZLATO
};

void PozoviKupce(int dan, int* balans, Skladiste* skladiste) {
    if (*balans < 0)
    {
        return 0;
    }

    int broj_kupaca = 1 + (dan - 1);// 3 prvog dana, +1 svaki sljedeci
    if (dan > 10) broj_kupaca = 10;
    
    printf("\n=== KUPCI NA DAN %d ===\n", dan);
    for (int i = 0; i < broj_kupaca; i++) {
        VRSTA_PREDMETA vrsta = (VRSTA_PREDMETA)(rand() % BROJ_VRSTA);
        STANJE stanje = (STANJE)(rand() % 3);
        float osnovna_cijena = OSNOVNE_CIJENE[vrsta];
        float kupac_cijena = osnovna_cijena * DohvatiFaktorStanja(stanje) * (0.7f + (rand() % 60) / 100.0f);
        
        printf("\nKupac %d nudi: %s (%s) za %.2f. Kupi? (Y/N): ", 
               i + 1, 
               DohvatiNazivVrste(vrsta),
               DohvatiNazivStanja(stanje),
               kupac_cijena);
        
        char odluka;
        do {
            scanf(" %c", &odluka);
        } while (odluka != 'Y' && odluka != 'y' && odluka != 'N' && odluka != 'n');
        
        if (odluka == 'Y' || odluka == 'y') {
            if (*balans >= kupac_cijena) {
                *balans -= (int)kupac_cijena;
                
                Predmet novi_predmet = {
                    .vrsta = vrsta,
                    .osnovna_cijena = 0.0f,  // Ne poznaje se još
                    .stanje = stanje,
                    .prodajna_cijena = 0.0f,  // Još nije postavljena
                    .dan_dobavljen = dan
                };
                DodajPredmet(skladiste, novi_predmet);
                
                printf("Kupio si predmet! Trenutni balans: %d\n", *balans);
            } else {
                printf("Nemas dovoljno novca!\n");
            }
        }
    }
}

void SimulirajProdaju(int* balans, Skladiste* skladiste) {
    printf("\n=== PRODAJA TOKOM NOCI ===\n");
    if (skladiste->broj_predmeta == 0) {
        printf("Nema predmeta za prodaju.\n");
        return;
    }
    
    int prodano = 0;
    for (int i = skladiste->broj_predmeta - 1; i >= 0; i--) {
        Predmet* predmet = &skladiste->predmeti[i];
        
        if (predmet->prodajna_cijena <= 0) continue;  // Cijena nije postavljena
        
        float realna_vrijednost = predmet->osnovna_cijena * DohvatiFaktorStanja(predmet->stanje);
        float omjer = realna_vrijednost / predmet->prodajna_cijena;
        
        // Šansa za prodaju: 100% ako je cijena <= realnoj vrijednosti
        // Smanjuje se kvadratično kako cijena raste
        float sansa = (omjer >= 1.0f) ? 1.0f : omjer * omjer;
        
        if ((rand() % 100) < (sansa * 100)) {
            *balans += (int)predmet->prodajna_cijena;
            printf("Prodan %s za %.2f! (+%.2f)\n", 
                   DohvatiNazivVrste(predmet->vrsta),
                   predmet->prodajna_cijena,
                   predmet->prodajna_cijena);
            
            UkloniPredmet(skladiste, i);
            prodano++;
        }
    }
    
    if (prodano == 0) {
        printf("Nista se nije prodalo.\n");
    }
    printf("Novi balans: %d\n", *balans);

    if (*balans <= 0)
    {
        printf("Bankrotirao si!\n");
    }
}

void PostaviCijenu(Skladiste* skladiste) {
    IspisiSkladiste(skladiste);
    if (skladiste->broj_predmeta == 0) return;
    
    printf("\nOdaberi redni broj predmeta: ");
    int index;
    scanf("%d", &index);
    index--;  // Pretvori u indeks
    
    if (index < 0 || index >= skladiste->broj_predmeta) {
        printf("Neispravan odabir!\n");
        return;
    }
    
    printf("Unesi novu cijenu: ");
    float nova_cijena;
    scanf("%f", &nova_cijena);
    
    if (nova_cijena > 0) {
        skladiste->predmeti[index].prodajna_cijena = nova_cijena;
        printf("Cijena postavljena!\n");
    } else {
        printf("Neispravna cijena!\n");
    }
}

void PozoviStrucnjaka(Skladiste* skladiste) {
    IspisiSkladiste(skladiste);
    if (skladiste->broj_predmeta == 0) return;
    
    printf("\nOdaberi redni broj predmeta za procjenu: ");
    int index;
    scanf("%d", &index);
    index--;  // Pretvori u indeks
    
    if (index < 0 || index >= skladiste->broj_predmeta) {
        printf("Neispravan odabir!\n");
        return;
    }
    
    Predmet* predmet = &skladiste->predmeti[index];
    predmet->osnovna_cijena = OSNOVNE_CIJENE[predmet->vrsta];
    
    printf("\nStrucnjak kaze:\n");
    printf("Vrsta: %s\n", DohvatiNazivVrste(predmet->vrsta));
    printf("Stanje: %s\n", DohvatiNazivStanja(predmet->stanje));
    printf("Osnovna vrijednost: %.2f\n", predmet->osnovna_cijena);
    printf("Trenutna vrijednost: %.2f\n", 
           predmet->osnovna_cijena * DohvatiFaktorStanja(predmet->stanje));
}