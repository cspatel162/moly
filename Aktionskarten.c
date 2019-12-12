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

	//Reservieren des Speicherplatzes f�r den Heap (f�r alle Stra�endaten)
	actioncards = calloc(zeilenanzahl, sizeof(struct actioncard));
	if (actioncards == 0) { printf("Nicht gen�gend Speicherplatz vorhanden!\n"); return 1; }
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
		printf("Titel: %s", ptr);
		//Einlesen des Textes
		for (int i = 0; i <= 199; i++) { actioncards[zaehler].text[i] = ' '; }
		ptr = strtok(NULL, delimiter);
		strcpy(actioncards[zaehler].text, ptr);
		printf(" --- Text: %s", ptr);
		//Einlesen Wert gegner_minus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].gegner_minus = atoi(ptr);
		printf(" --- GegnerMinus: %s", ptr);
		//Einlesen Wert gegner_plus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].gegner_plus = atoi(ptr);
		printf(" --- GegnerPlus: %s", ptr);
		//Einlesen Wert player_minus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].player_minus = atoi(ptr);
		printf(" --- PlayerMinus: %s", ptr);
		//Einlesen Wert player_plus
		ptr = strtok(NULL, delimiter);
		actioncards[zaehler].player_plus = atoi(ptr);
		printf(" --- PlayerPlus: %s\n", ptr);
		//printf("Daten eingelesen: %c", actioncards[zaehler].text[0]);
		zaehler++;
	}
	number_actioncards = zeilenanzahl;
	//fclose(file);
	return 0;
}


int actioncards_play(int person, int field_id)
{	

	if (person == 1)
	{ 
		//zuf�llige aktionsarte ziehen
		int zufall = wuerfel(0, number_actioncards);//es wird mit der Random/Wuerfel funktion aus dem Modul Spielmechanik gearbeitet

		money_player[1] = money_player[1] + actioncards[zufall].player_plus - actioncards[zufall].player_minus;
		money_player[2] = money_player[2] + actioncards[zufall].gegner_plus - actioncards[zufall].gegner_minus;
		matchfield_update(field_id, person, zufall);
		return 0;
	}


	//wenn KI/Gegner Karte bekommt

	if (person == 2)
	{
		//zuf�llige Aktionskarten ziehen

		int zufall = wuerfel(0, number_actioncards);  //es wird mit der Rand1om/Wuerfel funktion aus dem Modul Spielmechanik gearbeitet

		money_player[2] = money_player[2] + actioncards[zufall].player_plus - actioncards[zufall].player_minus;
		money_player[1] = money_player[1] + actioncards[zufall].gegner_plus - actioncards[zufall].gegner_minus;
		matchfield_update(field_id, person, zufall);
		return 0;
	}

	//falls eine falsche person �bergeben wurde

	return 1;
}