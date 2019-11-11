// Folgender Code MUSS immer am ANFANG der C-Datei stehen,
// damit Funktionen wie scanf, getch und gets benutzt werden koennen
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NX 5
#define NY 5

void main(void)
{

	srand(time(NULL));

	int NS = 0.2 * NX*NY;
	char Feld[NX][NY] = { ' ' };
	int i, x, y, k;
	int Punkte = 20;

	for (i = 0; i < NS; ) {					// Zufällige Schiffe Verteilung

		x = rand() % NX;
		y = rand() % NY;

		if (Feld[x][y] == 'S') continue;
		Feld[x][y] = 'S';

		i = i + 1;
	}


	for (k = 0; k < NY; k++) {				// Spielfeld Ausgabe



		for (i = 0; i < NX; i++) {

			printf("%c  ", Feld[i][k]);
		}
		printf("\n");
	}

	do
	{
		do {
			printf("Geben Sie die x-Koordinate ein.\n");

			scanf("%i", &x);

			if (x >= NX || x < 0) printf("Fehler. Eingabe liegt nicht im Spielfeldbereich.\n");
		} while (x >= NX || x < 0);

		do {
			printf("Geben Sie die y-Koordinate ein.\n");
			scanf("%i", &y);
			if (y >= NY || y < 0) printf("Fehler. Eingabe liegt nicht im Spielfeldbereich.\n");
			} while (y >= NY || y < 0);


		if (x == -1 || y == -1) {
			printf("Spiel beendet\n");
			break;
		}

		if (Feld[x][y] == 'S')
		{
			Punkte = Punkte + 10;
			NS = NS - 1;
			printf("Treffer! Aktuelle Punktzahl : %i\n", Punkte);
		}
		else
		{
			Punkte = Punkte - 5;
			printf("Verfehlt! Aktuelle Punktzahl : %i\n", Punkte);
		}
	} while (Punkte != 0 && NS != 0);


	





}


