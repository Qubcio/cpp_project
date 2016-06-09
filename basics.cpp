#include "basics.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void wait() {
	while (getchar() == NULL) {
		;
	}
}
void cScreen() {
	system("CLS");
}
int input(int a, int b) {
	int x;
	cout << "\nCo chcesz zrobic?\n";
	cin >> x;
	while (x < a || x > b) {
		while (getchar() != '\n') {
			;
		}
		cout << "Podana operacja nie istnieje. Podaj ponownie.\n";
		cin >> x;
	}

	return x;
}
int losuj(int a, int b) {
	return rand()%a + b;
}
void loadRanked() {
	fstream file;
	file.open(RANK, ios::in);
	if (!file.good()) {
		cout << "Nikt jeszcze nie znalazl sie w rankingu.\n";
	}
	else{
		string s = "";
		cout << "miejsce/licza zwyciestw/nazwa gracza\n\n";
		while (getline(file, s)) {
			cout << s << endl;
		}
	}
	cout << "\nRanking nie uwzglednia komputera.\n";
	file.close();
}