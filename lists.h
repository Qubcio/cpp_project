#ifndef SETS_HEADER
#define SETS_HEADER
#include "domino.h"
#include <string>
using namespace std;
/*klasa bazowa do pozostalych list zawierajacych kosci*/
class List {
protected:
	int size;									//ile kosci zawiera lista
	Domino *help;								//wskaznik pomocniczy do poruszania sie po listach
	Domino *head;								//wskazniki ustawione na poczatek listy
public:
	List *next;
	List();
	/*getter do dlugosci listy*/
	int getSize();
	/*setter do dlugosci listy*/
	void setSize(int);
	/*pokazuje cala liste (w formie |1:2| |2:5|)*/
	virtual void showList();
	/*wskazuje wybrany elemet z listy*/
	Domino* get(int);
	/*zabiera elemet z listy*/
	virtual Domino* take(int) = 0;
	/*czyszczenie listy po rundzie*/
	void clearList();
	/*wyglad listy kosci ale tylko same liczby (wyglad: 62342545...)*/
	string getList();
	~List();
};
/*kosci z ktorych mozna dobierac*/
class Pool : public List {
public:
	/*dodaje wybrany elemet do listy*/
	void add(Domino*);
	/*wyjecie kosci z talii wolnych*/
	Domino* take(int);
};
/*talia graczy*/
class Player : public List {
private:
	string name;							//nazwa gracza
	int points;								//pkt. gracza
public:
	Player();
	/*getter do nazwy gracza*/
	string getName();
	/*setter do nazwy gracza*/
	void setName(string);
	/*getter do pkt. gracza*/
	int getPoints();
	/*setter do pkt. gracza*/
	void setPoints(int);
	/*dodaje wybrany elemet do listy*/
	void add(Domino*);
	/*wyjecie kosci z talii gracza*/
	Domino* take(int);
	/*suma oczek na kosciach w calej liscie*/
	int sum();
};
/*ulozone kosci*/
class Deck : public List {
private:
	Domino *end;					//wskaznik do dodawania elemetow z drugiej strony
	int l;							//l-pierwsza wartosc z talii po lewej stronie
	int r;							//r-pierwsza wartosc z talii po prawej stronie
public:
	/*zwraca pierwsza z lewej wartosc na kosci w talii*/
	int getL();
	/*zwraca pierwsza z prawej wartosc na kosci w talii*/
	int getR();
	/*(elemet do dodania, true-dodaj z przodu| false-dodaj z tylu)*/
	bool check(Domino*, bool);
	/*dodaje (elemet, z ktorej strony true-przod, false-tyl) do listy*/
	void add(Domino*, bool);
	/*wyjmnij elemet z listy*/
	Domino* take(int);
};
#endif