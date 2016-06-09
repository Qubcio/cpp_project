#include "game.h"
#include "save.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


Game::Game(info i, bool l) : gInfo(i), load(l) {
	player1.setName(gInfo.name1);
	player2.setName(gInfo.name2);
	player1.setPoints(gInfo.point1);
	player2.setPoints(gInfo.point2);
	game();
}
void Game::fillLists() {
	if (!load) {
		//dla nowej gry
		for (int i = 0; i <= MAX_SPOTS; i++) {
			for (int j = i; j <= MAX_SPOTS; j++) {
				pool.add(new Domino(i, j));
			}
		}
		cout << "Oto wyglad pelnej listy kosci:\n";
		pool.showList();
		wait();
		cScreen();
		for (int i = 0; i < START; i++) {
			player1.add(rDomino());
			player2.add(rDomino());
		}
	}
	else{
		//dla wczytanej gry
		for (int i = 0; i < gInfo.poolList.length(); i += 2) {
			pool.add(new Domino(gInfo.poolList.at(i) - '0', gInfo.poolList.at(i + 1) - '0'));
		}
		for (int i = 0; i < gInfo.player1List.length(); i += 2) {
			player1.add(new Domino(gInfo.player1List.at(i) - '0', gInfo.player1List.at(i + 1) - '0'));
		}
		for (int i = 0; i < gInfo.player2List.length(); i += 2) {
			player2.add(new Domino(gInfo.player2List.at(i) - '0', gInfo.player2List.at(i + 1) - '0'));
		}
		for (int i = 0; i < gInfo.deckList.length(); i += 2) {
			deck.add(new Domino(gInfo.deckList.at(i) - '0', gInfo.deckList.at(i + 1) - '0'), false);
		}
		load = false;
	}
}
Domino* Game::rDomino() {
	return pool.take(losuj(pool.getSize(), 0));
}

