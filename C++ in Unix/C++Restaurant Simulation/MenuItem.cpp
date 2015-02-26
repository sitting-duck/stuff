#include "MenuItem.h"


MenuItem::MenuItem()
{
	code = ""; 
	name = "";
	price = 0.0;
}

MenuItem::MenuItem(string mcode, string mname, double mprice)
{
	code = mcode;
	name = mname;
	price = mprice;
}
MenuItem::MenuItem(const MenuItem& _m)
{
	code = _m.code;
	name = _m.name;
	price = _m.price;
}
MenuItem& MenuItem::operator = (const MenuItem& _m)
{
	code = _m.code;
	name = _m.name;
	price = _m.price;
	return *this;
}
MenuItem::~MenuItem()
{}
void MenuItem::printMenuItem()
{
	cout << "Code: " << code << " Name: " << name << " Price: " << price << endl;	
}
string MenuItem::getCode()
{
	return code;
}
string MenuItem::getName()
{
	return name;
}
double MenuItem:: getPrice()
{
	return price;
}

