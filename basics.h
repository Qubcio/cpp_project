//metody ktore moga sie przydac w kazdej klasie
#ifndef BASICS_STAFF_HEADER
#define BASICS_STAFF_HEADER
#include <string>
using namespace std;

#define AUTHOR			"Jakub Malinowski"								//tworca gry
#define KOMP			"Komputer"										//nazwa zarezerwowana dla trybu gry czlowiek vs komputer
#define SAVE			"save.txt"										//plik tekstowy do zapisu stanu gry
#define RANK			"rank.txt"										//plik do zapisu wynikow globalnych
#define RULES			"http://www.kurnik.pl/domino/zasady.phtml"		//strona z zasadami gry
#define ALL				28												//liczba wszystkich kosci do gry
#define MAX_SPOTS		6												//ile maksymalnie moze byc oczek po jednej stronie kosci
#define START			7												//ile kosci na start ma gracz
#define WIN_POINTS		100												//liczba pkt. przy ilu sie wygrywa
#define LINE			13												//liczba lini przy zapisywaniu

/*czekaj az zostanie nacisniety "enter"*/
void wait();					
/*usun wszystko z ekranu*/
void cScreen();
/*zwraca wartosc jak gracz poda wlasciwa mieszczaca sie w przedzialach <int,int>*/
int input(int, int);
/*zwraca losowa wartosc (z ilu, od ilu)*/
int losuj(int, int);
/*zwraca rozne elemety w zal. od tego co potrzeba*/
int nmb(string);
/*odczytanie z pliku listy rankingowej*/
void loadRanked();

/*wszystkie potrzebne informacje do stworzenia nowej lub wczytania starej gry*/
struct info {
	string name1;				//nazwa gracza pierwszego
	string name2;				//nazwa gracza drugiego
	bool type;					//rodzaj rozgrywki true - czlowiek vs komputer, false - czlowiek vs czlowiek
	bool nextIs;				//kto nastepnie wykonuje ruch true - player1, false - player2
	int round;					//ktora jest runda(gra sie X rund ale do momentu az ktos bedzie mial 100pkt.
	int tour;					//jedna tura oznacza jeden ruch obu graczy
	int point1;					//punkty gracza 1
	int point2;					//punkty gracza 2
	string poolList;			//lista kosci nie rozdanych
	string player1List;			//lista kosci gracza 1
	string player2List;			//lista kosci gracza 2
	string deckList;			//lista kosci ulozonych
};
/*
FORMA ZAPISANIA GRY:
Informacje:
0-data				"dd-mm-rr_hh:mm
1-typ				"0/1"		1-true(czlowiek vs komputer)/0-false(czlowiek vs czlowiek)
2-runda				"nr"
3-tura				"nr"
4-kto_nastepny		"0/1"		1-pierwszy/ 0-drugi gracz
5-nazwa gracz1		"Gracz1"
6-nazwa gracz2		"Gracz2"/"Komputer"
7-pkt gracz1		"nmb"
8-pkt gracz2		"nmb"
Talie w formie		"LRLRLR"
9-pola
10-gracz1
11-gracz2
12-stol
*/
#endif