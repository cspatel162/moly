// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);
#define ABSTAND 20


#include "Header.h"
#include <stdio.h>
#include<Windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Lokale Prototypen
//Funktionen die nur in diesem Modul aufgerufen werden können und müssen.
//int show_file(char[]);
void absatz(void);
void colourize(char);
void card_whrite(int, int);
void print_char(int anzahl, char inhalt[]);

CONSOLE_SCREEN_BUFFER_INFO Screen;
WORD wOldColAttr;
HANDLE hStdOut;

int show_file(char filename[15])
{	
	printf("\n");
	
	char zeile[500];
	FILE *file;
	file = fopen(filename, "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s geoeffnet werden.", filename);
		return 1;
	}

	while (!feof(file))
	{
		fgets(zeile, 500, file);
		printf("%s", zeile);
	}
	printf("\n");
	fclose(file);
	return 0;
}

void matchfield_update(int field_id, int action_id)
{
	clear_output();
	int zeile = 0;

	//Anweisungen
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//Aktuelle Konsoleninfo und  Textfarbe abspeichern
	GetConsoleScreenBufferInfo(hStdOut, &Screen);
	wOldColAttr = Screen.wAttributes;
	
	//Löschen der Ausgabe
	//Header der Tabelle erstellen
	print_char(78, "="); card_whrite(field_id, zeile, action_id); zeile++;  absatz();
	printf("||%45s  || %-8s||%-7s||%-6s||", "Straße", "Preis", "Haeuser", " "); card_whrite(field_id, zeile, action_id); zeile++; absatz();
	print_char(78, "="); card_whrite(field_id, zeile, action_id); zeile++; absatz();
	print_char(78, "="); card_whrite(field_id, zeile, action_id); zeile++; absatz();
	
	for (int i = 0; i <= number_streets-1; i++)
	{
		printf("||");
		colourize(matchfield[i].colour); printf("%45s  ", matchfield[i].name); colourize('x');
		if (matchfield[i].price == 0) { printf("||         ||"); }
		else { printf("|| %-8i||", matchfield[i].price); }
		
		
		char houses[] = "       ";
		for(int j = 0; j <= matchfield[i].house - 1; j++)
		{	houses[j] = 65;	}

		switch (matchfield[i].owner)
		{
			case 0: printf("%-7s", ""); break;
			case 1: colourize(colour_player); printf("%-7s", houses); colourize('x'); break;
			case 2: colourize(colour_ki); printf("%-7s", houses); colourize('x'); break;
			default: printf("   FAIL"); break;
		} printf("||");

		if (position_player[2] == i) 
		{	
			if (position_player[1] == i)
			{
				colourize(colour_player); printf(" X "); colourize('x');
				colourize(colour_ki); printf(" O "); colourize('x');
			}
			else
			{colourize(colour_ki); printf("    O "); colourize('x');}
		}
		else
		{
			if (position_player[1] == i)
			{ colourize(colour_player); printf("    X "); colourize('x'); }
			else
			{printf("      ");}
		}
		printf("||"); card_whrite(field_id, zeile, action_id); zeile++; absatz();
		print_char(78, "-"); card_whrite(field_id, zeile, action_id); zeile++; absatz();
	}
	printf("\n\n");
}

//lokale Funktionen um die hauptfunktionen übersichtlicher zu gestalten

//Vorgefertige Ausgabe Funktionen
void print_char(int anzahl, char inhalt[])
{
	for (int i = 0; i <= anzahl; i++)
	{
		printf("%s", inhalt);
	}
}

void absatz(void)
{
	printf("\n");
}

void colourize(char colour)
{
	switch (colour)
	{
		case 'g':/*grün*/	 SetConsoleTextAttribute(hStdOut, 32); break;
		case 'y':/*gelb*/	 SetConsoleTextAttribute(hStdOut, 160); break;
		case 'b':/*blau*/	 SetConsoleTextAttribute(hStdOut, 31); break;
		case 'h':/*türkis*/	 SetConsoleTextAttribute(hStdOut, 176); break;
		case 'i':/*grau*/	 SetConsoleTextAttribute(hStdOut, 128); break;
		case 'r':/*rot*/	 SetConsoleTextAttribute(hStdOut, 64); break;
		case 'o':/*orange*/	 SetConsoleTextAttribute(hStdOut, 96); break;
		case 'p':/*pink*/	 SetConsoleTextAttribute(hStdOut, 91); break;
		case 'x':/*reset*/	 SetConsoleTextAttribute(hStdOut, wOldColAttr); break;
		default: SetConsoleTextAttribute(hStdOut, wOldColAttr); break;
	}
}

