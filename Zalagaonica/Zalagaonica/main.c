#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	printf("Da li zelis objasnjenje ili ne? (Y/N)");
	char unos;
	do
	{
		scanf("%c", &unos);
	} while (unos != 'Y' && unos != 'N');
	if (unos == 'Y')
	{
		Objasnjenje();
	}
}