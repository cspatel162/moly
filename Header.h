#pragma once
//Erstellen eines Struct-Datentypen
struct field
{
	int owner;
	char name[45];
	char colour;
	int price;
	int rent[7];
	int house;
	int price_house[4];
};

struct actioncard
{
	char title[20];
	char text[200];
	int gegner_minus;
	int gegner_plus;
	int player_minus;
	int player_plus;
};

//Globale Variablen auf die jedes Modul direkten Zugriff hat
extern char *name_player;
extern int *money_player;
extern int *position_player;
extern struct field* matchfield;
extern struct actioncard* actioncards;
extern char colour_player;
extern char colour_ki;
extern int number_streets;
extern int number_actioncards;

//Alle genauen Informationen zu den Prototypen sind im Wiki nachzulesen.

//Prototypen des Main-Moduls
int break_menue(void);
int clear_output(void);

//Prototypen des Output-Moduls
void matchfield_update(int, char[]);



//Prototypen des Spielmechanik-Moduls

int spielzug(int);
int eingabe(int, int);						// 1. Parameter kleinstes Zeichen 2. Parameter größtes Zeichen ------ Beide exklusiv!

//Prototypen Modul Aktionskarten
int fetch_actioncards(void);
int actioncards_play(int);
