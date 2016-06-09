#include "lists.h"
#include <iostream>
using namespace std;

List::List() : size(0), head(NULL), next(NULL) {						//List
}
int List::getSize(){ return size; }
void List::setSize(int i){ size = i; }
void List::showList() {
	help = head;
	while (help != NULL) {
		cout << help->show() << " ";
		help = help->next;
	}
	putchar('\n');
}
Domino* List::get(int i) {
	int c = 0;
	help = head;
	while (c != i) {
		c++;
		help = help->next;
	}
	return help;
}
void List::clearList() {
	size = 0;
	delete head;
	head = NULL;
}
string List::getList() {
	string odp = "";
	help = head;
	while (help != NULL) {
		odp += to_string(help->getL());
		odp += to_string(help->getR());
		help = help->next;
	}
	return odp;
}
List::~List(){
	delete head;
}

void Pool::add(Domino *a) {									//Pool
	a->next = NULL;
	a->prev = NULL;
	size++;
	if (head == NULL) {
		head = a;
		return;
	}
	help = head;
	while (help->next != NULL) {
		help = help->next;
	}
	help->next = a;
}
Domino* Pool::take(int i) {
	size--;
	help = head;
	if (i == 0) {
		head = head->next;
		return help;
	}
	int c = 1;
	while (i != c) {
		help = help->next;
		c++;
	}
	Domino *ret = help->next;
	help->next = help->next->next;
	return ret;
}

Player::Player() : points(0) {								//Player
}
string Player::getName() { return name; }
void Player::setName(string n) { name = n; }
int Player::getPoints() { return points; }
void Player::setPoints(int  i) { points = i; }
void Player::add(Domino *a) {
	a->next = NULL;
	a->prev = NULL;
	size++;
	if (head == NULL) {
		head = a;
		return;
	}
	help = head;
	while (help->next != NULL) {
		help = help->next;
	}
	help->next = a;
}
Domino* Player::take(int i) {
	size--;
	help = head;
	if (i == 0) {
		head = head->next;
		return help;
	}
	int c = 1;
	while (i != c) {
		help = help->next;
		c++;
	}
	Domino *ret = help->next;
	help->next = help->next->next;
	return ret;
}
int Player::sum() {
	int x = 0;
	help = head;
	while (help != NULL) {
		x += (help->getL() + help->getR());
		help = help->next;
	}
	return x;
}

int Deck::getL(){ return l; }								//Deck
int Deck::getR(){ return r; }
bool Deck::check(Domino *a, bool side) {
	if ((head == NULL) || (side && (a->getL() == l || a->getR() == l))
		|| (!side && (a->getL() == r || a->getR() == r))) {
		return true;
	}
	else {
		return false;
	}
}
void Deck::add(Domino *a, bool side) {
	a->next = NULL;
	a->prev = NULL;
	if (head == NULL) {
		end = head = a;
	}else if (side) {
		if (a->getL() == l)
			a->sw();
		head->prev = a;
		a->next = head;
		head = head->prev;

	}
	else{
		if (a->getR() == r)
			a->sw();
		end->next = a;
		a->prev = end;
		end = end->next;
	}
	l = head->getL();
	r = end->getR();
}
Domino* Deck::take(int i) {
	size--;
	help = head;
	if (i == 0) {
		head = head->next;
		head->prev = NULL;
		return help;
	}
	int c = 1;
	while (i != c) {
		help = help->next;
		c++;
	}
	Domino *ret = help->next;
	help->next = help->next->next;
	help->next->next->prev = help;
	return ret;
}






