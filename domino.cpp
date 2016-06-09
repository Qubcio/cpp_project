#include "domino.h"
#include <iostream>
#include <string>
using namespace std;

Domino::Domino(int a, int b) : l(a), r(b), next(NULL), prev(NULL) {
}
int Domino::getL() { return l; }
int Domino::getR() { return r; }
void Domino::setL(int x) { l = x; }
void Domino::setR(int x) { r = x; }
string Domino::show() {
	string c = "";
	c += "|";
	c += to_string(l);
	c += ":";
	c += to_string(r);
	c += "|";
	return c;
}
Domino::~Domino() {
	delete next;
}
void Domino::sw() {
	int x = l;
	l = r;
	r = x;
}