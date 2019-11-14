// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#include "Header.h"
#include <stdio.h>
#include <string.h>

//Prototypen die nur in diesem Modul zur Verfügung stehen
int fetch_streetdata(void);
void end(void);
int welcome(void);

//int number_street;
struct field *matchfield;
char colour_player;
char colour_ki;
int position_player;
int position_ki;
int money_player;
int money_ki;
char *name_player;

int main()
{
	welcome();
	scanf(" ");
}

int welcome(void)
{
	
	
	show_file("logo.txt");
	printf("Herzlich willkommen bei MOLY, der digitalen Form von Monopoly.\n");
	printf("Bitte Maximiere das Fenster um den besten Ueberblick zu haben!\n\n");
	printf("Geben Sie ihen Nicknamen ein :");
	name_player = calloc(10, sizeof(char));
	scanf(" %s", name_player);
	
	fetch_streetdata("data.txt");
	matchfield_update(NULL);
}

int fetch_streetdata(char filename[])
{
	printf("DAteinname: %s", filename);
	//Ermitteln der Zeilenanzahl
	int zeilenanzahl = 0;
	FILE *file;
	file = fopen(filename, "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", filename);
		return 1;
	}
	char zw[100];
	while (!feof(file))
	{
		fgets(zw, 200, file);
		zeilenanzahl++;		
	}
	zeilenanzahl = zeilenanzahl - 1;
	fclose(file);
	//Reservieren des Speicherplatzes
	matchfield = calloc(zeilenanzahl, sizeof(struct field));
	if (matchfield == 0) { printf("Nicht genügend Speicherplatz vorhanden!\n"); return 1; }
	//Daten einlesen
	file = fopen(filename, "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", "streetdata.txt");
		return 1;
	}

	//Einlesen aller Daten
	int zaehler = 0;
	char datensatz[400];
	char delimiter[] = ",;";
	char *ptr;
	
	//Einlesen Spieldaten
	fgets(datensatz, 400, file);
	ptr = strtok(datensatz, delimiter);
	strcpy(name_player, ptr);

	ptr = strtok(NULL, delimiter);
	money_player = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	money_ki = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	position_player = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	position_ki = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	colour_player = *ptr;
	
	ptr = strtok(NULL, delimiter);
	colour_ki = *ptr;

	
	//Einlesen Strassen
	while (!feof(file))
	{
		struct field zw = *(matchfield + zaehler);
		//Zeile einlesen
		fgets(datensatz, 400, file);
		//printf("Zeile ist: %s\n", datensatz);
		
		ptr = strtok(datensatz, delimiter);
		matchfield[zaehler].owner = atoi(ptr);
		//Einlesen des Namen
		ptr = strtok(NULL, delimiter);
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
	
	number_streets = zeilenanzahl;
	fclose(file);
	return 0;
}

int schreibe_data(void)
{
	for (int i = 0; i <= number_streets; i++)
	{
		printf("Straße  : %s\n", matchfield[i].name);
		printf("Preis   : %i\n", matchfield[i].price);
		printf("Besitzer: %i\n\n", matchfield[i].owner);
	}
}

void end(void)
{
	free(matchfield);
	free(name_player);
	printf("Vielen Dank, dass du mit uns gespielt hast.\Bis zum nächsten mal.");
	scanf(" ");
}


