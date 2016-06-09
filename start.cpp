#include "start.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>			//setw(x)
#include "game.h"

using namespace std;

void start(info, bool);

LoadGame::LoadGame() {
	fstream file;
	string line = "";
	int nr_line = 0;
	file.open(SAVE, ios::in);
	while (getline(file, line)) {
		switch (nr_line){
		case 1:							i.type = stoi(line);	break;
		case 2:							i.round = stoi(line);	break;
		case 3:							i.tour = stoi(line);	break;
		case 4:							i.nextIs = stoi(line);	break;
		case 5:							i.name1 = line;			break;
		case 6:							i.name2 = line;			break;
		case 7:							i.point1 = stoi(line);	break;
		case 8:							i.point2 = stoi(line);	break;
		case 9:							i.poolList = line;		break;
		case 10:						i.player1List = line;	break;
		case 11:						i.player2List = line;	break;
		case 12:						i.deckList = line;		break;
		}
		nr_line++;
	}
	file.close();
	start(i, true);
}

NewGame::NewGame() {
	setType();
	setNames();
	i.round = 1;
	i.tour = 1;
	i.point1 = 0;
	i.point2 = 0;
	i.nextIs = (bool)losuj(2, 0);
	start(i, false);
}

void NewGame::setType() {
	cScreen();
	cout << "Prosze wybrac tryb gry.\n";
	cout << "1. Czlowiek vs Komputer.\n";
	cout << "2. Czlowiek vs Czlowiek.\n";
	i.type = (input(1, 2) == 1) ? true : false;
	cScreen();
}
void NewGame::setNames() {
	string name;
	cout << "Nazwy graczy:\n";
	cout << "Prosze podac nazwe gracza 1.\n";
	cin >> name;
	while (name.compare(KOMP) == 0) {
		cout << "Nazwa \"" << KOMP << "\" jest nazwa zarezerwowana, podaj inna.\n";
		cin >> name;
	}
	i.name1 = name;
	if (!i.type) {
		cout << "Prosze podac nazwe gracza 2.\n";
		cin >> name;
		while (name.compare(KOMP) == 0) {
			cout << "Nazwa \"" << KOMP << "\" jest nazwa zarezerwowana, podaj inna.\n";
			cin >> name;
		}
		i.name2 = name;
	}
	else {
		i.name2 = KOMP;
	}
	cScreen();
}

/*funkcja globalna do przesylania danych z Load i New Game do Game*/
void start(info i, bool load) {
	cScreen();
	cout << "Wybrano gre.\n";
	cout << "Statystyki na chwile obecna.\n";
	cout << setw(20) << "Tryb gry: ";
	if (i.type == true) {
		cout << "Czlowiek vs Komputer.\n";
	}
	else{
		cout << "Czlowiek vs Czlowiek.\n";
	}
	cout << setw(20) << "Nazwy graczy: " << i.name1 << " i " << i.name2 << endl;
	cout << setw(20) << "Runda: " << i.round << endl;
	cout << setw(20) << "Tura: " << i.tour << endl;
	string s = (i.nextIs) ? i.name1 : i.name2;
	cout << setw(20) << "Kolej: " << s << endl;
	wait();
	wait();
	Game g(i, load);
}