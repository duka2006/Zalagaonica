#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

void Objasnjenje() {
    printf("\nOvo je tvoj 1. dan kao sluzbeni vlasnik vlastite zalagaonice.\n");
    printf("Tvoj pocetni balans je: 1000\n");
    printf("Cilj je procijeniti predmete koje kupci donose i postaviti prodajne cijene.\n");
    printf("Mozes dovesti jednog strucnjaka dnevno, a svaki predmet koji procijenis bit ce memoriziran.\n");
    printf("Predmeti mogu biti u razlicitim stanjima: novo, rabljeno i potrgano.\n");
    printf("Ovisno o stanju, predmet gubi vrijednost: novo=100%%, rabljeno=70%%, potrgano=50%%.\n");
    printf("Komande: HELP (pomoc), LIST (skladiste), SETPRICE (postavi cijenu), INSPECT (strucnjak), SAVE (spremi), ENDDAY (zavrsi dan)\n");
    printf("Sretno!\n\n");
}

void StartUpit() {
    printf("\nZapocni novu partiju? (Y/N): ");
    char unos;
    do {
        scanf(" %c", &unos);
    } while (unos != 'Y' && unos != 'N' && unos != 'y' && unos != 'n');
    
    if (unos == 'Y' || unos == 'y') {
        StartNew();
    } else {
        StartSave();
    }
}

KOMANDA DohvatiKomandu(const char* str) {
    if (strcmp(str, "HELP") == 0) return HELP;
    else if (strcmp(str, "SAVE") == 0) return SAVE;
    else if (strcmp(str, "LIST") == 0) return LIST;
    else if (strcmp(str, "INSPECT") == 0) return INSPECT;
    else if (strcmp(str, "SETPRICE") == 0) return SETPRICE;
    else if (strcmp(str, "ENDDAY") == 0) return ENDDAY;
    else return DEFAULT;
}

void Komanda(int* balans, int* dan, Skladiste* skladiste) {
    printf("\n[Dan %d, Balans: %d] Unesi komandu (HELP za pomoc): ", *dan, *balans);
    char input[20];
    scanf("%s", input);

    switch (DohvatiKomandu(input)) {
    case HELP:
        KomandaHelp();
        break;
    case LIST:
        IspisiSkladiste(skladiste);
        break;
    case SAVE:
        KomandaSave(*balans, *dan, skladiste);
        break;
    case INSPECT:
        PozoviStrucnjaka(skladiste);
        break;
    case SETPRICE:
        PostaviCijenu(skladiste);
        break;
    case ENDDAY:
        (*dan)++;
        *balans -= 100;  // Dnevni troškovi
        if (*balans < 0)
        {
            GameEnd(dan);
            return;
        }  
        else
        {
            SimulirajProdaju(balans, skladiste);
            PozoviKupce(*dan, balans, skladiste);
            break;
        }
    case DEFAULT:
        printf("\nNepoznata komanda: %s", input);
        break;
    }
    Komanda(balans, dan, skladiste);
}

void KomandaHelp() {
    printf("\nDostupne komande:");
    printf("\nHELP   - Prikazi ove informacije");
    printf("\nLIST   - Prikazi sve predmete u skladistu");
    printf("\nSAVE   - Spremi trenutno stanje igre");
    printf("\nINSPECT- Pozovi strucnjaka za procjenu predmeta");
    printf("\nSETPRICE - Postavi cijenu za predmet");
    printf("\nENDDAY - Zavrsi dan i nastavi na sljedeci\n");
}

void KomandaSave(int balans, int dan, const Skladiste* skladiste) {
    FILE* fp = fopen("savegame.dat", "wb");
    if (fp) {
        // Spremi balans i dan
        fwrite(&balans, sizeof(int), 1, fp);
        fwrite(&dan, sizeof(int), 1, fp);
        
        // Spremi skladište
        SpremiSkladiste(fp, skladiste);
        fclose(fp);
        printf("\nIgra uspjesno spremljena!\n");
    } else {
        perror("\nGreska pri spremanju");
    }
}

void StartNew() {
    int balans = 1000;
    int dan = 1;
    Skladiste skladiste;
    InicijalizirajSkladiste(&skladiste);

    PozoviKupce(dan, &balans, &skladiste);
    Komanda(&balans, &dan, &skladiste);
    OslobodiSkladiste(&skladiste);
}

void StartSave() {
    int balans = 0;
    int dan = 0;
    Skladiste skladiste;
    InicijalizirajSkladiste(&skladiste);
    
    UcitajData(&balans, &dan, &skladiste);
    printf("\nUcitano: Balans=%d, Dan=%d", balans, dan);
    IspisiSkladiste(&skladiste);
    
    Komanda(&balans, &dan, &skladiste);
    OslobodiSkladiste(&skladiste);
}