void Game::game() {
	while (win()) {
		fillLists();
		playing = true;
		int x = 0;
		while (playing && player1.getSize() != 0 && player2.getSize() != 0 && win()) {
			x++;
			Player *h;
			string name = (gInfo.nextIs) ? gInfo.name1 : gInfo.name2;
			cScreen();
			cout << "Teraz bedzie kolej " << name << endl;
			if (!gInfo.type) {
				wait();
				//czlowiek vs czlowiek
				if (gInfo.nextIs) {
					playerMove(&player1);
				}
				else{
					playerMove(&player2);
				}
			}
			else{
				wait();
				//czlowiek vs komputer
				if (gInfo.nextIs) {
					playerMove(&player1);
				}
				else{
					compMove(&player2);
				}
			}
			if (x == 2) {
				gInfo.tour++;
				x = 0;
			}
		}
		roundOver();
		gInfo.round++;
		gInfo.tour = 1;
	}
	gameOver();
}
void Game::playerMove(Player* p) {
	bool move = true;
	while (move) {
		cScreen();
		switch (stats(p)) {
		case 1: {
					//doloz kosc do kosci juz ulozonych
					move = (setOut(p)) ? false : true;
					wait();
					wait();
		}	break;
		case 2: {
					//dobierz kosc do tali z jeszcze nie przydzielonych
					if (pool.getSize() != 0) {
						p->add(rDomino());
					}
					else{
						cout << "Czy na pewno chcesz pominac kolej?(1-tak, 2-nie)\n";
						move = (input(1, 2) == 1) ? false : true;
					}
		}	break;
		case 3: {
					//poddaj sie 
					if (pool.getSize() == 0){
						cout << "Czy na pewno chcesz sie poddac?(1-tak, 2-nie)\n";
						move = (input(1, 2) == 1) ? false : true;
						playing = move;
					}
					else{
						cout << "Nie rozdano jeszcze wszystkich kosci. Nie mozna sie poddac.\n";
						wait();
						wait();
					}
		}	break;
		case 4: {
					//zapisz stan gry
					makeSave();
					SaveGame s(gInfo);
		}	break;
		case 5: {
					//wyjdz z gry
					exit(0);
		}	break;
		}
	}
	gInfo.nextIs = (gInfo.nextIs) ? false : true;
}
void Game::makeSave() {
	gInfo.point1 = player1.getPoints();
	gInfo.point2 = player2.getPoints();
	gInfo.poolList = pool.getList();
	gInfo.player1List = player1.getList();
	gInfo.player2List = player2.getList();
	gInfo.deckList = deck.getList();
}
void Game::compMove(Player* c) {
	bool move = true;
	while (move) {
		for (int i = 0; i < c->getSize(); i++) {
			if (deck.check(c->get(i), true)) {
				deck.add(c->take(i), true);
				int s = deck.getL() + deck.getR();
				if (s % 5 == 0 && s != 0) {
					c->setPoints(c->getPoints() + s);
				}
				move = false;
				break;
			}
			else if (deck.check(c->get(i), false)) {
				deck.add(c->take(i), false);
				int s = deck.getL() + deck.getR();
				if (s % 5 == 0 && s != 0) {
					c->setPoints(c->getPoints() + s);
				}
				move = false;
				break;
			}
		}
		if (!move) break;
		if (pool.getSize() != 0) {
			c->add(rDomino());
		}
		else{
			break;
		}
	}
	gInfo.nextIs = (gInfo.nextIs) ? false : true;
}
int Game::stats(Player* p) {
	string n;
	cout << "\tRuch wykonuje: " << p->getName() << endl << endl;
	for (int i = 0; i < 33; i++)
		putchar('-');
	putchar('\n');
	cout << setw(15) << "Runda" << " : " << gInfo.round << endl;
	cout << setw(15) << "Tura" << " : " << gInfo.tour << endl;
	cout << setw(15) << "Wolne kosci" << " : " << pool.getSize() << endl;
	cout << setw(15) << player1.getName() << " : punkty = " << setw(3) << to_string(player1.getPoints())
		<< " | liczba kosci = " << setw(2) << to_string(player1.getSize()) << endl;
	cout << setw(15) << player2.getName() << " : punkty = " << setw(3) << to_string(player2.getPoints())
		<< " | liczba kosci = " << setw(2) << to_string(player2.getSize()) << endl;
	for (int i = 0; i < 33; i++)
		putchar('-');
	cout << "\nTali ulozona:\n";
	deck.showList();
	cout << "\nTwoja talia:\n";
	for (int i = 1; i <= p->getSize(); i++) {
		cout << setw(3) << i << "   ";
	}
	putchar('\n');
	p->showList();
	if (pool.getSize() != 0){
		cout << "1-wyloz, 2-dobierz, 3-poddaj_sie, 4-zapisz, 5-wyjdz.\n";
	}
	else{
		cout << "1-wyloz, 2-pomin_kolej, 3-poddaj_sie, 4-zapisz, 5-wyjdz.\n";
	}
	return input(1, 5);
}
bool Game::setOut(Player *p) {
	cout << "Ktora kosc chcesz dodac?(" << 1 << "-" << p->getSize() << ")\n";
	int x = input(1, p->getSize());
	x--;
	cout << "1-przod, 2-tyl.\n";
	bool y = (input(1, 2) == 1) ? true : false;
	if (deck.check(p->get(x), y)) {
		deck.add(p->take(x), y);
		int s = deck.getL() + deck.getR();
		cout << "Suma pkt. na krancach: " << s << endl;
		if (s % 5 == 0 && s != 0) {
			cout << "Gracz zdobywa: " << s << "pkt.\n";
			p->setPoints(p->getPoints() + s);
		}
		return true;
	}
	else{
		cout << "Nie da sie dodac elemetu.\n";
		return false;
	}
}
void Game::roundOver() {
	cScreen();
	List *s = &pool;
	List *h = s;
	s->next = &player1;
	s = s->next;
	s->next = &player2;
	s = s->next;
	s->next = &deck;
	s = h;
	cout << "Wyglad kosci : Nie uzytych, " << player1.getName() << ", " << player2.getName() << ", ulozonych.\n";
	while (s != NULL) {
		s->showList();
		s = s->next;
	}
	cout << "Suma oczek na pozostalych kosciach graczy:\n";
	cout << setw(15) << player1.getName() << " : " << player1.sum() << endl;
	cout << setw(15) << player2.getName() << " : " << player2.sum() << endl;
	int p = abs(player1.sum() - player2.sum());
	if (p % 5 > 2) {
		p = p / 5 * 5 + 5;
	}
	else{
		p = p / 5 * 5;
	}
	cout << "\nRunda " << gInfo.round << " zakonczyla sie";
	if ((player1.getSize() == 0) || (player1.sum() < player2.sum())) {
		cout << " zwyciestwem gracza " << player1.getName() << ".\n";
		cout << "Otrzymuje: " << p << "pkt.\n";
		player1.setPoints(player1.getPoints() + p);
		gInfo.nextIs = true;
	}
	else if ((player2.getSize() == 0) || (player1.sum() > player2.sum())) {
		cout << " zwyciestwem gracza " << player2.getName() << ".\n";
		cout << "Otrzymuje: " << p << "pkt.\n";
		player2.setPoints(player2.getPoints() + p);
		gInfo.nextIs = false;
	}
	else {
		cout << " remisem.\nNikt nie otrzymuje pkt.\n";
		gInfo.nextIs = (losuj(2, 0) == 1) ? true : false;
	}
	cout << "\nPo rundzie punkty graczy:\n";
	cout << setw(15) << player1.getName() << " : " << player1.getPoints() << endl;
	cout << setw(15) << player2.getName() << " : " << player2.getPoints() << endl;
	pool.clearList();
	player1.clearList();
	player2.clearList();
	deck.clearList();
	wait();
	cScreen();
}
void Game::gameOver() {
	Player c = (player1.getPoints() > player2.getPoints()) ? player1 : player2;
	cout << "Gre wygrywa gracz: " << c.getName() << " z wynikiem: " << c.getPoints() << "pkt.\n";;
	cout << "Koniec gry.\n";
	//dodaje do listy zwyciezcow tylko jezeli wygra gracz a nie komputer
	if (c.getName().compare("Komputer") != 0)
		Scoreboard(c.getName());
	wait();
	cScreen();
	loadRanked();
	cout << "\nKoniec. Dziekuje za gre.\n";
	wait();
	cScreen();
}
bool Game::win() {
	return player1.getPoints() < WIN_POINTS && player2.getPoints() < WIN_POINTS;
}

