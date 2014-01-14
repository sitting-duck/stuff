#ifndef ORDER_H
#define ORDER_H

#include "MenuItem.h"
#include "Menu.h"

class Order 
{
private:
	static const int maxItems=100;  // # of items in the order
	int numItems;  // current # of items in the order
	MenuItem **itemsp;
	double totalPrice;
public:
	Order();
	Order(int count); //allocates array of pointers to "selected" menu items
	int addItem(MenuItem *itemp); // add one item at a time to the order

	Order& operator =(const Order& _o);
	Order(const Order& _o);
	Order(int _numItems, MenuItem** _itemList);
	Order(string orderList, Menu *menu); // alternate way to setup the order
	~Order();
	void printOrder();
	int getNumItems();
	MenuItem** getItemsp();	
};
#endif
