// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#include "Header.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include<Windows.h>
#include <stdlib.h>
#include <time.h>


//Prototypen die nur in diesem Modul zur Verfügung stehen
int fetch_data(void);
void end(void);
void free_heap(void);
void welcome(void);
int new_game(void);
int load_game(void);
int save_game(void);

//Globale Variablen, die auch in der Header.h Datei aufgeführt sind.
struct field *matchfield;
struct actioncard *actioncards;
int number_streets;
int number_actioncards;
char *name_player;
char colour_player;
char colour_ki;
int *position_player;
int *money_player;

//Hilfsvariablen zur steuerung der Main-Methode
int turn;
int user;
int ki;
int status;

int main()
{
	position_player = calloc(3, sizeof(int));
	money_player = calloc(3, sizeof(int));
	
	user = 1;
	ki = 2;
	status = 1;
	turn = 1;
	welcome();
	//new_game();
	matchfield_update( NULL, NULL, NULL);

	
	while (status != 0)
	{
		spielzug(turn);
		if (money_player[turn] <= 0) { status = 0; }
		if (turn < 2) { turn++; }
		else { turn = 1; }
	}
	
	if (money_player[user] < 0) { printf("Du hast verloren\n"); }
	if (money_player[ki] < 0) { printf("Du hast gewonnen!\n"); }
	free_heap();
	end();
	
	//scanf(" %s");
}

void welcome(void)
{	
	show_file("logo.txt");
	printf("Herzlich willkommen bei MOLY, der digitalen Form von Monopoly.\n");
	printf("Bitte Maximiere das Fenster um den besten Ueberblick zu haben!\n\n");
	
	ausgabe(0, "Wollen Sie ein neus Spiel starten oder einen bestehenden Spielstand laden?\n");
	ausgabe(0, "1: Neues Spiel beginnen\n");
	ausgabe(0, "2: Bestehenden Spielstand laden\n");
	ausgabe(0, "3: Spielregeln nachschlagen\n");
	int action = eingabe(0,4);

	switch (action)
	{
	case 1: new_game(); break;
	case 2: load_game(); break;
	case 3: end(); break;
	default: break;
	}
}

int new_game()
{
	clear_output();
	show_file("logo.txt");
	printf("\nNeues Spiel wird erstellt.\n\n");
	
	fetch_data("data.txt");
	fetch_actioncards();

	printf("Geben Sie ihen Nicknamen ein :\n");

	char flash;

	gets(name_player);
	//fgets(name_player, 10, stdin);
	//scanf("%c%s", &flash, name_player);
	//scanf(" %s",  &name_player[1]);
	//printf(" ");	
}

int load_game()
{
	free_heap();
	position_player = calloc(3, sizeof(int));
	money_player = calloc(3, sizeof(int));
	if (position_player == 0 || money_player == 0) { printf("ERROR bei Speicherbelegung"); return 0; }


	FILE *file1;
	int savegame[8];
	char path[25] = "savegame/savegame0.txt";
	//Erstellen einer Tabelle mit allen Savegames
	//Tabellenkopf
	printf("\n\n|Nr.| %-20s | %-12s | %25s |\n", "Savegame", "Spielername", "Speicherdatum");
	for (int i = 0; i <= 70; i++) { printf("_"); } printf("\n");
	//Tabellenelemente
	int counter = 1;
	for (int i = 0; i <= 7; i++)
	{
			path[17] = 49 + i;
			file1 = fopen(path, "r");
			if (file1 != 0)
			{
				savegame[i] = 1; 
				printf("  %i   %s%i            ", counter, "savegame", i+1);

				char name[15];
				char date[30];
				char datensatz[400];
				char delimiter[] = ",;";
				char *ptr;

				fgets(datensatz, 400, file1);
				ptr = strtok(datensatz, delimiter);
				strcpy(name, ptr);
				for (int i = 0; i <= 6; i++) {ptr = strtok(NULL, delimiter);}
				ptr = strtok(NULL, delimiter);
				strcpy(date, ptr);

				printf("  %-12s   %25s  \n", name, date);
				fclose(file1);
				counter++;
			}
			else { savegame[i] = 0; }
	}

	//ES wird nachgezählt wie viele verfügbare Savegames vorhanden sind
	counter = 0;
	for (int i = 0; i <= 7; i++) { if (savegame[i] == 1) { counter++; } }
	if (counter == 0)//Kein Savegame vorhanden, neues Spiel wird erstellt
	{
		printf("\nLeider ist kein Spielstand vorhanden.\nBeliebige Taste druecken und bestaetigen um ein neues Spiel zu starten....");
		scanf(" %s");
		new_game(); return 1; 
	}
	printf("\n\n Wählen Sie ein Savegame: ");
	int selection;
	scanf(" %i", &selection);
	counter = 0;
	for (int i = 0; i <= 7; i++)
	{
		if (savegame[i] == 1) 
		{ 
			counter++; 
			if (counter == selection)
			{
				path[17] = 49 + i;

				printf("\n\n Sie haben die Nummer %i gewaehlt. Was wollen Sie tun?\n1. laden\n 2. loeschen\n\nEingabe:  ", selection);
				int selection;
				scanf(" %i", &selection);
				switch (selection)
				{
				case 1: fetch_data(path); 
					fetch_actioncards();
					return 0; break;
				case 2: remove(path); return load_game(); break;
				}
				return 3;
			}
			
		}
	}


		
}

