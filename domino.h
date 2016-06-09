//same klocek
#ifndef DOMINO_HEADER
#define DOMINO_HEADER
#include <string>
using namespace std;

/*klasa tworzaca jeden klocek domina*/
class Domino {
private:
	int l, r;														//liczby oczek na kosci l-lewa/ r-prawa strona
public:
	Domino(int, int);
	Domino *next, *prev;											//wskazniki do nastepnego i poprzedniego elemetu domina
	/*getter do l*/
	int getL();
	/*getter do r*/
	int getR();
	/*setter do l*/
	void setL(int);
	/*setter do r*/
	void setR(int);
	/*obrot klocka o 180 stopni*/
	void sw();
	/*zwraca klocek tak jak jest wyswietlany (|1:2|)*/
	string show();
	/*kasowanie klockow*/
	~Domino();
};
#endif