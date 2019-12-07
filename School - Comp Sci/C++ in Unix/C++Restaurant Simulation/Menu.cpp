#include "Menu.h"

Menu::Menu()
{
	numItems = 0;
	menup = NULL;
}
Menu::Menu(const Menu& _m)
{
	numItems = _m.numItems;
	copyToMenu(numItems, _m.menup);
}
void Menu::copyToMenu(int _numItems, MenuItem* _menup)
{
	numItems = _numItems;
	delete[] menup;
	menup = new MenuItem[numItems];
	for(int i = 0; i < numItems; i++)
	{
		menup[i] = menup[i];
	}
}
Menu::~Menu()
{
	delete[] menup;
}
void Menu::printMenu()
{
	for(int i = 0; i < numItems; i++)
	{
		menup[i].printMenuItem();
	}
}
void Menu::addItem(MenuItem item) //add one menu item at a time
{
	MenuItem* tempMenu = new MenuItem[numItems +1];
	for(int i = 0; i < numItems; i++)
	{
		tempMenu[i] = menup[i];
	}
	delete[] menup;

	menup = new MenuItem[numItems+1];
	for(int i =0; i < numItems; i++)
	{
		menup[i] = tempMenu[i];
	}


//	copyToMenu(numItems+1, tempMenu);
	menup[numItems] = item;
	numItems++;
	delete[] tempMenu;
}

MenuItem* Menu::findItem(string _code) //lookup operation
{
	for(int i = 0; i < numItems; i++)
	{
		if(menup[i].getCode().compare(_code) == 0)
		{
			return &menup[i];
		}
		
	}
	return NULL;
}


