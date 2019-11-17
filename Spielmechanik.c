// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);


// Einbindung von Headerdatei und C-Bibliotheken
#include "Header.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// Modul Prototypen


int wuerfel(int, int);						// 1. Parameter Kleinste Zahl im Wertebereich ; 2. Parameter Größte Zahl nicht im Wertebereich

int eingabe(int, int);						// 1. Parameter kleinstes Zeichen 2. Parameter größtes Zeichen ------ Beide exklusiv!

void posi(int, int *, int*);						// 1. Parameter Wuerfelzahl		2. Parameter Adresse der position_player Variable

void puffer(void);							// Puffer -- Programmstop bis '1' eingegeben wird



// Zaeler für Überprüfung ob alle Straßen in Besitz sind

int strasse1 = 0;
int strasse2 = 0;
int strasse3 = 0;
int strasse4 = 0;
int strasse5 = 0;
int strasse6 = 0;
int strasse7 = 0;
int strasse8 = 0;




void spielzug(void)
{
	srand(time(NULL));		//Zufallszahlen Reset


	int a = 0;				// Variable um Position zwischen zu speichern
	int b = 0;				// Zwischen Variable um die Vollstaendigkeit einer Strassenreihe zu bestaetigen
	int antwort = 0;		//Zwischenspeicher für Returnwert der eingabe-Funktion
	
	int safe = 0;				//Zwischenspeicher für Returnwert der eingabe-Funktion
	int bewegung = 0;			//Zwischenvariable um Wuerfelzahl zu speichern

	printf("\tSie sind am Zug.\n\tDruecken Sie die 1 um zu Wuerfeln.\n");		// Aufforderung um zu Wuerfeln. 1 fuer Wuerfeln
	safe = eingabe(0, 2);
	if (safe == 1)
	{
		bewegung = wuerfel(1, 7);																		// Wuerfelzahl wird in bewegung gespeichert
		posi(bewegung, &position_player, &money_player);																// position_player wird aktualisiert nach dem was gewuerfelt wurde
	
		matchfield_update(position_player, NULL);														// Öberfläche wird aktualisiert
		printf("\tSie haben %i gewuerfelt und auch nach vorne gerueckt\n", bewegung);					// INFO Ausgabe an Spieler

	}
	
			// Überprüfung auf welchem Feld der Spieler jetzt steht:	Feld_id überprüfen


	//if (strcmp(matchfield[position_player].name, "Aktionskarte") == 0);		//Überprüfung auf Aktionsfeld
	//{
	//
	//	matchfield_update(position_player, NULL);
	//  puffer;
	//}

	 if (strcmp(matchfield[position_player].name, "Gefaengnis") == 0);		//Überprüfung auf Gefängnis
	 {
		 position_player = 10;												// Position des Spielers auf Gefängniss setzen
		 money_player = money_player - 1000;								// Strafzahlung von 1000															
		 matchfield_update(position_player, NULL);
		 printf("\tSie sind im Gefaengnis geladet. :( \n");
		 puffer;
	 }


	 // Wenn Feld NICHT in Besitz und KI gehört.

	 if (matchfield[position_player].owner == 2)			// Gegner gehört Feld
	 {
		 

		 money_player = money_player - matchfield[position_player].rent[matchfield[position_player].house];			// Kosten der Miete abhängig von Anzahl der Häuser
		 money_ki = money_ki + matchfield[position_player].rent[matchfield[position_player].house];				//matchfield[i].rent[X]		X = matchfield[i].house
		 matchfield_update(position_player, NULL);
		 printf("\tSie mussten Miete zahlen!\n");
		 puffer;
		
	 }


	 // Wenn Feld NICHT in Besitz und NIEMAND gehört.

	 if (matchfield[position_player].owner == 0 && strcmp(matchfield[position_player].name, "Aktionskarte") != 0 && strcmp(matchfield[position_player].name, "Gefaengnis") != 0)												// Ueberpruefen ob es keinem gehoert und kein aktionskarte und gefaengnis
	 {

		 printf("\t Wollen Sie das Objekt erwerben?\n\t 1 fuer ja, 2 fuer nein\n");				// Kaufanfrage

		 antwort = eingabe(0, 3);

		 if (antwort == 1) 
		 {
																// Ausreichend Geld?

			 if (money_player >= matchfield[position_player].price)								// Wenn JA --> Feld_id wird geaendert und Kaufpreis abgezogen
			 {
				 money_player = money_player - matchfield[position_player].price;				// Kaufpreis
				 matchfield[position_player].owner = 1;											// Feld_id

				 matchfield_update(position_player, NULL);
				 printf("\tObjekt erworben\n");
				 puffer;

				 // Je nach dem welche Straßenreihe gekauft wurde wird der Zaehler erhöht um bei einem Hauskauf kontrollieren zu koennen ob alle Teile in Besitz sind 
				 a = position_player;
				 switch (a)
				 {

				 case 1:		strasse1++;		break;
				 case 3:		strasse1++;		break;
				 case 6:		strasse2++;		break;
				 case 8:		strasse2++;		break;
				 case 9:		strasse2++;		break;
				 case 11:		strasse3++;		break;
				 case 13:		strasse3++;		break;
				 case 14:		strasse3++;		break;
				 case 16:		strasse4++;		break;
				 case 18:		strasse4++;		break;
				 case 19:		strasse4++;		break;
				 case 21:		strasse5++;		break;
				 case 23:		strasse5++;		break;
				 case 24:		strasse5++;		break;
				 case 26:		strasse6++;		break;
				 case 27:		strasse6++;		break;
				 case 29:		strasse6++;		break;
				 case 31:		strasse7++;		break;
				 case 32:		strasse7++;		break;
				 case 34:		strasse7++;		break;
				 case 37:		strasse8++;		break;
				 case 39:		strasse8++;		break;

				 }
			 }
			 else { printf("\tNicht genug Geld\n"); puffer; }												// Wenn NEIN --> Nichts 

		 }


	 }

		// Wenn Feld NICHT in Besitz hier --> ENDE
		// Nach dem Kauf wird abgefragt ob ein Haus gebaut werden soll



	 // Wenn Feld in Besitz

	 if (matchfield[position_player].owner == 1)
	 {
		 printf("\tWollen Sie ein Haus bauen?\n\t 1 fuer Ja, 2 fuer Nein");
		 antwort = eingabe(0, 3);

		while (antwort == 1)	//Haus Bauen, Geld, alle Straßen in Besitz
		 {
			// Ausreichend Geld?

			 if (money_player >= matchfield[position_player].price_house[matchfield[position_player].house])	// 

			 {
				 //Kontrolle ob alle Straßen im Besitz

				 a = position_player;
					 switch (a) {

					 case 1:		if (strasse1 == 2) b = 1; break;		// Wenn b auf 1 gesetzt wird dann ist die Straßenkombi auf der gestanden wird im Besitz
					 case 3:		if (strasse1 == 2) b = 1; break;
					 case 6:		if (strasse2 == 3) b = 1; break;
					 case 8:		if (strasse2 == 3) b = 1; break;
					 case 9:		if (strasse2 == 3) b = 1; break;
					 case 11:		if (strasse3 == 3) b = 1; break;
					 case 13:		if (strasse3 == 3) b = 1; break;
					 case 14:		if (strasse3 == 3) b = 1; break;
					 case 16:		if (strasse4 == 3) b = 1; break;
					 case 18:		if (strasse4 == 3) b = 1; break;
					 case 19:		if (strasse4 == 3) b = 1; break;
					 case 21:		if (strasse5 == 3) b = 1; break;
					 case 23:		if (strasse5 == 3) b = 1; break;
					 case 24:		if (strasse5 == 3) b = 1; break;
					 case 26:		if (strasse6 == 3) b = 1; break;
					 case 27:		if (strasse6 == 3) b = 1; break;
					 case 29:		if (strasse6 == 3) b = 1; break;
					 case 31:		if (strasse7 == 3) b = 1; break;
					 case 32:		if (strasse7 == 3) b = 1; break;
					 case 34:		if (strasse7 == 3) b = 1; break;
					 case 37:		if (strasse8 == 2) b = 1; break;
					 case 39:		if (strasse8 == 2) b = 1; break;
					 

					 }

					 if (b == 1) 
					 {
						 money_player = money_player - matchfield[position_player].price_house[matchfield[position_player].house];		// Kaufpreis abziehen
						 matchfield[position_player].house++;																			// Häuseranzahl um 1 erhöhen
						 b = 0;
						 matchfield_update(position_player, NULL);																		// Spielfeld aktualisieren
						 puffer;
					 }
					 else { printf("\tNicht alle Strassen in Besitz\n"); puffer; }


					 printf("\tWollen Sie noch ein Haus bauen?\n\t 1 fuer Ja, 2 fuer Nein");
					 antwort = eingabe(0, 3);


			 }
			 else { printf("\t Nicht genuegend Geld\n"); puffer; }

		 }
		


	 }



}


