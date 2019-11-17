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
	char text[300];
	int gegner_minus;
	int gegner_plus;
	int player_minus;
	int player_plus;
};

//Globale Variablen auf die jedes Modul direkten Zugriff hat
extern char *name_player;
extern int money_player;
extern int money_ki;
extern int position_player;
extern int position_ki;
extern struct field* matchfield;
extern struct actioncard* actioncards;
extern char colour_player;
extern char colour_ki;
extern int number_streets;

//Alle genauen Informationen zu den Prototypen sind im Wiki nachzulesen.

//Prototypen des Main-Moduls


//Prototypen des Output-Moduls
void matchfield_update(int, char[]);



//Prototypen des Spielmechanik-Moduls

void spielzug(void);
