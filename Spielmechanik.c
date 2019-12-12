// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#define STARTSPRUNG 5000 //Wert der gutgeschrieben wird, wenn man Los überfährt

// Einbindung von Headerdatei und C-Bibliotheken
#include "Header.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// Modul Prototypen


int wuerfel(int, int);						// 1. Parameter Kleinste Zahl im Wertebereich ; 2. Parameter Größte Zahl nicht im Wertebereich

int posi(int, int	);						// 1. Parameter Wuerfelzahl		2. Person ID 1 steht für Player, 2 für KI

//void puffer(void);							// Puffer -- Programmstop bis '1' eingegeben wird

int ausgabe(int , char[]);



int spielzug(int person_id)
{
	srand(time(NULL));		//Zufallszahlen Reset


	int zw_position = 0;	// Variable um Position zwischen zu speichern
	int zw_answer = 0;		// Zwischenspeicher für Returnwert der eingabe-Funktion
	
	int safe = 0;				//Zwischenspeicher für Returnwert der eingabe-Funktion
	int bewegung = 0;	//Zwischenvariable Würfelzahl
	int field_id = 0;		//Zwischenvariable Auf welchem Feld die Person steht


	//Spielstein bewegen
	if (person_id != 2)
	{
		printf("\tSie sind am Zug.\n\tDruecke beliebige Taste um zu Wuerfeln oder druecken Sie 'b' um ins Pausenmenue zu kommen....\n");
		char zw = ' ';
		//getc(stdin);
		eingabe(NULL, NULL);
	}
	else
	{
		printf("\tDruecke beliebige Taste um den Computer seinen Zug machen zu lassen oder druecken Sie 'b' um ins Pausenmenue zu kommen....\n");
		char zw = ' ';
		//getc(stdin);
		eingabe(NULL, NULL);
	}

	matchfield_update(position_player[person_id], person_id, NULL);
	
		//printf("Augenzahl eingeben:");
		//bewegung = 1;

		bewegung = wuerfel(1, 7);																		// Wuerfelzahl wird in bewegung gespeichert
		posi(bewegung, person_id);																// position_player wird aktualisiert nach dem was gewuerfelt wurde
		
		//position der Person herausfinden
		field_id = position_player[person_id];

		matchfield_update(field_id, person_id, NULL);														// Öberfläche wird aktualisiert
		printf("\tSie haben %i gewuerfelt.\n\n", bewegung);					// INFO Ausgabe an Spieler
	
		
																									
	//Sonderfeld Aktionskarte
	if (strcmp(matchfield[field_id].name, "Aktionskarte") == 0)
	{
		actioncards_play(person_id, field_id);
		printf("Du bist auf Aktionskarte gelandet!!\n");
		return 0;
	}


	// Sonderfeld GoToGefängnis
	 if (strcmp(matchfield[field_id].name, "GO TO ASKABAN") == 0)
	 {
		 //Ermitteln der Position des Gefängnis
		 int jail_id= 0;
		 for (int i = 0; i <= number_streets - 1; i++) { if (strcmp(matchfield[i].name, "ASKABAN") == 0) { jail_id = i; } }

		 //Spielstein auf Gefaengnis setzen und Strafzahlung
		 position_player[person_id] = jail_id;				
		 money_player[person_id] = money_player[person_id] - 1000;															
		 
		 matchfield_update(field_id, person_id, NULL);
		 
		 ausgabe(person_id, "Sie Sind im Gefaengnis gelandet!!\n\n");
		 return 1;
	 }

	 //Sonderfeld LOS
	 if (strcmp(matchfield[field_id].name, "LOS") == 0)
	 {
		 return 2;
	 }

	 //Sonderfeld Gefängnis
	 if (strcmp(matchfield[field_id].name, "ASKABAN") == 0)
	 {
		 return 4;
	 }


	 //Straßenbehandlung:

	 // Wenn Feld der anderen Person gehört und Miete mus gezahlt werden RETURN 4
	 if (matchfield[field_id].owner != person_id && matchfield[field_id].owner != 0)
	 {
		 int gegner_id = matchfield[field_id].owner; //Ermitteln des Besitzers
		
		 int rent = matchfield[field_id].rent[matchfield[field_id].house];  //Ermittlung Miethöhe
		 money_player[person_id] = money_player[person_id] - rent;			//Abziehen des Betrags beim Gläubiger
		 money_player[gegner_id] = money_player[gegner_id] + rent;			//Gutschrift beim Besitzer des Feldes
		 ausgabe(person_id, "\tSie mussten Miete zahlen!\n");
		 return 4;
	 }

	 // Wenn Feld noch niemanden gehört  RETURN 5 Feld gekauft RETURN 6 Feld nicht gekauft
	 if (matchfield[field_id].owner == 0)												// Ueberpruefen ob es keinem gehoert und kein aktionskarte und gefaengnis
	 {
		 ausgabe(person_id, "Wollen Sie das Objekt erwerben?\n\t 1 fuer ja, 2 fuer nein");				// Kaufanfrage
		 if (person_id == 2) { zw_answer = wuerfel(1, 3); printf("\tDie KI hat %i gewuerfelt\n", zw_answer); }	//Für KI wird eine automatische Eingabe erzeugt
		 else { zw_answer = eingabe(0, 3); }

		 //Haus kaufen
		 if (zw_answer == 1) 
		 {
			 //Prüfung des Kontostands
			 if (money_player[person_id] >= matchfield[field_id].price)	// Wenn JA --> Feld_id wird geaendert und Kaufpreis abgezogen
			 {
				 //Preis abbuchen, und als Besitzer eintragen
				 money_player[person_id] = money_player[person_id] - matchfield[field_id].price;				// Kaufpreis
				 matchfield[field_id].owner = person_id;

				 matchfield_update(field_id, person_id, NULL);
				 ausgabe(person_id, "Objekt erworben");
				 return 5;
			 }
			 
			 else { printf("\tNicht genug Geld\n\n"); puffer; }												// Wenn NEIN --> Nichts 

		 }

		 //Haus nicht kaufen
		 return 6;
	 }

	 // Wenn Feld in Besitz Return 7
	 if (matchfield[field_id].owner == person_id)
	 {
		 //Kaufanfrage
		 ausgabe(person_id, "Wollen Sie ein Haus bauen?\n 1 fuer Ja, 2 fuer Nein");
		 if (person_id == 2) { zw_answer = wuerfel(1, 3); }	//Für KI wird eine automatische Eingabe erzeugt
		 else { zw_answer = eingabe(0, 3); }


		while (zw_answer == 1)	//Haus Bauen, Geld, alle Straßen in Besitz
		 {
			// Prüfung Kontostand
			int price_newhouse = matchfield[field_id].price_house[matchfield[field_id].house];
			if (money_player[person_id] >= price_newhouse)
			{
				//Kontrolle ob alle Straßen im Besitz
				int buy_ok = 0; //Wenn alle im Besitz zw_own = 1
				char colour = matchfield[field_id].colour;
				int exist = 0;
				int own = 0;
				//Zählen der Anzahl der Straßen der Farbe
				for (int y = 0; y <= number_streets - 1; y++)
				{ if (matchfield[y].colour == colour) { exist++; } }
				//Zählen der Straßen der Farbe die in Besitz sind
				for (int z = 0; z <= number_streets - 1; z++)
				{ 
					if (matchfield[z].colour == colour && matchfield[z].owner == person_id)
					{own++;}
				}

				if (exist == own) { buy_ok = 1; } //Kauf genehmigt

				//Haus bauen
 				if (buy_ok == 1) 
				{
					//Haus bezahlen und Haus eintragen
					 money_player[person_id] = money_player[person_id] - price_newhouse;
					 matchfield[field_id].house++;
					 matchfield_update(field_id, person_id, NULL);																		// Spielfeld aktualisieren
					 ausgabe(person_id, "Haus wurde gebaut!");
				 }
				else { ausgabe(person_id, "Haus konnt nicht gebaut werden. (Farb-Besitz-Problem)"); return 7; }
				 
				printf("Wollen Sie ein weiteres Haus bauen?\n 1 fuer Ja, 2 fuer Nein");
				if (person_id == 2) { zw_answer = wuerfel(1, 3); }	//Für KI wird eine automatische Eingabe erzeugt
				else { zw_answer = eingabe(0, 3); }
			 }
			 else { ausgabe(person_id, "Nicht genuegend Geld"); zw_answer = 0;}
		 }
	 return 7;
	 }
	 
}


