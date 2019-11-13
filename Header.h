#pragma once
//Erstellen eines Struct-Datentypen
struct field
{
	int owner;
	char name[20];
	char colour;
	int price;
	int rent[7];
	int house;
};

//Globale Variablen auf die jedes Modul direkten Zugriff hat
extern char name_player[10];
extern int money_player;
extern int money_ki;
extern int position_player;
extern int position_ki;
extern struct field* matchfield;
extern int colour_player[];
extern int colour_ki[];
extern int number_streets;

//Alle genauen Informationen zu den Prototypen sind im Wiki nachzulesen.

//Prototypen des Main-Moduls


//Prototypen des Output-Moduls
int matchfield_update(void);
int output_field(struct field*);