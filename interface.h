#ifndef INTERFACE_HEADER
#define INTERFACE_HEADER
/*Menu(nowa gra, wczytaj, pomoc, wyjscie)*/
class Interface {
public:
	Interface();
	/*Wyswietla na ekranie menu.*/
	void menu();
	/*Rozpoczecie nowej gry.*/
	void newGame();
	/*Zaladowanie zapisanej gry.*/
	void load();
	/*Podstawowe informacje ja sie w grze poruszac.*/
	void help();
	/*globalny ranking graczy*/
	void ranking();
	/*Zawiera switch'a z opcjami z menu do wyboru.*/
	void options(int);
};

#endif