// Wuerfelfunktion

int wuerfel(int min, int max)				// 1. Parameter Kleinste Zahl ; 2. Parameter Größte Zahl
{
	

	int i = rand() % (max - min) + min;		// Erzeugen Zufallszahl zwischen min - max
	printf("\tSie haben die Zahl %i gewuerfelt \n", i);						// Ausgabe der Zufallszahl

	return i;
}




// Eingabefunktion mit Kontrolle des Wertebereichs

int eingabe (int min, int max)			// 1. Parameter kleinstes Zeichen 2. Parameter größtes Zeichen ------ Beide exklusiv!
{
	int speicher;

	do {
		scanf(" %i", &speicher);



		if (speicher <= min || speicher >= max) printf("\tEingabe nicht im erlaubten Eingabe Bereich! Neueingabe!\n ");

		
	
	} while (speicher <= min || speicher >= max);

	printf("\tSie haben die 1 gedrueckt.\n\n");

	return speicher;

}



// Funktion um Spielerposition zu Aktualisieren

void posi(int beweg, int * position_player, int * money_player)
{
	int i = 0;

	for (i = 0 ; i < beweg ; i++ ) {
		*position_player = (*position_player)+1;

		if (*position_player == number_streets) 
			{

			*position_player = 0;
			*money_player = (*money_player) + 4000;

			}
		}

}


void puffer(void)
{
	int egal = 0;
	printf("Druecke 1 zum fortfahren");
	egal = eingabe(0, 2);
}

