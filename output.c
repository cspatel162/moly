// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#include "Header.h"
#include <stdio.h>
#include<Windows.h>

//Lokale Prototypen
//Funktionen die nur in diesem Modul aufgerufen werden können und müssen.
int show_file(char[]);


int show_file(char filename[15])
{
	char zeile[200];
	FILE *file;

	printf("\n");

	file = fopen(filename, "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s geoeffnet werden.", filename);
		return 1;
	}

	while (!feof(file))
	{
		fgets(zeile, 200, file);
		printf("%s", zeile);
	}
	printf("\n");
	fclose(file);
	return 0;
}

int matchfield_update(void)
{

}

int output_field(struct field *ptr)
{
	
}