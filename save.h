#ifndef SAVE_HEADER
#define SAVE_HEADER
#include <iostream>
#include <fstream>
#include "basics.h"

using namespace std;
/*
FORMA ZAPISANIA GRY:
Informacje:
0-data				"dd-mm-rr_hh:mm
1-typ				"t/f"
2-runda				"nr"
3-tura				"nr"
4-kto_nastepny		"0/1"	1-pierwszy/ 0-drugi gracz
5-nazwa gracz1		"Gracz"
6-nazwa gracz2		"Gracz"/"Komputer"
7-pkt gracz1		"nmb"
8-pkt gracz2		"nmb"
Talie w formie		"LRLRLR"
9-pola
10-gracz1
11-gracz2
12-stol
*/

/*zapisanie stanu gry*/
class SaveGame{
public:
	SaveGame(info);
	/*funkcja zwracajaca stringa przechowujacego date robienia zapisu*/
	string date();
};

/*informacje o jednym miejscu w rankingu*/
class Ranked {
private:
	friend class Scoreboard;
	int place;									//miejsce
	int wins;									//wygrane
	string name;								//nazwa gracza
	Ranked *next, *prev;						//wskazniki na nastepny/poprzedni
public:
	Ranked(string);
	/*zwraca stringa do zapiu w rankingu*/
	string makeLine();
};

/*wyglad linii zapisanych w rankingu przelozone na int,int,string(miejsce wygrane nazwa)*/
class Scoreboard {
private:
	fstream file;								//plik dla rankingu
	string name;								//nazwa gracza
	Ranked *head;								//wskaznik do 1.miejsca w rankingu
	Ranked *help;								//wsk. pomocniczy
public:
	Scoreboard(string);
	/*odczytuje z pliku ranking graczy*/
	void readFile();
	/*sortowanie listy rankingowej*/
	void sortList();
	/*zapisanie listy rankingowej*/
	void saveFile();
};
#endif