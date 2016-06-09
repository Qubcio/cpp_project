#ifndef PLAY_TIME_HEADER
#define PLAY_TIME_HEADER
#include "basics.h"
#include "start.h"
#include "lists.h"
#include <string>
using namespace std;
/*okres samej gry*/
class Game {
private:
	info gInfo;				//informacie do zapisania/wczytania
	Pool pool;				//pola z ktorej mozna dobierac kosci
	Player player1;			//kosci gracza 1
	Player player2;			//kosci gracza 2
	Deck deck;				//kosci ktore zostaly ulozone
	bool playing;			//czy runda trwa
	bool load;				//czy trzeba zaladowac stan gry
public:
	/*konstruktor*/
	Game(info, bool);
	/*uzupelnia listy na poczatku rozgrywki*/
	void fillLists();
	/*dodaje do wybranej listy losowa kosc z pool*/
	Domino* rDomino();
	/*sama rozgrywka*/
	void game();
	/*ruch gracza*/
	void playerMove(Player*);
	/*ruch komputera*/
	void compMove(Player*);
	/*statystyki podczas ruchu gracza*/
	int stats(Player*);
	/*wylozenie kosci do juz ulozonych*/
	bool setOut(Player*);
	/*wyswietlenie statystyk po rundzie*/
	void roundOver();
	/*wyswietlenie statystyk po wygraniu przez kogos gry*/
	void gameOver();
	/*warunek zakonczenia gry*/
	bool win();
	/*uzupelnienie informacji do zapisu*/
	void makeSave();
};

#endif