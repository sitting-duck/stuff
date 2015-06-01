#include "Order.h"


Order::Order()
{
	numItems = 0;
	itemsp = NULL;
	totalPrice = 0;
}
Order::Order(const Order& _o)
{
	numItems = _o.numItems;
	itemsp = new MenuItem*[numItems];
	for(int i = 0; i < numItems; i++)
	{
		itemsp[i] = _o.itemsp[i];
	}
	totalPrice = _o.totalPrice;

}
Order& Order::operator =(const Order& _o)
{
	numItems = _o.numItems;
	delete[] itemsp;
	itemsp = new MenuItem*[numItems];
	for(int i = 0; i < numItems; i++)
	{
		itemsp[i] = _o.itemsp[i];
	}
	totalPrice = _o.totalPrice;
	return *this;
}
Order::Order(int _numItems, MenuItem** _itemList)
{
	numItems = _numItems;
	itemsp = new MenuItem*[_numItems];
	for(int i = 0; i < numItems; i++)
	{
		itemsp[i] = _itemList[i];
		totalPrice+=itemsp[i]->getPrice();
	}
}
Order::~Order()
{
	delete[] itemsp;
}
void Order::printOrder()
{
	for(int i = 0; i < numItems; i++)
	{
		itemsp[i]->printMenuItem();
	}
	cout << "TOTAL: " << totalPrice << endl;
}
int Order::getNumItems()
{
	return numItems;
}
MenuItem** Order::getItemsp()
{
	return itemsp;
}