void UcitajData(int* balans, int* dan, Skladiste* skladiste) {
    FILE* fp = fopen("savegame.dat", "rb");
    if (fp) {
        // Učitaj balans i dan
        fread(balans, sizeof(int), 1, fp);
        fread(dan, sizeof(int), 1, fp);
        
        // Učitaj skladište
        UcitajSkladiste(fp, skladiste);
        fclose(fp);
    } else {
        perror("\nGreska pri ucitavanju");
        *balans = 1000;
        *dan = 1;
    }
}

const char* DohvatiNazivVrste(VRSTA_PREDMETA vrsta) {
    const char* nazivi[] = {
        "Sat", "Naruknica", "Slika", "Telefon",
        "Laptop", "Gitara", "Bicikl", "Zlato"
    };
    return nazivi[vrsta];
}

const char* DohvatiNazivStanja(STANJE stanje) {
    switch (stanje) {
        case NOVO: return "Novo";
        case RABLJENO: return "Rabljeno";
        case POTRGANO: return "Potrgano";
        default: return "Nepoznato";
    }
}

float DohvatiFaktorStanja(STANJE stanje) {
    switch (stanje) {
        case NOVO: return 1.0f;
        case RABLJENO: return 0.7f;
        case POTRGANO: return 0.5f;
        default: return 0.0f;
    }
}

void InicijalizirajSkladiste(Skladiste* skladiste) {
    skladiste->broj_predmeta = 0;
    skladiste->kapacitet = 10;
    skladiste->predmeti = (Predmet*)malloc(skladiste->kapacitet * sizeof(Predmet));
}

void ProsiriSkladiste(Skladiste* skladiste) {
    skladiste->kapacitet *= 2;
    skladiste->predmeti = (Predmet*)realloc(skladiste->predmeti, skladiste->kapacitet * sizeof(Predmet));
}

void OslobodiSkladiste(Skladiste* skladiste) {
    free(skladiste->predmeti);
    skladiste->predmeti = NULL;
    skladiste->broj_predmeta = 0;
    skladiste->kapacitet = 0;
}

void DodajPredmet(Skladiste* skladiste, Predmet predmet) {
    if (skladiste->broj_predmeta >= skladiste->kapacitet) {
        ProsiriSkladiste(skladiste);
    }
    skladiste->predmeti[skladiste->broj_predmeta++] = predmet;
}

void UkloniPredmet(Skladiste* skladiste, int index) {
    if (index < 0 || index >= skladiste->broj_predmeta) return;
    
    for (int i = index; i < skladiste->broj_predmeta - 1; i++) {
        skladiste->predmeti[i] = skladiste->predmeti[i + 1];
    }
    skladiste->broj_predmeta--;
}

void IspisiPredmet(const Predmet* predmet) {
    float trenutna_vrijednost = predmet->osnovna_cijena * DohvatiFaktorStanja(predmet->stanje);
    printf("%-10s | %-10s | Osnovna: %-6.2f | Stanje: %-8s | Prodajna: %-6.2f | Vrijednost: %-6.2f",
           DohvatiNazivVrste(predmet->vrsta),
           (predmet->osnovna_cijena > 0) ? "Poznat" : "Nepoznat",
           predmet->osnovna_cijena,
           DohvatiNazivStanja(predmet->stanje),
           predmet->prodajna_cijena,
           trenutna_vrijednost);
}

void IspisiSkladiste(const Skladiste* skladiste) {
    if (skladiste->broj_predmeta == 0) {
        printf("\nSkladiste je prazno!\n");
        return;
    }
    
    printf("\n=== SKLADISTE ===\n");
    for (int i = 0; i < skladiste->broj_predmeta; i++) {
        printf("%d. ", i + 1);
        IspisiPredmet(&skladiste->predmeti[i]);
        printf("\n");
    }
}

void SpremiSkladiste(FILE* fp, const Skladiste* skladiste) {
    fwrite(&skladiste->broj_predmeta, sizeof(int), 1, fp);
    for (int i = 0; i < skladiste->broj_predmeta; i++) {
        fwrite(&skladiste->predmeti[i], sizeof(Predmet), 1, fp);
    }
}

void UcitajSkladiste(FILE* fp, Skladiste* skladiste) {
    fread(&skladiste->broj_predmeta, sizeof(int), 1, fp);
    skladiste->kapacitet = skladiste->broj_predmeta + 5;
    skladiste->predmeti = (Predmet*)malloc(skladiste->kapacitet * sizeof(Predmet));
    fread(skladiste->predmeti, sizeof(Predmet), skladiste->broj_predmeta, fp);
}
void GameEnd(int* dan)
{
    printf("Bankrotirao si!\n");
    printf("Poslovao si %d dana.\n", *dan);
    printf("Hvala na igranju!");
}