int save_game()
{
	FILE *file;
	char path[25] = "savegame/savegame0.txt";
	int selection = 0;

	printf("Wollen Sie ein neues Savegame speichern oder ein bestehendes überschreiben?\n1. neues Savegame\n2.überschreiben\n\nEingabe:");
	scanf(" %i", &selection);
		
	//Pfad erstellen für neues Dokument
	if (selection == 1)
	{
		int x = 0; int y = 0;
		while (x == 0)
		{
			path[17] = 49 + y;
			file = fopen(path, "r");
			if (file != 0) { y++; fclose(file);}
			else { x++; }
			
		}printf("Der neue Pfad ist %s", path);
	}
	

	//Pfad erstellen für bestehendes Dokument und löschen des alten Dokuments
	if (selection == 2)
	{
		int savegame[8];

		//Tabelle zum Anzeigen aller bestehender Savegames
		//Tabellenkopf
		printf("\n\n|Nr.| %-20s | %-12s | %25s |\n", "Savegame", "Spielername", "Speicherdatum");
		for (int i = 0; i <= 70; i++) { printf("_"); } printf("\n");
		
		//Tabellenelemente
		int counter = 1;
		for (int i = 0; i <= 7; i++)
		{
			path[17] = 49 + i;
			file = fopen(path, "r");
			if (file != 0)
			{	//Ein Element wurde gefunden. Nun wird es in der Tabelle eingetragen
				savegame[i] = 1;
				printf("  %i   %s%i            ", counter, "savegame", i + 1);

				char name[15];
				char date[35];
				char datensatz[400];
				char delimiter[] = ",;";
				char *ptr;

				fgets(datensatz, 400, file);
				ptr = strtok(datensatz, delimiter);
				strcpy(name, ptr);
				for (int i = 0; i <= 6; i++) { ptr = strtok(NULL, delimiter); }
				ptr = strtok(NULL, delimiter);
				strcpy(date, ptr);

				printf("  %-12s   %25s  \n", name, date);
				fclose(file);
				counter++;
				fclose(file);
			}
			else //Wenn Dokument dokument nicht vorhanden
			{ savegame[i] = 0; }
		}


			counter = 0;
			for (int i = 0; i <= 7; i++) { if (savegame[i] == 1) { counter++; } }
			if (counter == 0) { new_game(); return 0; }//Kein Savegame vorhanden, neues Spiel wird erstellt
			printf("\n\n Wählen Sie ein Savegame: ");
			selection = 0;
			scanf(" %i", &selection);
			counter = 0;
			for (int i = 0; i <= 7; i++)
			{
				if (savegame[i] == 1)
				{
					counter++;
					if (counter == selection)
					{
						path[17] = 49 + i;
						remove(path);
					}
				}
			}
	}

	//Abspeichern beginnen
	//Datei erstellen
	FILE *file2;
	file2 = fopen(path, "w");
	if (file2 == 0) { printf("ERROR: DAtei konnte nicht geöffnet werden"); return 1; }
	//Eingabe der Daten
	time_t now;
	now = time(0);
	char time[30]; strcpy(time, ctime(&now));
	time[24] = ' ';
	printf("Die Urheit ist %s", time);
	//Abspeichern der Rahmendaten
	fprintf(file2, "%s,;%i,;%i,;%i,;%i,;%c,;%c,;%i,;%s,;\n", name_player, money_player[1], money_player[2], position_player[1], position_player[2], colour_player, colour_ki, turn, time);

	//Abspeichern der einzelnen Straßen
	for (int i = 0; i <= number_streets - 1; i++)
	{
		fprintf(file2, "%i,;%s,;%c,;%i,;%i,;%i,;%i,;%i,;%i,;%i,;%i,;%i,;%i,;%i,;%i,;%i,;", matchfield[i].owner, matchfield[i].name, matchfield[i].colour, matchfield[i].price, matchfield[i].rent[0], matchfield[i].rent[1], matchfield[i].rent[2], matchfield[i].rent[3], matchfield[i].rent[4], matchfield[i].rent[5], matchfield[i].rent[6], matchfield[i].house, matchfield[i].price_house[0], matchfield[i].price_house[1], matchfield[i].price_house[2], matchfield[i].price_house[3]);
		if (i <= (number_streets - 2)) { fprintf(file2, "\n"); }
	}
	fclose(file2);
}

