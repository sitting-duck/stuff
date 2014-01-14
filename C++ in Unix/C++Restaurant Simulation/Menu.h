#ifndef MENU_H
#define MENU_H
#include "MenuItem.h"

class Menu 
{
private:
	static const int maxItems = 100; // MAX capacity 
	int numItems; // current # of items in menu
	MenuItem *menup;  

public:
	Menu();
	Menu(const Menu& _m);
	Menu operator =(const Menu& _m);
	Menu(int _numItems); //constructor to allocate memory
	void addItem(MenuItem item); //add one menu item at a time
	MenuItem* findItem(string code); //lookup operation
	~Menu(); //destructor
	void printMenu();
	void copyToMenu(int _numItems, MenuItem* _menup);
};

// Usage:
// Menu menu;
// MenuItem *ip = menu.findItem(code);

// IMPLEMENTATION:
// MenuItem* Menu::findItem(string code) CORRECT
// MenuItem Menu::*findItem(string code) WRONG
#endif
