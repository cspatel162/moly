// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);
#define ABSTAND 20


#include "Header.h"
#include <stdio.h>
#include<Windows.h>

//Lokale Prototypen
//Funktionen die nur in diesem Modul aufgerufen werden können und müssen.
int show_file(char[]);
int absatz(void);
void colourize(char);
void card_whrite(int, int);
int print_char(int anzahl, char inhalt[]);

int number_streets;
struct field *matchfield;
char colour_player;
char colour_ki;
int position_player;
int position_ki;
char *name_player;

CONSOLE_SCREEN_BUFFER_INFO Screen;
WORD wOldColAttr;
HANDLE hStdOut;

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

int matchfield_update(int field_id)
{
	int zeile = 0;

	//Anweisungen
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//Aktuelle Konsoleninfo und  Textfarbe abspeichern
	GetConsoleScreenBufferInfo(hStdOut, &Screen);
	wOldColAttr = Screen.wAttributes;
	
	//Löschen der Ausgabe
	system("cls");
	//show_file("logo.txt");
	//Header der Tabelle erstellen
	print_char(78, "="); card_whrite(field_id, zeile); zeile++;  absatz();
	printf("||%45s  || %-8s||%-7s||%-7s||", "Straße", "Preis", "Haeuser", " "); card_whrite(field_id, zeile); zeile++; absatz();
	print_char(78, "="); card_whrite(field_id, zeile); zeile++; absatz();
	print_char(78, "="); card_whrite(field_id, zeile); zeile++; absatz();
	
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

		if (position_ki == i) 
		{	
			if (position_player == i)
			{
				colourize(colour_player); printf(" X "); colourize('x');
				colourize(colour_ki); printf(" O "); colourize('x');
			}
			else
			{colourize(colour_ki); printf("    O "); colourize('x');}
		}
		else
		{
			if (position_player == i)
			{ colourize(colour_player); printf("    X "); colourize('x'); }
			else
			{printf("      ");}
		}
		printf("||"); card_whrite(field_id, zeile); zeile++; absatz();
		print_char(78, "-"); card_whrite(field_id, zeile); zeile++; absatz();
	}
	printf("\n\n");
}


//lokale Funktionen um die hauptfunktionen übersichtlicher zu gestalten
//Vorgefertige Ausgabe Funktionen
int print_char(int anzahl, char inhalt[])
{
	for (int i = 0; i <= anzahl; i++)
	{
		printf("%s", inhalt);
	}
}

int absatz(void)
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
		case 'r':/*rot*/	 SetConsoleTextAttribute(hStdOut, 64); break;
		case 'o':/*orange*/	 SetConsoleTextAttribute(hStdOut, 96); break;
		case 'p':/*pink*/	 SetConsoleTextAttribute(hStdOut, 91); break;
		case 'x':/*reset*/	 SetConsoleTextAttribute(hStdOut, wOldColAttr); break;
		default: SetConsoleTextAttribute(hStdOut, wOldColAttr); break;
	}
}

void card_whrite(int field_id, int zeile)
{
	//Anweisungen
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//Aktuelle Konsoleninfo und  Textfarbe abspeichern
	GetConsoleScreenBufferInfo(hStdOut, &Screen);
	wOldColAttr = Screen.wAttributes;

	if (strcmp(matchfield[field_id].name, "Aktionskarte") == 0)
	{

		print_char(ABSTAND, " ");
		switch (zeile)
		{
		case 0: print_char(40, "="); break;
		case 1: printf("||"); print_char(36, " "); printf("||"); break;
		case 2: printf("||"); print_char(36, " "); printf("||"); break;
		case 3: printf("||"); print_char(36, " "); printf("||"); break;
		case 4: printf("||"); print_char(36, " "); printf("||"); break;
		case 5: printf("||"); print_char(36, " "); printf("||"); break;
		case 6: print_char(40, "="); break;
		default: break;
		}
		return 0;
	}

	if (strcmp(matchfield[field_id].name, "Los") == 0)
	{
		print_char(ABSTAND, " ");
		switch (zeile)
		{
		case 14: printf("Dein Nickname  : %-10s", name_player); break;
		case 15: printf("Deine Farbe    : "); colourize(colour_player); printf(" X "); colourize("x"); printf(" %c", colour_player); break;
		case 16: printf("Ihr Kontostand :  %8i", money_player); break;
		default: break;
		}
		return 0;
	}
	
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
		case 14: printf("Dein Nickname  : %-10s", name_player); break;
		case 15: printf("Deine Farbe    : "); colourize(colour_player); printf(" X "); colourize("x"); printf(" %c", colour_player); break;
		case 16: printf("Ihr Kontostand :  %8i", money_player); break;
		default: break;
		}
	}
	else 
	{
		print_char(ABSTAND, " ");
		switch (zeile)
		{
		case 14: printf("Dein Nickname  : %-10s", name_player); break;
		case 15: printf("Deine Farbe    : "); colourize(colour_player); printf(" X "); colourize("x"); printf(" %c", colour_player); break;
		case 16: printf("Ihr Kontostand :  %8i", money_player); break;
		default: break;
		}
	}
	return 0;
}