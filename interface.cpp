#include "basics.h"
#include "interface.h"
#include "start.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

Interface::Interface() {
	srand(time(NULL));
	cout << "\tWitaj w grze \"DOMINO\", autor: " << AUTHOR << "\n\n";
	menu();
}
void Interface::menu() {
	cout << "  MENU:\n";
	cout << "1.Nowa gra.\n";
	cout << "2.Wczytaj.\n";
	cout << "3.Pomoc.\n";
	cout << "4.Ranking graczy.\n";
	cout << "5.Wyjscie.\n";
	options(input(1, 5));
}
void Interface::options(int x) {
	switch (x) {
	case 1:		newGame();					break;
	case 2:		load();						break;
	case 3:		help();						break;
	case 4:		ranking();					break;
	case 5:		exit(0);
	}
}
void Interface::newGame() {
	cScreen();
	cout << "Rozpoczac nowa gre.\n1. Tak.\n2. Nie.\n";
	if (input(1, 2) == 1) {
		NewGame n;
	}
	else{
		cScreen();
		menu();
	}
}
void Interface::load() {
	cScreen();
	fstream plik;
	plik.open(SAVE, ios::in);
	if (!plik.good()) {
		cout << "Nie zapisano jeszcze gry.\n";
		plik.close();
		wait();
		wait();
		cScreen();
		menu();
	}
	else{
		string linia;
		cout << "Czy chcesz wczytac gre (z ";
		getline(plik, linia);
		cout << linia << ").\n1.Tak, 2.Nie." << endl;
		plik.close();
		if (input(1, 2)) {
			cout << "Wczytano gre." << endl;
			LoadGame l;
		}
		else {
			cScreen();
			menu();
		}
	}
}
void Interface::help() {
	cScreen();
	cout << "Autor gry: " << AUTHOR << endl;
	cout << "Podstawowe informacje ktore nalezy wiedziec grajac w \"Domino\"\n";
	cout << "1. Poruszaj sie w grze przez naciskanie klawiszy numerycznych zgodnie z opcjami obok.\n";
	cout << "2. Jesli w grze nic sie nie dzieje i gra nie daje Ci znaku do wyboru czegos,\n";
	cout << "\toznacza to ze daje Ci czas do zapoznaniasie z informacjami na\n\tekranie i wcisniecie nastepnie \"Enter\".\n";
	cout << "3. Na ekranie np. |1:3| bedzie oznaczalo jedna kosc majaca 1 i 3 oczka.\n";
	cout << "4. Zasady gry sa zrobione zgodnie z zasadami ze strony \"" << RULES <<"\"";
	cout << "\nWcisnij \"Enter\" aby wrocic do menu.\n";
	wait();
	wait();
	cScreen();
	menu();
}
void Interface::ranking() {
	cScreen();
	cout << "\tRANKING:\n\n";
	loadRanked();
	cout << "\nWcisnij \"Enter\", aby wrocic do menu.\n";
	wait();
	wait();
	cScreen();
	menu();
}