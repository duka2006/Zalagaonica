#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int main(void) {
	srand((unsigned int)time(NULL));
    
	printf("Zelis li objasnjenje igre? (Y/N): ");
	char unos;
	do {
		scanf(" %c", &unos);
	} while (unos != 'Y' && unos != 'N' && unos != 'y' && unos != 'n');
    
	if (unos == 'Y' || unos == 'y') {
		Objasnjenje();
	}
    
	StartUpit();
	return 0;
}