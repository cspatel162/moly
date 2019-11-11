// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);



/*
	1. Wuerfelfunktion [Zufallszahl von 1 - 6] mit Ausgabe an Spieler printf
	2. Schnittstelle mit Modul Spielfeld: Nutzung gemeinsamer Variable "Wuerfelzahl"		Spielfeld.c gibt Aktualisierung heraus
	3. Feld Prueffunktion: 3 Moegliche Ergebnisse *Aktionfeld
												*in Besitz			Variable "Spieler"
												*nicht in Besitz	Variable "Spieler"

							//Schnittstelle zu Aktionskarten.c Uebergabe Information welcher "Spieler"	-->	Aktionskarten.c greift 
																										auf Variablen "Geld" des entsprechenden "Spielers" zu , und vlt auch"Position"
	4. *in Besitz --> Aufruf Fkt. HausBau mit Abfrage ueber Geld bzw. Abzug.		
					// Schnittstelle Spielfeld.c bei Hausbau entsprechende Markierung setzen - Variable "Position" "Geld" "Spieler"

	5. *nicht in Besitz --> Aufruf Fkt. (Kaufen?/Miete zahlen) Nutzung Variablen "Geld" "Spieler" "Position"
							Setzen Miete / Abzug Kaufpreis / Ueberpruefung ob genug Geld da ist.

	
	
	
	*/