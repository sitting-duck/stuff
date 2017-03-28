#ifndef MENUITEM_H
#define MENUITEM_H
#include <iostream>
#include <string>

using namespace std;

class MenuItem
{
private:
	string code; // See sample codes in config.txt
	string name; // Full name of the entry
	double price; // price of the item

public:
	MenuItem();
	MenuItem(const MenuItem& _m);
	MenuItem(string mcode, string mname, double mprice);
	MenuItem& operator = (const MenuItem& _m);
	~MenuItem();
	void printMenuItem();
	string getCode();
	string getName();
	double getPrice();
};
#endif