// Eingabefunktion mit Kontrolle des Wertebereichs
int eingabe (int min, int max)			// 1. Parameter kleinstes Zeichen 2. Parameter größtes Zeichen ------ Beide exklusiv!
{
	int zahl;
	char zeichen;
	//scanf(" %c", &zeichen);
	zeichen = getc(stdin);

	if (min == NULL && max == NULL && zeichen != 'b')
	{
		while (getchar() != '\n');
		return 0;
	}
	
	switch (zeichen)
	{
	case 48: zahl = 0; break;
	case 49: zahl = 1; break;
	case 50: zahl = 2; break;
	case 51: zahl = 3; break;
	case 52: zahl = 4; break;
	case 53: zahl = 5; break;
	case 54: zahl = 6; break;
	case 55: zahl = 7; break;
	case 56: zahl = 8; break;
	case 57: zahl = 9; break;
	case 'b': break_menue(); return NULL;
	default: printf("\nUngueltige Eingabe %c\n", zeichen); return eingabe(min, max);
	}
	if (zahl < min || zahl > max)
	{
		while (getchar() != '\n');
		return eingabe(min, max);
	}
	else
	{
		while (getchar() != '\n');
		return zahl;
	}
}
// Wuerfelfunktion

int wuerfel(int min, int max)				// 1. Parameter Kleinste Zahl ; 2. Parameter Größte Zahl
{
	int i = rand() % (max - min) + min;		// Erzeugen Zufallszahl zwischen min - max
	//printf("\tSie haben die Zahl %i gewuerfelt \n\n", i);						// Ausgabe der Zufallszahl
	//printf("Simulierter Würfel:");
	//i = eingabe(0, 12);
	return i;
}



// Funktion um Spielerposition zu Aktualisieren
int posi(int beweg, int person_id)
{
	int i = 0;

	for (i = 0 ; i < beweg ; i++ )
	{
			position_player[person_id] = position_player[person_id] + 1;
			if (position_player[person_id] == number_streets -1)
			{
				position_player[person_id] = 0;
				money_player[person_id] = money_player[person_id] + STARTSPRUNG;
			}
	}
	return 0;
}


void puffer(void)
{
	//int egal = 0;
	printf("Druecke beliebige Taste um fortzufahren...");
	//egal = eingabe(0, 2);
	char zw = ' ';
	scanf(" %c", &zw);
}


int ausgabe(int person_id, char text[])
{
	if (person_id != 2)
	{
		printf("\t%s\n", text);

	}
	return 0;
}