int fetch_data(char filename[])
{
	//printf("DAteinname: %s", filename);
	//Ermitteln der Zeilenanzahl
	int zeilenanzahl = 0;
	FILE *file;
	file = fopen(filename, "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", filename);
		return 1;
	}
	char zw[200];
	while (!feof(file))
	{
		fgets(zw, 200, file);
		zeilenanzahl++;		
	}
	zeilenanzahl = zeilenanzahl - 1;
	fclose(file);

	//Reservieren des Speicherplatzes für den Heap (für alle Straßendaten)
	matchfield = calloc(zeilenanzahl, sizeof(struct field));
	if (matchfield == 0) { printf("Nicht genügend Speicherplatz vorhanden!\n"); return 1; }
	//Daten einlesen
	file = fopen(filename, "r");
	if (file == 0)
	{
		printf("ERROR: Die Datei %s konnte nicht geoeffnet werden.", "streetdata.txt");
		return 2;
	}

	//Einlesen aller Daten
	int zaehler = 0;
	char datensatz[400];
	char delimiter[] = ",;";
	char *ptr;
	
	//Einlesen aller allgemeinen Spieldaten
	fgets(datensatz, 400, file);
	ptr = strtok(datensatz, delimiter);
	name_player = calloc(50, sizeof(char));
	strcpy(name_player, ptr);

	ptr = strtok(NULL, delimiter);
	money_player[1] = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	money_player[2] = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	position_player[1] = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	position_player[2] = atoi(ptr);

	ptr = strtok(NULL, delimiter);
	colour_player = *ptr;
	
	ptr = strtok(NULL, delimiter);
	colour_ki = *ptr;

	ptr = strtok(NULL, delimiter);
	turn = atoi(ptr);

	
	//Einlesen aller Strassen
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
		printf("Name     : %s\n", (matchfield+zaehler)->name);
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
		
		//Einlesen Häuserpreise
		for (int i = 0; i <= 3; i++)
		{
			ptr = strtok(NULL, delimiter);
			matchfield[zaehler].price_house[i] = atoi(ptr);
			//printf("Miete mit %i Haeusern: %i\n",i , (matchfield + zaehler)->rent[i]);
		}
		
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
	printf("Vielen Dank, dass du mit uns gespielt hast.\Bis zum nächsten mal.");
	
}

void free_heap(void)
{
	free(matchfield);
	free(name_player);
	//free(actioncards);
	free(position_player);
	free(money_player);
}

int break_menue(void)
{
	clear_output();
	printf("Pausenmenue\n\n1: Spielstand speichern\n2: anderen Spielstand laden\n3:weiterspielen\n4: Spiel nach diesem Spielzug beenden.\n\n");

	int zeichen = eingabe(0, 4);

	//Spiel speichern
	if (zeichen == 1)
	{
		save_game(); return break_menue();
	}

	//Spiel laden
	if (zeichen == 2)
	{
		load_game();
		return 2;
	}

	//Spiel beenden
	if (zeichen == 4)
	{
		status = 0;
		return 4;
	}
	
	return 3;


}

int clear_output(void)
{
	char flash;
	scanf("%c", &flash);
	system("cls");
	printf("\n");
	return 0;
}