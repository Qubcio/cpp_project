#include <iostream>
#include <ctime>
#include <fstream>
#include "save.h"

using namespace std;
SaveGame::SaveGame(info i) {
	string z[LINE];
	z[0] = date();
	z[1] = to_string(i.type);
	z[2] = to_string(i.round);
	z[3] = to_string(i.tour);
	z[4] = to_string(i.nextIs);
	z[5] = i.name1;
	z[6] = i.name2;
	z[7] = to_string(i.point1);
	z[8] = to_string(i.point2);
	z[9] = i.poolList;
	z[10] = i.player1List;
	z[11] = i.player2List;
	z[12] = i.deckList;
	fstream plik;
	plik.open(SAVE, ios::out);
	for (int i = 0; i < LINE; i++) {
		plik << z[i] << endl;
	}
	plik.close();
	cout << "Zapisano stan gry.\n";
	wait();
	wait();
}
string SaveGame::date() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	string time = "";
	time += to_string(now->tm_mday);
	time += "-";
	time += to_string(now->tm_mon + 1);
	time += "-";
	time += to_string(now->tm_year - 100);
	time += "_";
	time += to_string(now->tm_hour);
	time += ":";
	time += to_string(now->tm_min);
	return time;
}




Scoreboard::Scoreboard(string n) : name(n), head(NULL) {
	file.open(RANK, ios::in);
	if (!file.good()) {
		//gdy jeszcze nikogo nie ma w rankingu
		file.close();
		file.open(RANK, ios::out);
		file << "1 1 " << name;
	}
	else{
		//gdy juz znalazy sie osoby w rankingu
		readFile();
		sortList();
		saveFile();
	}
	file.close();
}
void Scoreboard::readFile() {
	string line;
	//zrobienie listy wynikow dotychczasowych
	while (getline(file, line)) {
		if (head == NULL) {
			help = head = new Ranked(line);
		}
		else{
			help->next = new Ranked(line);
			help->next->prev = help;
			help = help->next;
		}
	}
}
void Scoreboard::sortList(){
	//znalezienie wyniku w liscie na ostatnim miejscu
	int x = 0;
	help = head;
	while (help != NULL && (help->name).compare(name) != 0){
		help = help->next;
		x++;
	}
	int c = 0;
	if (x == 0) {
		//pierwsze miejsce zdobyl wygrana
		head->wins++;
	}
	else if (help == NULL) {
		//jezeli nie ma takiego w rankingu to dodaj go na koniec
		string t = "1 1 ";
		t += name;
		help = head;
		while (help->next != NULL) {
			help = help->next;
		}
		help->next = new Ranked(t);
	}
	else{
		//gdy znajduje sie gdzies wsrodku
		help = head;
		while (c != (x - 1)) {
			c++;
			help = help->next;
		}
		Ranked *p = help->next;
		if (help->next->next == NULL) {
			help->next = NULL;
		}
		else{
			help->next = help->next->next;
			help->next->prev = help;
		}
		p->wins++;
		//sprawdzenie o ile sie odniusl w rankingu
		Ranked *w;
		while (help != NULL && p->wins > help->wins) {
			help = help->prev;
		}
		if (help == NULL) {
			//gdy zmienia sie glowa
			head->prev = p;
			p->next = head;
			head = p;
		}
		else if (help->next == NULL) {
			help->next = p;
			p->prev = help;
		}
		else{
			p->prev = help;
			p->next = help->next;
			help->next = p;
			help->next->prev = p;
		}


	}
	//wyswietlenie listy
	help = head;
	c = 1;
	while (help != NULL) {
		help->place = c;
		help = help->next;
		c++;
	}
	help = head;
	/*while (help != NULL) {
		cout << help->makeLine() << endl;
		help = help->next;
	}*/
}
void Scoreboard::saveFile() {
	file.close();
	file.open(RANK, ios::out);
	help = head;
	while (help != NULL) {
		file << help->makeLine() << endl;
		help = help->next;
	}
}

Ranked::Ranked(string line) : next(NULL), prev(NULL) {
	int x = 0;
	string t;
	for (int i = 0; i < 3; i++) {
		t = "";
		while (x < line.length() && line.at(x) != '\n' && line.at(x) != ' '){
			t += line.at(x);
			x++;
		}
		switch (i) {
		case 0:{
				   place = stoi(t);
		}	break;
		case 1:{
				   wins = stoi(t);
		}	break;
		case 2:{
				   name = t;
		}	break;
		}
		x++;
	}
}
string Ranked::makeLine() {
	string c = "";
	c += to_string(place);
	c += " ";
	c += to_string(wins);
	c += " ";
	c += name;
	return c;
}





































