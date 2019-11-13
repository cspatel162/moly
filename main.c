// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#include "Header.h"
#include <stdio.h>
#include <string.h>

//Prototypen die nur in diesem Modul zur Verfügung stehen
int fetch_data(void);
void end(void);
int welcome(void);

int number_street;
struct field *matchfield;

int main()
{
	show_file("logo.txt");
	fetch_data();
	schreibe_data();

	scanf(" ");
}

int welcome(void)
{
	
}

int fetch_data(void)
{
	//Ermitteln der Zeilenanzahl
	int zeilenanzahl = 0;
	FILE *file;
	file = fopen("streetdata.txt", "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", "streetdata.txt");
		return 1;
	}
	char zw[100];
	while (!feof(file))
	{
		fgets(zw, 200, file);
		zeilenanzahl++;		
	}
	fclose(file);
	//Reservieren des Speicherplatzes
	matchfield = calloc(zeilenanzahl, sizeof(struct field));
	if (matchfield == 0) { printf("Nicht genügend Speicherplatz vorhanden!\n"); return 1; }
	//Daten einlesen
	file = fopen("streetdata.txt", "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", "streetdata.txt");
		return 1;
	}

	//Einlesen aller Daten
	int zaehler = 0;
	char datensatz[200];
	char delimiter[] = ",;";
	char *ptr;
	while (!feof(file))
	{
		struct field zw = *(matchfield + zaehler);
		//Zeile einlesen
		fgets(datensatz, 200, file);
		//printf("Zeile ist: %s\n", datensatz);

		matchfield[zaehler].owner = 0;
		//Einlesen des Namen
		ptr = strtok(datensatz, delimiter);
		strcpy(matchfield[zaehler].name, ptr);
		//printf("Name     : %s\n", (matchfield+zaehler)->name);
		//Einlesen Farbe
		ptr = strtok(NULL, delimiter);
		matchfield[zaehler].colour = *ptr;
		//printf("Farbe     : %c\n", (matchfield + zaehler)->colour);
		//Einlesen Preis
		ptr = strtok(NULL, delimiter);
		matchfield[zaehler].price = atoi(ptr);
	    //printf("Preis     : %i\n", (matchfield + zaehler)->price);
		//Einlesen Mieten
		for (int i = 0; i <= 6; i++)
		{
			ptr = strtok(NULL, delimiter);
			matchfield[zaehler].rent[i] = atoi(ptr);
			//printf("Miete mit %i Haeusern: %i\n",i , (matchfield + zaehler)->rent[i]);
		}
		//Einlesen Häuser
		ptr = strtok(NULL, delimiter);
		matchfield[zaehler].house = atoi(ptr);
		//printf("Haeuser     : %i\n", (matchfield + zaehler)->house);
		
		zaehler++;
	}
	number_street = zeilenanzahl;
	fclose(file);
	return 0;
}

int schreibe_data(void)
{
	for (int i = 0; i <= number_street-1; i++)
	{
		printf("Straße  : %s\n", matchfield[i].name);
		printf("Preis   : %i\n", matchfield[i].price);
		printf("Besitzer: %i\n\n", matchfield[i].owner);
	}
}

void end(void)
{
	free(matchfield);
	printf("Vielen Dank, dass du mit uns gespielt hast.\Bis zum nächsten mal.");
	scanf(" ");
}