void card_whrite(int field_id, int zeile, int action_id)
{
	//Anweisungen
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//Aktuelle Konsoleninfo und  Textfarbe abspeichern
	GetConsoleScreenBufferInfo(hStdOut, &Screen);
	wOldColAttr = Screen.wAttributes;

	//Sollte eine Aktionskarte ausgegeben werden wird dieser Abschnitt ausgeführt und beendet die Funktion
	if (strcmp(matchfield[field_id].name, "Aktionskarte") == 0)
	{
		int z = 0;

		//Erstellen des Abstands zum Spielfeld
		print_char(ABSTAND, " ");
		switch (zeile)
		{
		case 0: print_char(45, "="); break;
		case 1: printf("||   "); printf("%-35s", "Aktionskarte");  printf("   ||"); break;
		case 2: print_char(45, "="); break;
		case 3: printf("||"); for (z = 0; z <= 41; z++) {  printf("%1c", actioncards[action_id].text[z]); } printf("||"); break;
		case 4: printf("||"); for (z = 42; z <= 83; z++) { printf("%1c", actioncards[action_id].text[z]); } printf("||"); break;
		case 5: printf("||"); for (z = 84; z <= 126; z++) { printf("%1c", actioncards[action_id].text[z]); } printf("||"); break; 
		case 6: print_char(45, "="); break;

		case 14: printf("Dein Nickname  : %-10s", name_player); break;
		case 15: printf("Deine Farbe    : "); colourize(colour_player); printf(" X "); colourize("x"); printf(" %c", colour_player); break;
		case 16: printf("Ihr Kontostand :  %8i", money_player[1]); break;
		case 17: printf("KI  Kontostand :  %8i", money_player[2]); break;
		default: break;
		}

		return 0;
	}

	//Sollte das Startfeld ausgegeben werden wird dieser Abschnitt ausgeführt und beendet die Funktion
	if (strcmp(matchfield[field_id].name, "Los") == 0)
	{
		print_char(ABSTAND, " ");
		switch (zeile)
		{
		case 14: printf("Dein Nickname  : %-10s", name_player); break;
		case 15: printf("Deine Farbe    : "); colourize(colour_player); printf(" X "); colourize("x"); printf(" %c", colour_player); break;
		case 16: printf("Ihr Kontostand :  %8i", money_player[1]); break;
		default: break;
		}
		return 0;
	}
	
	//Sollte eine Straße ausgegeben werden wird dieser Abschnitt ausgeführt und beendet die Funktion
	if (field_id != NULL)
	{

		print_char(ABSTAND, " ");
		switch (zeile)
		{
		case 0: print_char(27, "="); break;
		case 1: printf("||"); colourize(matchfield[field_id].colour); printf(" %-22s ", matchfield[field_id].name); colourize("x"); printf("||"); break;
		case 2: print_char(27, "-"); break;
		case 3: printf("||"); printf(" Preis    :  %7i  ", matchfield[field_id].price); print_char(1, " "); printf("||"); break;
		case 4: print_char(27, "-"); break;
		case 5: printf("||"); printf(" Miete:"); print_char(16, " "); printf("||"); break;
		case 6: printf("||"); printf(" 0 Haeuser:   %6i", matchfield[field_id].rent[0]); print_char(3, " "); printf("||"); break;
		case 7: printf("||"); printf(" 1 Haus   :   %6i", matchfield[field_id].rent[1]); print_char(3, " "); printf("||"); break;
		case 8: printf("||"); printf(" 2 Haeuser:   %6i", matchfield[field_id].rent[2]); print_char(3, " "); printf("||"); break;
		case 9: printf("||"); printf(" 3 Haeuser:   %6i", matchfield[field_id].rent[3]); print_char(3, " "); printf("||"); break;
		case 10: printf("||"); printf(" 4 Haeuser:   %6i", matchfield[field_id].rent[4]); print_char(3, " "); printf("||"); break;
		case 11: printf("||"); printf(" Hotel    :   %6i", matchfield[field_id].rent[5]); print_char(3, " "); printf("||"); break;
		case 12: print_char(27, "-"); break;
		case 13: printf("||"); printf(" Kaufpreise Haeuser:"); print_char(3, " "); printf("||"); break;
		case 14: printf("||"); printf(" 1.Haus:   %6i", matchfield[field_id].price_house[0]); print_char(6, " "); printf("||"); break;
		case 15: printf("||"); printf(" 2.Haus:   %6i", matchfield[field_id].price_house[1]); print_char(6, " "); printf("||"); break;
		case 16: printf("||"); printf(" 3.Haus:   %6i", matchfield[field_id].price_house[2]); print_char(6, " "); printf("||"); break;
		case 17: printf("||"); printf(" 4.Haus:   %6i", matchfield[field_id].price_house[3]); print_char(6, " "); printf("||"); break;
		case 18: print_char(27, "-"); break;
		case 21: printf("Dein Nickname  : %-10s", name_player); break;
		case 22: printf("Deine Farbe    : "); colourize(colour_player); printf(" X "); colourize("x"); printf(" %c", colour_player); break;
		case 23: printf("Ihr Kontostand :  %8i", money_player[1]); break;
		case 24: printf("KI  Kontostand :  %8i", money_player[2]); break;
		default: break;
		}
	}

	//Wenn gar keine Karte ausgegeben werden soll.
	else 
	{
		print_char(ABSTAND, " ");
		switch (zeile)
		{
		case 14: printf("Dein Nickname  : %-10s", name_player); break;
		case 15: printf("Deine Farbe    : "); colourize(colour_player); printf(" X "); colourize("x"); printf(" %c", colour_player); break;
		case 16: printf("Ihr Kontostand :  %8i", money_player[1]); break;
		case 17: printf("KI  Kontostand :  %8i", money_player[2]); break;
		default: break;
		}
	}
	//printf(" ");
	return 0;
}
