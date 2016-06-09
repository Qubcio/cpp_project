#ifndef SETING_GAME_DETAILS_HEADER
#define SETING_GAME_DETAILS_HEADER
#include <string>
#include "basics.h"
using namespace std;
/*rozpoczecie nowej gry*/
class NewGame {
private:
	info i;							//informacje potrzebne do rozpoczecia nowej gry
public:
	NewGame();
	/*wybranie trybu gry*/
	void setType();
	/*wybranie nazwy gracza*/
	void setNames();
};
/*wczytanie gry zapisanej*/
class LoadGame {
private:
	info i;							//informacje potrzebne do zaladowania wczesniejszej gry
public:
	LoadGame();
};

#endif