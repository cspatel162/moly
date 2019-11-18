// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#include "Header.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

struct actioncard *actioncards;
int number_actioncards;


int fetch_actioncards(void)
{
	//Ermitteln der Zeilenanzahl
	int zeilenanzahl = 0;
	FILE *file;
	file = fopen("actioncards.txt", "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", "actioncards.txt");
		return 1;
	}
	char zw[500];
	while (!feof(file))
	{
		fgets(zw, 500, file);
		zeilenanzahl++;
	}
	zeilenanzahl = zeilenanzahl - 1;
	fclose(file);

	//Reservieren des Speicherplatzes für den Heap (für alle Straßendaten)
	actioncards = calloc(zeilenanzahl, sizeof(struct actioncard));
	if (actioncards == 0) { printf("Nicht genügend Speicherplatz vorhanden!\n"); return 1; }
	//Daten einlesen
	file = fopen("actioncards.txt", "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", "actioncards.txt");
		return 2;
	}

	int zaehler = 0;
	char datensatz[500];
	char delimiter[] = ",;";
	char *ptr;

	//Einlesen aller Aktionskarten
	while (!feof(file))
	{
		//Zeile einlesen
		fgets(datensatz, 500, file);

		//Einlesen Titel
		ptr = strtok(datensatz, delimiter);
		strcpy(actioncards[zaehler].title, ptr);
		//printf("Titel: %s", ptr);
		//Einlesen des Textes
		for (int i = 0; i <= 199; i++) { actioncards[zaehler].text[i] = ' '; }
		ptr = strtok(NULL, delimiter);
		strcpy(actioncards[zaehler].text, ptr);
		//Einlesen Wert gegner_minus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].gegner_minus = atoi(ptr);
		//Einlesen Wert gegner_plus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].gegner_plus = atoi(ptr);
		//Einlesen Wert player_minus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].player_minus = atoi(ptr);
		//Einlesen Wert player_plus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].player_plus = atoi(ptr);
		//printf("Daten eingelesen: %c", actioncards[zaehler].text[0]);
		zaehler++;
	}
	number_actioncards = zeilenanzahl;
	fclose(file);
	return 0;
}


int actioncards_play(int person)
{	

	if (person == 1)
	{ 
		//zufällige aktionsarte ziehen
		int id = wuerfel(0, number_actioncards);  //es wird mit der Random/Wuerfel funktion aus dem Modul Spielmechanik gearbeitet
		
		money_player = money_player + actioncards[id].player_plus - actioncards[id].player_minus;
		money_ki = money_ki + actioncards[id].gegner_plus - actioncards[id].gegner_minus;
		return 0;
	}


	//wenn KI/Gegner Karte bekommt

	if (person == 2)
	{
		//zufällige Aktionskarten ziehen
		
		int id = wuerfel(0,number_actioncards);  //es wird mit der Random/Wuerfel funktion aus dem Modul Spielmechanik gearbeitet

		money_ki = money_player + actioncards[id].player_plus - actioncards[id].player_minus;
		money_player = money_ki + actioncards[id].gegner_plus - actioncards[id].gegner_minus;
		return 0;
	}

	//falls eine falsche person übergeben wurde

	return 1;
}